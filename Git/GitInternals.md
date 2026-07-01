# Git Internals

> [!NOTE]
> **Purpose:** Understand how Git stores data internally. This chapter focuses on Git's architecture rather than day-to-day commands.

---

## 🎯 Why should I care?

Understanding Git internals helps you:

- Debug Git problems
- Understand why commands behave the way they do
- Appreciate Git's performance
- Learn how distributed version control actually works
- Build a stronger systems mindset

You don't need to memorize every detail, but knowing the architecture makes advanced Git much easier.

---

## Prerequisites

- Git Fundamentals
- Commits
- Branching and Merging
- Git History
- Git Recovery (recommended)

---

# Table of Contents

## Part 1 — The `.git` Directory

## Part 2 — Git Objects
- Blob
- Tree
- Commit
- Tag

## Part 3 — References
- HEAD
- Branches
- Tags

## Part 4 — The Index (Staging Area)

## Part 5 — Object Database

## Part 6 — Packfiles

## Cheat Sheet

## Related Notes

---

# Part 1 — The `.git` Directory

> [!NOTE]
>
> Every Git repository contains a hidden `.git` directory.
>
> It stores:
>
> - Repository history
> - Branches
> - Commits
> - Configuration
> - Objects
> - References

---

## What is `.git`?

When you run:

```bash
git init
```

Git creates:

```
project/

├── .git/
├── src/
├── README.md
└── ...
```

The `.git` folder is the **entire Git repository**.

Your project files are **not** the repository.

The repository lives inside:

```
.git/
```

---

## Think of it like this

```
Project Files
        │
        ▼
Working Directory

----------------------

Git Database

↓

.git/
```

The working directory contains your editable files.

The `.git` directory stores Git's data.

---

## What's Inside?

Typical structure:

```
.git/

├── HEAD
├── config
├── objects/
├── refs/
├── logs/
├── hooks/
├── index
└── ...
```

We'll learn what each of these does throughout this chapter.

---

## Why is `.git` Important?

Without `.git`:

- No commits
- No branches
- No history
- No tags
- No version control

Deleting `.git` removes Git tracking from the project.

> **⚠️ Note:** Your project files remain, but Git history is lost unless you have another copy (e.g., on GitHub).

---

## Key Takeaways

- `.git` is the heart of every Git repository.
- It stores Git's metadata and history.
- Your project files and Git's database are separate.

---

# Part 2 — Git Objects

> [!NOTE]
>
> Git stores **everything** as objects.
>
> There are only **4 object types**:
>
> - Blob → File contents
> - Tree → Directory structure
> - Commit → Snapshot + metadata
> - Tag → Named reference
>
> Everything else is built on top of these.

---

## Git's Storage Model

Unlike many version control systems, Git doesn't store "changes".

Instead, it stores **objects**.

```
Project

↓

Git Objects

├── Blob
├── Tree
├── Commit
└── Tag
```

Think of these as the building blocks of Git.

---

# Blob Object

## What is a Blob?

A **Blob** stores the contents of a file.

It does **not** store:

- filename
- directory
- permissions
- commit information

It only stores the file's data.

Example:

```
hello.cpp

↓

#include <iostream>

↓

Blob
```

---

### Important

If two files have **identical contents**:

```
a.txt

Hello
```

```
b.txt

Hello
```

Git stores **only one Blob**.

```
Blob

Hello
```

This saves storage.

---

# Tree Object

## What is a Tree?

A **Tree** represents a directory.

It stores:

- filenames
- folders
- Blob references
- Tree references

Example:

```
project/

├── main.cpp
├── README.md
└── src/
    └── app.cpp
```

Internally:

```
Tree

├── Blob → README.md
├── Blob → main.cpp
└── Tree → src
```

Notice:

Trees don't store file contents.

They point to Blobs.

---

# Commit Object

## What is a Commit?

A Commit is **not** your files.

A Commit stores metadata about a snapshot.

It contains:

- Author
- Date
- Commit message
- Parent commit
- Reference to a Tree

```
Commit

↓

Tree

↓

Blobs
```

---

### Visual

```
Commit

↓

Tree

├── Blob
├── Blob
└── Tree

        ↓

      Blob
```

The Commit points to a Tree.

The Tree points to Blobs.

---

## Why is this useful?

Suppose you change only:

```
README.md
```

Git creates:

- new Blob
- new Tree
- new Commit

Unchanged Blobs are reused.

Git does **not** copy the whole project again.

This makes Git extremely efficient.

---

# Tag Object

A Tag stores information about a release.

Example:

```
v1.0

↓

Commit
```

Annotated Tags also store:

- Tag name
- Creator
- Date
- Message

---

# Relationship Between Objects

Everything connects like this:

```
Commit

↓

Tree

├── Blob
├── Blob
└── Tree

        ↓

      Blob
```

Remember:

- Commits point to Trees.
- Trees point to Blobs.
- Tags point to Commits.

---

## Object NOTE

| Object | Stores |
|---------|--------|
| Blob | File contents |
| Tree | Directory structure |
| Commit | Snapshot metadata |
| Tag | Named reference to a commit |

---

> [!TIP]
> Git doesn't think in terms of files and folders first.
>
> It thinks in terms of **objects connected together**.

---

## Common Misconceptions

❌ A Commit stores every file separately.

✔ A Commit points to a Tree.

---

❌ Trees contain file contents.

✔ Trees contain references to Blobs and other Trees.

---

❌ A Blob knows its filename.

✔ A Blob stores only file contents.

---

## Key Takeaways

- Git stores data as objects.
- There are only four object types.
- Blobs store file contents.
- Trees store directory structure.
- Commits point to Trees.
- Tags point to Commits.
- Object reuse is one reason Git is fast and storage-efficient.

---

# Part 3 — References

> [!NOTE]
>
> References (refs) are **named pointers** to Git objects.
>
> Common references:
>
> - Branches
> - Tags
> - HEAD
>
> References make it easy to access commits without remembering commit hashes.

---

## Why References?

Imagine remembering this commit every time:

```
8d3f7c2b8b5e91f4d...
```

Not practical.

Instead, Git lets you use names.

```
main

↓

Commit
```

The branch name **points** to the latest commit.

---

# Branch References

A branch is simply a reference to a commit.

Example:

```
main

↓

A ── B ── C
          ▲
          │
        main
```

Here:

- `main` points to commit **C**.

Nothing more.

---

## What Happens After a Commit?

Suppose you commit again.

Before:

```
A ── B ── C
          ▲
        main
```

After:

```
A ── B ── C ── D
               ▲
             main
```

Git simply moves the branch reference.

The older commits remain unchanged.

---

# HEAD

## What is HEAD?

`HEAD` represents **your current location** in the repository.

Usually:

```
HEAD

↓

main

↓

Commit D
```

Think of it as:

> "Where am I currently working?"

---
## HEAD and Branch Relationship

> [!SUMMARY]
>
> `HEAD` usually points to a **branch**, and the branch points to the latest commit.
>
> Only in a **Detached HEAD** state does `HEAD` point directly to a commit.

---

### Normal State

```
HEAD
 │
 ▼
main
 │
 ▼
Commit D
```

In this state:

- `HEAD` points to the current branch.
- The branch points to the latest commit.
- New commits move the branch forward automatically.

---

### Detached HEAD State

```
HEAD
 │
 ▼
Commit C
```

Here:

- `HEAD` points directly to a commit.
- No branch points to your current position.
- New commits are not attached to any branch unless you create one.

---

### Comparison

| Normal HEAD | Detached HEAD |
|--------------|---------------|
| HEAD → Branch → Commit | HEAD → Commit |
| New commits move the branch | New commits are not attached to a branch |
| Standard development | Temporary exploration or recovery |

---

> [!TIP]
> Most of the time, `HEAD` points to a branch.
>
> A Detached HEAD is a temporary state used for inspecting old commits, testing, or recovering work.

---

## Switching Branches

Current branch:

```
HEAD

↓

main
```

After:

```bash
git switch feature/login
```

```
HEAD

↓

feature/login
```

HEAD now points to the new branch.

---

# Detached HEAD

Sometimes HEAD points directly to a commit.

```
HEAD

↓

Commit C
```

Instead of:

```
HEAD

↓

main

↓

Commit C
```

This is called a **Detached HEAD** state.

You can still explore the repository and even make commits, but those commits won't belong to any branch unless you create one.

> [!NOTE]
> Detached HEAD is **not an error**.
>
> Git intentionally allows it so you can inspect old commits, test previous versions, or recover lost work without affecting existing branches.

---

> [!TIP]
> If you accidentally commit in a Detached HEAD state, don't panic.
>
> Create a new branch to keep your work:
>
> ```bash
> git switch -c my-branch
> ```

---

# Tag References

Tags are also references.

Unlike branches:

- Branches move.
- Tags usually stay fixed.

```
v1.0

↓

Commit B
```

Even after new commits:

```
A ── B ── C ── D
     ▲
    v1.0
```

The tag still points to commit **B**.

---

# Reference Overview

```
HEAD
 │
 ▼
main
 │
 ▼
Commit
 │
 ▼
Tree
 │
 ▼
Blob
```

Git navigation starts from references.

---

# Why References Matter

Almost every Git command uses references.

Examples:

```bash
git switch main
```

```bash
git merge feature/login
```

```bash
git reset HEAD~1
```

```bash
git checkout v1.0
```

You rarely work with raw commit hashes.

---

## Common Misconceptions

❌ A branch contains commits.

✔ A branch is only a pointer to the latest commit.

---

❌ HEAD is a branch.

✔ HEAD points to the currently checked-out branch (or commit).

---

❌ Tags move like branches.

✔ Tags are intended to remain fixed.

---

## Key Takeaways

- References are named pointers.
- Branches are movable references.
- Tags are fixed references.
- HEAD represents your current working position.
- Git commands primarily operate using references rather than commit hashes.

---

# Part 4 — The Index (Staging Area)

> [!NOTE]
>
> The **Index** (also called the **Staging Area**) is a temporary area between your working directory and the next commit.
>
> ```
> Working Directory
>        │
>    git add
>        ▼
>      Index
>        │
>   git commit
>        ▼
>     Repository
> ```

---

## What is the Index?

The Index is a file inside `.git` that stores **what will go into the next commit**.

Think of it as a **draft** of your next commit.

---

## Why Does Git Have an Index?

Without an Index:

```
Edit File

↓

Commit
```

Every edited file would be committed immediately.

Instead, Git lets you choose exactly what to commit.

```
Edit File

↓

git add

↓

Index

↓

git commit
```

This gives you more control.

---

## Workflow

```
Working Directory
        │
        │ Edit files
        ▼
Modified Files
        │
        │ git add
        ▼
Index (Staged)
        │
        │ git commit
        ▼
Repository
```

---

## Example

Suppose you modify two files:

```
README.md

main.cpp
```

You only want to commit `main.cpp`.

```bash
git add main.cpp
```

Current state:

```
README.md      → Modified

main.cpp       → Staged
```

Now:

```bash
git commit
```

Only `main.cpp` is included in the commit.

---

## The Three States

Every file is usually in one of these states.

```
Working Directory

↓

Modified

↓

Staged

↓

Committed
```

### Modified

You changed the file.

Git knows it differs from the last commit.

---

### Staged

The changes have been added to the Index.

They are ready for the next commit.

---

### Committed

The changes are permanently stored in Git history.

---

## Where is the Index?

Inside the repository:

```
.git/

├── HEAD
├── config
├── index
├── objects/
└── refs/
```

The `index` file tracks everything you've staged.

---

## Checking the Index

Use:

```bash
git status
```

Example:

```
Changes to be committed:

    modified: main.cpp
```

This means the changes are in the Index.

---

## Why is the Index Useful?

Benefits:

- Commit only selected files.
- Split large changes into multiple commits.
- Create cleaner commit history.
- Review staged changes before committing.

---

> [!TIP]
> A commit is created from the **Index**, **not directly from the Working Directory**.

---

## Common Misconceptions

❌ `git add` creates a commit.

✔ It stages changes in the Index.

---

❌ Modified files are automatically committed.

✔ Only staged changes are committed.

---

❌ The Index is the repository.

✔ The Index is a temporary staging area.

---

## Key Takeaways

- The Index is also called the Staging Area.
- `git add` copies changes into the Index.
- `git commit` creates a commit from the Index.
- The Index allows selective and organized commits.

---

# Part 5 — Object Database

> [!NOTE]
>
> Git stores every object inside the **Object Database**.
>
> - Content-addressable storage
> - Objects identified by hashes
> - Duplicate content stored only once
> - Foundation of Git's speed and reliability

---

## What is the Object Database?

The Object Database is where Git permanently stores all objects.

```
.git/

├── objects/
└── ...
```

Objects include:

- Blob
- Tree
- Commit
- Tag

Whenever you create a commit, Git stores these objects inside:

```
.git/objects/
```

---

## Content-Addressable Storage

Unlike traditional file systems, Git doesn't identify objects by filenames.

Instead, every object is identified by a **hash** calculated from its contents.

```
File Content

↓

Hash

↓

Git Object
```

This means:

> **Same content = Same hash = Same object**

---

## Example

Suppose you have:

```
notes.txt

Hello Git
```

Git calculates a unique hash.

```
Hello Git

↓

a1b2c3...
```

Git stores:

```
a1b2c3...
```

instead of:

```
notes.txt
```

The filename is stored separately in Tree objects.

---

## Why Hashes?

Hashes provide several benefits.

### Unique Identification

Every object has its own identifier.

```
Blob

↓

Hash
```

---

### Data Integrity

If the contents change:

```
Hello Git
```

↓

```
Hello Git!
```

A completely different hash is generated.

Git immediately knows the file has changed.

---

### No Duplicate Storage

Suppose two files contain exactly:

```
Hello
```

Git stores:

```
Blob

Hello
```

only once.

Both Tree objects simply reference the same Blob.

This saves storage space.

---

## Object Relationships

```
Commit
   │
   ▼
 Tree
 ├── Blob
 ├── Blob
 └── Tree
      │
      ▼
    Blob
```

Everything inside Git is connected through object references.

---

## Loose Objects

Initially, Git stores objects individually.

```
.git/objects/

├── 1a/
├── 3f/
├── 7b/
└── ...
```

These are called **Loose Objects**.

As the repository grows, Git reorganizes them for efficiency.

We'll see how in the next section.

---

> [!TIP]
> Git never stores "version 1", "version 2", "version 3" of a file.
>
> It stores objects and connects them using references.

---

## Common Misconceptions

❌ Git stores files by filename.

✔ Git stores objects by their content hash.

---

❌ Every commit duplicates the whole project.

✔ Unchanged objects are reused.

---

❌ Hashes are just random IDs.

✔ A hash is calculated from the object's content.

---

## Key Takeaways

- Git stores objects inside `.git/objects/`.
- Objects are identified by their content hash.
- Identical content is stored only once.
- Hashes provide unique identification and integrity checking.
- Reusing existing objects makes Git fast and storage-efficient.

---

# Part 6 — Packfiles

> [!NOTE]
>
> As a repository grows, Git combines many loose objects into **Packfiles**.
>
> Benefits:
>
> - Smaller repository size
> - Faster cloning
> - Faster fetching
> - Faster pushing

---

## Why Packfiles?

Initially, Git stores every object separately.

```
.git/

└── objects/

    ├── 1a/
    ├── 2b/
    ├── 3c/
    ├── ...
```

For a large repository, this could mean **millions of tiny files**.

Problems:

- More disk space
- Slower file access
- Slower network transfers

Git solves this using **Packfiles**.

---

## What is a Packfile?

A Packfile combines many Git objects into a small number of compressed files.

Instead of:

```
Blob 1

Blob 2

Blob 3

Commit

Tree
```

Git stores:

```
Packfile

├── Blob 1
├── Blob 2
├── Blob 3
├── Commit
└── Tree
```

---

## Loose Objects vs Packfiles

### Loose Objects

```
Object A

Object B

Object C

Object D
```

Each object exists as an individual file.

---

### Packfiles

```
Packfile

├── Object A
├── Object B
├── Object C
└── Object D
```

Many objects are stored together.

---

## Compression

Git doesn't simply group objects.

It also compresses them.

Example:

```
Version 1

Hello World
```

```
Version 2

Hello World!
```

Instead of storing both copies independently, Git stores the shared data efficiently.

This helps reduce repository size.

---

## When Are Packfiles Created?

Git automatically creates Packfiles during operations such as:

- Repository optimization
- Cloning
- Fetching
- Pushing
- Garbage collection (`git gc`)

Most of the time, you don't need to manage Packfiles manually.

---

## Where Are They Stored?

Inside:

```
.git/

└── objects/

    └── pack/
```

Example:

```
pack-xxxx.pack

pack-xxxx.idx
```

- `.pack` → Compressed object data
- `.idx` → Index used to locate objects quickly

---

## Why Should I Care?

You usually don't interact with Packfiles directly.

However, they explain why Git can efficiently handle repositories containing:

- Thousands of commits
- Millions of lines of code
- Large development histories

---

> [!TIP]
> Packfiles are an internal optimization.
>
> Git manages them automatically, so you rarely need to think about them during everyday development.

---

## Common Misconceptions

❌ Packfiles replace commits.

✔ Packfiles only change **how objects are stored**, not the repository history.

---

❌ You should create Packfiles manually.

✔ Git automatically manages them.

---

## Key Takeaways

- Git initially stores objects as Loose Objects.
- As repositories grow, Git packs them into Packfiles.
- Packfiles reduce storage and improve performance.
- Git manages Packfiles automatically.

---

# Mental Model

> [!NOTE]
>
> If you remember **one diagram** from this chapter, remember this one.

```
                  Working Directory
                         │
                  git add │
                         ▼
                 Index (Staging Area)
                         │
               git commit │
                         ▼
                      Commit
                         │
                         ▼
                       Tree
                  ┌──────┴──────┐
                  ▼             ▼
               Blob         Tree (subdir)
                                │
                                ▼
                              Blob
```

References point to commits:

```
HEAD
 │
 ▼
main
 │
 ▼
Commit
```

Git stores everything inside:

```
.git/

├── objects/
├── refs/
├── index
├── HEAD
└── ...
```

---

# Cheat Sheet

## Repository Structure

```
.git/

├── HEAD
├── config
├── index
├── objects/
├── refs/
├── logs/
└── hooks/
```

---

## Four Git Objects

| Object | Purpose |
|----------|---------|
| Blob | Stores file contents |
| Tree | Stores directory structure |
| Commit | Stores snapshot metadata |
| Tag | Named reference to a commit |

---

## Important References

| Reference | Purpose |
|------------|---------|
| HEAD | Current position |
| Branch | Movable pointer to latest commit |
| Tag | Fixed pointer to a commit |

---

## Data Flow

```
Edit File

↓

git add

↓

Index

↓

git commit

↓

Commit Object

↓

Repository
```

---

## Storage Flow

```
Commit

↓

Tree

↓

Blob
```

---

# Common Misconceptions

### ❌ Git stores projects as folders.

✔ Git stores **objects**.

---

### ❌ A Branch contains commits.

✔ A branch is only a **reference** to the latest commit.

---

### ❌ Commits contain every file.

✔ Commits point to a Tree.

---

### ❌ Trees contain file data.

✔ Trees point to Blobs.

---

### ❌ Blob stores filenames.

✔ Blob stores only file contents.

---

### ❌ `git add` creates a commit.

✔ It updates the Index.

---

### ❌ Packfiles change Git history.

✔ They only optimize storage.

---

# NOTE

Git Internals is built on a few simple ideas:

- Git stores everything as **objects**.
- Objects are stored in `.git/objects`.
- Branches, Tags, and HEAD are **references** to commits.
- The Index prepares changes for the next commit.
- Objects are identified by their content hash.
- Packfiles optimize storage and performance.
- Understanding these concepts makes advanced Git much easier to reason about.

> [!TIP]
> You don't need to memorize Git's internals.
>
> Instead, remember the relationships:
>
> ```
> Working Directory
>        │
>        ▼
>      Index
>        │
>        ▼
>     Commit
>        │
>        ▼
>      Tree
>        │
>        ▼
>      Blob
> ```
>
> Once this model clicks, many Git commands become much easier to understand.
