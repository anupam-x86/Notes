# Tracking and Ignoring Files in Git

Not every file in a project should be tracked by Git.

Git is designed to track **source content**, not generated or temporary data.

To manage this, Git uses tracking rules and the `.gitignore` file.

---

## What Git Should Track

Git is meant to track:
- Source code
- Configuration files
- Documentation
- Project logic

These represent meaningful changes in a project.

---

## What Git Should NOT Track

Some files are not useful in version history:

### Examples:
- compiled files (`.exe`, `.out`)
- build folders (`/dist`, `/build`)
- dependency folders (`node_modules/`)
- logs (`.log`)
- temporary files
- IDE settings

These change frequently and do not represent project logic.

---

> [!NOTE]
> Git should track "what you write", not "what is generated".

---

## What is .gitignore?

`.gitignore` is a file that tells Git:

> “Do not track these files or folders.”

---

### Example `.gitignore`

```
node_modules/
dist/
*.log
.env
```

---

## How .gitignore Works

When Git sees a file:
1. It checks `.gitignore`
2. If matched → file is ignored
3. If not → file is tracked normally

---

> [!IMPORTANT]
> `.gitignore` only affects untracked files.
> Already tracked files are NOT ignored automatically.

---

## Ignoring Already Tracked Files

If a file is already tracked:

```bash
git rm --cached <file>
```

This removes it from tracking but keeps it locally.

---

## Pattern Matching in .gitignore

### Ignore folder
```
build/
```

### Ignore all files of type
```
*.log
```

### Ignore specific file
```
config.json
```

### Ignore everything except one file
```
*
!important.txt
```

---

## Why Ignoring Matters

Without ignoring:
- repositories become large
- irrelevant files pollute history
- merges become noisy
- builds cause unnecessary changes

---

## Clean Repository Principle

A good repository contains only:
- source code
- necessary configuration
- documentation

Everything else should be ignored.

---

## git status and ignored files

Ignored files:
- do NOT appear in `git status`
- are invisible to Git tracking

---

## Common Mistakes

> [!WARNING]

- committing `node_modules`
- committing build output
- forgetting `.env` in `.gitignore`
- thinking ignored files are removed from disk

---

## Important Behavior Rule

> [!NOTE]
> Git does not ignore files already committed.

To fix this:
- remove from tracking
- then commit the change

---

## Relationship with Staging

```
Working Directory
        ↓
.gitignore filters files
        ↓
Staging Area (only allowed files)
        ↓
Commit
```

Ignored files never reach staging.

---

## Why .gitignore is Critical

It ensures:
- clean commit history
- smaller repositories
- faster operations
- better collaboration

---
- how to navigate past versions

This leads into **Git History and Logs**.
