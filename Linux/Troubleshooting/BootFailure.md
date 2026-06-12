# Fedora UEFI Boot Failure Incident Report & Recovery Guide

This document is a complete production-grade record of a real Fedora boot failure, including:

- Symptom analysis
- Root cause identification
- Boot chain breakdown
- Full recovery procedure
- Snapper context
- Verification steps
- Deep diagnostics (UEFI, GRUB, LUKS, BLS, Secure Boot)
- Timeline reconstruction

It also serves as a reusable Linux boot failure troubleshooting reference.

---

# 1. Initial Failure (Observed Symptom)

## Error Message

```
Failed to open \EFI\fedora\grubx64.efi - Not Found
Failed to load image \EFI\fedora\grubx64.efi: Not Found
start_image() returned Not Found
```

---

## Meaning

This indicates a **UEFI firmware-level boot failure**.

The system never reaches GRUB, kernel, or initramfs.

---

[!NOTE]
At this stage:
- Linux is not running
- GRUB is not executed
- Only UEFI firmware is active

---

# 2. Boot Chain Analysis

```
UEFI Firmware
↓
EFI boot entry lookup ❌ FAILED
↓
shimx64.efi (not reached)
↓
grubx64.efi (missing)
↓
Linux kernel (never executed)
↓
initramfs (never executed)
```

---

# 3. Pre-Recovery System Diagnostics (Critical Layer)

## 3.1 Disk Identification

```bash
lsblk -f
blkid
```

Purpose:
- Identify EFI partition (FAT32)
- Identify LUKS partition
- Identify BTRFS root subvolumes

---

## 3.2 EFI Partition Integrity Check

```bash
fsck.fat -v /dev/nvme0n1p1
```

Purpose:
- Detect EFI filesystem corruption
- Ensure FAT32 integrity

---

## 3.3 EFI Mount Verification

```bash
mount | grep efi
ls /boot/efi/EFI/
```

---

## 3.4 Secure Boot State

```bash
mokutil --sb-state
```

Purpose:
- Verify if shim is required
- Confirm secure boot dependency

---

## 3.5 Previous Boot Errors

```bash
journalctl -b -1 -p err
```

Purpose:
- Identify failure point before reboot crash

---

## 3.6 BLS Boot Entries Check

```bash
ls /boot/loader/entries/
```

Purpose:
- Confirm Fedora Boot Loader Spec entries exist

---

## 3.7 EFI Fallback Boot Path Check

```bash
ls /boot/efi/EFI/BOOT/
```

Fallback path:
```
/EFI/BOOT/BOOTX64.EFI
```

---

# 4. Root Cause Analysis

## Primary Cause

Missing or broken EFI bootloader:

```
/EFI/fedora/grubx64.efi
```

---

## Likely Causes

- Interrupted `dnf upgrade`
- GRUB/shim update failure
- EFI partition not mounted during update
- Broken UEFI boot entry
- Overwritten boot entry
- Partial bootloader installation

---

[!WARNING]
This issue is NOT related to:
- TPM hardware
- Linux kernel
- filesystem corruption
- LUKS encryption failure

It is strictly a **UEFI bootloader chain failure**.

---

# 5. Symptom Chain After Failure

```
UEFI retries boot entry
↓
Repeated firmware boot attempts
↓
TPM logs measurement events
↓
Boot loop appears
↓
User observes TPM extend messages
```

---

[!NOTE]
TPM logs are a side effect of repeated boot attempts, not a root cause.

---

# 6. LUKS Validation Step

```bash
cryptsetup luksDump /dev/nvme0n1p7
ls /dev/mapper/
```

Purpose:
- Confirm encryption structure
- Verify decrypted mapping exists

---

# 7. Recovery Method (Live USB Environment)

## Step 1: Unlock LUKS

```bash
cryptsetup luksOpen /dev/nvme0n1p7 fedora-root
```

---

## Step 2: Mount system

```bash
mount -o subvol=root /dev/mapper/fedora-root /mnt
mount /dev/nvme0n1p6 /mnt/boot
mount /dev/nvme0n1p1 /mnt/boot/efi
```

---

## Step 3: Verify EFI mount

```bash
ls /mnt/boot/efi/EFI/fedora
```

Expected:
- shimx64.efi
- grubx64.efi
- grub.cfg

---

## Step 4: Bind system directories

```bash
mount --bind /dev /mnt/dev
mount --bind /proc /mnt/proc
mount --bind /sys /mnt/sys
mount --bind /run /mnt/run
```

---

## Step 5: Enter system (chroot)

```bash
chroot /mnt
```

---

# 8. Core Fix Procedures

## Fix 1: Reinstall GRUB + Shim

### Why both matter

- shimx64.efi → Secure Boot entry point
- grubx64.efi → Bootloader logic

If either is missing → boot fails

```bash
dnf reinstall grub2-efi-x64 grub2-efi-x64-modules shim-x64
```

---

## Fix 2: Regenerate GRUB config

```bash
grub2-mkconfig -o /boot/grub2/grub.cfg
```

---

## Fix 3: Rebuild initramfs

```bash
dracut --force --regenerate-all
```

---

## Fix 4: Restore EFI boot entry

```bash
efibootmgr -c -d /dev/nvme0n1 -p 1 \
-L "Fedora" \
-l '\EFI\fedora\shimx64.efi'
```

---

## Fix 5: Verify boot entries

```bash
efibootmgr -v
```

Check:
- correct disk
- correct EFI path
- Fedora entry priority

---

# 9. Snapper Context (Important Clarification)

Snapper operates at filesystem level, not EFI level.

[!NOTE]
Snapper cannot fix:
- Missing EFI boot files
- Broken UEFI boot entries

It can only restore:
- system files
- configs
- kernel-related filesystem state

```bash
snapper list
snapper rollback <id>
```

---

# 10. Verification Steps

## 10.1 Check EFI files

```bash
ls /boot/efi/EFI/fedora
```

Expected:

```
shimx64.efi
grubx64.efi
grub.cfg
```

---

## 10.2 Check fallback boot

```bash
ls /boot/efi/EFI/BOOT/
```

---

## 10.3 Confirm system boot

- Fedora boots normally
- GRUB menu appears
- No boot loop
- No TPM repetition

---

# 11. Final Root Cause Summary

## Primary Issue

```
Missing EFI bootloader file:
\EFI\fedora\grubx64.efi
```

---

## Failure Chain

```
Missing grubx64.efi
↓
UEFI boot failure
↓
Repeated boot attempts
↓
TPM logs appear (symptom only)
↓
Boot loop observed
```

---

## Final Fix Applied

```
Reinstall GRUB + shim
Rebuild GRUB config
Rebuild initramfs
Restore EFI boot entry
Ensure correct boot order
```

---

# 12. Timeline of Events

```
1. System update or change occurred
2. EFI boot file became missing/broken
3. UEFI failed to locate grubx64.efi
4. Boot loop started
5. TPM logs appeared due to retries
6. Live USB recovery initiated
7. Disk + EFI + LUKS diagnosed
8. System mounted and chrooted
9. GRUB + shim reinstalled
10. EFI entry restored
11. Boot order verified
12. System boot successful
```

---

# 13. Key Lessons

- UEFI failure happens before Linux starts
- Missing EFI files break boot completely
- TPM messages are symptoms, not causes
- Snapper cannot fix EFI-layer issues
- Always verify EFI mount before GRUB repair
- Always check fallback boot path
- Always verify boot order after repair
- Live USB + chroot is standard recovery method

---

# 14. Golden Rule

Always identify the first failing layer:

- EFI failure → bootloader issue
- GRUB failure → configuration or kernel selection issue
- Kernel failure → initramfs/system issue
```
