# Merge Conflicts in Git

A merge conflict happens when Git cannot automatically combine changes from different sources.

It is not an error — it is a **decision point**.

---

## When Conflicts Occur

Conflicts happen when two changes affect the same part of a file.

Common situations:
- merging branches
- pulling updates
- rebasing commits
- applying stashes
- cherry-picking commits

---

> [!NOTE]
> Any operation that combines histories can cause conflicts.

---

## Why Conflicts Happen

Git tries to automatically merge changes.

If changes are:
- in different files → Git merges automatically
- in different lines → Git merges automatically
- in same lines → Git cannot decide → conflict

---

## Conflict Structure in File

When a conflict happens, Git marks it like this:

```
<<<<<<< HEAD
your current branch changes
=======
incoming branch changes
>>>>>>> feature-branch
```

---

## Meaning of Markers

- `<<<<<<< HEAD` → your current branch
- `=======` → separator
- `>>>>>>> branch` → incoming changes

---

## How to Resolve a Conflict

### Step 1: Open the file
Locate conflict markers.

---

### Step 2: Decide final code
You can:
- keep current version
- keep incoming version
- combine both
- rewrite completely

---

### Step 3: Remove markers

Delete:
```
<<<<<<<
=======
>>>>>>>
```

---

### Step 4: Mark as resolved

```bash
git add <file>
```

---

### Step 5: Complete operation

For merge:
```bash
git commit
```

For rebase:
```bash
git rebase --continue
```

---

## Conflict in Different Operations

---

### 1. Merge Conflicts

```bash
git merge feature
```

Occurs when two branches diverge.

---

### 2. Pull Conflicts

```bash
git pull
```

Internally:
```
fetch + merge
```

So conflicts come from merge.

---

### 3. Rebase Conflicts

```bash
git rebase main
```

Occurs per commit being replayed.

> [!IMPORTANT]
> Rebase conflicts may happen multiple times in one operation.

---

### 4. Stash Conflicts

```bash
git stash pop
```

Occurs when saved changes don’t match current code.

---

### 5. Cherry-pick Conflicts

```bash
git cherry-pick <commit>
```

Occurs when applying a commit to incompatible context.

---

## Conflict Resolution Strategies

### 1. Accept current version
Keep your branch changes.

### 2. Accept incoming version
Overwrite with incoming changes.

### 3. Manual merge
Combine both logically.

### 4. Rewrite section
Clean redesign of conflicting part.

---

> [!TIP]
> There is no “correct” side in a conflict — only the correct final state.

---

## How to Avoid Conflicts

You cannot fully avoid conflicts, but you can reduce them:

- pull frequently
- keep branches small
- commit often
- avoid long-lived branches
- communicate in team workflows

---

## Common Mistakes

> [!WARNING]

- deleting conflict markers incorrectly
- committing without reviewing conflict resolution
- using `--force` to avoid solving conflicts
- ignoring small conflicts (they accumulate)

---

## Mental Model

```
Git tries automatic merge
        ↓
If overlap in same lines
        ↓
Conflict appears
        ↓
User decides final version
        ↓
Commit continues
```

---

## Key Idea

> Conflicts are not failures — they are Git asking for human judgment.

---

## Where Conflicts Come From

- Branch merging
- Pulling updates
- Rebasing commits
- Applying stash
- Cherry-picking commits

---

>[!Note]
> If Git cannot safely choose:
> It pauses and asks you to decide

---
