# Git Best Practices

Using Git effectively is not about knowing every command—it is about creating a clean, understandable, and maintainable project history.

---

## Commit Frequently

Create commits whenever a logical unit of work is complete.

Good:
- Fix login validation
- Add authentication middleware
- Update documentation

Avoid:
- One large commit containing unrelated changes

---

## Commit Discipline (Maintaining Clean History)

Good Git history is not accidental—it is intentional.

### Follow this pattern:
- One feature = multiple small commits
- Each commit should be reversible independently
- Avoid mixing refactor + feature + bug fix

### Avoid:
- WIP dumps ("work in progress")
- unrelated changes in one commit
- fixing multiple bugs in one commit

---

## Write Meaningful Commit Messages

A commit message should describe **what changed**.

Good:

```text
Add user authentication
Fix memory leak in parser
Update README installation guide
```

Poor:

```text
update
fix
changes
test
```

---

## Keep Commits Focused

Each commit should represent **one logical change**.

Instead of:

```
Fix bug
Add feature
Update documentation
```

Create separate commits for each task.

This makes history easier to understand and revert.

---

## Use Branches for New Work

Avoid developing directly on `main`.

Create a separate branch for:

- new features
- bug fixes
- experiments
- refactoring

Example:

```bash
git switch -c feature/login
```

---

## Pull Before Push

Before pushing your work:

```bash
git pull
```

This helps synchronize your branch with the remote repository and reduces merge conflicts.

---

## Review Changes Before Committing

Use:

```bash
git status
git diff
```

Verify:
- which files changed
- what changed
- what will be committed

---

## Shared History Safety Rule

Once commits are pushed to a shared repository:

- ❌ Do NOT use `git reset --hard`
- ❌ Do NOT rebase shared commits
- ✔ Use `git revert` for undoing changes safely

### Rule of thumb:
> If others can see it → do not rewrite it

---

## Keep `.gitignore` Updated

Ignore files that do not belong in version control.

Common examples:

- build output
- dependencies
- logs
- temporary files
- environment files

---

> [!IMPORTANT]
> Never commit secrets such as API keys, passwords, or private certificates.

---

## Avoid Force Push

```bash
git push --force
```

Force pushing rewrites remote history.

Use it only when you fully understand its impact.

---

## Resolve Conflicts Carefully

When a merge conflict occurs:

1. Read both versions.
2. Decide the correct result.
3. Test the project.
4. Commit the resolved changes.

Do not resolve conflicts without understanding them.

---

## Make Small Changes

Small commits are:

- easier to review
- easier to test
- easier to revert
- easier to understand

---

## Keep the Repository Clean

A repository should contain:

- source code
- required configuration
- documentation

Avoid committing:

- generated files
- IDE settings (unless shared)
- build artifacts
- temporary files

---

## Common Mistakes

> [!WARNING]
>
> - Working directly on `main`
> - Forgetting to pull before pushing
> - Creating very large commits
> - Using unclear commit messages
> - Ignoring merge conflicts
> - Accidentally committing sensitive files
> - Deleting `.git`
> - Using `git reset --hard` without understanding it

---

## Common Workflow Patterns

### Feature development
```
git switch -c feature/name
git add .
git commit -m "feature work"
git push origin feature/name
```

### Bug fix
```
git switch -c fix/issue-name
git add .
git commit -m "fix bug"
git push
```

### Safe sync
```
git pull
git add .
git commit -m "update"
git push
```

----
# Git Workflow Summary

```
Create repository
        ↓
Edit files
        ↓
git status
        ↓
git add
        ↓
git commit
        ↓
git pull
        ↓
git push
```

---

# Git Mental Model

```
Working Directory
        ↓
Staging Area (Index)
        ↓
Local Repository
        ↓
Remote Repository
```

Remember:

- Working Directory → where you edit files
- Staging Area → what will be committed
- Local Repository → project history
- Remote Repository → shared repository

---

# Essential Commands

| Command | Purpose |
|----------|---------|
| `git init` | Initialize a repository |
| `git clone` | Copy an existing repository |
| `git status` | Show repository status |
| `git add` | Stage changes |
| `git commit` | Create a snapshot |
| `git log` | View commit history |
| `git diff` | Compare changes |
| `git branch` | List or create branches |
| `git switch` | Switch branches |
| `git merge` | Merge branches |
| `git restore` | Discard local changes |
| `git reset` | Unstage or move branch pointer |
| `git revert` | Undo a commit safely |
| `git stash` | Temporarily save changes |
| `git fetch` | Download remote updates |
| `git pull` | Fetch and merge updates |
| `git push` | Upload commits |

---

# Core Principles

Remember these ideas:

- Git records **snapshots**, not file versions.
- Commits are the permanent units of history.
- Stage only the changes you intend to commit.
- Branches are lightweight pointers to commits.
- Remotes synchronize repositories—they do not replace local history.
- Check `git status` before running most Git commands.

---
