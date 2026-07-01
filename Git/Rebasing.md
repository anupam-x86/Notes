# Git Rebasing

Rebasing is a way to move or rewrite commits to create a **clean, linear history**.

It is an alternative to merging.

---

## What is rebasing?

Rebasing takes commits from one branch and **replays them on top of another branch**.

Instead of combining histories like merge, it rewrites history in a straight line.

---

### Example (before rebase)

```
main:     A → B → C
                \
feature:         D → E
```

---

### After rebase

```
main:     A → B → C → D → E
```

---

## Why rebasing is used

Rebase is used to:
- keep history clean and linear
- avoid merge commits
- integrate latest changes from main branch

---

> [!NOTE]
> Rebase does NOT create a merge commit. It rewrites commit history.

---

## Basic rebase command

```bash
git rebase main
```

This moves your current branch on top of `main`.

---

## When to use rebase

Use rebase when:
- working on your own branch
- before merging feature into main
- updating branch with latest main changes

---

## Rebase vs Merge

| Feature | Merge | Rebase |
|--------|------|--------|
| History style | Branching | Linear |
| Merge commit | Yes | No |
| Safe in shared branches | Yes | Risky |
| History rewriting | No | Yes |

---

## Important warning

> [!WARNING]
> Never rebase commits that are already pushed and shared with others.

Because:
- it rewrites history
- can break other developers’ work

---

## Handling conflicts in rebase

If conflicts happen:

1. Fix the file manually
2. Stage the file:
   ```bash
   git add <file>
   ```
3. Continue rebase:
   ```bash
   git rebase --continue
   ```

To cancel rebase:
```bash
git rebase --abort
```

---

## Mental model

```
Take commits from feature branch
        ↓
Remove them temporarily
        ↓
Replay them on top of main
        ↓
Create new linear history
```

---

## When NOT to use rebase

Avoid rebase when:
- working in shared team branches
- history is already published
- multiple people depend on same commits

---

## Key idea

> Merge preserves history. Rebase rewrites history.

---

## Simple rule

- Use **merge** for safety
- Use **rebase** for clean history
