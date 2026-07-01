# Remote Repositories in Git

A remote repository is a version of your project stored on another machine, usually a server.

It allows multiple developers to work on the same project.

Common platforms:
- GitHub
- GitLab
- Bitbucket

---

## Why Remote Repositories Exist

Git locally is powerful, but limited to one machine.

Remote repositories enable:
- collaboration
- backup
- sharing code
- working across devices

---

> [!NOTE]
> Remote repository = shared synchronization point, not just a backup.

---

## Local vs Remote

Local repo:
- exists on your computer
- full control
- offline work

Remote repo:
- exists on server
- shared with others
- sync point for collaboration

---

## Connecting to Remote (`git remote`)

To link local repo to remote:

```bash
git remote add origin <url>
```

---

### Example

```bash
git remote add origin https://github.com/user/project.git
```

---

## Checking Remote

```bash
git remote -v
```

Shows:
- fetch URL
- push URL

---

## Pushing Changes (`git push`)

Uploads local commits to remote.

```bash
git push origin main
```

---

### What happens:
- local commits → remote repo
- updates GitHub branch

---

> [!IMPORTANT]
> git push only sends commits, not working files.

---

## Pulling Changes (`git pull`)

Fetch + merge in one step:

```bash
git pull origin main
```

---

It:
- downloads changes
- merges into local branch

---

## Fetching Changes (`git fetch`)

```bash
git fetch
```

Downloads changes but does NOT merge them.

---

### Difference:

| Command | Downloads | Merges |
|--------|----------|--------|
| fetch | yes | no |
| pull | yes | yes |

---

## Remote Workflow

```
Local repo → commit → push → Remote repo
Remote repo → fetch/pull → Local repo
```

---

## Tracking Branches

When you clone:

```
main → origin/main
```

This links local branch to remote branch.

---

## Common Mistakes

> [!WARNING]

- forgetting to pull before push
- force pushing without understanding
- pushing unfinished work
- not setting upstream branch

---

## Safe Workflow Pattern

```
pull → work → add → commit → push
```

---

## Why Remotes Matter

Remote repositories enable:
- teamwork
- backup safety
- distributed development
- CI/CD integration

---
