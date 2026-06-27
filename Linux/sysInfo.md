# Linux System Architecture and Auditing


# System Diagnostics Path

The following workflow provides a high-level decision tree for responding to Linux system alerts.

```text
                  [ Linux Server Alert ]
                            │
                            ▼
              Is the system responsive?
             /                          \
      [ No ]                          [ Yes ]
         │                                 │
         ▼                                 ▼
CHECK KERNEL / HARDWARE           AUDIT RESOURCE TRIAGE
 ├── sudo dmesg -w                 ├── free -h  (RAM saturation)
 └── sudo journalctl -b -p 3       ├── htop     (CPU/Process bottleneck)
                                   └── df -h    (Storage capacity)
                                             │
                                             ▼
                              CHECK DEPENDENT BOUNDARIES
                               ├── systemctl --failed (Daemons)
                               ├── sudo ss -tulnp      (Ports)
                               └── w                   (User sessions)
```

---

# Subsystem Functional Deep Dives

## 1. Hardware Topology and Firmware Discovery

Linux gathers hardware configuration data by querying the SMBIOS/DMI tables exposed by the system firmware and by probing physical hardware buses through the kernel.

### fastfetch / inxi -F

These utilities provide a quick overview of the operating environment.

**fastfetch**

- Fast verification of:
  - Linux distribution
  - Kernel version
  - Desktop environment
  - Shell
  - Terminal
  - Hardware summary

**inxi -F**

Provides a significantly deeper system inventory, including:

- Graphics subsystem
- Xorg or Wayland information
- Audio subsystem
- Network interfaces
- Storage devices
- Power management
- Kernel modules
- Advanced hardware configuration

---

### lshw -short / lscpu

These tools inspect hardware hierarchy and processor architecture.

#### lshw -short

Builds a structural inventory of installed hardware, including:

- Motherboard
- CPU
- Memory
- Storage controllers
- Network adapters
- Graphics devices
- Peripheral hardware

This output is useful for quickly validating detected hardware and identifying missing devices.

#### lscpu

Parses processor information (primarily sourced from `/proc/cpuinfo`) to expose architectural characteristics, including:

- CPU architecture
- Processing cores
- Hardware threads
- Physical sockets
- NUMA topology
- Cache hierarchy
- CPU flags
- Virtualization support
- Hardware vulnerability mitigations

---

### lspci -k / lsusb -v

These commands inspect system buses and verify driver bindings.

#### lspci -k

Displays PCI and PCIe devices together with the kernel modules responsible for managing them.

The `-k` flag is especially important because it reveals:

- Active kernel driver
- Available kernel modules
- Driver binding status

If a hardware device is not functioning correctly, this command confirms whether the appropriate kernel driver successfully attached to the device.

#### lsusb -v

Produces a verbose dump of USB subsystem descriptors, including:

- Vendor information
- Product identifiers
- Device classes
- USB versions
- Interface descriptors
- Endpoint configuration

---

### sudo dmidecode -t memory

Queries the firmware's SMBIOS/DMI tables directly to obtain physical memory information.

Unlike many higher-level utilities, `dmidecode` retrieves firmware-reported hardware metadata without relying on kernel abstractions.

Typical information includes:

- Installed DIMMs
- Memory slot population
- Maximum supported memory
- Module speed
- Manufacturer
- Serial numbers
- Part numbers
- Available expansion slots

> [!WARNING]
> Virtualization environments abstract physical hardware. Running hardware discovery tools inside guest environments such as AWS EC2, Proxmox/KVM virtual machines, VMware guests, VirtualBox, or Docker containers will typically report the virtual hardware presented by the hypervisor (for example, **QEMU Virtual CPU** or **Amazon Nitro**) rather than the underlying bare-metal platform.

---

## 2. Computational Resource Triage and Virtual Memory

System performance degradation generally originates from saturation of one or more primary resources:

- CPU
- RAM
- Storage I/O
- Kernel file descriptors

### free -h

Provides a human-readable snapshot of memory allocation.

When investigating memory pressure or Out-Of-Memory (OOM) conditions, prioritize the **available** field rather than **free**.

Linux intentionally utilizes unused RAM as filesystem cache. As a result, the **free** value commonly approaches zero on healthy production systems and should not, by itself, be interpreted as a memory shortage.

## 2. Computational Resource Triage and Virtual Memory (Continued)

### `vmstat 1`

Displays live kernel statistics related to virtual memory, process scheduling, CPU activity, and I/O. Running the command with an interval of `1` second provides a continuously updating view of system performance.

```bash
vmstat 1
```

The output includes several important categories:

* **Processes**

  * `r` — Number of runnable processes waiting for CPU time.
  * `b` — Number of processes blocked, typically waiting for I/O.

* **Memory**

  * Total usage of memory and buffers.

* **Swap**

  * `si` — Swap-in operations (disk → RAM).
  * `so` — Swap-out operations (RAM → disk).

* **I/O**

  * Block input/output statistics.

* **System**

  * Interrupts and context switches.

* **CPU**

  * User, system, idle, wait, and stolen CPU time.

> [!IMPORTANT]
> When diagnosing performance degradation caused by memory exhaustion, pay close attention to the `si` (swap-in) and `so` (swap-out) columns under the **Swap** section. Persistent non-zero values indicate that the system is actively swapping memory pages between RAM and disk, a condition commonly referred to as **thrashing**. Thrashing significantly degrades system performance because disk access is orders of magnitude slower than physical memory.

---

### `htop`

Provides an interactive, real-time visualization of system processes and resource utilization.

Compared to `top`, `htop` offers a more intuitive interface for monitoring process activity, CPU utilization, memory consumption, and thread behavior.

Key capabilities include:

* Interactive process management
* CPU usage per core
* Memory and swap utilization
* Process tree visualization
* Thread inspection
* Search and filtering
* Process sorting

Important scheduling fields include:

* **NI (Nice Value)** — User-defined scheduling priority.
* **PR (Priority)** — Kernel scheduling priority, including real-time priorities where applicable.

`htop` is especially useful for identifying:

* Runaway processes
* CPU bottlenecks
* Memory-heavy applications
* Zombie processes
* Thread-intensive workloads

---

### `sudo iotop`

Monitors disk Input/Output activity on a per-process basis.

```bash
sudo iotop
```

While utilities such as `df` report storage capacity, they provide no visibility into storage performance. `iotop` fills this gap by displaying real-time disk read and write operations performed by individual processes.

Typical use cases include identifying:

* Excessive disk writes
* Storage-intensive applications
* Backup jobs
* Database workloads
* Log-heavy services
* Unexpected disk activity

This is particularly valuable when investigating systems experiencing:

* High disk latency
* Slow application response
* Elevated I/O wait (`wa`)
* Storage controller saturation

---

### `uptime / mpstat`

These commands evaluate overall processor load and CPU utilization.

#### `uptime`

Displays:

* Current system time
* System uptime
* Logged-in users
* Load averages over:

  * 1 minute
  * 5 minutes
  * 15 minutes

Example:

```bash
uptime
```

The load averages represent the number of tasks that are either:

* Runnable (`R` state), or
* In uninterruptible sleep (`D` state), usually waiting on disk I/O.

#### `mpstat -P ALL`

Displays CPU utilization for every logical processor individually.

```bash
mpstat -P ALL
```

This command is useful for identifying:

* Hot CPU cores
* Uneven scheduler distribution
* NUMA imbalance
* Thread pinning issues
* Processor affinity problems

> [!NOTE]
> System load averages represent the number of processes in either the runnable (`R`) state or the uninterruptible sleep (`D`) state, typically while waiting for disk I/O. On an 8-core processor, a load average of **8.00** indicates that all available processing capacity is fully utilized. A sustained load average of **16.00** indicates that the scheduler queue contains roughly twice as many runnable tasks as the system can execute simultaneously.

---

# 3. Storage Systems and Filesystem Attributes

Linux maps block storage devices to mounted filesystems, identifying volumes through universally unique identifiers (UUIDs) and maintaining their relationships within the Virtual Filesystem (VFS) layer.

---

### `df -h / du -sh * | sort -h`

These commands are commonly used together to identify storage consumption.

#### `df -h`

Displays filesystem usage in a human-readable format.

```bash
df -h
```

Use this command to determine:

* Filesystem capacity
* Used space
* Available space
* Mount points
* Storage utilization percentage

#### `du -sh * | sort -h`

After identifying a filesystem nearing capacity, navigate to its mount point and run:

```bash
du -sh * | sort -h
```

This command:

* Calculates directory sizes
* Sorts them from smallest to largest
* Helps locate directories consuming excessive storage

Together, these commands provide an efficient workflow for locating disk space issues.

---

### `findmnt`

Displays the current mount hierarchy maintained by the kernel.

```bash
findmnt
```

Unlike `df`, `findmnt` focuses on filesystem relationships and mount configuration rather than storage capacity.

Information includes:

* Mount tree
* Source devices
* Target mount points
* Filesystem types
* Mount options
* Read-only (`ro`) status
* Bind mounts
* Network filesystems (NFS/SMB)
* Temporary filesystems

This command is particularly useful for troubleshooting mount failures or verifying complex storage layouts.

---

### `lsattr / chattr`

These utilities manage filesystem-level attributes maintained by the filesystem driver.

#### `lsattr`

Displays special filesystem attributes associated with files and directories.

```bash
lsattr <filename>
```

Common attributes include:

* Immutable (`i`)
* Append-only (`a`)
* No dump (`d`)
* Synchronous updates (`S`)

These attributes exist independently of standard Unix file permissions.

#### `chattr`

Modifies filesystem attributes.

Example:

```bash
sudo chattr -i <filename>
```

This removes the immutable attribute, allowing the file to be modified or deleted.

> [!TIP]
> If an administrative user cannot modify or delete a file—even when operating with root privileges using commands such as `sudo rm -rf`—inspect the file attributes using `lsattr <filename>`. If the immutable (`i`) attribute is set, the filesystem itself prevents modification until the attribute is explicitly removed with `sudo chattr -i <filename>`.

---

# 4. Network Architecture and Socket States

Modern Linux distributions have largely replaced the legacy **net-tools** suite (`ifconfig`, `netstat`, and `route`) with the more capable and actively maintained **iproute2** infrastructure.

---

### `ip a / ip r`

These commands inspect network interfaces and the kernel routing table.

#### `ip a`

Displays the complete network interface configuration, including:

* Interface names
* Operational state
* MAC addresses
* IPv4 addresses
* IPv6 addresses
* Broadcast addresses
* Interface flags

Use this command to verify:

* Whether an interface is up
* Assigned IP addresses
* Interface status
* Layer 2 (MAC) addressing

Example:

```bash
ip a
```

---

#### `ip r`

Displays the kernel routing table.

```bash
ip r
```

This output includes:

* Default gateway
* Directly connected networks
* Static routes
* Dynamic routes
* Route metrics

This command is particularly useful when diagnosing:

* Gateway configuration issues
* Missing routes
* Network reachability problems
* Multi-homed systems

---

### `ip -s link`

Displays interface statistics together with packet counters and error metrics.

```bash
ip -s link
```

While `ip a` focuses on interface configuration, the `-s` option instructs the kernel to include operational statistics.

Important fields include:

* RX packets
* TX packets
* RX bytes
* TX bytes
* RX errors
* TX errors
* Dropped packets
* Overruns
* Carrier errors
* Collisions (where applicable)

Pay particular attention to:

* `RX errors`
* `TX errors`
* `dropped`
* `overrun`

Increasing values often indicate:

* Driver issues
* Faulty hardware
* Buffer exhaustion
* Network congestion
* Interface misconfiguration

---

### `sudo ss -tulnp`

Audits listening sockets maintained by the Linux networking stack.

```bash
sudo ss -tulnp
```

This command displays active listening services together with the process that owns each socket.

Flag breakdown:

| Flag | Description                                             |
| ---- | ------------------------------------------------------- |
| `t`  | Display TCP sockets                                     |
| `u`  | Display UDP sockets                                     |
| `l`  | Show listening sockets only                             |
| `n`  | Display numerical addresses without DNS resolution      |
| `p`  | Display the associated Process ID (PID) and daemon name |

Typical uses include:

* Identifying listening services
* Verifying service startup
* Confirming bound ports
* Detecting unexpected listeners
* Troubleshooting firewall or connectivity issues

---

### `sudo lsof -i`

Linux treats network sockets as file descriptors. The `lsof` utility inspects open file descriptors to identify which process owns a network connection or listening socket.

Example:

```bash
sudo lsof -i :
```

Typical information includes:

* Process name
* PID
* User
* Protocol
* Local address
* Remote address
* Port
* Connection state

This command is especially useful when determining which application is currently occupying a specific network port.

---

### `dig / host`

These utilities query DNS servers directly to validate name resolution.

Unlike common client utilities, they bypass many local resolver caches and focus on authoritative DNS responses.

---

#### `dig`

Provides detailed DNS query information.

Example:

```bash
dig example.com
```

Useful for inspecting:

* A records
* AAAA records
* MX records
* TXT records
* NS records
* SOA records
* DNS response timing
* Authority sections

---

#### `host`

Offers a simplified interface for DNS lookups.

Example:

```bash
host example.com
```

Useful for quickly verifying:

* Forward DNS resolution
* Reverse DNS lookups
* Mail server records

Together, `dig` and `host` help isolate:

* DNS configuration errors
* Upstream resolver issues
* Incorrect DNS records
* Routing problems affecting name resolution

---

# 5. Access Management, Identity, and Init States

Auditing system access involves verifying active users, security identities, process limits, historical logins, and the operational state of background services.

---

### `systemctl --failed`

Queries the systemd service manager for failed units.

```bash
systemctl --failed
```

This command reports services and targets that:

* Failed during boot
* Crashed after startup
* Entered a failed state
* Require administrative attention

Reviewing failed units is often one of the first steps when troubleshooting system initialization problems.

---

### `ulimit -a`

Displays the current resource limits applied to the active shell session.

```bash
ulimit -a
```

Linux enforces resource boundaries on user processes to prevent excessive resource consumption.

Common limits include:

* Maximum open files (`open files (-n)`)
* Maximum user processes
* Stack size
* Core file size
* Locked memory
* File size
* Virtual memory

If applications such as databases or web servers report **"Too many open files"**, verify the current **open files (`-n`)** limit using this command.

---

### `w / who -a`

These utilities display information about currently logged-in users.

---

#### `w`

Displays:

* Logged-in users
* Source IP addresses
* Login time
* Idle time
* CPU usage
* Active command
* Associated pseudo-terminal (`pts`)

Example:

```bash
w
```

---

#### `who -a`

Provides a broader overview of login sessions and system state.

Example:

```bash
who -a
```

This includes:

* Login sessions
* Run-level information
* Boot time
* Init process information
* Terminal state

Together, these commands are useful for auditing active user sessions and investigating system access.

---

### `last -n 10`

Reads the binary `/var/log/wtmp` database and displays recent login history.

```bash
last -n 10
```

Typical entries include:

* User logins
* User logouts
* SSH sessions
* Console sessions
* System boots
* System shutdowns
* Reboots

Because `last` reads the login database in reverse chronological order, it provides a concise history of recent system activity.

---

### `id`

Displays the security identity of the current user or another specified account.

```bash
id
```

The output includes:

* Real User ID (UID)
* Effective User ID
* Primary Group ID (GID)
* Supplementary groups

This command is frequently used to verify:

* Group membership
* Administrative privileges
* Effective execution context
* Permission-related issues

---

# 6. Kernel Space Logs and Low-Level Debugging

When application-level logs are insufficient for diagnosing system behavior, administrators should inspect the kernel's logging facilities. The Linux kernel continuously records hardware events, driver activity, filesystem messages, and critical system conditions that may never appear in application logs.

---

### `sudo journalctl -b -xe`

Queries the **systemd journal** for the current boot session.

```bash
sudo journalctl -b -xe
```

Flag breakdown:

| Flag | Description                                                          |
| ---- | -------------------------------------------------------------------- |
| `-b` | Display logs from the current boot only.                             |
| `-x` | Include additional explanatory text for log entries where available. |
| `-e` | Jump directly to the end of the journal output.                      |

This command is particularly useful when investigating:

* Failed services
* Boot failures
* Authentication problems
* Filesystem issues
* Driver initialization failures
* Kernel messages captured by systemd
* Service dependency failures

Using `-b` narrows the investigation to the active boot session, eliminating noise from previous boots and making troubleshooting significantly easier.

---

### `sudo dmesg -w`

Monitors the kernel ring buffer in real time.

```bash
sudo dmesg -w
```

Unlike `journalctl`, which queries the persistent systemd journal, `dmesg` displays messages generated directly by the Linux kernel.

Typical events include:

* Hardware detection
* Driver initialization
* PCIe device events
* USB device connections
* Storage controller activity
* Filesystem mount operations
* Filesystem corruption
* Network driver events
* Kernel warnings
* Kernel panics
* Memory allocation failures

One of the most important uses of `dmesg` is identifying **Out-Of-Memory (OOM) Killer** events. When the system exhausts available memory, the kernel may forcibly terminate one or more processes to recover resources. These events are recorded in the kernel ring buffer and can be viewed immediately using `dmesg -w`.

Running the command with the `-w` flag keeps the output open and continuously streams new kernel messages as they occur, making it especially useful during hardware testing, driver debugging, and live troubleshooting.

---

# System Architecture Reference Matrix

The following table summarizes the relationship between common inspection targets, their underlying Linux data sources, and the primary utilities used to audit them.

| Inspection Target                        | Data Source Layer                 | Primary Audit Tool        |
| ---------------------------------------- | --------------------------------- | ------------------------- |
| **Chassis and SMBIOS Specifications**    | Motherboard DMI Tables            | `sudo dmidecode` / `lshw` |
| **Bus Topology (PCIe, NVMe, GPU)**       | PCI Configuration Space           | `lspci -k`                |
| **RAM Allocation and Page Buffers**      | `/proc/meminfo`                   | `free -h`                 |
| **Virtual Memory Paging Rates**          | Page Cache Activity Profiles      | `vmstat 1`                |
| **Processor Microarchitecture**          | `/proc/cpuinfo`                   | `lscpu`                   |
| **Filesystem Storage and Mounts**        | Virtual Filesystem (VFS) Layer    | `df -h` / `findmnt`       |
| **Network Interface Packet Health**      | Socket Buffer Hardware Statistics | `ip -s link`              |
| **Network Sockets and Port Bindings**    | Kernel Network Stack              | `ip a` / `sudo ss -tulnp` |
| **Kernel Execution and Hardware Faults** | Kernel Ring Buffer                | `sudo dmesg -w`           |
| **Process Shell Resource Enforcement**   | Session Resource Limits           | `ulimit -a`               |
| **Active Process Environments**          | `/proc/[PID]/` Virtual Filesystem | `htop` / `w`              |

---

# Quick Reference Summary

The following workflow provides a practical sequence for investigating Linux system issues:

1. **Verify system responsiveness**

   * Use `dmesg` and `journalctl` to inspect kernel and boot-time failures.

2. **Assess resource utilization**

   * Check memory with `free -h`.
   * Monitor processes using `htop`.
   * Evaluate CPU load with `uptime` or `mpstat`.
   * Inspect disk activity using `iotop`.

3. **Evaluate storage health**

   * Identify filesystem usage with `df -h`.
   * Locate large directories using `du`.
   * Review mounted filesystems using `findmnt`.

4. **Inspect networking**

   * Verify interfaces with `ip a`.
   * Review routing using `ip r`.
   * Audit packet statistics with `ip -s link`.
   * Check listening ports using `ss`.
   * Identify port ownership with `lsof`.
   * Validate DNS resolution using `dig` or `host`.

5. **Audit users and services**

   * Review failed services with `systemctl --failed`.
   * Verify resource limits using `ulimit -a`.
   * Inspect logged-in users with `w` or `who -a`.
   * Review login history with `last`.
   * Confirm user identity and group membership with `id`.

6. **Investigate kernel-level events**

   * Use `journalctl` for persistent system logs.
   * Monitor live kernel events with `dmesg -w`.

---
