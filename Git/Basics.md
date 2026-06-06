# Git Basics

## Workflow

git status
git add .
git commit -m "message"
git push

# Git Workflow

Working Directory
↓
git add
↓
Staging Area
↓
git commit
↓
Local Repository
↓
git push
↓
GitHub Repository

Difference: Working Directory != Staging Area != Commit



## Git Commands Priority

### Daily
git status
git add
git commit
git push
git pull
git log

### Useful
git diff
git restore
git branch
git switch
git merge

### Learn Later
git stash
git reset
git rebase
git cherry-pick

## Important Realizations

### Mistake I Made

I confused:

Working Directory

with

Local Repository

### Correct Understanding

Working Directory:
- Current files on my computer.
- Changes can exist here without being committed.

Local Repository:
- Contains committed snapshots.
- Git history lives here.

Example:

Modify README.md
↓
Working Directory

git add README.md
↓
Staging Area

git commit -m "Update README"
↓
Local Repository

## Goal

Become comfortable, not a Git wizard.