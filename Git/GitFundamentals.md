# Git Fundamentals

## Introduction

Modern software projects are constantly changing. New features are added, bugs are fixed, code is refactored, and experiments are conducted. Without a system to track these changes, managing a project quickly becomes difficult.

Imagine working on a project for several weeks. One day, you accidentally delete an important function or introduce a bug that breaks the application. Without a record of previous versions, recovering your work may be impossible.

A common beginner's solution is to create multiple copies of the project:

```
Project/
Project_Final/
Project_Final2/
Project_Final_Updated/
Project_Final_Updated_ReallyFinal/
```

While this approach works for very small projects, it quickly becomes confusing and inefficient. It becomes difficult to determine which version is the latest, what changes were made, or who made them when working in a team.

Version Control Systems (VCS) were created to solve these problems.

---

## What is a Version?

A version is a particular state of a project at a specific point in time.

For example:

Version 1
- Login page

Version 2
- Added registration page

Version 3
- Fixed login bug

Each version represents the project after a set of changes.

Git stores these versions so they can be revisited at any time.
---

## What is Version Control?

A **Version Control System (VCS)** is software that records changes made to files over time. Instead of creating multiple copies of a project, a VCS stores the complete history of modifications.

This allows developers to:

- Track every change made to a project.
- Restore previous versions if something breaks.
- Compare different versions of files.
- Work on new features without affecting stable code.
- Collaborate with multiple developers safely.

Think of version control as an unlimited **Undo** button for an entire project.

---

## Why Do We Need Version Control?

Without a Version Control System, managing software projects becomes increasingly difficult as they grow.

Some common problems include:

- Accidentally deleting important code.
- Overwriting someone else's changes in a team project.
- Forgetting what changes were made and why.
- Being unable to restore a previous working version.
- Difficulty identifying when a bug was introduced.
- Maintaining multiple copies of the same project with unclear names.
- No reliable history of who made specific changes.

A Version Control System solves these problems by maintaining a structured history of the project while allowing developers to safely experiment, collaborate, and recover from mistakes.

---

## Evolution of Version Control Systems

Version control systems have evolved over time to address the limitations of earlier approaches.

### Local Version Control Systems (LVCS)

The earliest systems stored version history only on the developer's computer.

```
Developer
    │
 Local Version History
```

Although this was better than manually creating project copies, it had significant limitations:

- History was unavailable on other computers.
- Collaboration was difficult.
- Hardware failures could result in complete data loss.

---

### Centralized Version Control Systems (CVCS)

To improve collaboration, centralized systems introduced a shared server that stored the project's history.

```
          Central Server
         /      |      \
      Dev A   Dev B   Dev C
```

Examples:

- Subversion (SVN)
- Perforce

Advantages:

- Easier collaboration.
- Centralized project history.
- Simpler administration.

Disadvantages:

- Single point of failure.
- Limited offline functionality.
- Developers depend on the central server.

---

### Distributed Version Control Systems (DVCS)

Git belongs to this category.

Instead of relying entirely on a central server, every developer has a complete copy of the repository and its entire history.

```
Developer A  <------>  GitHub  <------>  Developer B
      ↑                                ↑
 Complete Repository             Complete Repository
```

This approach offers several advantages:

- Full project history on every machine.
- Most operations work offline.
- Faster performance.
- Better reliability.
- Easier branching and merging.

Distributed Version Control Systems have become the standard choice for modern software development.

---

## What is Git?

Git is a **Distributed Version Control System (DVCS)** created to efficiently track changes in files and coordinate work between developers.

Git was designed with four primary goals:

- Speed
- Data integrity
- Efficient branching
- Distributed collaboration

Unlike cloud services, Git itself is software installed on your computer. It works entirely locally unless you choose to connect it to a remote repository.

Git stores snapshots of your project rather than recording only individual file differences. Each commit represents the state of the project at a particular point in time.

---

## What Does Git Track?

Git is designed to track changes made to a project's contents.

Git can track:

- Files
- File modifications
- File deletions
- File renames
- Directory structure (through tracked files)
- Branches
- Commits
- Tags

Git does **not** automatically track every file in a project.

A file must first be added to Git before it becomes part of the repository's history.

Some files are intentionally excluded from tracking, such as:

- Build output
- Temporary files
- Log files
- Dependency caches
- IDE configuration files

These are commonly excluded using a `.gitignore` file, which will be discussed later.

---
## Brief History of Git

Git was created in **2005** by **Linus Torvalds**, the creator of the Linux kernel.

Before Git, Linux kernel development relied on another version control system called **BitKeeper**. When licensing issues arose, the Linux community needed a replacement that was:

- Fast
- Reliable
- Distributed
- Free and open source

Linus Torvalds designed Git to meet these requirements, and it has since become the most widely used version control system in software development.

---

## Features of Git

Some of Git's most important features include:

### Fast

Git performs most operations locally, making common tasks extremely fast.

### Distributed

Every repository contains the complete project history.

### Reliable

Git uses cryptographic hashing to protect data integrity.

### Lightweight Branching

Creating and switching branches is almost instantaneous.

### Offline Development

Most Git operations work without an internet connection.

### Open Source

Git is free to use and actively maintained by a large community.

---

## Why is Git Fast?

Git performs most operations locally because every repository contains its complete history.

Unlike centralized systems that frequently communicate with a server, Git can perform many tasks without an internet connection.

Examples of local operations include:

- Viewing commit history
- Creating commits
- Creating branches
- Switching branches
- Comparing changes
- Merging branches

Since these operations do not require network communication, Git is exceptionally fast.

---

## Data Integrity in Git

One of Git's most important design principles is **data integrity**.

Every object stored by Git—including commits, files, and trees—is identified using a unique cryptographic hash known as a **SHA hash**.

Example:

```
e83c5163316f89bfbde7d9ab23ca2e25604af290
```

This hash uniquely identifies an object based on its contents.

If the contents change, the hash also changes.

This allows Git to:

- Detect accidental corruption.
- Ensure project history remains consistent.
- Identify commits uniquely.
- Verify data integrity across repositories.

You'll encounter these hashes frequently when viewing commit history.

---

## Common Git Terminology

Before working with Git, it's useful to become familiar with a few commonly used terms.

| Term | Description |
|------|-------------|
| Repository (Repo) | A Git-managed project containing files and history. |
| Commit | A snapshot of the project at a specific point in time. |
| Branch | An independent line of development. |
| Clone | A local copy of an existing repository. |
| Remote | Another copy of the repository stored elsewhere. |
| Origin | The default name given to the primary remote repository. |
| HEAD | A reference to the currently checked-out commit or branch. |

These concepts will be explored in greater detail throughout the following chapters.

---

## Git vs GitHub

One of the most common beginner misconceptions is treating Git and GitHub as the same thing.

They are related but different.

| Git | GitHub |
|------|---------|
| Version control software | Cloud hosting platform |
| Installed on your computer | Accessible through the internet |
| Tracks project history | Hosts Git repositories |
| Works offline | Requires internet for synchronization |
| Can exist without GitHub | Uses Git repositories |

An easy analogy:

- Git = Microsoft Word
- GitHub = Google Drive

You can write documents in Microsoft Word without using Google Drive. Similarly, you can use Git without GitHub.

GitHub simply provides online storage and collaboration features for Git repositories.

Other Git hosting platforms include:

- GitLab
- Bitbucket
- Azure DevOps

---

## What is a Repository?

A **repository**, often shortened to **repo**, is the storage location managed by Git.

A repository contains:

- Project files
- Complete commit history
- Branch information
- Tags
- Configuration
- Metadata required by Git

There are two common types of repositories:

### Local Repository

Stored on your own computer.

You can work with it entirely offline.

### Remote Repository

Stored on another computer or cloud service such as GitHub.

It allows multiple developers to share and synchronize their work.

Most projects have one local repository and one or more remote repositories.

---

## Git Isn't Just for Source Code

Although Git is widely used for software development, it can manage almost any text-based project.

Common examples include:

- Programming projects
- Documentation
- Markdown notes
- Books
- Technical manuals
- LaTeX documents
- Configuration files
- Personal knowledge bases

Git is particularly effective for text-based content because it can efficiently detect and record line-by-line changes between versions.

---
## Installing Git

Download Git from the official website:

https://git-scm.com/

Choose the installer for your operating system and complete the installation using the default settings unless you have specific requirements.

After installation, verify that Git is available by running:

```bash
git --version
```

Example:

```text
git version 2.50.1
```

If you see a version number, Git has been installed successfully.

---

## Configuring Git

Before creating commits, Git should know who you are. Configure your username and email once using:

```bash
git config --global user.name "Your Name"

git config --global user.email "your@email.com"
```

These values become part of the metadata stored in every commit you create.

You can verify your configuration using:

```bash
git config --list
```

---

## The Typical Git Workflow

Most Git projects follow a simple workflow.

```
Create or Clone Repository
           │
           ▼
      Edit Files
           │
           ▼
     Select Changes
           │
           ▼
     Create a Commit
           │
           ▼
Repeat Development Cycle
           │
           ▼
Synchronize with GitHub
```

Although this workflow appears simple, each stage involves important concepts that will be explored in the following chapters.

---

## Summary

You should now understand:

- Why version control is necessary.
- The difference between centralized and distributed version control.
- What Git is and why it was created.
- The difference between Git and GitHub.
- What repositories are.
- How to install Git.
- How to configure Git for the first time.

At this point, Git is installed and ready to use.

The next step is understanding **how Git internally tracks every file you modify**. Before creating your first repository and making commits, it's important to understand Git's workflow and the different areas that every file passes through.
