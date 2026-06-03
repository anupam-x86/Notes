# NVIDIA Setup

## Hardware

GPU:

* NVIDIA GeForce RTX 3050 Laptop GPU
* 4 GB VRAM

System Type:

* Hybrid Graphics Laptop
* Intel UHD Graphics (Integrated)
* NVIDIA RTX 3050 (Dedicated)

---

# Objective

Enable proprietary NVIDIA drivers while keeping Secure Boot enabled.

---

# Initial Symptoms

After installing the NVIDIA driver:

```text
NVIDIA-SMI has failed because it couldn't communicate with the NVIDIA driver.
```

During boot:

```text
NVIDIA kernel module missing
```

Manual loading:

```bash
sudo modprobe nvidia
```

Result:

```text
Key was rejected by service
```

---

# Investigation

## Check Driver Installation

Command:

```bash
modinfo nvidia
```

Result:

* NVIDIA module present
* Driver version: 595.71.05

Conclusion:

Driver was installed.

---

## Check Secure Boot Key

Command:

```bash
sudo mokutil --list-enrolled | grep -i NVIDIA
```

Result:

```text
Issuer: CN=NVIDIA Secure Boot
Subject: CN=NVIDIA Secure Boot
```

Conclusion:

NVIDIA signing certificate existed.

---

## Check Kernel Messages

Observed:

```text
integrity: Loaded X.509 cert 'NVIDIA Secure Boot'
```

and

```text
nouveau ...
```

This suggested Secure Boot trust issues and NVIDIA module loading problems.

---

# Root Cause

Secure Boot did not trust the NVIDIA kernel module.

Because the module was not accepted by Secure Boot, Linux could not load the NVIDIA driver.

---

# Solution

1. Install NVIDIA driver from RPM Fusion.
2. Generate Machine Owner Key (MOK).
3. Import MOK.
4. Reboot.
5. Enroll MOK during boot.
6. Rebuild NVIDIA kernel modules.
7. Reboot again.

---

# Verification

Command:

```bash
nvidia-smi
```

Output:

* Driver Version: 595.71.05
* CUDA Version: 13.2
* RTX 3050 detected

Example:

```text
NVIDIA GeForce RTX 3050 Laptop GPU
```

Result:

Driver working correctly.

---

# Useful Commands

## Check Driver Status

```bash
nvidia-smi
```

---

## View Driver Information

```bash
modinfo nvidia
```

---

## Check Loaded Modules

```bash
lsmod | grep nvidia
```

---

## Check Secure Boot State

```bash
mokutil --sb-state
```

---

## List Enrolled Keys

```bash
sudo mokutil --list-enrolled
```

---

# Concepts Learned

## Kernel Module

A piece of code loaded into the Linux kernel to provide hardware support.

Examples:

* NVIDIA Driver
* Wi-Fi Driver
* Bluetooth Driver

---

## Secure Boot

A security feature that allows only trusted software to load during startup.

---

## MOK

Machine Owner Key.

Allows the user to add trusted certificates for Secure Boot.

---

## Hybrid Graphics

This laptop contains two GPUs:

### Intel UHD Graphics

Used for:

* Battery efficiency
* Everyday tasks

### RTX 3050

Used for:

* Gaming
* CUDA
* AI/ML
* GPU acceleration

---

# Lessons Learned

* Driver installation and driver loading are different things.
* A driver can be installed but still fail to load.
* Secure Boot can block unsigned kernel modules.
* Error messages are often the fastest path to the solution.
* `nvidia-smi` is the quickest way to verify NVIDIA driver functionality.
