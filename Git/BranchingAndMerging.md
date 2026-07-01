# Branching and Merging in Git

Branches allow you to work on multiple features independently without affecting the main project.

They are one of Git’s most powerful features.

---

## What is a Branch?

A branch is a **separate line of development**.

Instead of working in a single timeline, Git allows multiple timelines.

Example:

```
main:    A → B → C
               ↘
feature:        D → E
```

Each branch has its own history.

---

> [!NOTE]
> A branch is just a pointer to a commit.

---

## Why Branches Exist

Branches allow:
- feature development
- bug fixing
- experimentation
- parallel work
- isolated changes

Without branches, all changes would go into one timeline.

---

## Default Branch (main)

Every Git repository starts with a default branch:

```
main
```

This is usually the stable version of the project.

---

## Creating a Branch

```bash
git branch feature
```

This creates a new branch but does not switch to it.

---

## Switching Branches

```bash
git checkout feature
```

or modern:

```bash
git switch feature
```

---

## Create + Switch Together

```bash
git checkout -b feature
```

or

```bash
git switch -c feature
```

---

## HEAD and Branches

HEAD points to the current branch.

Example:

```
HEAD → main → commit C3
```

When you switch branches:

```
HEAD → feature → commit C3
```

---

> [!IMPORTANT]
> HEAD moves when you switch branches.

---

## How Branches Work Internally

Branches do NOT copy files.

They only point to commits.

```
main → C3
feature → C3
```

When you commit:

```
feature → C4
```

main remains unchanged.

---

## Merging Branches

Merging combines changes from one branch into another.

---

### Step 1: Switch to target branch

```bash
git checkout main
```

---

### Step 2: Merge

```bash
git merge feature
```

---

## Merge Result

Before merge:

```
main:    A → B → C
feature:       → D → E
```

After merge:

```
main:    A → B → C → M
                     ↑
                 merge commit
```

---

## Types of Merge

### 1. Fast-forward merge
If no divergence exists:

```
A → B → C
```

Branch pointer just moves forward.

---

### 2. 3-way merge
When branches diverge:

Git creates a merge commit.

---

## Merge Conflicts

Conflicts happen when:
- same file
- same lines
- different changes

---

Example:

```
main:    "hello world"
feature: "hello git"
```

Git cannot decide automatically.

---

## Resolving Conflicts

Steps:

1. Open conflicting file
2. Manually fix changes
3. Remove conflict markers
4. Stage file
5. Commit

```bash
git add .
git commit
```

---

> [!WARNING]
> Conflicts are normal in collaborative development.

---

## Deleting Branches

After merging:

```bash
git branch -d feature
```

Force delete:

```bash
git branch -D feature
```

---

## Common Mistakes

> [!WARNING]

- forgetting to switch branch before commit
- merging without checking changes
- deleting branch before merge
- not resolving conflicts properly

---

## Mental Model

```
Branch = pointer to commit
Commit = snapshot
Merge = combine snapshots
HEAD = current position
```

---

## Why Branching is Powerful

Branches allow:
- safe experimentation
- isolated features
- clean history
- team collaboration

---
