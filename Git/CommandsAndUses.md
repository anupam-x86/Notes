# Git Commands and Uses (Quick Reference)

This file is a clean cheat sheet of Git commands grouped by purpose.

---

# Repository Setup

```bash
git init
```
Create a new repository.

```bash
git clone <url>
```
Copy an existing repository.

```bash
git remote add origin <url>
```
Connect local repo to remote.

```bash
git remote -v
```
View remote connections.

---

# Status & Inspection

```bash
git status
```
Show current state of files.

```bash
git diff
```
Show unstaged changes.

```bash
git diff --staged
```
Show staged changes.

---

# Staging

```bash
git add <file>
```
Stage specific file.

```bash
git add .
```
Stage all changes.

```bash
git add -A
```
Stage all changes including deletions.

---

# Commits

```bash
git commit -m "message"
```
Create a commit.

```bash
git commit --amend
```
Modify last commit.

---

# History

```bash
git log
```
Full commit history.

```bash
git log --oneline
```
Compact history view.

```bash
git log --graph --oneline --all
```
Visual branch history.

---

# Branching

```bash
git branch
```
List branches.

```bash
git branch <name>
```
Create branch.

```bash
git switch <name>
```
Switch branch.

```bash
git switch -c <name>
```
Create + switch branch.

---

# Merging

```bash
git merge <branch>
```
Merge branch into current branch.

---

# Rebasing

```bash
git rebase <branch>
```
Reapply commits on top of another branch.

---

# Tags

```bash
git tag
```
List tags.

```bash
git tag <name>
```
Create lightweight tag.

```bash
git tag -a <name> -m "msg"
```
Create annotated tag.

```bash
git push --tags
```
Push tags.

---

# Undoing Changes

```bash
git restore <file>
```
Discard changes.

```bash
git restore --staged <file>
```
Unstage file.

```bash
git reset --soft <commit>
```

```bash
git reset --mixed <commit>
```

```bash
git reset --hard <commit>
```

```bash
git revert <commit>
```
Safe undo via new commit.

---

# Stash

```bash
git stash
```
Save temporary work.

```bash
git stash pop
```
Restore stash.

```bash
git stash list
```
View stashes.

---

# Remote

```bash
git push origin <branch>
```

```bash
git pull
```

```bash
git fetch
```

---

# Git Config

```bash
git config --global user.name "Name"
git config --global user.email "email"
git config --list
```

---
