# Fedora Day 1 Setup

**Date:** 2026-06-03

## Objective

Install Fedora as a dual-boot operating system alongside Windows and set up a complete development environment for learning Linux, programming, Git, and future BTech CSE studies.

---

# Hardware

## Laptop

* ASUS Vivobook K3605VC
* RAM: 16 GB
* CPU: Intel Core i5-13420H
* GPU:

  * NVIDIA GeForce RTX 3050 Laptop GPU (4 GB)
  * Intel UHD Graphics
* SSD: 512 GB

---

# Initial Disk Layout

The laptop originally contained only Windows.

Total SSD size:

* 512 GB

After shrinking the Windows partition:

| Partition                 | Size     |
| ------------------------- | -------- |
| Windows                   | ~250 GB  |
| Fedora                    | ~225 GB  |
| EFI & Recovery Partitions | Existing |

---

# Fedora Installation

## Chosen Distribution

Fedora Workstation 44

## Desktop Environment

GNOME

### Why GNOME?

* Default Fedora experience
* Large community support
* Stable and polished
* Most Fedora documentation assumes GNOME

---

# Dual Boot Setup

Fedora was installed alongside Windows.

Both operating systems share the same SSD but use separate partitions.

Boot selection occurs during system startup.

---

# UEFI

## What I Learned

UEFI (Unified Extensible Firmware Interface) is firmware that starts before the operating system.

Boot process: Power Button → UEFI → Boot Manager → Windows / Fedora

My laptop uses UEFI instead of Legacy BIOS.

---

# Secure Boot

## Decision

Kept Secure Boot enabled.

## What I Learned

Secure Boot verifies trusted software before it is loaded during startup.

This increases security but can complicate third-party driver installation.

---

# NVIDIA Driver Installation

## GPU

NVIDIA GeForce RTX 3050 Laptop GPU

## Problem Encountered

After installing NVIDIA drivers:

NVIDIA-SMI has failed because it couldn't communicate with the NVIDIA driver.

During boot I also saw:

NVIDIA kernel module missing.

Running:

modprobe nvidia

returned:

Key was rejected by service

## Cause

The NVIDIA kernel module was not trusted by Secure Boot.

## Solution

1. Installed NVIDIA drivers from RPM Fusion.
2. Generated a Machine Owner Key (MOK).
3. Imported the key.
4. Enrolled the key during boot.
5. Rebuilt NVIDIA kernel modules.
6. Rebooted.

## Verification

Command:

nvidia-smi

Output confirmed:

* Driver Version: 595.71.05
* CUDA Version: 13.2
* RTX 3050 detected successfully

Result:

NVIDIA drivers working correctly with Secure Boot enabled.

---

# Machine Owner Key (MOK)

## What I Learned

MOK stands for Machine Owner Key.

It allows users to add their own trusted signing certificates to Secure Boot.

This made it possible to use proprietary NVIDIA drivers without disabling Secure Boot.

---

# Development Environment Setup

## Installed Tools

### C++

* gcc
* gcc-c++

### Build Tools

* make

### Python

* python3
* python3-pip

### Version Control

* git

### Editor

* Visual Studio Code

---

# Git and GitHub Setup

## Tasks Completed

* Configured Git username
* Configured Git email
* Generated SSH key
* Added SSH key to GitHub
* Verified SSH authentication
* Created first repository
* Successfully pushed commits to GitHub

## Basic Workflow Learned

git status

git add .

git commit -m "message"

git push

## What I Learned

Git is a version control system.

GitHub hosts Git repositories online.

A commit represents a snapshot of a project at a specific point in time.

---

# Linux Concepts Encountered

During the first day I encountered the following concepts:

* Partitions
* UEFI
* Secure Boot
* MOK Enrollment
* Kernel Modules
* NVIDIA Drivers
* Terminal Commands
* Git
* GitHub
* SSH Keys

These concepts are not fully understood yet and require further study.

---

# Lessons Learned

* Linux troubleshooting often involves reading error messages carefully.
* Secure Boot and NVIDIA drivers can work together when modules are properly signed.
* GitHub authentication through SSH is more convenient than using passwords.
* Understanding concepts is more important than memorizing commands.
* Fedora provides a strong environment for programming and learning Linux.

---

# Day 1 Outcome

Successfully achieved:

* Fedora installation
* Dual boot with Windows
* NVIDIA driver setup
* Secure Boot enabled
* Git and GitHub configuration
* VS Code installation
* Python development setup
* C++ development setup

Status:

Fedora system fully operational and ready for learning Linux, C++, Python, Git, and future software development.
