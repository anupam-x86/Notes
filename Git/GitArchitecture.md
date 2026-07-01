# Git Architecture

## Understanding How Git Thinks Internally

Now that you understand what Git is and why it exists, the next step is to understand how Git actually works behind the scenes.

Most beginners think Git simply "saves files", but Git does something more structured. It does not track your project as a collection of files in real time. Instead, it manages a system of **snapshots** that move through defined stages before becoming part of the project history.

To use Git effectively, you must understand this internal workflow.

---

## The Four Areas of Git

Git organizes your work into four main areas:

### 1. Working Directory
### 2. Staging Area (Index)
### 3. Local Repository
### 4. Remote Repository

Each area represents a different state of your project.

---

## 1. Working Directory

This is the area where you actively work.

It contains:
- Project files you can see and edit
- Source code
- Documents
- Any untracked or modified files

When you open a project folder, you are looking at the Working Directory.

At this stage:
- Changes exist only on your machine
- Git may or may not be aware of changes yet

---

>[!NOTE]
> ## Tracked vs Untracked Files
>
> Git does not automatically track every file in your project.
>
> Files in the Working Directory are classified as:
>
> ### Untracked files
> - Git is not monitoring them yet
> - They are not part of version history
> 
> ### Tracked files
> - Git is already aware of them
> - Their changes are monitored

Only tracked files can move into the staging area.

---

## 2. Staging Area (Index)

The Staging Area is an intermediate area between your working files and your commit history.

It acts as a **preparation space**.

Instead of saving everything immediately, Git allows you to select exactly what should go into the next commit.

Example:

You modify three files:

```
file1.cpp
file2.cpp
file3.cpp
```

But you only want to commit two of them.

You place only selected changes into the staging area.

This gives you control over what each commit represents.

---

## 3. Local Repository

Once changes are committed, they are stored in the Local Repository.

This is where Git keeps:
- Full project history
- All commits
- Branches
- Tags

Each commit is a **snapshot of the entire project at a point in time**.

Important:
- This is still on your computer
- No internet is required
- You can navigate history freely

---

## 4. Remote Repository

The Remote Repository is a version of your project stored on another system (usually a server).

Examples:
- GitHub
- GitLab
- Bitbucket

It allows:
- Backup of your project
- Collaboration with others
- Sharing code across machines

The remote repository is not automatically updated. You must explicitly push changes to it.

---

## Git Workflow (How Data Moves)

The flow of data in Git follows a strict path:

```
Working Directory
        │
        ▼
   Staging Area
        │
        ▼
 Local Repository
        │
        ▼
 Remote Repository
```

Each step requires an explicit action from the user.

---

## Git is Not Automatic

A key concept beginners often miss:

Git does not automatically save your work.

You must explicitly tell Git:

- What to track
- What to stage
- What to commit
- What to send to remote

This is why Git is powerful—it gives you full control over history creation.

---
## HEAD (Current Position in Git)

Git uses a pointer called **HEAD** to track your current position in history.

>[!IMPORTANT]
> HEAD usually points to a **branch**, not directly to a commit.

Example:

```
HEAD → main → latest commit
```

When you switch branches, HEAD moves with it.

If you checkout a specific commit directly, Git enters a **detached HEAD state**.

We will explore this in detail in branching.
---

## How Git Stores Data

Git does NOT store file differences like traditional systems.

Instead, Git stores **snapshots**.

Each commit contains:
- A full snapshot of the project
- Metadata (author, time, message)
- A reference to previous commits

This makes Git:
- Fast
- Reliable
- Easy to restore

---

## Why This Architecture Matters

Understanding this structure helps you:

- Know exactly where your changes are
- Avoid losing work
- Understand staging vs committing
- Debug Git issues confidently
- Work efficiently with branches and remotes

---

## Visual Summary

```
Edit files
   ↓
Working Directory
   ↓
git add
   ↓
Staging Area
   ↓
git commit
   ↓
Local Repository
   ↓
git push
   ↓
Remote Repository
```

---
