# NVIDIA Proprietary Driver Setup on Fedora 44 (Secure Boot Enabled)

## Hardware

### GPU Configuration

- **Dedicated GPU:** NVIDIA GeForce RTX 3050 Laptop GPU
  - 4 GB VRAM
- **Integrated GPU:** Intel UHD Graphics

### System Type

Hybrid graphics laptop (Intel + NVIDIA)

---

# Goal

Install and use the proprietary NVIDIA driver while **keeping Secure Boot enabled**, without disabling any firmware security features.

---

# Initial Problem

After installing the NVIDIA packages, the driver appeared to be installed, but it wasn't actually working.

Running:

```bash
nvidia-smi
```

produced:

```text
NVIDIA-SMI has failed because it couldn't communicate with the NVIDIA driver.
```

Trying to manually load the kernel module:

```bash
sudo modprobe nvidia
```

returned:

```text
modprobe: ERROR: could not insert 'nvidia': Key was rejected by service
```

---

# Understanding the Error

The important part of the error is:

```text
Key was rejected by service
```

This does **not** indicate that the NVIDIA package is missing.

Instead, it means:

- The kernel module exists.
- Linux attempted to load it.
- Secure Boot rejected it because the module was not signed with a trusted key.

This immediately points to a **Secure Boot trust problem**, not a package installation problem.

---

# Step 1 — Verify That the Driver Was Installed

First, confirm that the NVIDIA kernel module actually exists.

```bash
modinfo nvidia
```

If information about the module is displayed, then:

- The NVIDIA packages are installed.
- The kernel module has been built.
- The module exists on disk.

Therefore, the installation itself succeeded.

The remaining issue is that the kernel refuses to load the module.

---

# Step 2 — Check Whether the Module Is Signed

Kernel modules contain signature metadata.

Inspect it with:

```bash
modinfo nvidia | grep -E "signer|sig_id"
```

Initial output:

```text
sig_id:
signer:
```

Both fields were empty.

This means:

- The module has no PKCS#7 signature.
- Secure Boot cannot verify its authenticity.
- The module is considered untrusted.

As a result, the kernel refuses to load it.

---

# Why Secure Boot Rejects the Module

When Secure Boot is enabled, Linux enforces kernel module signature verification.

Only modules signed by a trusted certificate are allowed to load.

Unsigned modules are rejected before they can interact with kernel space.

This explains why:

```bash
sudo modprobe nvidia
```

returned:

```text
Key was rejected by service
```

The driver itself was not broken.

The kernel simply did not trust it.

---

# Root Cause #1

The NVIDIA kernel module existed but was **not signed with a trusted key**.

The installation completed successfully, but Secure Boot prevented the module from loading.

Without a trusted signature, the NVIDIA driver cannot become active.

# Signing NVIDIA Kernel Modules with akmods

After identifying that Secure Boot was rejecting the NVIDIA module, the next step was to configure **akmods** to automatically sign every NVIDIA kernel module it builds.

---

# Understanding akmods

Fedora's NVIDIA packages from RPM Fusion use **akmods** instead of shipping prebuilt kernel modules.

Whenever:

- a new kernel is installed,
- the NVIDIA driver is updated,

`akmods` automatically builds a kernel module specifically for your current kernel.

The build process is roughly:

```text
Install NVIDIA package
        │
        ▼
akmods builds kernel module
        │
        ▼
(Optional) Sign the module
        │
        ▼
Module stored in /lib/modules/<kernel>/
```

If Secure Boot is enabled, the module **must be signed** before the kernel will load it.

---

# Step 3 — Check for Existing Signing Keys

Fedora's akmods package can generate a signing key pair.

Verify whether one already exists:

```bash
sudo ls /etc/pki/akmods/certs
```

Output:

```text
private_key.priv
public_key.der
```

These files represent a cryptographic key pair.

| File | Purpose |
|------|---------|
| `private_key.priv` | Used to digitally sign kernel modules. Keep this file secret. |
| `public_key.der` | Public certificate used to verify module signatures. This certificate must be enrolled as a Machine Owner Key (MOK). |

---

# Public Key vs Private Key

Digital signatures rely on asymmetric cryptography.

```text
Private Key
      │
Signs module
      │
      ▼
Signed NVIDIA Module
      │
Verified using
      ▼
Public Certificate
```

The **private key** signs modules.

The **public certificate** allows the kernel to verify that signature.

Anyone may have the public certificate.

Only the private key must remain protected.

---

# Step 4 — Configure akmods

By default, akmods may not know which key pair to use.

Create the configuration file:

```bash
sudo nano /etc/akmods/sign-keypair.inc
```

Add:

```bash
KERNEL_MODULES_SIGN_KEY="/etc/pki/akmods/private/private_key.priv"
KERNEL_MODULES_SIGN_CERT="/etc/pki/akmods/certs/public_key.der"
```

This tells akmods:

- which private key signs modules,
- which certificate corresponds to that key.

---

# Step 5 — Store the Private Key Securely

Move the private key into the expected directory.

```bash
sudo mkdir -p /etc/pki/akmods/private

sudo mv /etc/pki/akmods/certs/private_key.priv \
/etc/pki/akmods/private/
```

The resulting structure becomes:

```text
/etc/pki/akmods/

├── certs/
│   └── public_key.der
│
└── private/
    └── private_key.priv
```

---

# Step 6 — Set Correct Permissions

Protect the private signing key.

```bash
sudo chown root:root /etc/pki/akmods/private/private_key.priv
sudo chmod 600 /etc/pki/akmods/private/private_key.priv
```

### Why `600` instead of `644`?

A private key should **never** be world-readable.

Permission `600` means:

- Owner (root): read/write
- Group: no access
- Others: no access

This prevents other users from copying the signing key.

---

# Step 7 — Rebuild the NVIDIA Module

Force akmods to rebuild and sign the NVIDIA kernel module.

```bash
sudo akmods --force --rebuild
```

During this process:

1. The NVIDIA module is compiled.
2. The private key signs the module.
3. A PKCS#7 signature is embedded into the module.

---

# Step 8 — Verify the Signature

Check the rebuilt module:

```bash
modinfo nvidia | grep -E "signer|sig_id"
```

Expected output:

```text
sig_id: PKCS#7
signer: Fedora NVIDIA Module Signing
```

This confirms:

- The module has been signed.
- The signature is embedded.
- Secure Boot can now verify its authenticity **provided the corresponding public certificate is trusted**.

---

# Important: Signing Alone Is Not Enough

A signed module is **not automatically trusted**.

Secure Boot only trusts signatures made with certificates stored in its trust database.

For self-signed modules, the corresponding **public certificate** must be enrolled as a **Machine Owner Key (MOK)**.

Without enrolling the certificate, the kernel will still reject the module, even if it contains a valid signature.

---

# Root Cause #1 Resolved

The NVIDIA module is now:

- successfully built,
- digitally signed,
- ready to be trusted by Secure Boot after the signing certificate is enrolled.

The next step is ensuring the certificate is trusted and resolving any remaining driver conflicts.

# Enrolling the Machine Owner Key (MOK)

Signing the NVIDIA module is only **half** of the Secure Boot process.

The Linux kernel will only load signed kernel modules if the **certificate used to sign them is trusted**.

For self-signed modules, this trust is established by enrolling the public certificate as a **Machine Owner Key (MOK)**.

---

# Understanding Secure Boot Trust

Secure Boot maintains a database of trusted certificates.

When a kernel module is loaded, Linux performs the following checks:

```text
Kernel module
      │
      ▼
Is the module signed?
      │
 ┌────┴────┐
 │         │
No        Yes
 │         │
Reject     ▼
     Is the signing certificate trusted?
              │
        ┌─────┴─────┐
        │           │
       No          Yes
        │           │
Reject module   Load module
```

A valid signature is **not enough**.

The certificate used to create that signature must also exist in the firmware's trusted key database.

---

# What Is a Machine Owner Key (MOK)?

A **Machine Owner Key (MOK)** is a certificate that you, the system owner, choose to trust.

It allows Secure Boot to accept:

- custom kernel modules,
- third-party drivers,
- locally built modules,

without disabling Secure Boot.

Common uses include:

- NVIDIA proprietary drivers
- VirtualBox kernel modules
- VMware kernel modules
- Custom kernel modules built with DKMS or akmods

---

# Step 9 — Import the Public Certificate

Import the public certificate generated by akmods:

```bash
sudo mokutil --import /etc/pki/akmods/certs/public_key.der
```

You will be prompted to create a temporary password.

Example:

```text
input password:
confirm password:
```

This password is **not** your Linux password.

It is only used once during the enrollment process after rebooting.

---

# Step 10 — Reboot

Restart the computer.

```bash
sudo reboot
```

Instead of booting directly into Fedora, the **MOK Manager** screen should appear.

---

# MOK Manager

The MOK Manager runs before Linux starts.

Choose the following options:

```text
Enroll MOK
        ↓
Continue
        ↓
Yes
        ↓
Enter password
        ↓
Reboot
```

After confirming the password, the public certificate is added to the firmware's trusted key database.

---

# Step 11 — Verify Secure Boot Status

After logging back into Fedora, verify that Secure Boot is still enabled.

```bash
mokutil --sb-state
```

Expected output:

```text
SecureBoot enabled
```

---

# Step 12 — Verify the Enrolled Key

List all enrolled Machine Owner Keys:

```bash
sudo mokutil --list-enrolled
```

Look for the certificate used to sign the NVIDIA modules.

Example:

```text
CN=Fedora NVIDIA Module Signing
```

If the certificate appears, Secure Boot now trusts modules signed with your private key.

---

# What If the MOK Screen Never Appears?

Possible causes include:

- The import command failed.
- The system was not rebooted after importing.
- Fast Boot or firmware settings skipped the MOK Manager.
- The certificate was already enrolled.
- The firmware cleared pending MOK enrollment requests.

You can retry the import:

```bash
sudo mokutil --import /etc/pki/akmods/certs/public_key.der
```

and reboot again.

---

# Why This Step Matters

Without MOK enrollment:

- The module is correctly signed.
- The signature is valid.
- The kernel **still rejects the module** because the signing certificate is unknown.

With MOK enrollment:

```text
Private key
      │
Signs NVIDIA module
      │
      ▼
Signed module
      │
Verified using
      ▼
Public certificate
      │
Stored as MOK
      │
      ▼
Secure Boot trusts module
      │
      ▼
Kernel loads NVIDIA driver
```

---

# Root Cause #1 Fully Resolved

At this stage:

- ✔ NVIDIA module exists.
- ✔ NVIDIA module is signed.
- ✔ The signing certificate is enrolled.
- ✔ Secure Boot trusts the module.

If `modprobe nvidia` still fails after these steps, the problem is **no longer Secure Boot**.

The next investigation is determining **which driver currently owns the NVIDIA GPU**, since another driver (typically `nouveau`) may already be bound to the hardware.

# Resolving the `nouveau` Driver Conflict

After signing the NVIDIA module and enrolling the Machine Owner Key (MOK), the original error changed.

Running:

```bash
sudo modprobe nvidia
```

no longer produced:

```text
Key was rejected by service
```

Instead, it returned:

```text
modprobe: ERROR: could not insert 'nvidia': No such device
```

Although this looks like a different problem, it is actually a good sign.

It indicates that **Secure Boot is no longer blocking the module**.

The kernel successfully verified the module's signature and attempted to load it.

The remaining issue was that the NVIDIA hardware was already being controlled by another driver.

---

# Understanding the "No Such Device" Error

This error does **not** necessarily mean that the GPU is missing or broken.

Instead, it usually means one of the following:

- another driver has already claimed the device,
- the device is disabled,
- the hardware is inaccessible,
- the kernel cannot bind the module to the GPU.

On Fedora, the most common cause is the **nouveau** driver.

---

# Step 13 — Identify Which Driver Owns the GPU

Display PCI devices and their associated drivers:

```bash
lspci -nnk | grep -A3 -i nvidia
```

Example output:

```text
01:00.0 VGA compatible controller: NVIDIA Corporation GA107M
        Kernel driver in use: nouveau
        Kernel modules: nouveau, nvidia_drm, nvidia
```

The important line is:

```text
Kernel driver in use: nouveau
```

This confirms that Linux had already attached the open-source `nouveau` driver to the NVIDIA GPU.

---

# Understanding Driver Binding

Each hardware device can normally be controlled by **one kernel driver at a time**.

The process looks like this:

```text
PCI Device
      │
      ▼
Kernel detects hardware
      │
      ▼
Select driver
      │
 ┌────┴────┐
 │         │
nouveau   nvidia
```

If `nouveau` claims the GPU first, the proprietary NVIDIA driver cannot attach to the same hardware.

---

# Why `modprobe` Still Failed

Even though the NVIDIA module loaded successfully into the kernel, it could not take control of the GPU because:

```text
GPU
 │
 ▼
Already attached to nouveau
 │
 ▼
NVIDIA driver cannot bind
 │
 ▼
"No such device"
```

The module itself was working correctly.

The hardware was simply unavailable.

---

# Root Cause #2

The **nouveau** driver had already claimed the NVIDIA GPU before the proprietary driver could attach.

This prevented the NVIDIA driver from becoming active.

---

# Step 14 — Disable the `nouveau` Driver

Create a blacklist configuration file:

```bash
sudo nano /etc/modprobe.d/blacklist-nouveau.conf
```

Add the following:

```conf
blacklist nouveau
options nouveau modeset=0
```

### What These Options Do

**`blacklist nouveau`**

Prevents the kernel from automatically loading the `nouveau` module.

**`options nouveau modeset=0`**

Disables kernel mode setting (KMS) for `nouveau`, ensuring it cannot initialize the GPU during boot.

---

# Step 15 — Rebuild the initramfs

The initramfs contains the drivers loaded during early boot.

Even after blacklisting `nouveau`, the existing initramfs may still include it.

Rebuild the initramfs:

```bash
sudo dracut --force
```

This creates a new boot image that excludes the blacklisted driver.

---

# Step 16 — Reboot

Restart the system:

```bash
sudo reboot
```

During the next boot:

1. `nouveau` is not loaded.
2. The NVIDIA module is available.
3. The kernel binds the GPU to the proprietary NVIDIA driver.

---

# Verify That `nouveau` Is Gone

Check whether the `nouveau` module is loaded:

```bash
lsmod | grep nouveau
```

Expected output:

```text
(no output)
```

No output indicates that the module is no longer active.

---

# Verify NVIDIA Modules

Check the NVIDIA kernel modules:

```bash
lsmod | grep nvidia
```

Typical output:

```text
nvidia
nvidia_modeset
nvidia_drm
nvidia_uvm
```

These modules provide different parts of the NVIDIA driver stack.

| Module | Purpose |
|---------|---------|
| `nvidia` | Core GPU driver |
| `nvidia_modeset` | Display mode management |
| `nvidia_drm` | DRM/KMS integration for graphics and Wayland |
| `nvidia_uvm` | Unified Virtual Memory (CUDA, AI, compute workloads) |

---

# Verify the Driver

Finally, confirm that the proprietary driver is active:

```bash
nvidia-smi
```

Expected output:

```text
+------------------------------------------------------+
| NVIDIA-SMI 595.xx                                    |
| Driver Version: 595.xx                               |
| CUDA Version: 13.x                                   |
+------------------------------------------------------+
```

You should also see your GPU listed, for example:

```text
NVIDIA GeForce RTX 3050 Laptop GPU
```

This confirms that:

- the kernel module loaded successfully,
- Secure Boot accepted the module,
- the NVIDIA driver claimed the GPU,
- the driver is communicating correctly with the hardware.

---

# Root Cause #2 Resolved

At this point:

- ✔ `nouveau` is disabled.
- ✔ The proprietary NVIDIA driver owns the GPU.
- ✔ Kernel modules are loaded.
- ✔ `nvidia-smi` communicates with the driver successfully.

The NVIDIA driver is now fully operational while Secure Boot remains enabled.

# Verification, Troubleshooting Checklist, and Key Concepts

With the NVIDIA driver successfully installed, signed, and loaded, it's useful to know how to verify the installation and troubleshoot future problems.

---

# Verification Commands

## Check NVIDIA Driver Status

```bash
nvidia-smi
```

Purpose:

- Verifies that the NVIDIA driver is loaded.
- Confirms communication between user-space tools and the kernel driver.
- Displays GPU information, driver version, CUDA version, temperature, utilization, and running processes.

Example:

```text
+------------------------------------------------------+
| NVIDIA-SMI 595.xx                                    |
| Driver Version: 595.xx                               |
| CUDA Version: 13.x                                   |
+------------------------------------------------------+
```

If this command works, the driver is functioning correctly.

---

## Check Loaded NVIDIA Modules

```bash
lsmod | grep nvidia
```

Expected modules:

```text
nvidia
nvidia_modeset
nvidia_drm
nvidia_uvm
```

If no modules appear, the driver has not been loaded.

---

## Check Module Information

```bash
modinfo nvidia
```

Useful information includes:

- module version
- filename
- license
- dependencies
- firmware
- signature information

---

## Verify Module Signature

```bash
modinfo nvidia | grep -E "signer|sig_id"
```

Expected:

```text
sig_id: PKCS#7
signer: Fedora NVIDIA Module Signing
```

If these fields are empty, the module is unsigned.

---

## Check Which Driver Owns the GPU

```bash
lspci -nnk | grep -A3 -i nvidia
```

Correct output:

```text
Kernel driver in use: nvidia
```

Incorrect output:

```text
Kernel driver in use: nouveau
```

If `nouveau` is listed, the proprietary driver is not controlling the GPU.

---

## Check Secure Boot Status

```bash
mokutil --sb-state
```

Expected:

```text
SecureBoot enabled
```

or

```text
SecureBoot disabled
```

This confirms whether firmware Secure Boot is currently active.

---

## List Enrolled Machine Owner Keys

```bash
sudo mokutil --list-enrolled
```

Look for your signing certificate, for example:

```text
CN=Fedora NVIDIA Module Signing
```

If it is missing, Secure Boot will not trust modules signed with that certificate.

---

## Check Whether `nouveau` Is Loaded

```bash
lsmod | grep nouveau
```

Expected:

```text
(no output)
```

If `nouveau` appears here, it may still be preventing the proprietary driver from binding to the GPU.

---

# Common Error Messages

## Error

```text
Key was rejected by service
```

### Meaning

Secure Boot rejected the kernel module.

### Possible Causes

- Module is unsigned.
- Signing certificate is not enrolled.
- Signature is invalid.

---

## Error

```text
No such device
```

### Meaning

The NVIDIA module loaded, but could not bind to the hardware.

### Possible Causes

- `nouveau` already owns the GPU.
- Hardware is disabled.
- Device initialization failed.

---

## Error

```text
NVIDIA-SMI has failed because it couldn't communicate with the NVIDIA driver.
```

### Meaning

The userspace tools cannot communicate with the kernel driver.

Possible reasons include:

- NVIDIA module is not loaded.
- Driver failed to initialize.
- Secure Boot blocked the module.
- Incorrect kernel module is active.

---

# Debugging Workflow

When troubleshooting NVIDIA drivers, follow this sequence instead of making random changes.

```text
Install NVIDIA packages
        │
        ▼
Does the kernel module exist?
        │
        ▼
modinfo nvidia
        │
        ▼
Is the module signed?
        │
        ▼
modinfo | grep signer
        │
        ▼
Is the signing certificate enrolled?
        │
        ▼
mokutil --list-enrolled
        │
        ▼
Is Secure Boot enabled?
        │
        ▼
mokutil --sb-state
        │
        ▼
Which driver owns the GPU?
        │
        ▼
lspci -nnk
        │
        ▼
Is nouveau loaded?
        │
        ▼
lsmod | grep nouveau
        │
        ▼
Are NVIDIA modules loaded?
        │
        ▼
lsmod | grep nvidia
        │
        ▼
Does nvidia-smi work?
```

Following this order helps isolate the problem systematically.

---

# Key Concepts

## Kernel Module

A **kernel module** is a piece of code that extends the Linux kernel without requiring a reboot.

Examples include:

- NVIDIA GPU driver
- Wi-Fi drivers
- Bluetooth drivers
- Filesystem drivers
- USB drivers

Kernel modules can be loaded and unloaded dynamically.

---

## Secure Boot

Secure Boot is a UEFI security feature that ensures only trusted software runs during the boot process.

For Linux kernel modules, Secure Boot verifies that each module is signed by a trusted certificate before allowing it to load.

Its goal is to prevent unauthorized or malicious kernel code from executing.

---

## Machine Owner Key (MOK)

A **Machine Owner Key (MOK)** is a user-managed certificate enrolled into the system's Secure Boot trust database.

It allows Secure Boot to trust:

- self-signed kernel modules,
- third-party drivers,
- locally built modules.

The private key signs modules, while the enrolled public certificate allows the kernel to verify those signatures.

---

## akmods

`akmods` automatically builds kernel modules when a new kernel is installed.

For RPM Fusion's NVIDIA packages, it:

1. Detects the running kernel.
2. Builds the NVIDIA module.
3. Optionally signs the module.
4. Installs it into the kernel module directory.

This avoids needing precompiled modules for every kernel version.

---

## initramfs

The **initial RAM filesystem (initramfs)** is a temporary root filesystem loaded early during boot.

It contains:

- essential kernel modules,
- firmware,
- storage drivers,
- boot-time utilities.

After changing driver blacklists, rebuilding the initramfs ensures the updated configuration is used during the next boot.

---

## nouveau

`nouveau` is the open-source NVIDIA graphics driver included with the Linux kernel.

### Advantages

- Open source.
- Automatically available on most Linux distributions.
- Works without proprietary software.

### Limitations

- Lower performance for many workloads.
- Limited support for CUDA.
- Limited support for AI and GPU compute.
- Does not provide the full NVIDIA feature set.

Because only one driver can control the GPU at a time, `nouveau` must usually be disabled before using the proprietary NVIDIA driver.

---

## Hybrid Graphics

A hybrid graphics laptop contains two GPUs:

```text
Intel Integrated GPU
        │
        ├── Desktop
        ├── Web browsing
        ├── Battery-efficient workloads
        │
        ▼
NVIDIA Dedicated GPU
        │
        ├── Gaming
        ├── CUDA
        ├── AI / Machine Learning
        ├── Video rendering
        └── GPU-accelerated applications
```

Linux dynamically selects which GPU should handle a workload, depending on system configuration and user preferences.

---

# Final Lessons Learned

This troubleshooting process reinforces several important principles:

- Installing a package does **not** guarantee that the driver is active.
- A kernel module can exist without being loaded.
- A signed module is useless unless its signing certificate is trusted.
- Secure Boot verifies trust before allowing kernel code to execute.
- Only one kernel driver can own a hardware device at a time.
- Driver issues are easiest to solve by verifying one layer at a time instead of changing multiple things simultaneously.

---

# Complete Troubleshooting Flow

```text
Install NVIDIA packages
        │
        ▼
Kernel module exists
        │
        ▼
Module is signed
        │
        ▼
Signing certificate enrolled (MOK)
        │
        ▼
Secure Boot trusts the module
        │
        ▼
nouveau disabled
        │
        ▼
NVIDIA driver binds to GPU
        │
        ▼
Kernel modules loaded
        │
        ▼
nvidia-smi works
        │
        ▼
CUDA and GPU acceleration available
```

Following this workflow provides a structured approach to diagnosing most Secure Boot–related NVIDIA driver issues on Fedora.
