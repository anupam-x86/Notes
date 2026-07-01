# Git Commands and Uses

This file is a quick reference for Git commands and their practical usage.

It focuses on **what each command does and when to use it**, not deep explanations.

---

# Repository Setup

## Initialize a new repository
```bash
git init
```
Creates a new Git repository in the current folder.

---

## Clone an existing repository
```bash
git clone <url>
```
Copies a remote repository to local machine with full history.

---

## Check remote connections
```bash
git remote -v
```
Shows linked remote repositories.

---

## Add remote repository
```bash
git remote add origin <url>
```
Connects local repo to remote.

---

# File Status

## Check status
```bash
git status
```
Shows staged, modified, and untracked files.

---

## View differences (unstaged)
```bash
git diff
```
Shows changes not yet staged.

---

## View staged differences
```bash
git diff --staged
```
Shows changes ready to commit.

---

# Staging

## Stage a file
```bash
git add <file>
```

## Stage all changes
```bash
git add .
```

## Stage everything (including deletions)
```bash
git add -A
```

---

# Committing

## Create commit
```bash
git commit -m "message"
```

## Amend last commit
```bash
git commit --amend
```

---

# History

## View full history
```bash
git log
```

## Compact history
```bash
git log --oneline
```

## Graph view
```bash
git log --oneline --graph --all
```

---

# Branching

## List branches
```bash
git branch
```

## Create branch
```bash
git branch <name>
```

## Switch branch
```bash
git switch <name>
```

## Create + switch
```bash
git switch -c <name>
```

---

# Merging

## Merge branch into current branch
```bash
git merge <branch>
```

---

# Undoing Changes

## Discard file changes
```bash
git restore <file>
```

## Unstage file
```bash
git restore --staged <file>
```

## Reset commit (soft/mixed/hard)
```bash
git reset --soft <commit>
git reset --mixed <commit>
git reset --hard <commit>
```

## Revert commit safely
```bash
git revert <commit>
```

---

# Stash

## Save work temporarily
```bash
git stash
```

## Apply last stash
```bash
git stash pop
```

## List stashes
```bash
git stash list
```

---

# Remote Operations

## Push to remote
```bash
git push origin <branch>
```

## Pull changes (fetch + merge)
```bash
git pull
```

## Fetch changes only
```bash
git fetch
```

---

# Tagging

## Create tag
```bash
git tag <name>
```

## Push tags
```bash
git push --tags
```

---

# File Ignore

## .gitignore file
Used to exclude files from tracking.

Example:
```
node_modules/
.env
dist/
```

---

# Useful Combined Workflows

## Standard workflow
```bash
git status
git add .
git commit -m "message"
git push
```

---

## Safe update workflow
```bash
git pull
git add .
git commit -m "update"
git push
```

---

## Feature workflow
```bash
git switch -c feature-name
git add .
git commit -m "feature work"
git push origin feature-name
```

---

# Key Reminders

- `git status` → always check before committing
- `git add` → selects what goes into commit
- `git commit` → saves snapshot
- `git push` → sends to remote
- `git pull` → syncs with remote

---
