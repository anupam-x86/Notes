# Git Basics

## What is Git?

Version Control System

Purpose:
- Track history
- Restore old versions
- Collaborate
- Backup code

---

## Git Pipeline

Working Directory
↓ git add
Staging Area
↓ git commit
Local Repository
↓ git push
GitHub Repository

---

## Commands

### git status
Shows current repository state.

### git add
Moves changes to staging area.

### git commit -m "message"
Creates snapshot.

### git push
Uploads commits to GitHub.

### git pull
Downloads latest changes.

### git log
Shows commit history.

### git diff
Shows changes before staging.

### git diff --staged
Shows changes that will be committed.

### git restore file.txt
Restore working directory from staging area.

### git restore --staged file.txt
Remove file from staging area.

---

## Important Concepts

Working Directory
- Current files.

Staging Area
- Selected changes for next commit.

Local Repository
- Commit history.

GitHub Repository
- Remote copy.

Commit Hash
- Unique ID of a commit.

HEAD
- Current commit pointer.

origin/main
- GitHub's main branch.

---

## Mistakes I Made

Confused:
Working Directory
with
Local Repository

Correct:
Working Directory = current files
Local Repository = committed snapshots
