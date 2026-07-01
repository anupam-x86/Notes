# Git Commands and Uses (Core Workflow)

> [!NOTE]
> **Purpose:** A task-oriented reference for Git commands organized around the Git workflow. Use this file as a quick lookup while working on projects.

---

## 🎯 Why should I care?

Instead of memorizing every Git command, understand **what you want to do**, then find the corresponding command.

---

# Table of Contents

1. Working Directory
2. Staging Area
3. Commit System
4. Core Workflow Loop
5. Branching System
6. Merging
7. Rebasing
8. Tags
9. Timeline Model
10. Undo System
11. Stash
12. Remote Repository
13. Repository Management
14. File Inspection
15. Branch Management
16. Remote Branch Management
17. Repository Maintenance
18. Git Config
19. Git Aliases
20. Daily Git Workflow
21. Command Relationships
22. Full Git System Mapping
23. Final Mental Model

---

# 1. Working Directory (Your Files)

This is where you edit your project files.

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

### View changes

```bash
git diff
```

Shows line-by-line changes that haven't been staged.

---

### Discard local changes

```bash
git restore <file>
```

Restores the file to its last committed state.

---

> [!IMPORTANT]
> This only affects local uncommitted changes.

---

# 2. Staging Area (Selection Layer)

The staging area determines what goes into the next commit.

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

Moves the file back to the working directory while keeping its changes.

---

> [!NOTE]
> The staging area is a temporary selection layer, not permanent storage.

---

# 3. Commit System (Snapshots)

Commits record snapshots of your project.

---

### Create commit

```bash
git commit -m "message"
```

---

### Modify previous commit

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

### Show current commit

```bash
git rev-parse HEAD
```

Returns the current commit hash.

---

# 4. Core Workflow Loop

The basic Git development cycle:

```text
Edit
 ↓
git status
 ↓
git add
 ↓
git commit
```

Or conceptually:

```text
Working Directory
        ↓
Staging Area
        ↓
Repository
```

---

# 5. Branching System (Timeline Layer)

Branches are movable pointers to commits.

---

### Create branch

```bash
git branch <name>
```

---

### Switch branch

```bash
git switch <name>
```

---

### Create and switch

```bash
git switch -c <name>
```

---

### List branches

```bash
git branch
```

---

> [!IMPORTANT]
> A branch is **not** a copy of your project. It is simply a pointer to the latest commit.

---

# 6. Merging (Combining Timelines)

Merge combines two branches.

---

### Merge branch

```bash
git merge <branch>
```

---

Merge:

- combines histories
- may create a merge commit
- preserves branch history

---

> [!NOTE]
> Merge focuses on preserving the development history.

---

# 7. Rebasing (History Rewrite)

Rebase moves commits onto a new base.

---

### Rebase current branch

```bash
git rebase <branch>
```

---

Rebase:

- rewrites commit history
- creates a linear history
- avoids unnecessary merge commits

---

### Continue after conflict

```bash
git add <file>
git rebase --continue
```

---

### Abort rebase

```bash
git rebase --abort
```

---

> [!WARNING]
> Avoid rebasing commits that have already been shared with others.

---

# 8. Tags (Version Markers)

Tags mark important commits, such as releases.

---

### Create lightweight tag

```bash
git tag <name>
```

---

### Create annotated tag

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
> Tags are fixed references. They do not move like branches.

---

# 9. Timeline Model

Branching:

```text
A → B → C
     ↘
      D → E
```

After Merge:

```text
A → B → C → M
          ↗
        D → E
```

After Rebase:

```text
A → B → C → D → E
```

---

# 10. Undo System (Correction Layer)

Choose the appropriate undo command based on what you want to undo.

---

## A) Working Directory

### Discard local changes

```bash
git restore <file>
```

---

## B) Staging Area

### Unstage a file

```bash
git restore --staged <file>
```

---

## C) Commit History

### Safe undo

```bash
git revert <commit>
```

Creates a new commit that reverses changes.

---

### Hard reset

```bash
git reset --hard <commit>
```

Moves the branch pointer and discards local changes.

---

### Soft reset

```bash
git reset --soft <commit>
```

Moves the branch pointer but keeps changes staged.

---

### Mixed reset (default)

```bash
git reset --mixed <commit>
```

Moves the branch pointer and unstages changes.

---

> [!IMPORTANT]
> Use `git revert` for shared history.
>
> Use `git reset` only when rewriting local history.

---

# 11. Stash (Temporary Storage)

Temporarily save unfinished work.

---

### Save current work

```bash
git stash
```

---

### Restore latest stash

```bash
git stash pop
```

---

### List stashes

```bash
git stash list
```

---

### Apply stash without removing it

```bash
git stash apply
```

---

### Delete a stash

```bash
git stash drop
```

---

> [!NOTE]
> Stash lets you pause work and return to it later without creating unnecessary commits.

# 12. Remote Repository (Synchronization Layer)

Remote repositories allow multiple developers to collaborate by synchronizing local repositories.

---

### Add remote

```bash
git remote add origin <url>
```

Connects your local repository to a remote repository.

---

### View remotes

```bash
git remote -v
```

Lists all configured remote repositories.

---

### Push changes

```bash
git push origin <branch>
```

Uploads local commits to the remote repository.

---

### Push and set upstream

```bash
git push -u origin <branch>
```

Pushes the branch and remembers its upstream.

---

### Fetch changes

```bash
git fetch
```

Downloads remote changes without modifying your current branch.

---

### Pull changes

```bash
git pull
```

Downloads and merges remote changes into the current branch.

---

> [!IMPORTANT]
> `git fetch` downloads changes.
>
> `git pull` = `git fetch` + `git merge` (or rebase depending on configuration).

---

# 13. Repository Management

Manage repositories from creation to cloning.

---

### Initialize repository

```bash
git init
```

Creates a new Git repository.

---

### Clone repository

```bash
git clone <url>
```

Creates a local copy of an existing repository.

---

### Show repository root

```bash
git rev-parse --show-toplevel
```

Displays the root directory of the current repository.

---

### Show Git version

```bash
git --version
```

Displays the installed Git version.

---

> [!NOTE]
> Use `git init` for new projects.
>
> Use `git clone` for existing repositories.

---

# 14. File Inspection

Inspect files and commits before making changes.

---

### View staged changes

```bash
git diff --staged
```

Shows changes that will be included in the next commit.

---

### Compare two commits

```bash
git diff <commit1> <commit2>
```

Shows differences between two commits.

---

### Show commit details

```bash
git show <commit>
```

Displays commit metadata and changes.

---

### Show current commit

```bash
git show HEAD
```

Displays the latest commit.

---

### Show current commit hash

```bash
git rev-parse HEAD
```

Prints the current commit hash.

---

> [!TIP]
> Review changes before committing to avoid accidental mistakes.

---

# 15. Branch Management

Manage local branches.

---

### Delete merged branch

```bash
git branch -d <branch>
```

Deletes a branch that has already been merged.

---

### Force delete branch

```bash
git branch -D <branch>
```

Deletes a branch even if it hasn't been merged.

---

### Rename current branch

```bash
git branch -m <new-name>
```

Renames the current branch.

---

### View branch tracking

```bash
git branch -vv
```

Shows upstream tracking information.

---

> [!IMPORTANT]
> Delete feature branches after merging to keep the repository clean.

---

# 16. Remote Branch Management

Manage branches on remote repositories.

---

### List remote branches

```bash
git branch -r
```

---

### List all branches

```bash
git branch -a
```

Shows local and remote branches.

---

### Delete remote branch

```bash
git push origin --delete <branch>
```

Removes a branch from the remote repository.

---

### Fetch all remotes

```bash
git fetch --all
```

Downloads updates from every configured remote.

---

> [!NOTE]
> Remote branches are read-only references until checked out locally.

---

# 17. Repository Maintenance

Optimize and maintain repository health.

---

### Garbage collection

```bash
git gc
```

Optimizes storage and compresses repository data.

---

### Verify repository

```bash
git fsck
```

Checks repository integrity.

---

### Remove untracked files

```bash
git clean -fd
```

Deletes untracked files and directories.

---

### Count Git objects

```bash
git count-objects -v
```

Shows object database statistics.

---

### Remove stale remote references

```bash
git remote prune origin
```

Removes references to deleted remote branches.

---

> [!WARNING]
> `git clean -fd` permanently deletes untracked files.

---

# 18. Git Config (Identity Layer)

Configure Git for your user account.

---

### Set username

```bash
git config --global user.name "Your Name"
```

---

### Set email

```bash
git config --global user.email "you@example.com"
```

---

### View configuration

```bash
git config --list
```

Displays all Git configuration values.

---

### Edit global configuration

```bash
git config --global --edit
```

Opens the global Git configuration file.

---

> [!NOTE]
> Git records your configured name and email in every commit.

---

# 19. Git Aliases

Aliases shorten frequently used commands.

---

### Create alias

```bash
git config --global alias.st status
```

Now:

```bash
git st
```

works the same as:

```bash
git status
```

---

### Useful aliases

```bash
git config --global alias.st status

git config --global alias.br branch

git config --global alias.sw switch

git config --global alias.cm commit

git config --global alias.co checkout

git config --global alias.lg "log --oneline --graph --decorate --all"
```

---

> [!TIP]
> Use aliases only for commands you type frequently.

---

# 20. Daily Git Workflow

A common feature development workflow.

---

## Start New Work

```text
Switch to main
        ↓
git pull
        ↓
Create feature branch
```

---

## Develop Feature

```text
Edit Files
      ↓
git status
      ↓
git add
      ↓
git commit
```

---

## Share Work

```text
git push
      ↓
Open Pull Request
      ↓
Code Review
      ↓
Merge
```

---

## Finish Feature

```text
Delete Feature Branch
        ↓
Switch to main
        ↓
git pull
```

---

> [!IMPORTANT]
> One feature → One branch → One Pull Request.

---

# 21. Command Relationships

Git commands represent transitions between repository states.

---

Development Flow

```text
Working Directory
        │
git status
        │
        ▼
git add
        │
        ▼
Staging Area
        │
git commit
        ▼
Repository
        │
git push
        ▼
Remote Repository
```

---

Undo Flow

```text
Working Directory
        │
git restore
        ▼
Staging Area
        │
git restore --staged
        ▼
Repository
        │
git revert / git reset
```

---

Synchronization Flow

```text
Remote Repository
       ▲
       │
git push
       │
Local Repository
       │
git fetch
       ▼
Remote Repository
```

---

# 22. Full Git System Mapping

Every Git command belongs to one layer.

```text
Repository Setup
│
├── git init
├── git clone
└── git remote

Working Directory
│
├── git status
├── git diff
└── git restore

Staging Area
│
├── git add
└── git restore --staged

Commit History
│
├── git commit
├── git log
├── git show
└── git revert

Branches
│
├── git branch
├── git switch
├── git merge
└── git rebase

Remote
│
├── git fetch
├── git pull
└── git push

Maintenance
│
├── git gc
├── git fsck
├── git clean
└── git remote prune
```

---

# 23. Final Mental Model

Git is not just a collection of commands.

It is a system built around:

- Snapshots (Commits)
- References (Branches, Tags, HEAD)
- States (Working Directory, Staging Area, Repository)
- Transitions (Add, Commit, Merge, Rebase, Reset)
- Synchronization (Fetch, Pull, Push)

---

## Complete Git Workflow

```text
                 Edit Files
                     │
                     ▼
            Working Directory
                     │
               git status
                     │
               git restore
                     ▼
              git add
                     ▼
             Staging Area
                     │
       git restore --staged
                     ▼
              git commit
                     ▼
              Local Repository
             /      |       \
            /       |        \
       Branches   Tags      HEAD
            \       |        /
             \      |       /
               Commit Graph
                     │
         git push / git fetch / git pull
                     ▼
            Remote Repository
```

---

> [!SUMMARY]
>
> Remember the core flow:
>
> ```text
> Edit
>   ↓
> Status
>   ↓
> Stage
>   ↓
> Commit
>   ↓
> Push
> ```
>
> Most Git commands are simply tools for moving between these stages safely and efficiently.
