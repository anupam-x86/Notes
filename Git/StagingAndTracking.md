# Staging and Tracking in Git

Before a commit is created, Git needs a way to decide **what should be included in that snapshot**.

This is handled by the **staging area (index)** and Git’s tracking system.

---

## What is Staging?

The staging area is a preparation space between:

```
Working Directory → Staging Area → Commit
```

It allows you to select exactly what will go into the next commit.

---

> [!NOTE]
> Staging is not a storage area.
> It is a selection layer for the next commit.

---

## git add (Staging Changes)

```bash
git add <file>
```

This moves changes from:
```
Working Directory → Staging Area
```

Example:
```bash
git add main.cpp
```

Now Git includes this file in the next commit.

---

## git add does NOT commit

A very common misunderstanding:

> [!IMPORTANT]
> `git add` does NOT save history.
> It only prepares changes for commit.

---

## File States in Git

Git classifies files into states:

### 1. Untracked
Git does not know the file exists.

### 2. Tracked
Git is monitoring the file.

### 3. Modified
Tracked file has changes.

### 4. Staged
Changes are selected for commit.

### 5. Committed
Changes are stored in history.

---

## Lifecycle Flow

```
Untracked → Tracked → Modified → Staged → Committed
```

This cycle repeats continuously during development.

---

## Why Staging Exists

Without staging, Git would always commit everything.

Staging allows:
- splitting work into logical commits
- avoiding accidental commits
- partial commits of large changes
- better project history structure

---

## Example Workflow

You modify 3 files:

```
file1.cpp
file2.cpp
file3.cpp
```

You only want to commit 2:

```bash
git add file1.cpp
git add file3.cpp
```

Then commit:

```bash
git commit -m "Update feature logic"
```

---

## git add variations

### Add specific file
```bash
git add file.cpp
```

### Add all changes
```bash
git add .
```

### Add all tracked + untracked changes
```bash
git add -A
```

---

> [!TIP]
> Use `git add .` carefully — it may include unwanted files.

---

## What is “Tracked” in Git?

A file becomes tracked when:
- it has been committed once, OR
- it has been staged at least once

Tracked files:
- are monitored for changes
- appear in `git status`

---

## git status and staging

```bash
git status
```

Shows:
- modified files (not staged)
- staged files (ready to commit)
- untracked files

This command reflects the full staging state.

---

## Staging Area = Index

Internally:
- staging area = index

Both refer to the same concept.

---

> [!NOTE]
> Index stores the exact snapshot that will become the next commit.

---

## How Git builds a commit

```
Working Directory
        ↓ (git add)
Staging Area (Index)
        ↓ (git commit)
Local Repository (history)
```

Each commit is built from the staging area, not directly from working files.

---

## Common Mistakes

> [!WARNING]

- thinking `git add` commits changes
- forgetting to stage modified files
- using `git add .` blindly
- not checking `git status` before commit

---

## Why this matters

Staging gives Git its most powerful feature:

> the ability to build precise snapshots of your project

This is what makes Git history clean and meaningful.

---

## What Comes Next

Now that staging is clear, the next step is:

- how Git records snapshots internally
- how commits are linked
- how `.gitignore` prevents unwanted tracking

This leads into **Git history and file filtering behavior**.
