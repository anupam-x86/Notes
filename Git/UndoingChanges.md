# Undoing Changes in Git

Mistakes are normal in development. Git provides multiple ways to undo changes depending on **what stage the change is in**.

Understanding *which undo tool to use* is critical.

---

## Git Undo Model (Mental Map)

```
Working Directory → Staging Area → Local Repository
        ↑                ↑                 ↑
     restore          reset            revert
```

Each tool works at a different level.

---

## 1. git restore (Working Directory)

Used to discard **uncommitted changes**.

```bash
git restore <file>
```

This resets file back to last committed state.

---

### Example

```bash
git restore main.cpp
```

Removes changes made in working directory.

---

> [!NOTE]
> `git restore` only affects uncommitted changes.

---

## Restore Staged File

```bash
git restore --staged <file>
```

Moves file back from staging to working directory.

---

## 2. git reset (Staging / History Control)

`git reset` is used to undo staging or move branch pointer.

---

### Unstage file

```bash
git reset <file>
```

Removes file from staging area.

---

### Example

```
Working Directory → Staged → Unstaged
```

---

### Reset commit (soft/mixed/hard)

```bash
git reset --soft <commit>
git reset --mixed <commit>
git reset --hard <commit>
```

---

### Types

#### soft
- keeps changes staged
- moves HEAD only

#### mixed (default)
- keeps changes in working directory
- unstages everything

#### hard
- deletes all changes
- resets working directory completely

---

> [!WARNING]
> `--hard` permanently deletes uncommitted work.

---

## 3. git revert (Safe History Undo)

```bash
git revert <commit>
```

Creates a **new commit** that undoes changes.

---

### Example

```
C1 → C2 → C3
         ↓ revert C3
C1 → C2 → C3 → C4 (undo C3)
```

---

> [!IMPORTANT]
> revert does NOT delete history.
> It adds a new corrective commit.

---

## 4. git stash (Temporary Save)

Used when you want to **save work without committing**.

```bash
git stash
```

Saves current changes and cleans working directory.

---

### Restore stash

```bash
git stash pop
```

---

### Use case

- switching branches quickly
- pausing work
- avoiding incomplete commits

---

## Difference Between Undo Commands

| Command | Purpose | Affects |
|--------|--------|--------|
| restore | discard file changes | working directory |
| reset | undo staging or commits | staging / history |
| revert | safely undo commit | history (adds new commit) |
| stash | temporarily save work | working state |

---

## When to Use What

### Use restore when:
- you messed up a file
- you want to discard local changes

---

### Use reset when:
- you want to unstage files
- you want to move branch backward (carefully)

---

### Use revert when:
- you already pushed commits
- you want safe undo in shared repo

---

### Use stash when:
- switching tasks temporarily
- keeping work unfinished

---

## Common Mistakes

> [!WARNING]

- using `reset --hard` without understanding
- using reset on shared branches
- confusing revert with reset
- losing work due to wrong restore

---

## Safety Rule

> [!IMPORTANT]
> If history is shared, prefer `git revert` over `git reset`

---

## Mental Model

```
restore → undo file changes
reset   → undo staging/history
revert  → undo commit safely
stash   → pause work
```

---
