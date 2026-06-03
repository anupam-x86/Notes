# System Specifications

Last Updated: 2026-06-03

## Device Information

### Laptop

* Model: ASUS Vivobook K3605VC
* Host Name: fedora

---

## Operating System

* Distribution: Fedora Linux 44 (Workstation Edition)
* Architecture: x86_64
* Kernel: Linux 7.0.10-201.fc44.x86_64

---

## Desktop Environment

* Desktop Environment: GNOME 50.2
* Window Manager: Mutter
* Display Protocol: Wayland

---

## Hardware

### CPU

* Intel Core i5-13420H
* 8 Cores / 12 Threads
* Maximum Frequency: 4.60 GHz

### Memory

* Installed RAM: 16 GB

### GPU

#### Integrated GPU

* Intel UHD Graphics

#### Dedicated GPU

* NVIDIA GeForce RTX 3050 Laptop GPU
* VRAM: 4 GB

### Storage

* SSD Capacity: 512 GB

### Display

* Resolution: 1920 × 1200
* Refresh Rate: 144 Hz
* Size: 16 inches

---

## Fedora Storage Layout

### Root Filesystem

* Mount Point: /
* Filesystem: Btrfs
* Size: ~223 GB

### Windows Partition

* Size: ~250 GB

### Configuration

* Dual Boot: Yes
* Secure Boot: Enabled

---

## Development Environment

### Programming Languages

* Python 3
* C++

### Tools

* Git
* GCC
* G++
* Make
* Pip

### Editor

* Visual Studio Code

---

## Terminal Environment

### Shell

* Bash

### Terminal Emulator

* Ptyxis

---

## Appearance

### Theme

* WhiteSur Dark

### Icons

* WhiteSur

### Cursor

* Adwaita

---

## Network

### Wi-Fi Interface

* wlo1

---

## NVIDIA Status

Verification Command:

```bash
nvidia-smi
```

Expected Result:

* RTX 3050 detected
* Driver loaded successfully
* CUDA available

---

## Quick System Information Commands

### Fastfetch

```bash
fastfetch
```

### CPU Information

```bash
lscpu
```

### Memory Information

```bash
free -h
```

### Storage Information

```bash
df -h
```

### GPU Information

```bash
nvidia-smi
```

### Kernel Version

```bash
uname -r
```
