# GitHub Collaboration

> [!NOTE]
> **Purpose:** Learn the standard GitHub workflow used in internships, open-source projects, hackathons, and software companies.

---

## 🎯 Why should I care?

You'll use this in almost every collaborative project.

- ✅ Internships
- ✅ Open Source
- ✅ Team Projects
- ✅ Hackathons
- ✅ Software Engineering Jobs

Without understanding collaboration, knowing Git commands alone isn't enough.

---

## Prerequisites

Before reading this chapter, you should know:

- Git Fundamentals
- Branching and Merging
- Remote Repositories
- Rebasing (recommended)

---

# Table of Contents

## Part 1 — Collaboration Workflow
- Team Workflow
- Local vs Remote
- Feature Branches

## Part 2 — Clone vs Fork

## Part 3 — Pull Requests

## Part 4 — Code Reviews

## Part 5 — Merge Strategies

## Part 6 — Branch Protection

## Part 7 — GitHub Flow

## Cheat Sheet

## Common Mistakes


---

# Part 1 — Collaboration Workflow

## Goal

Develop features **independently** while keeping `main` stable.

Instead of everyone working directly on `main`:

```text
❌ Bad

Developer A ─┐
Developer B ─┼──► main
Developer C ─┘
```

Developers work on separate branches:

```text
✅ Good

                 main
                  │
      ┌───────────┼───────────┐
      │           │           │
feature/auth feature/ui feature/api
```

Each developer can work independently without affecting others.

---

## Standard Workflow

```text
Clone Repository
        │
        ▼
Create Feature Branch
        │
        ▼
Write Code
        │
        ▼
Commit
        │
        ▼
Push
        │
        ▼
Open Pull Request
        │
        ▼
Code Review
        │
        ▼
Merge
        │
        ▼
Delete Feature Branch
```

This is the workflow you'll see in most software teams.

---

## Local vs Remote

```text
Your Computer

Working Directory
        │
        ▼
Local Git Repository
        │
        ▼
GitHub Repository
```

Remember:

- Git manages your local repository.
- GitHub stores the shared remote repository.

---

## Why Feature Branches?

Never develop directly on `main`.

Instead:

```text
main
│
├── feature/login
├── feature/payment
├── feature/profile
└── bugfix/navbar
```

Benefits:

- Isolated development
- Easier reviews
- Safer merges
- Multiple developers can work simultaneously

---

> [!TIP]
> In most companies, developers **cannot push directly to `main`**. Changes are merged through Pull Requests after review.

---

## Key Takeaways

- Every feature gets its own branch.
- `main` should remain stable.
- Collaboration happens through Pull Requests.
- GitHub is the central place where team members exchange changes.

---

# Part 2 — Clone vs Fork

> [!NOTE]
> **Remember**
>
> - **Clone** → Copy a repository to your local machine.
> - **Fork** → Copy a repository to **your GitHub account**.
> - Clone is common in teams.
> - Fork is common in open source.

---

## Why do both exist?

GitHub supports two common collaboration models.

### Team Collaboration

Everyone works on the **same repository**.

```
Company Repository
        │
        ▼
     git clone
        │
        ▼
Local Repository
```

Developers usually have permission to push branches.

---

### Open Source Collaboration

Contributors usually **don't** have write access.

Instead:

```
Original Repository
        │
      Fork
        │
        ▼
 Your GitHub Repository
        │
     git clone
        │
        ▼
Local Repository
```

Changes are later proposed through a Pull Request.

---

## Clone

Creates a **local copy** of a repository.

```bash
git clone <repository-url>
```

Example:

```bash
git clone https://github.com/user/project.git
```

After cloning:

```
GitHub Repository
        │
        ▼
Local Repository
```

Use Clone when:

- Working on your own projects
- Working in a company repository
- You already have repository access

---

## Fork

Creates a **copy of someone else's repository on your GitHub account**.

```
Original Repository
        │
        ▼
Fork
        │
        ▼
Your Repository
```

After forking, you usually clone **your fork**, not the original repository.

```
Original Repository
        │
      Fork
        │
        ▼
git clone
        │
        ▼
Local Repository
```

Use Fork when:

- Contributing to open-source projects
- You don't have write access
- You want your own independent copy

---

## Clone vs Fork

| Clone | Fork |
|-------|------|
| Local copy | GitHub copy |
| Uses `git clone` | Uses GitHub's **Fork** button |
| Doesn't create another GitHub repository | Creates a new repository in your account |
| Common in companies | Common in open source |

---

## Typical Workflows

### Company / Team

```
Repository
    │
git clone
    │
Feature Branch
    │
Commit
    │
Push
    │
Pull Request
```

---

### Open Source

```
Original Repository
        │
      Fork
        │
Clone Fork
        │
Feature Branch
        │
Commit
        │
Push
        │
Pull Request
        │
Original Repository
```

---

> [!TIP]
> In most companies, you'll **clone** the repository.
>
> In most open-source projects, you'll **fork** first, then clone your fork.

---

## Common Mistakes

❌ Thinking Fork and Clone are the same.

❌ Cloning the original repository when you should clone your fork.

❌ Trying to push directly to the original repository without permission.

---

## Key Takeaways

- Clone copies a repository to your computer.
- Fork copies a repository to your GitHub account.
- Team projects usually use **Clone**.
- Open-source contributions usually use **Fork → Clone → Pull Request**.

---

# Part 3 — Pull Requests (PR)

> [!NOTE]
> **Remember**
>
> - A Pull Request (PR) is a request to merge one branch into another.
> - PRs enable discussion and code review before merging.
> - A PR doesn't merge code automatically.

---

## What is a Pull Request?

A Pull Request is a request asking maintainers to review and merge your changes.

```
feature/login
      │
      ▼
Pull Request
      │
      ▼
main
```

Think of it as saying:

> "I've finished my work. Please review it before adding it to the project."

---

## Why not merge directly?

Without PRs:

```
Developer
    │
    ▼
main
```

Problems:

- No review
- Bugs reach production
- No discussion
- Hard to track changes

With PRs:

```
Developer
    │
Feature Branch
    │
    ▼
Pull Request
    │
Code Review
    │
Merge
    │
main
```

---

## Typical PR Workflow

```
Create Branch
      │
      ▼
Write Code
      │
      ▼
Commit
      │
      ▼
Push Branch
      │
      ▼
Open Pull Request
      │
      ▼
Review
      │
      ▼
Make Changes (if requested)
      │
      ▼
Merge
```

---

## Creating a Pull Request

1. Push your branch.

```bash
git push origin feature/login
```

2. Open GitHub.

3. Click **Compare & Pull Request**.

4. Add:
   - Title
   - Description

5. Submit the PR.

---

## PR Title

Good:

```
Add JWT Authentication
```

```
Fix Navbar Overflow
```

```
Improve Database Queries
```

Bad:

```
Update
```

```
Changes
```

```
Fix
```

---

## PR Description

A good PR should answer:

- What changed?
- Why was it changed?
- Anything reviewers should know?

Example:

```text
## Changes

- Added JWT authentication
- Added login middleware
- Updated API documentation

## Testing

- Tested login
- Tested logout
- Existing tests passed
```

---

## Updating a Pull Request

You don't create another PR.

Simply commit more changes.

```bash
git add .

git commit -m "Address review comments"

git push
```

The existing PR updates automatically.

---

## Draft Pull Requests

Sometimes your work isn't finished yet.

Create a **Draft PR** when:

- You want early feedback.
- Work is still in progress.
- Not ready to merge.

```
🚧 Draft PR

↓

Discussion

↓

Complete Work

↓

Ready for Review
```

---

## Closing vs Merging

**Merge**

- Changes become part of the target branch.

**Close**

- PR is rejected or abandoned.
- No code is merged.

---

> [!TIP]
> Keep Pull Requests small.
>
> Reviewing 200 lines is much easier than reviewing 2,000.

---

## Common Mistakes

❌ One PR containing multiple unrelated features.

❌ Opening a PR directly from `main`.

❌ Poor PR titles.

❌ No description.

❌ Ignoring review comments.

---

## Key Takeaways

- A Pull Request requests a merge.
- PRs encourage review and discussion.
- Push new commits to update an existing PR.
- Keep PRs focused on one feature or fix.

---

# Part 4 — Code Reviews

> [!NOTE]
> **Remember**
>
> - Every Pull Request should be reviewed.
> - The goal is to improve the code, **not criticize the developer**.
> - Reviews improve code quality and help share knowledge.

---

## What is a Code Review?

A Code Review is the process of examining code before it is merged into the project.

Typical workflow:

```
Developer
    │
    ▼
Open Pull Request
    │
    ▼
Reviewer
    │
    ▼
Review Code
    │
    ▼
Approve / Request Changes
```

---

## Why Code Reviews?

Benefits:

- Catch bugs early
- Improve code quality
- Maintain coding standards
- Share knowledge across the team
- Prevent accidental mistakes

A second pair of eyes often catches things the author misses.

---

## Review Outcomes

A reviewer usually chooses one of these:

### ✅ Approve

Looks good and is ready to merge.

```
PR
 │
 ▼
Approved
 │
 ▼
Merge
```

---

### 🔄 Request Changes

The code works, but improvements are needed before merging.

Examples:

- Bug found
- Missing tests
- Better naming
- Style issues
- Logic improvements

---

### 💬 Comment

No approval or rejection.

Used for:

- Asking questions
- Suggesting improvements
- Starting discussions

---

## Typical Review Cycle

```
Open PR
    │
    ▼
Review
    │
    ▼
Feedback
    │
    ▼
Update Code
    │
    ▼
Push Changes
    │
    ▼
Review Again
    │
    ▼
Merge
```

You don't need to open another PR.

Simply push new commits.

---

## Good Review Comments

Examples:

```
Can this function be simplified?
```

```
Consider renaming this variable.
```

```
Great implementation!
```

```
Please add a test for this case.
```

Focus on the code—not the person.

---

## Review Etiquette

### As the Author

✅ Explain your changes clearly.

✅ Respond politely to feedback.

✅ Ask questions if something is unclear.

✅ Update your code when necessary.

---

### As the Reviewer

✅ Be respectful.

✅ Explain *why* a change is suggested.

✅ Praise good code when appropriate.

✅ Review the code, not the developer.

---

> [!TIP]
> Treat review comments as learning opportunities.
>
> Even experienced developers receive review feedback every day.

---

## Common Mistakes

❌ Taking review comments personally.

❌ Approving code without reading it.

❌ Leaving vague comments like:

```
Bad code.
```

Instead explain **why** something should change.

---

## Key Takeaways

- Code reviews improve quality and maintainability.
- Reviews are collaborative, not competitive.
- Most PRs go through one or more review rounds.
- Professional communication is just as important as technical skills.

---

# Part 5 — Merge Strategies

> [!NOTE]
> **Remember**
>
> GitHub provides three ways to merge a Pull Request:
>
> - **Merge Commit** → Preserve complete history.
> - **Squash Merge** → Combine commits into one.
> - **Rebase Merge** → Linear history without a merge commit.
>
> Choose the strategy based on the project's workflow.

---

## Why Multiple Merge Strategies?

Suppose a feature branch has several commits.

```
main

A ── B

feature/login

      └── C ── D ── E
```

When the feature is finished, GitHub asks **how** it should be merged.

Different projects prefer different histories.

---

# 1. Merge Commit

Creates a **new merge commit** that combines both branches.

```
Before

main

A ── B

      \
       C ── D ── E
```

```
After

A ── B ─────── M
      \       /
       C ── D ── E
```

Where:

- `M` = Merge Commit

---

### Advantages

- Preserves complete history
- Shows exactly when branches were merged
- Good for long-running feature branches

---

### Disadvantages

- History becomes more complex
- Many merge commits can clutter the commit graph

---

### Best Used When

- Working in teams
- Long feature branches
- History is important

---

# 2. Squash Merge

Combines all commits into **one commit** before merging.

```
Before

feature

C ── D ── E
```

```
After

main

A ── B ── S
```

Where:

- `S` = Squashed commit containing all changes

---

### Advantages

- Clean history
- One commit per feature
- Easier to read `git log`

---

### Disadvantages

- Original commit history is lost
- Individual commits cannot be reviewed later

---

### Best Used When

- Small features
- Open Source contributions
- Repositories with a clean-history policy

---

# 3. Rebase Merge

GitHub rebases the feature branch onto the latest target branch.

```
Before

A ── B

      \
       C ── D
```

```
After

A ── B ── C' ── D'
```

Notice:

```
C'
D'
```

are **new commits**.

Their commit hashes change because history is rewritten.

---

### Advantages

- Clean, linear history
- No merge commit
- Easy to follow project history

---

### Disadvantages

- Commit hashes change
- Can be confusing if you don't understand rebasing

---

### Best Used When

- Teams prefer linear history
- Small feature branches
- Projects using a rebase workflow

---

# Comparison

| Strategy | Merge Commit | Squash Merge | Rebase Merge |
|-----------|--------------|--------------|--------------|
| Merge Commit Created | ✅ | ❌ | ❌ |
| Preserves Commit History | ✅ | ❌ | ✅ |
| Linear History | ❌ | ✅ | ✅ |
| Clean `git log` | ⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐⭐ |

---

# Which One Should I Use?

There is no universally "best" option.

It depends on the project's workflow.

General guideline:

| Situation | Recommended |
|-----------|-------------|
| Company projects | Merge Commit or Rebase Merge |
| Open Source | Squash Merge is common |
| Personal projects | Any (choose a consistent style) |

Always follow the project's contribution guidelines.

---

> [!TIP]
> Before contributing to a repository, check how previous Pull Requests were merged.
>
> Match the existing workflow instead of introducing a different one.

---

# Common Mistakes

❌ Choosing a merge strategy without understanding its impact.

❌ Assuming Squash Merge preserves individual commits.

❌ Rebasing shared branches without team agreement.

---

# Key Takeaways

- Merge Commit preserves the complete branch history.
- Squash Merge combines all feature commits into one.
- Rebase Merge creates a clean, linear history.
- Different projects use different strategies—follow the project's conventions.

  ---

# Part 6 — Branch Protection

> [!NOTE]
> **Remember**
>
> Branch Protection prevents important branches (e.g., `main`) from being modified accidentally or without review.

---

## Why Branch Protection?

Imagine every developer can push directly to `main`.

```
Developer A ─┐
Developer B ─┼──► main
Developer C ─┘
```

Problems:

- Bugs can reach production.
- Unreviewed code gets merged.
- Anyone can accidentally overwrite important code.

Instead, teams protect important branches.

```
Developer
    │
Feature Branch
    │
Pull Request
    │
Code Review
    │
Merge
    │
main
```

---

## Common Branch Protection Rules

A repository can require:

- ✅ Pull Request before merging
- ✅ At least one approval
- ✅ All CI/CD checks pass
- ✅ Branch is up to date
- ✅ No direct pushes to `main`

---

## Typical Protected Workflow

```
Create Feature Branch
        │
        ▼
Develop Feature
        │
        ▼
Open Pull Request
        │
        ▼
Review + Checks
        │
        ▼
Merge into main
```

Direct pushes to `main` are blocked.

---

## Why It's Useful

Benefits:

- Prevents accidental mistakes.
- Improves code quality.
- Ensures every change is reviewed.
- Keeps the default branch stable.

---

> [!TIP]
> In most companies, `main` (or `master`) is protected by default.
>
> Developers work on feature branches and merge through Pull Requests.

---

## Common Mistakes

❌ Developing directly on `main`.

❌ Disabling protection without a valid reason.

❌ Merging without reviewing failed CI/CD checks.

---

## Key Takeaways

- Protect important branches like `main`.
- Use Pull Requests instead of direct pushes.
- Require reviews and automated checks before merging.
- Branch Protection helps maintain a stable codebase.

  ---

# Part 7 — GitHub Flow

> [!NOTE]
> **Remember**
>
> GitHub Flow is a lightweight branching workflow used by many teams.
>
> ```
> main
>   ↓
> Feature Branch
>   ↓
> Commit
>   ↓
> Push
>   ↓
> Pull Request
>   ↓
> Review
>   ↓
> Merge
>   ↓
> Delete Branch
> ```

---

## What is GitHub Flow?

GitHub Flow is a simple workflow for developing features without affecting the stable branch.

Instead of working directly on `main`, every change is developed on its own branch.

---

## Workflow

### 1. Start from `main`

```
main
```

Make sure it's up to date.

---

### 2. Create a Feature Branch

```
main
  │
  └── feature/login
```

```bash
git switch -c feature/login
```

---

### 3. Develop the Feature

```
feature/login

Commit 1

↓

Commit 2

↓

Commit 3
```

Commit regularly with meaningful messages.

---

### 4. Push the Branch

```bash
git push origin feature/login
```

Your branch is now available on GitHub.

---

### 5. Open a Pull Request

```
feature/login

↓

Pull Request

↓

main
```

Explain:

- What changed
- Why it changed
- Anything reviewers should know

---

### 6. Code Review

Possible outcomes:

```
Approve
```

or

```
Request Changes
```

or

```
Comment
```

If changes are requested:

```
Fix

↓

Commit

↓

Push
```

The Pull Request updates automatically.

---

### 7. Merge

Once approved:

```
feature/login

↓

Merge

↓

main
```

Choose the project's preferred merge strategy.

---

### 8. Delete the Feature Branch

After merging:

```
feature/login

❌ Delete
```

Keeping old branches around makes repositories harder to navigate.

Deleting the branch **does not delete** the merged commits.

---

## Complete Workflow

```
main
  │
  ▼
Create Feature Branch
  │
  ▼
Develop Feature
  │
  ▼
Commit
  │
  ▼
Push
  │
  ▼
Open Pull Request
  │
  ▼
Code Review
  │
  ▼
Merge
  │
  ▼
Delete Branch
```

---

> [!TIP]
> One feature (or bug fix) should usually have **one branch** and **one Pull Request**.

---

## Why GitHub Flow?

Benefits:

- Easy to learn
- Keeps `main` stable
- Supports parallel development
- Encourages code review
- Works well for continuous development

---

## When is GitHub Flow Used?

Common in:

- Open Source projects
- Startups
- Small to medium teams
- Web applications with frequent deployments

Large organizations may use more complex workflows, but GitHub Flow is an excellent foundation.

---

## Key Takeaways

- Keep `main` stable.
- Create a branch for every feature or fix.
- Open a Pull Request for review.
- Merge after approval.
- Delete the feature branch once merged.

---

# Cheat Sheet

## Standard Team Workflow

```text
Clone
  ↓
Create Branch
  ↓
Develop
  ↓
Commit
  ↓
Push
  ↓
Pull Request
  ↓
Code Review
  ↓
Merge
  ↓
Delete Branch
```

---

## Common Commands

### Clone a Repository

```bash
git clone <repository-url>
```

---

### Create & Switch to a Branch

```bash
git switch -c feature/login
```

---

### Push a New Branch

```bash
git push -u origin feature/login
```

---

### Push Updates

```bash
git push
```

---

### Keep Local `main` Updated

```bash
git switch main
git pull origin main
```

---

### Delete Local Branch

```bash
git branch -d feature/login
```

---

### Delete Remote Branch

```bash
git push origin --delete feature/login
```

---

# Common Mistakes

### ❌ Working directly on `main`

✔ Create a feature branch first.

---

### ❌ One Pull Request for multiple features

✔ One feature (or bug fix) = One Pull Request.

---

### ❌ Large Pull Requests

✔ Keep PRs small and focused.

---

### ❌ Poor Commit Messages

Bad:

```
Update
```

Good:

```
Fix login validation
```

```
Add user profile page
```

```
Refactor authentication middleware
```

---

### ❌ Ignoring Review Feedback

Review comments are meant to improve the code, not criticize the developer.

---

### ❌ Forgetting to Sync Before Starting Work

Before creating a new branch:

```bash
git switch main
git pull origin main
```

---

### ❌ Keeping Old Branches Forever

Delete merged branches to keep the repository clean.

---

# Best Practices

✅ One branch per feature.

✅ One Pull Request per branch.

✅ Write meaningful commit messages.

✅ Write clear PR titles and descriptions.

✅ Review code respectfully.

✅ Keep `main` deployable.

✅ Delete merged branches.

✅ Follow the repository's contribution guidelines.

---
