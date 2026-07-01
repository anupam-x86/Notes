# Repository Management in Git

Now that you understand Git’s internal model (Working Directory → Staging Area → Local Repository → Remote Repository), we can start working with actual repositories.

This chapter focuses on creating, loading, and inspecting repositories.

---

## What is a Repository?

A **Git repository** is a project that Git tracks over time.

It contains:
- Project files
- Full commit history
- Branches
- Configuration data

> [!NOTE]
> A repository is not just a folder. It becomes a repository only after Git tracking is initialized.

---

## Types of Repositories

### 1. Local Repository
A repository stored on your computer.

Characteristics:
- Works offline
- Contains full history
- Created using `git init` or `git clone`

---

### 2. Remote Repository
A repository stored on a server.

Examples:
- GitHub
- GitLab
- Bitbucket

Used for:
- Collaboration
- Backup
- Sharing code between machines

---

## Creating a New Repository (`git init`)

To start Git tracking in a folder:

```bash
git init
```

This command:
- Creates a hidden `.git` directory
- Initializes Git tracking system
- Turns a normal folder into a repository

---

### Example

```bash
mkdir my-project
cd my-project
git init
```

After this:
- Git starts tracking changes in this folder
- You now have a local repository

---

> [!IMPORTANT]
> `git init` does NOT:
> - Create commits
> - Track files automatically
> - Connect to GitHub
>
> It only initializes Git's internal structure.

---

## Checking Repository Status (`git status`)

```bash
git status
```

This command shows the current state of your repository.

It displays:
- Untracked files
- Modified files
- Staged files
- Current branch information

---

### Example Output

```
Untracked files:
  file1.cpp

Changes not staged for commit:
  modified: file2.cpp
```

---

> [!TIP]
> Run `git status` frequently. It is the safest way to understand what Git is doing.

---

## Cloning an Existing Repository (`git clone`)

To copy an existing repository:

```bash
git clone <repository-url>
```

---

### Example

```bash
git clone https://github.com/user/project.git
```

This command:
- Downloads the full project
- Includes complete history
- Sets up remote connection automatically

---

## What `git clone` creates

After cloning:

- A project folder is created
- `.git` directory is included
- Remote is automatically set as `origin`
- All branches are downloaded

---

> [!NOTE]
> `git clone` = copy + history + remote setup

---

## Difference: `git init` vs `git clone`

| Feature | git init | git clone |
|--------|----------|------------|
| Creates new repo | Yes | No |
| Copies existing repo | No | Yes |
| Includes history | No | Yes |
| Sets remote | No | Yes |

---

## The `.git` Folder

When you run `git init`, Git creates a hidden directory:

```
.git/
```

This folder contains:
- Commit history
- Branch data
- Configuration
- Internal Git objects

---

> [!WARNING]
> Deleting `.git` removes Git tracking completely.
>
> Your files remain, but all history is lost.

---

## File States in Git

Git classifies files into four states:

### 1. Untracked
Git does not know about the file.

### 2. Modified
File is being tracked but has changes.

### 3. Staged
Changes are prepared for commit.

### 4. Committed
Changes are saved in history.

---

## How This Connects to Git Architecture

Git repository management is built on the architecture you already learned:

```
Working Directory → edit files
        ↓
Staging Area → select changes
        ↓
Local Repository → save history
        ↓
Remote Repository → share project
```

`git init` and `git clone` simply create or load this structure.

---

## Common Mistakes

> [!WARNING]
> - Running `git init` in the wrong directory
> - Forgetting to check `git status`
> - Assuming Git tracks files automatically
> - Confusing `clone` with `init`
> - Deleting `.git` accidentally

---
