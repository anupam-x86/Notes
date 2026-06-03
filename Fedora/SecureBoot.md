# Secure Boot

## What is Secure Boot?

Secure Boot is a security feature provided by UEFI firmware.

Its purpose is to ensure that only trusted software is allowed to run during system startup.

---

# Why Secure Boot Exists

Without Secure Boot: `Power On → Anything can load`

With Secure Boot: `Power On → Verify Signature → Trusted Software Loads`

This helps protect against:

* Bootkits
* Rootkits
* Malicious bootloaders
* Unauthorized kernel modules

---

# Boot Process

Simplified startup sequence:

Power Button → UEFI Firmware → Secure Boot Verification → Bootloader → Linux Kernel → Drivers and Services → Desktop Environment

---

# UEFI

UEFI stands for:

Unified Extensible Firmware Interface

UEFI replaces the older BIOS system.

Responsibilities:

* Hardware initialization
* Boot management
* Secure Boot support

---

# Digital Signatures

Secure Boot works by checking digital signatures.

Concept:

```text
Software
    +
Trusted Signature
    =
Allowed to Load
```

If software is not signed by a trusted key:

```text
Rejected
```

---

# Kernel Modules

A kernel module is code loaded into the Linux kernel.

Examples:

* NVIDIA Driver
* Wi-Fi Driver
* Bluetooth Driver
* Filesystem Drivers

Modules are loaded after the kernel starts.

Example command:

```bash
lsmod
```

---

# Problem Encountered

During NVIDIA setup:

```bash
sudo modprobe nvidia
```

returned:

```text
Key was rejected by service
```

---

# Cause

The NVIDIA kernel module was installed.

However:

* Secure Boot did not trust the module.
* The module could not load.
* NVIDIA driver failed to start.

---

# Machine Owner Key (MOK)

## Definition

MOK stands for:

Machine Owner Key

It allows users to add their own trusted signing certificates.

---

# Why MOK Exists

Many Linux users need:

* NVIDIA Drivers
* Virtual Machine Modules
* Third-party Drivers

These may not be trusted by default.

MOK provides a way to trust them without disabling Secure Boot.

---

# NVIDIA Secure Boot Fix

Steps performed:

1. Install NVIDIA drivers.
2. Generate signing key.
3. Import key.
4. Reboot.
5. Open MOK Manager.
6. Enroll key.
7. Reboot.
8. Rebuild modules if necessary.

Result:

```bash
nvidia-smi
```

worked successfully.

---

# Commands

## Check Secure Boot Status

```bash
mokutil --sb-state
```

---

## List Enrolled Keys

```bash
sudo mokutil --list-enrolled
```

---

## Search for NVIDIA Certificate

```bash
sudo mokutil --list-enrolled | grep -i NVIDIA
```

---

# Concepts Learned

## UEFI

Modern firmware that starts the computer.

---

## Secure Boot

Verifies trusted software before loading.

---

## Digital Signature

Proof that software originates from a trusted source.

---

## Kernel Module

Additional functionality loaded into the Linux kernel.

---

## MOK

User-controlled trust mechanism for Secure Boot.

---

# Personal Notes

For this Fedora installation:

* Secure Boot remains enabled.
* NVIDIA drivers work correctly.
* MOK enrollment completed successfully.

This setup allows security and proprietary NVIDIA drivers to coexist.

---

# Lessons Learned

* Secure Boot is not the same thing as UEFI.
* A driver being installed does not mean it can load.
* Digital signatures determine trust.
* MOK allows users to extend Secure Boot trust.
* Understanding the cause of an error is more important than memorizing the fix.
