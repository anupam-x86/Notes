# Commits in Git

A commit is the core unit of Git history. It represents a **snapshot of your project at a specific point in time**.

Every meaningful change in Git eventually becomes a commit.

---

## What is a Commit?

A commit is:
- A snapshot of the entire project
- Stored permanently in the local repository
- Identified by a unique SHA hash

Each commit includes:
- Project state (snapshot)
- Author information
- Timestamp
- Commit message
- Reference to previous commit

---

> [!NOTE]
> Git does NOT store differences between files.
> It stores complete snapshots (with optimization internally).

---

## Commit Structure (Conceptual)

Each commit points to:
- A snapshot of files
- The previous commit

This creates a chain of history:

```
C1 → C2 → C3 → C4
```

Each commit builds on the previous one.

---

## Creating a Commit

A commit happens in two steps:

### 1. Stage changes

```bash
git add <file>
```

### 2. Commit staged changes

```bash
git commit -m "message"
```

---

> [!IMPORTANT]
> Only staged changes are included in a commit.
> Unstaged changes are ignored.

---

## Why Staging Exists

Staging allows you to:
- Select specific changes for a commit
- Split work into logical snapshots
- Avoid committing incomplete work

Example:
You modify 5 files but only 2 are ready → stage only those 2.

---

## Commit Message

Every commit requires a message:

```bash
git commit -m "Fix login validation bug"
```

Good commit messages:
- Describe *what changed*
- Avoid vague messages like "update" or "fix"

---

> [!TIP]
> Write commit messages as if explaining the change to another developer.

---

## Viewing Commit History

```bash
git log
```

Shows:
- commit hash
- author
- date
- message

Simplified view:

```bash
git log --oneline
```

---

## Commit Hash (SHA)

Each commit has a unique ID:

```
e83c5163316f89bfbde7d9ab23ca2e25604af290
```

This hash:
- uniquely identifies the commit
- changes if content changes
- ensures integrity

---

> [!NOTE]
> Commit hash = fingerprint of project state

---

## Commit Lifecycle

```
modify files
     ↓
stage changes
     ↓
create commit
     ↓
stored in local repository
```

---

## What Makes a Good Commit

A good commit:
- is small and focused
- represents one logical change
- has a clear message
- does not mix unrelated changes

---

## Common Mistakes

> [!WARNING]

- committing without staging check
- huge commits with many unrelated changes
- vague messages like "fix"
- forgetting to commit frequently

---

## Commit vs Save

| Save in editor | Git commit |
|----------------|------------|
| Local file save | Project snapshot |
| No history | Stored history |
| Overwritten | Permanent record |

---

## Why Commits Matter

Commits allow you to:
- revert changes
- track project evolution
- collaborate safely
- debug when bugs were introduced

---

## What Comes Next

Now that commits are clear, the next step is understanding:

- how Git tracks changes before commits
- how files are selected for commits
- how `.gitignore` controls what Git ignores

This leads into **staging and tracking system in detail**.
