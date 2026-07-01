# Git History and Logs

Git does not just store versions of a project — it also provides tools to **navigate and understand the entire history of changes**.

This is done through logs, commit graphs, and diffing tools.

---

## What is Git History?

Git history is the ordered sequence of commits in a repository.

Each commit represents:
- a snapshot of the project
- a point in time
- a unique identifier (SHA hash)

Example:

```
C1 → C2 → C3 → C4
```

Each commit builds on the previous one.

---

## Viewing History (`git log`)

```bash
git log
```

This shows the full commit history.

Each entry contains:
- commit hash
- author
- date
- commit message

---

### Example output

```
commit a1b2c3d4
Author: John
Date: ...
    Fix login bug
```

---

## Simplified History View

```bash
git log --oneline
```

Example:

```
a1b2c3d Fix login bug
d4e5f6a Add authentication
f7g8h9i Initial commit
```

---

> [!TIP]
> `--oneline` is the most commonly used form for quick history inspection.

---

## Commit Graph

Git history is not always linear.

Branches create diverging paths:

```
A → B → C
      ↘
        D → E
```

To visualize this:

```bash
git log --graph --oneline
```

---

## What is a Commit Hash?

Each commit has a unique ID:

```
e83c5163316f89bfbde7d9ab23ca2e25604af290
```

This hash:
- identifies the commit
- ensures integrity
- links history together

---

> [!NOTE]
> If commit content changes, the hash changes too.

---

## Viewing Changes Between Commits

```bash
git diff
```

Shows:
- line-by-line differences
- modifications in files

---

### Compare two commits

```bash
git diff <commit1> <commit2>
```

---

## Types of Diffs

### 1. Working Directory vs Staging
```bash
git diff
```

### 2. Staging vs Last Commit
```bash
git diff --staged
```

### 3. Commit vs Commit
```bash
git diff A B
```

---

## Why History Matters

Git history allows you to:
- understand project evolution
- find when bugs were introduced
- revert unwanted changes
- review past decisions

---

## HEAD and History Navigation

`HEAD` points to your current position in history.

Example:

```
main → C4
        ↑
       HEAD
```

When you move through commits or branches, HEAD moves accordingly.

---

## Detached HEAD State (Basic Idea)

If you check out a commit directly:

```
git checkout <commit>
```

You enter a state where HEAD is not on a branch.

This is called **detached HEAD**.

---

> [!IMPORTANT]
> In detached HEAD, changes are not attached to a branch unless explicitly saved.

---

## Git History is Immutable

Once a commit is created:
- it does not change
- it remains part of history
- new commits extend it

---

> [!NOTE]
> Git does not edit history — it adds to it.

---

## Common Mistakes

> [!WARNING]

- confusing `git log` with file history only
- ignoring commit messages
- not using `--graph` for branches
- losing context in large histories

---

## Mental Model of History

```
Commit = snapshot
History = linked snapshots
Branch = pointer to a snapshot
HEAD = current pointer position
```

---
