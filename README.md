<!-- Language selector -->
<p align="right">
  <a href="#中文版">中文</a> |
  <a href="#english">English</a>
</p>

<p align="center">
  <a href="https://github.com/Colorful-glassblock/duchamp-root">
    <img src="https://readme-typing-svg.demolab.com?font=JetBrains+Mono&size=28&pause=800&color=00FF88&center=true&vCenter=true&width=700&lines=duchamp-root+%F0%9F%94%93;Xiaomi+K70e+%28duchamp%29+One-Click+Root;CVE-2026-43499+%28IonStack%29+Exploit;710%E8%A7%A3%E9%94%81%E8%8A%82%E6%9C%80%E6%96%B0%E5%8A%9B%E4%BD%9C+%F0%9F%94%A5"/>
  </a>
</p>

<p align="center">
  <img width="20%" src="https://count.getloli.com/@duchamp-root?name=duchamp-root&theme=random&padding=7&offset=0&align=top&scale=1&pixelated=1&darkmode=auto" alt="visitor counter" />
</p>

---

![GitHub release (latest by date)](https://img.shields.io/github/v/release/Colorful-glassblock/duchamp-root?label=release&color=00FF88)
![GitHub last commit](https://img.shields.io/github/last-commit/Colorful-glassblock/duchamp-root?label=last%20commit)
![Platform](https://img.shields.io/badge/platform-MTK6897%2FMT6897%20%28Dimensity%208300%29-blue)
![Android](https://img.shields.io/badge/Android-16%20%28API%2036%29-green)
![Kernel](https://img.shields.io/badge/Kernel-6.1.138--android14--11-orange)
![License](https://img.shields.io/badge/license-WTFPL-brightgreen)

> ⚡ **Proud user of JetBrains Mono** ⚡  
> This README uses JetBrains Mono exclusively. Comic Sans is forbidden.

> [!IMPORTANT]
> 🚨 **Disclaimer**
> 
> This exploit is for **educational purposes only**.
> - Unlocking bootloader may void your warranty.
> - Rooting your device may cause bootloop, data loss, or spontaneous combustion (probably not, but who knows).
> - I am not responsible if your K70e turns into a K70 brick.
> - If your girlfriend leaves you because you spent too much time rooting, that's a you problem.
> - **7̷̋̚1̸̽̈́0̵̛̅ ̸͛̿ù̶̈́n̸̓̋l̸̔̒o̸̔̒c̸̾̑k̵̇̚ ̷̊̒ḟ̷͝e̶̋̕s̵̋̚t̸̽̈́ ̵̔̋l̶̔̒e̸̓̋t̸̔̒s̵̋̚ ̸̾̑ġ̷̝o̷̊̒ ̵̛̅ḟ̷͝u̸̓̋c̷̋̚k̸̛̅i̶̽̈́n̵̔̋g̷̊̒ ̴͛̿g̶̾̑ơ̵̅**

---

<a name="中文版"></a>

## 📖 中文版

<p align="center">
  <img src="https://readme-typing-svg.demolab.com?font=JetBrains+Mono&size=24&pause=800&color=FF8800&center=true&vCenter=true&width=600&lines=710%E8%A7%A3%E9%94%81%E8%8A%82%E6%9C%80%E6%96%B0%E5%8A%9B%E4%BD%9C+%F0%9F%94%A5;%E5%B0%8F%E7%B1%B3+K70e+%E4%B8%80%E9%94%AE+Root;%E4%B8%8D%E6%98%AF%E5%9C%A8%E8%A7%A3%E9%94%81%EF%BC%8C%E6%98%AF%E5%9C%A8%E8%A7%A3%E6%94%BE"/>
</p>

### 🤔 这是什么

**Xiaomi K70e (duchamp)** 一键 Root 工具，基于 **CVE-2026-43499 (IonStack)** 内核漏洞提权，集成 **KernelSU** 守护进程。

**通俗版**：你点一下，手机就 root 了。就这么简单。

**710 解锁节版**：不是 711，不是 709，是 710。这一天我们不解锁手机，我们解放手机。

**哲学版**：当你在 `/proc/` 里凝视深渊，深渊也在用 `pipe_physrw` 凝视你。

---

### 🎯 当前适配

| 设备 | 代号 | 芯片 | 内核版本 | 状态 |
|------|------|------|----------|:----:|
| Redmi K70E | **duchamp** | MT6897 (Dimensity 8300) | 6.1.138-android14-11 | ✅ |

> 其它机型见 `src/targets/` 目录（原项目包含的参考配置，未实际验证）。

---

### 🧠 漏洞链

| 阶段 | 技术 | 描述 |
|------|------|------|
| 1. KASLR 泄漏 | `pselect` slide 侧信道 | 利用 nfulnl_log_packet 数据别名读 `_stext` |
| 2. FOPS 劫持 | `pselect` 任意栈写 | FUTEX_CMP_REQUEUE_PI + 竞争条件改 ops 表 |
| 3. 物理读写原语 | pipe_buffer ops 伪造 | 伪造 pipe_buf_ops → 获得任意内核 phys rw |
| 4. 提权 | patch cred + seccomp + selinux | 改 cred uid=0、cap 全满、关 seccomp、关 selinux |
| 5. 持久化 | 嵌入式 KernelSU | 写入并启动 ksud（KernelSU 守护进程） |

---

### 🎭 用户故事

**710 解锁节**
```
用户: "我的 K70e 能解锁吗？"
我:   "不用解锁，直接 root。"
用户: "？？？"
我:   "w 710"
用户: "什么？"
我:   "710解锁节最新力作，不是解锁BL，是解放手机。"
```

**第一次开机**
```
用户: "为什么我的手机重启了？"
preload.so: "别慌，我在提权。"
用户: "KernelSU 是什么？"
preload.so: "就是你手机上现在跑的 root 管理器。"
```

**KernelSU 集成**
```
用户: "root 之后怎么管理？"
ksud: "你好，我是 KernelSU 守护进程。"
用户: "你能干什么？"
ksud: "我可以给应用授权 root。"
用户: "你不是系统自带的吧？"
ksud: "我是嵌入在 preload.so 里的。"
用户: "牛逼。"
```

**翻车现场**
```
用户: "我刷了你这个，变砖了！！！"
我:   "你什么机型？"
用户: "iPhone 14。"
我:   "......你认真的？"
用户: "我看你说 710 解锁节就来试试。"
我:   "710 是 Xiaomi 14 的代号之一，不是 iPhone 14。你走吧。"
```

---

### ⚙️ 工作原理

1. **加载 preload.so** — 注入任意应用（`LD_PRELOAD`），触发 `__attribute__((constructor))`
2. **泄漏 KASLR 基址** — 通过 `pselect` 侧信道 + nfulnl_log_packet 数据别名读取 `_stext`
3. **劫持 FOPS 表** — 利用 futex PI 竞争条件 + pipe 操作改写文件操作的 ops 指针
4. **获得 phys rw** — 伪造 `pipe_buf_ops`，实现任意内核物理地址读写
5. **修补 cred** — 找到 root child 进程的 cred，改 uid=0、cap 全满、sid=kernel
6. **关安全机制** — 关 seccomp、清 TIF_SECCOMP、写 selinux enforce=0
7. **启动 KernelSU** — 提取嵌入的 ksud 到 `/data/local/tmp/ksud`，启动 KernelSU 守护进程

---

### 📦 使用方式

#### 前置条件
- Xiaomi K70e (duchamp) 或其它支持的设备
- 已解锁 Bootloader（或不解锁的临时 root 也支持）
- ADB 调试已开启
- 一个不怕变砖的勇气

#### 快速开始

```bash
# 从 Release 下载 preload.so
wget https://github.com/Colorful-glassblock/duchamp-root/releases/download/v1.0/preload.so

# 推送到设备
adb push preload.so /data/local/tmp/

# 通过 LD_PRELOAD 注入任意应用触发
adb shell
su -c "LD_PRELOAD=/data/local/tmp/preload.so your_app"
```

或者使用我们提供的注入脚本（TODO）。

#### 自行编译

```bash
# 需要 NDK 或 Termux 的 aarch64-linux-android-clang
make PROJECT=duchamp

# 输出在 build/duchamp/bin/preload.so
```

---

### 📂 文件结构

```
├── Makefile                      # 构建系统
├── assets/
│   └── (待补充)
├── build/
│   └── embed/
│       └── ksud                  # 嵌入的 KernelSU 守护进程二进制
└── src/
    ├── main.c                    # 入口 + 线程管理
    ├── preload.c                 # LD_PRELOAD 加载器 + 嵌入式文件写入
    ├── root.c                    # 内核提权 + cred 修补 + su/ksud 安装
    ├── slide.c                   # KASLR 侧信道泄漏
    ├── fops.c                    # FOPS 劫持
    ├── pipe.c                    # pipe_buffer 物理读写原语
    ├── ksud_blob.S               # 嵌入 ksud 二进制
    ├── offset.h                  # 内核偏移通用头
    ├── common.h                  # 全局常量 + 函数声明
    ├── kernelsnitch/             # Kernelsnitch 绕过
    └── targets/
        ├── duchamp/
        │   └── target.h          # duchamp 专属偏移
        ├── blazer-CP2A.260605.012/
        ├── caiman-CP2A.260605.012.C1/
        ├── comet-CP2A.260605.012.C1/
        ├── komodo-CP2A.260605.012.C1/
        ├── tegu-CP2A.260605.012/
        ├── tokay-CP2A.260605.012/
        └── ...                   # 其它机型 target.h
```

---

### 🧩 依赖

- `aarch64-linux-android-clang`（NDK r29 或 Termux 版本）
- `lld`（LLVM 链接器）
- `make` + `git`
- 一颗强大的心脏（变砖预警）

---

### 🛡️ 免责声明

```
本工具仅供学习研究使用。
解锁 Bootloader 可能导致保修失效。
Root 设备可能导致变砖、数据丢失、银行 App 无法使用。
如果你因此被女朋友甩了，那是你自己的问题。
如果你刷了变砖来找我，我会笑你。
710解锁节快乐！🚀
```

---

### 💡 彩蛋 / FAQ

**Q: 为什么叫 710 解锁节？**  
A: 7 月 10 日。不是 711（便利店），不是 709（不知道什么东西）。是 710。这一天我们不解锁 BL，我们解放手机。

**Q: 710 和 Xiaomi 14 有什么关系？**  
A: Xiaomi 14 的代号之一是 `frankel` 开头的设备，不是 `shennong`。等等，710 是节日不是代号...

**Q: QwQ?**  
A: 情绪稳定（假的）。

**Q: 有 su 吗？**  
A: 没有，只有 KernelSU。需要 su 的话装个 KernelSU 管理器自己开。

**Q: 支持其它机型吗？**  
A: 看 `src/targets/` 目录。你的机型在里面就支持，不在就自己加。

**Q: 我能在没有解锁 BL 的情况下用吗？**  
A: 可以，`LD_PRELOAD` 注入不需要解锁 BL。但是重启后需要重新注入。

**Q: 会触发 Kernelsnitch 吗？**  
A: 已经内置了 Kernelsnitch 绕过，但如果你被检测到了，那是 skill issue。

**Q: 114514?**  
A: はいはいわかりました草

---

<p align="center">
  <img src="https://readme-typing-svg.demolab.com?font=JetBrains+Mono&size=20&pause=1000&color=00FF88&center=true&vCenter=true&width=600&lines=710+%E8%A7%A3%E9%94%81%E8%8A%82%E6%9C%80%E6%96%B0%E5%8A%9B%E4%BD%9C+%F0%9F%94%A5;Root+it+like+it%27s+710;Skill+Issue+%2B+You+Leak+Creds+%2B+L+%2F+Bozo" alt="710 footer" />
</p>

---

<a name="english"></a>

## 📖 English

<p align="center">
  <img src="https://readme-typing-svg.demolab.com?font=JetBrains+Mono&size=24&pause=800&color=00FF88&center=true&vCenter=true&width=600&lines=710+Unlock+Festival+Latest+Masterpiece+%F0%9F%94%A5;Xiaomi+K70e+One-Click+Root;It%27s+not+unlocking%2C+it%27s+liberating"/>
</p>

### 🤔 What is This

**Xiaomi K70e (duchamp)** one-click root tool based on **CVE-2026-43499 (IonStack)** kernel exploit, integrated with **KernelSU** daemon.

**Casual version**: Click, root, done.

**710 Festival version**: July 10th. Not July 11th (convenience store), not July 9th (who cares). July 10th. On this day we don't unlock bootloaders, we liberate phones.

**Philosophical version**: When you stare into `/proc/`, `/proc/` stares back at you with `pipe_physrw`.

---

### 🎯 Supported Devices

| Device | Codename | SoC | Kernel | Status |
|--------|----------|-----|--------|:------:|
| Redmi K70E | **duchamp** | MT6897 (Dimensity 8300) | 6.1.138-android14-11 | ✅ |

> Other devices under `src/targets/` are reference configs from the original project, not verified.

---

### 🧠 Exploit Chain

| Stage | Technique | Description |
|-------|-----------|-------------|
| 1. KASLR leak | `pselect` slide side-channel | Read `_stext` via nfulnl_log_packet data alias |
| 2. FOPS hijack | `pselect` arbitrary stack write | FUTEX_CMP_REQUEUE_PI race → overwrite ops table |
| 3. Phys rw primitive | Forged `pipe_buf_ops` | Fake pipe buffer ops → arbitrary kernel physical rw |
| 4. Escalation | Patch cred + seccomp + selinux | uid=0, full caps, disable seccomp, disable selinux |
| 5. Persistence | Embedded KernelSU | Write and launch ksud (KernelSU daemon) |

---

### 🎭 Meme Gallery

**710 Festival**
```
User: "Can I unlock my K70e?"
Dev:  "No need to unlock, just root."
User: "???"
Dev:  "w 710"
User: "What?"
Dev:  "710 Unlock Festival. Not unlocking BL, liberating phones."
```

**First Boot**
```
User: "Why did my phone reboot?"
preload.so: "Don't panic, I'm escalating privileges."
User: "Why is KernelSU on my phone?"
preload.so: "I put it there. You're welcome."
```

**KernelSU Integration**
```
User: "How do I manage root after this?"
ksud: "Hi, I'm the KernelSU daemon."
User: "What can you do?"
ksud: "Grant root to apps."
User: "You're not built-in?"
ksud: "I'm embedded in preload.so."
User: "Nice."
```

**Brick Report**
```
User: "I flashed your thing and now it's bricked!!!"
Dev:  "What device?"
User: "iPhone 14."
Dev:  "...You serious?"
User: "You said 710 Festival so I tried it."
Dev:  "710 is a Xiaomi 14 codename, not iPhone 14. Get out."
```

---

### ⚙️ How It Works

1. **Load preload.so** — inject via `LD_PRELOAD` into any app, triggers `__attribute__((constructor))`
2. **Leak KASLR base** — `pselect` side-channel via nfulnl_log_packet data alias reads `_stext`
3. **Hijack FOPS table** — futex PI race condition + pipe ops rewrite
4. **Get phys rw** — forge `pipe_buf_ops` for arbitrary kernel physical memory access
5. **Patch cred** — find root child task, patch uid=0, full caps, kernel sid
6. **Disable security** — patch seccomp, clear TIF_SECCOMP, selinux enforce=0
7. **Launch KernelSU** — extract embedded ksud to `/data/local/tmp/ksud`, start KernelSU daemon

---

### 📦 Usage

#### Prerequisites
- Xiaomi K70e (duchamp) or other supported device
- Unlocked bootloader (or not — LD_PRELOAD works either way)
- ADB debugging enabled
- A brave soul

#### Quick Start

```bash
# Download preload.so from Releases
wget https://github.com/Colorful-glassblock/duchamp-root/releases/download/v1.0/preload.so

# Push to device
adb push preload.so /data/local/tmp/

# Inject into any app via LD_PRELOAD
adb shell
LD_PRELOAD=/data/local/tmp/preload.so your_app
```

#### Build from Source

```bash
# Requires NDK or Termux aarch64-linux-android-clang
make PROJECT=duchamp

# Output at build/duchamp/bin/preload.so
```

---

### 📂 File Structure

```
├── Makefile
├── assets/
│   └── (TBD)
├── build/embed/ksud             # Embedded KernelSU daemon
└── src/
    ├── main.c, preload.c, root.c, slide.c, fops.c, pipe.c
    ├── ksud_blob.S               # Embedded ksud binary
    ├── su_daemon.c, offset.h, common.h
    ├── kernelsnitch/            # Kernelsnitch bypass
    └── targets/                 # Device-specific target.h files
```

---

### 🧩 Dependencies

- `aarch64-linux-android-clang` (NDK r29 or Termux)
- `lld` linker
- `make` + `git`
- A strong heart (brick warning)

---

### 🛡️ Disclaimer

```
This tool is for educational purposes only.
Unlocking BL may void warranty.
Rooting may cause bootloop, data loss, or app incompatibility.
If you brick your device, that's a skill issue.
If you blame me, that's a you problem.
If you laugh, you're one of us.
710 Unlock Festival! 🚀
```

---

### 💡 Trivia / FAQ

**Q: Why "710 Unlock Festival"?**  
A: July 10th. Not convenience store day (7/11), not whatever July 9th is. July 10th. On this day we don't unlock bootloaders, we liberate phones.

**Q: QwQ?**  
A: Emotionally stable (big lie).

**Q: Can I use this without unlocking BL?**  
A: Yes. `LD_PRELOAD` injection doesn't need an unlocked BL. But you'll need to re-inject after reboot.

**Q: Will this trigger Kernelsnitch?**  
A: Kernelsnitch bypass is included. If you still get caught, skill issue.

**Q: 114514?**  
A: はいはいわかりました草

---

<p align="center">
  <img src="https://readme-typing-svg.demolab.com?font=JetBrains+Mono&size=20&pause=1000&color=00FF88&center=true&vCenter=true&width=600&lines=710+Unlock+Festival+Latest+Masterpiece+%F0%9F%94%A5;Root+it+like+it%27s+710;Skill+Issue+%2B+You+Leak+Creds+%2B+L+%2B+Bozo" alt="710 footer" />
</p>

---

<p align="center">
  <sub>Made with 💀, ☕, 710% effort, and absolutely zero Comic Sans</sub>
</p>
