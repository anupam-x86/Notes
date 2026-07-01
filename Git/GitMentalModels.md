# Git Mental Models

This file explains Git in terms of **how to think**, not how to use commands.

If you understand these models, Git becomes predictable instead of confusing.

---

# 1. Git is a State Machine

Git is not a file tracker.

It is a system that moves your project through states.

```
Working → Staging → Committed → Shared
```

Each action moves the project from one state to another.

---

# 2. Git is a Snapshot System

Every commit is a complete snapshot of your project.

Not differences. Not patches.

```
Commit = full project state at a point in time
```

This is why Git can:
- restore old versions
- compare changes
- move between versions instantly

---

# 3. Git is a Pointer System

Git does NOT move files.

It moves pointers.

### Main pointers:

- HEAD → current position
- Branch → movable pointer to commits
- Tag → fixed pointer to a commit

```
HEAD → Branch → Commit
```

---

# 4. Working Directory vs Git History

Git separates:

### Working Directory
- your actual files
- editable space

### Git History
- saved snapshots (commits)
- immutable records

```
Working files ≠ Git history
```

---

# 5. Staging Area is a Selection Layer

Staging is not storage.

It is a **filter layer**.

It decides:

> what will go into the next snapshot

```
Edit → Stage → Commit
```

---

# 6. Branching is Parallel Timelines

A branch is not a copy of your project.

It is a **movable pointer to a commit history line**.

```
main:     A → B → C
                \
feature:         D → E
```

Both branches share history until they diverge.

### Key idea:
> Branch = independent timeline of commits

---

# 7. Merging is Timeline Combination

Merge combines two timelines into one.

```
A → B → C
       ↘
        D → E
```

After merge:

```
A → B → C → M
          ↗
        D → E
```

M = merge commit (combination point)

### Key idea:
> Merge does NOT delete history — it joins it

---

# 8. Conflicts are Decision Points

Conflicts happen when Git cannot automatically combine changes.

```
Same file + same line + different edits = conflict
```

Git stops and asks:

> “Which version should I keep?”

### Key idea:
> Conflict = human decision required, not Git failure

---

# 9. HEAD is Your Current Position

HEAD is a pointer that tells Git:

> “Where am I right now?”

Usually:

```
HEAD → branch → latest commit
```

When you switch branches, HEAD moves.

Detached HEAD = pointing directly to a commit instead of a branch.

### Key idea:
> HEAD defines your current working context

---

# 10. Undo System is Layer-Based

Git undo depends on *which layer you are targeting*.

---

### Working Directory (unstaged changes)
- you edit files directly

Undo:
> discard local edits

---

### Staging Area
- selected changes waiting for commit

Undo:
> unstage changes (remove from next snapshot)

---

### Commit History
Two types of undo:

#### Safe undo:
- creates a new commit
- does NOT change history

```
git revert
```

#### Unsafe undo:
- rewrites history

```
git reset
```

---

### Key idea:
> Undo depends on which layer you are affecting

---

# 11. Rebase is History Rewriting

Rebase does NOT merge histories.

It **replays commits in a new position**.

```
Before:
A → B → C
     \
      D → E

After rebase:
A → B → C → D → E
```

### Key idea:
> Rebase rewrites history to make it linear

### Important consequence:
- Commit IDs change
- History is replaced, not preserved

---

# 12. Tags are Fixed Markers

A tag is a permanent label on a commit.

```
A → B → C (v1.0)
```

Unlike branches:
- tags do NOT move
- tags do NOT change history

### Key idea:
> Tag = permanent version marker in history

---

# 13. Remote System is Synchronization Layer

Local and remote repositories are separate systems.

```
Local Repo ↔ Remote Repo
```

### Flow model:

- push → send commits to remote
- pull → bring remote changes locally
- fetch → download without merging

### Key idea:
> Remote is a sync system, not a storage replacement

---

# 14. Git Workflow is a Loop

All Git activity follows a repeating cycle:

```
Edit → Stage → Commit → Sync
```

or in system form:

```
Working → Staging → Local Repo → Remote Repo
```

### Key idea:
> Git is a repeating state transition loop

---

# 15. Full Git Mental Model (Complete System)

If you combine everything:

```
You edit files
      ↓
Working Directory
      ↓ (stage selection)
Staging Area
      ↓ (snapshot creation)
Commit (Local History)
      ↓ (sync)
Remote Repository
```

Alongside:

- HEAD → current position
- Branch → timeline pointer
- Commit → snapshot
- Tag → fixed marker

---

# 16. Final Mental Rule

> Git is not about files — it is about moving through states and controlling history.

---

