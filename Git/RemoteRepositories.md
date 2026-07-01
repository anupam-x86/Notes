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

## Local Branch vs Remote Tracking Branch

> [!SUMMARY]
>
> Git keeps **two separate copies** of your branch:
>
> - **Local branch** → Your working copy.
> - **Remote-tracking branch** → Git's local record of the remote repository.

---

### Visual Model

```
Local Repository                  Remote Repository

main  ────────────────►      origin/main
```

Your local branch (`main`) is where you work.

`origin/main` represents the latest state Git knows about on the remote.

---

### Relationship

```
Local Branch

main

        tracks

origin/main
```

When a branch tracks a remote branch, Git knows:

- where to push changes
- where to pull updates from

---

### What Happens During `git fetch`

Before:

```
Local

main

A ── B

origin/main

A ── B
```

Someone pushes commit **C** to the remote.

After:

```bash
git fetch
```

```
Local

main

A ── B

origin/main

A ── B ── C
```

Notice:

- `origin/main` moves.
- `main` does **not** move.

---

### What Happens During `git pull`

```bash
git pull
```

Internally:

```
git fetch

↓

git merge
```

Result:

```
Local

main

A ── B ── C

origin/main

A ── B ── C
```

Now both branches are synchronized.

---

### What Happens During `git push`

Before:

```
main

A ── B ── C

origin/main

A ── B
```

Run:

```bash
git push
```

After:

```
main

A ── B ── C

origin/main

A ── B ── C
```

The remote branch is updated to match your local branch.

---

> [!IMPORTANT]
> Think of `main` and `origin/main` as **two different pointers**.
>
> Git synchronizes them using `fetch`, `pull`, and `push`.

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
