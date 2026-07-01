# Git Commands and Uses (Core Workflow)

This file maps Git commands to real workflow actions.

---

# 1. Working Directory (Your Files)

This is where you edit code.

---

### Check project state
```bash
git status
```

Shows:
- modified files
- untracked files
- staged files

---

### View changes (before staging)
```bash
git diff
```

Shows exact line-by-line changes.

---

### Discard local changes
```bash
git restore <file>
```

Removes changes in working directory.

---

> [!IMPORTANT]
> This affects ONLY your local edits, not commits.

---

# 2. Staging Area (Selection Layer)

This decides what goes into the next commit.

---

### Stage a file
```bash
git add <file>
```

---

### Stage everything
```bash
git add .
```

---

### Remove from staging
```bash
git restore --staged <file>
```

---

> [!NOTE]
> Staging is just a selection layer — not permanent storage.

---

# 3. Commit System (Snapshots)

Each commit is a saved snapshot of project state.

---

### Create commit
```bash
git commit -m "message"
```

---

### Modify last commit
```bash
git commit --amend
```

---

### View history
```bash
git log
```

---

### Compact history
```bash
git log --oneline
```

---

### Visual history
```bash
git log --graph --oneline --all
```

---

# 4. Core Workflow Loop

This is the basic Git cycle:

```
edit → status → add → commit
```

or:

```
Working → Staging → Commit
```

---
# 5. Branching System (Timeline Layer)

Branches are pointers to different lines of development.

---

### Create a branch
```bash
git branch <name>
```

---

### Switch branch
```bash
git switch <name>
```

---

### Create + switch
```bash
git switch -c <name>
```

---

### View branches
```bash
git branch
```

---

> [!IMPORTANT]
> Branches are NOT copies — they are pointers to commits.

---

# 6. Merging (Combining Timelines)

Merge combines two branches into one history.

---

### Merge branch into current branch
```bash
git merge <branch>
```

---

### What merge does:
- combines histories
- may create a merge commit
- preserves both timelines

---

> [!NOTE]
> Merge = history preservation + combination

---

# 7. Rebase (History Rewrite System)

Rebase moves commits to a new base.

---

### Rebase current branch onto another
```bash
git rebase <branch>
```

---

### What rebase does:
- rewrites commit history
- creates linear timeline
- removes merge commits

---

> [!WARNING]
> Do NOT rebase shared/public commits.

---

### Abort rebase (if something goes wrong)
```bash
git rebase --abort
```

---

### Continue after conflict
```bash
git add <file>
git rebase --continue
```

---

# 8. Tags (Version Markers)

Tags mark important commits (like releases).

---

### Create tag
```bash
git tag <name>
```

---

### Annotated tag
```bash
git tag -a <name> -m "message"
```

---

### View tags
```bash
git tag
```

---

### Push tags
```bash
git push --tags
```

---

> [!IMPORTANT]
> Tags are fixed — they do NOT move like branches.

---

# 9. Timeline Model (Mental Mapping)

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

After rebase:
```
A → B → C → D → E
```

---

# 10. Undo System (Correction Layer)

Git provides different undo tools depending on the level.

---

# A) Working Directory Undo

### Discard local changes
```bash
git restore <file>
```

Removes uncommitted changes.

---

# B) Staging Area Undo

### Unstage file
```bash
git restore --staged <file>
```

Moves file back to working directory.

---

# C) Commit History Undo

---

### Safe undo (recommended)
```bash
git revert <commit>
```

Creates a new commit that reverses changes.

---

### Dangerous undo (rewrites history)
```bash
git reset --hard <commit>
```

Removes commits permanently (local only safe use).

---

### Soft reset (keep changes staged)
```bash
git reset --soft <commit>
```

---

### Mixed reset (default)
```bash
git reset --mixed <commit>
```

---

> [!IMPORTANT]
> Use revert for shared branches. Use reset only locally.

---

# 11. Stash (Temporary Storage)

### Save work temporarily
```bash
git stash
```

---

### Restore stash
```bash
git stash pop
```

---

### View stashes
```bash
git stash list
```

---

> [!NOTE]
> Stash = pause and resume work later

---

# 12. Remote Repository (Sync Layer)

Git connects local work with remote repositories.

---

### Add remote
```bash
git remote add origin <url>
```

---

### View remote
```bash
git remote -v
```

---

### Push changes
```bash
git push origin <branch>
```

---

### Pull changes (fetch + merge)
```bash
git pull
```

---

### Fetch only (no merge)
```bash
git fetch
```

---

> [!IMPORTANT]
> Remote is synchronization, not primary storage.

---

# 13. Git Config (Identity Layer)

---

### Set username
```bash
git config --global user.name "Name"
```

---

### Set email
```bash
git config --global user.email "email"
```

---

### View config
```bash
git config --list
```

---

> [!NOTE]
> This links commits to your identity.

---

# 14. Full Git System Mapping

Every command fits into a layer:

```
Working Directory → git restore / git status
Staging Area      → git add / git restore --staged
Commit History    → git commit / git log
Branching         → git branch / git switch
Merge/Rebase      → git merge / git rebase
Undo              → git reset / git revert
Temporary state   → git stash
Remote sync       → git push / git pull / git fetch
Identity          → git config
```

---

# 15. Final Mental Model

Git is not a command system.

It is a system of:

- snapshots (commits)
- pointers (HEAD, branches, tags)
- states (working, staging, repo)
- transitions (merge, rebase, reset)

---
