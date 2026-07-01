# Git Tags

Tags are used in Git to mark specific points in history as important.

Most commonly, tags are used to mark **releases**.

---

## What is a tag?

A tag is a label given to a specific commit.

Example:
```
v1.0 → First stable release
v2.0 → Major update
```

---

## Why tags are used

Tags help you:
- mark stable versions
- track releases
- easily return to important points in history
- organize project milestones

---

> [!NOTE]
> Tags do NOT move like branches. They are fixed pointers to commits.

---

## Types of tags

### 1. Lightweight tag
Simple pointer to a commit.

```bash
git tag v1.0
```

---

### 2. Annotated tag (recommended)

Stores extra information:
- tag message
- author
- date

```bash
git tag -a v1.0 -m "First release"
```

---

## Viewing tags

```bash
git tag
```

Shows all tags in repository.

---

## Viewing tag details

```bash
git show v1.0
```

Displays commit and tag information.

---

## Pushing tags to remote

Tags are NOT sent automatically with push.

### Push single tag:
```bash
git push origin v1.0
```

### Push all tags:
```bash
git push --tags
```

---

## Deleting tags

### Local delete:
```bash
git tag -d v1.0
```

### Remote delete:
```bash
git push origin --delete v1.0
```

---

## Tags vs Branches

| Feature | Tag | Branch |
|--------|-----|--------|
| Moves with commits | ❌ No | ✅ Yes |
| Purpose | Mark version | Active development |
| Changeable | ❌ No | ✅ Yes |

---

## When to use tags

Use tags when:
- releasing software versions
- marking stable points
- creating checkpoints for deployment

---

## Mental model

```
Commit history:
A → B → C → D

Tag:
        v1.0 → C
```

Tag stays fixed even if new commits are added.

---

## Key idea

> Tags are permanent labels for important commits.
