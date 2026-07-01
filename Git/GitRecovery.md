# Git Recovery

> [!NOTE]
> This chapter covers Git's recovery tools and techniques for restoring lost work, recovering from mistakes, and debugging problems. Most Git mistakes are recoverable if you know the right tool to use.

---

# Table of Contents

1. [Recovery vs Undo](#recovery-vs-undo)
2. [Why Recovery is Possible](#why-recovery-is-possible)
3. [Git Reflog](#git-reflog)
   - What is Reflog?
   - Reflog vs Git Log
   - Viewing Reflog
   - Recovering Lost Commits
   - Recovering Deleted Branches
   - Recovering Detached HEAD
4. [Git Cherry-pick](#git-cherry-pick)
   - What is Cherry-pick?
   - Merge vs Cherry-pick
   - Basic Usage
   - Cherry-pick Conflicts
   - Real-world Uses
5. [Git Bisect](#git-bisect)
   - What is Git Bisect?
   - Binary Search
   - Starting a Bisect Session
   - Automatic Bisect
6. [Recovery Decision Tree](#recovery-decision-tree)
7. [Common Recovery Scenarios](#common-recovery-scenarios)
8. [Recovery Cheat Sheet](#recovery-cheat-sheet)
9. [Best Practices](#best-practices)
10. [Common Mistakes](#common-mistakes)
11. [Mental Model](#mental-model)
12. [NOTE](#NOTE)

---

Mistakes are inevitable in software development.

You may accidentally:
- delete commits
- delete branches
- reset your branch to the wrong commit
- commit on the wrong branch
- lose work while experimenting

Fortunately, Git is designed to make most of these mistakes recoverable.

Unlike traditional file systems, Git rarely deletes data immediately. Most "lost" work still exists somewhere inside Git until it is eventually cleaned up.

This chapter explains how Git helps you recover from common mistakes and introduces the tools designed specifically for recovery.

---

## Recovery vs Undo

Although they sound similar, **undoing changes** and **recovering lost work** are different concepts.

### Undo

Undo changes that are still under your control.

Examples:
- discard local edits
- unstage files
- revert a commit

Common commands:

```bash
git restore
git reset
git revert
git stash
```

These commands modify your current work or history intentionally.

---

### Recovery

Recovery is used when something appears to be **lost**.

Examples:

- accidentally deleting commits
- deleting a branch
- using `git reset --hard`
- making commits in detached HEAD
- recovering an old version

Recovery usually involves locating existing Git objects rather than creating new ones.

Common tools:

```bash
git reflog
git cherry-pick
git bisect
```

---

> [!IMPORTANT]
> Undo changes modifies history or working files.
>
> Recovery finds work that already exists but is no longer easy to reach.

---

# Why Recovery is Possible

Many beginners believe that once something disappears from a branch, it has been permanently deleted.

Usually this is false.

Git stores commits separately from branch names.

Consider this history:

```
main

A → B → C → D
```

Here:

```
main
 │
 ▼
 D
```

The branch is only pointing to commit **D**.

If you move the branch:

```
git reset --hard B
```

Git changes only the pointer.

```
main

A → B

C → D
```

Commits **C** and **D** still exist.

The branch no longer points to them, but Git still remembers they existed.

Recovery simply means finding those commits again.

---

## The Golden Rule

> [!IMPORTANT]
> Git almost never loses commits immediately.
>
> It usually loses **references** to commits.

Understanding this single idea explains why recovery is often possible.

---

# Git Reflog

The most important recovery tool in Git is **Reflog**.

If you learn only one recovery command, learn this one.

---

## What is Reflog?

Reflog (Reference Log) records every movement of important Git references such as:

- HEAD
- branch pointers

Whenever you:

- commit
- checkout
- merge
- reset
- rebase
- switch branches

Git records that movement.

Think of Reflog as a history of **where HEAD has been**.

---

## Reflog vs Git Log

Many beginners confuse these two commands.

### Git Log

```bash
git log
```

Shows:

- project history
- commits reachable from the current branch

Example:

```
A → B → C → D
```

---

### Git Reflog

```bash
git reflog
```

Shows:

- every movement of HEAD
- commits that may no longer belong to any branch
- recent history of your Git operations

Even if a commit disappears from `git log`, it may still appear in `git reflog`.

---

## Viewing Reflog

```bash
git reflog
```

Example:

```
7fd8123 HEAD@{0}: commit: Fix login bug

a13bd91 HEAD@{1}: reset: moving to HEAD~1

bc92aa1 HEAD@{2}: commit: Add login page

81da443 HEAD@{3}: checkout: moving from feature to main
```

Each entry records:

- commit hash
- reference position
- Git action

---

## Understanding `HEAD@{n}`

> [!NOTE]
>
> Every entry in the reflog is a previous position of **HEAD**.
>
> `HEAD@{0}` is your current position.
>
> Older numbers represent older HEAD positions.

---

### Visual Model

```
HEAD@{0}

↓

Current Position

------------------

HEAD@{1}

↓

Previous Position

------------------

HEAD@{2}

↓

Earlier Position

------------------

HEAD@{3}

↓

Even Earlier Position
```

---

### Example

Suppose your reflog shows:

```text
abc1234 HEAD@{0}: commit: Update README
def5678 HEAD@{1}: reset --hard HEAD~1
ghi9012 HEAD@{2}: commit: Add login feature
```

This means:

- `HEAD@{0}` → Current position
- `HEAD@{1}` → Position before the reset
- `HEAD@{2}` → Even earlier position

---

### Recover a Previous State

Move back to an earlier HEAD position:

```bash
git reset --hard HEAD@{1}
```

Or inspect an older commit:

```bash
git switch --detach HEAD@{2}
```

If you want to keep working from there:

```bash
git switch -c recovery-branch
```

---

> [!TIP]
> Think of the reflog as Git's **history of HEAD movements**, not just a history of commits.
>
> Even if a commit is no longer reachable from a branch, it often remains recoverable through the reflog.
---

## Mental Model

Imagine Git maintaining a travel diary.

```
HEAD

↓

Commit A

↓

Commit B

↓

Commit C

↓

Commit B

↓

Commit D
```

Even though you moved backward and forward, Git remembers the entire journey.

That journey is Reflog.

---

## Why Reflog is So Powerful

Suppose you accidentally run:

```bash
git reset --hard HEAD~3
```

Your branch moves backward.

```
Before

A → B → C → D → E

After

A → B
```

At first glance:

```
C
D
E
```

appear to be gone.

However:

```bash
git reflog
```

will still contain the old position.

Example:

```
HEAD@{1}
```

pointing to commit **E**.

Recovery becomes possible.

---

> [!TIP]
> Whenever you think:
>
> "I lost my commits."
>
> Run:
>
> ```bash
> git reflog
> ```
>
> before trying anything else.

---

## Reflog Lifetime

Reflog is not permanent.

Git eventually removes very old entries during garbage collection.

However, recent work is usually recoverable for a long time (typically around 90 days for reachable entries, depending on Git configuration).

This makes Reflog an excellent safety net during everyday development.

---
# Recovering Lost Commits with Reflog

The most common use of Reflog is recovering commits that appear to have disappeared.

Remember:

> [!IMPORTANT]
> If a commit is no longer reachable from a branch, it is not necessarily deleted.

As long as Git still remembers the commit through Reflog, it can usually be recovered.

---

## Scenario 1 — Accidental `git reset --hard`

Suppose your history looks like this:

```
main

A → B → C → D → E
```

You accidentally run:

```bash
git reset --hard HEAD~3
```

Your branch now becomes:

```
main

A → B
```

At first glance, commits:

```
C
D
E
```

appear to be gone.

However, Git only moved the branch pointer.

Those commits still exist.

---

## Step 1 — View Reflog

Run:

```bash
git reflog
```

Example:

```
c9b82ab HEAD@{0}: reset: moving to HEAD~3

4e8b13d HEAD@{1}: commit: Add authentication

82aa72c HEAD@{2}: commit: Create login page

61f0d7a HEAD@{3}: commit: Initial project
```

Notice that **HEAD@{1}** still points to the commit before the reset.

---

## Step 2 — Recover the Commit

There are multiple recovery methods depending on what you want.

### Method 1 — Move the Branch Back (Most Common)

```bash
git reset --hard HEAD@{1}
```

Result:

```
main

A → B → C → D → E
```

Your branch points back to the latest commit.

Everything is restored.

---

### Method 2 — Recover Using the Commit Hash

Instead of using `HEAD@{1}`, you can use the commit hash shown by Reflog.

Example:

```bash
git reset --hard 4e8b13d
```

This produces the same result.

---

> [!WARNING]
> `git reset --hard` changes your working directory.
>
> Make sure you understand what will be replaced before running it.

---

# Scenario 2 — Recovering a Deleted Branch

Suppose you had:

```
main

A → B → C

feature

      \
       D → E
```

After finishing development, you accidentally delete the branch:

```bash
git branch -D feature
```

Now:

```
feature
```

no longer exists.

Many beginners assume the commits have been permanently deleted.

Usually they have not.

---

## Finding the Lost Branch

Run:

```bash
git reflog
```

or

```bash
git reflog show feature
```

(if available)

Example:

```
91ab234 HEAD@{5}: checkout: moving from feature to main

82ac443 Commit: Finish payment integration
```

The last commit of the deleted branch still exists.

---

## Recreate the Branch

Simply create a new branch pointing to that commit.

```bash
git checkout -b feature 82ac443
```

or using the modern command:

```bash
git switch -c feature 82ac443
```

Result:

```
main

A → B → C

feature

      \
       D → E
```

The branch has been restored.

---

> [!TIP]
> Deleting a branch usually deletes only the branch pointer.
>
> The commits remain until Git eventually removes unreachable objects.

---

# Scenario 3 — Detached HEAD Recovery

Suppose you checkout an old commit:

```bash
git checkout C
```

Git enters detached HEAD.

```
A → B → C → D

          ↑

        HEAD
```

You make two commits:

```
A → B → C → X → Y

             ↑

           HEAD
```

Then you switch back:

```bash
git switch main
```

Now:

```
main

A → B → C → D
```

Commits:

```
X
Y
```

appear to disappear.

---

## Recover Detached HEAD Work

Run:

```bash
git reflog
```

Find the detached HEAD commits.

Example:

```
ab72e11 HEAD@{3}: commit: Experiment

8c4d229 HEAD@{4}: commit: Prototype
```

Create a branch:

```bash
git switch -c experiment ab72e11
```

Now:

```
main

A → B → C → D

experiment

          \
           X → Y
```

The work is safely attached to a branch again.

---

> [!IMPORTANT]
> Detached HEAD commits are not lost immediately.
>
> They become difficult to reach because no branch points to them.

---

# Scenario 4 — Recovering After an Accidental Checkout

Sometimes you checkout another branch before remembering to commit.

This does **not** delete your work.

Git usually prevents switching if it would overwrite uncommitted changes.

If changes are committed, Reflog records every movement.

Always check:

```bash
git status
```

followed by:

```bash
git reflog
```

before assuming work has been lost.

---

# Recovering Without Moving Your Current Branch

Sometimes you only want to inspect a recovered commit.

Instead of resetting:

```bash
git checkout <commit>
```

or

```bash
git switch --detach <commit>
```

This lets you inspect old history without changing your branch.

If you decide to keep that work:

```bash
git switch -c recovered-work
```

creates a new branch from that commit.

---

# Mental Model

Imagine commits as houses.

Branches are simply signposts pointing toward one house.

```
Commit A

↓

Commit B

↓

Commit C
          ↑
        main
```

If the signpost moves:

```
Commit A

↓

Commit B
 ↑
main

↓

Commit C
```

The house still exists.

You only moved the sign.

Reflog remembers where the sign used to point.

Recovery simply means placing the sign back.

---

# Git Cherry-pick

Sometimes you don't want to merge an entire branch.

Instead, you only want **one specific commit** from another branch.

This is exactly what **Cherry-pick** is designed for.

---

## What is Cherry-pick?

`git cherry-pick` copies the changes introduced by an existing commit and applies them as a **new commit** on your current branch.

Unlike merging or rebasing, Cherry-pick does **not** combine branch histories.

Instead, it copies only the commits you choose.

---

## Why is it Called "Cherry-pick"?

Imagine a basket of cherries.

```
🍒 🍒 🍒 🍒 🍒
```

Instead of taking the whole basket, you pick only the cherries you want.

Git does the same thing with commits.

```
feature

A → B → C → D → E
```

Instead of merging the entire branch, you might only want commit **D**.

Cherry-pick lets you do exactly that.

---

## Merge vs Cherry-pick

### Merge

```
main

A → B

      \
       C → D → E
```

After merge:

```
A → B → M
      \  /
       C → D → E
```

Entire branch history is preserved.

---

### Cherry-pick

Current branch:

```
main

A → B
```

Feature branch:

```
feature

A → B → C → D → E
```

Cherry-pick commit **D**:

```
main

A → B → D'
```

Notice:

```
D'
```

is **not the original commit**.

It is a **new commit** containing the same changes.

---

> [!IMPORTANT]
> Cherry-pick copies changes, not commits.
>
> The new commit has a different commit hash because it has a different parent and metadata.

---

# Basic Syntax

```bash
git cherry-pick <commit-hash>
```

Example:

```bash
git cherry-pick a82bc19
```

Git applies the changes introduced by that commit to your current branch.

If everything succeeds, Git automatically creates a new commit.

---

# How Cherry-pick Works

Suppose you have:

```
main

A → B
```

Feature branch:

```
feature

A → B → C → D
```

Commit **D** fixes a critical bug.

Instead of merging everything:

```
C
```

and

```
D
```

you only need:

```
D
```

Checkout `main`:

```bash
git switch main
```

Run:

```bash
git cherry-pick <hash-of-D>
```

Result:

```
main

A → B → D'
```

Only the bug fix is copied.

---

# Cherry-picking Multiple Commits

Git can cherry-pick multiple commits.

Example:

```bash
git cherry-pick commit1 commit2 commit3
```

Git applies them one by one.

---

You can also specify a commit range.

```bash
git cherry-pick A..D
```

Git copies every commit after **A** up to **D**.

---

# Cherry-pick Conflicts

Sometimes Git cannot automatically apply the changes.

Example:

```
main

A → B
```

Feature:

```
A → C
```

Both branches changed the same lines.

When cherry-picking:

```bash
git cherry-pick abc123
```

Git reports:

```
CONFLICT
```

Just like a merge conflict.

---

## Resolving the Conflict

1. Open the conflicted files.

2. Resolve the conflict manually.

3. Stage the resolved files.

```bash
git add .
```

Continue:

```bash
git cherry-pick --continue
```

Git finishes creating the new commit.

---

## Abort Cherry-pick

If you decide not to continue:

```bash
git cherry-pick --abort
```

Git restores the repository to the state before the cherry-pick started.

---

# Real-world Uses

## 1. Bug Fixes

Suppose:

```
main
```

contains a production release.

```
develop
```

contains months of unfinished work.

You fix a critical bug in `develop`.

Instead of merging everything:

```
develop

Feature A
Feature B
Feature C
Bug Fix
```

you cherry-pick only the bug fix into `main`.

---

## 2. Accidentally Committed on the Wrong Branch

Suppose you accidentally commit on:

```
main
```

instead of:

```
feature
```

Simply cherry-pick that commit onto the correct branch.

---

## 3. Sharing One Feature

A teammate needs only one of your commits.

Instead of merging your entire branch, they cherry-pick just that commit.

---

# When Should You Use Cherry-pick?

Good situations:

- Apply a bug fix to another branch.
- Copy a small feature.
- Recover a detached HEAD commit.
- Move a commit to the correct branch.
- Backport fixes to older releases.

---

# When Should You NOT Use Cherry-pick?

Avoid Cherry-pick when:

- You want the complete branch history.
- The entire feature should be merged.
- Multiple developers are repeatedly cherry-picking between the same branches.

In these cases, **Merge** or **Rebase** is usually the better choice.

---

# Common Mistakes

### Mistake 1

Thinking Cherry-pick moves commits.

It does not.

It copies the changes.

---

### Mistake 2

Being surprised by a new commit hash.

This is expected.

The copied commit is a completely new commit.

---

### Mistake 3

Cherry-picking dozens of commits.

If you're copying many commits, you probably wanted a merge or rebase instead.

---

# Mental Model

Imagine commits as pages in a notebook.

```
Notebook A

Page 1

Page 2

Page 3
```

Cherry-pick is like photocopying **Page 2** and placing it into another notebook.

The copied page contains the same information, but it is **not the original page**.

Git does exactly this with commits.

---

# Git Bisect

Imagine this situation:

Your project worked perfectly yesterday.

Today, after hundreds of commits, you discover that something is broken.

The question is:

> **Which commit introduced the bug?**

Checking every commit one by one would be slow and frustrating.

Git provides a tool specifically for this problem:

```bash
git bisect
```

---

## What is Git Bisect?

Git Bisect is a debugging tool that helps you find the commit that introduced a bug.

Instead of checking every commit sequentially, Git uses the **Binary Search** algorithm to locate the problematic commit much faster.

---

## Why Does Git Bisect Exist?

Suppose your project has **1000 commits**.

Without Bisect:

```
Commit 1

↓

Commit 2

↓

Commit 3

↓

...

↓

Commit 1000
```

You might need to test hundreds of commits.

With Bisect:

```
1000 commits

↓

500

↓

250

↓

125

↓

63

↓

31

↓

16

↓

8

↓

4

↓

2

↓

1
```

Git cuts the search space in half each time.

This is exactly how **Binary Search** works.

---

> [!NOTE]
> Binary Search requires two known points:
>
> - One commit where the project works (**Good**)
> - One commit where the project is broken (**Bad**)

Git repeatedly checks the commit in the middle until it finds the first bad commit.

---

# How Git Bisect Works

Imagine this commit history.

```
A → B → C → D → E → F → G → H
```

Suppose:

```
A
B
C
D
```

work correctly.

```
E
F
G
H
```

contain the bug.

The first bad commit is:

```
E
```

Instead of testing:

```
A
B
C
D
E
F
G
H
```

Git jumps directly to the middle.

```
A → B → C → D → E → F → G → H
                ↑
```

If **D** works,

Git knows the bug must be after D.

Now it searches only:

```
E → F → G → H
```

Again it chooses the middle.

```
E → F → G → H
      ↑
```

Eventually only one commit remains.

That commit introduced the bug.

---

# Starting a Bisect Session

Begin with:

```bash
git bisect start
```

Now tell Git:

Current commit is bad.

```bash
git bisect bad
```

Next, specify a commit where everything worked correctly.

Example:

```bash
git bisect good 8ab21d4
```

Git immediately checks out a commit approximately halfway between the two.

---

# Testing Each Commit

Git now asks you to test the checked-out commit.

If the project works:

```bash
git bisect good
```

If the bug exists:

```bash
git bisect bad
```

Git continues narrowing the search.

Example:

```
Bad

↓

Middle Commit

↓

Good

↓

Middle Again

↓

Good

↓

Middle Again

↓

Bad

↓

First Bad Commit Found
```

Repeat until Git reports:

```
<commit hash> is the first bad commit
```

---

# Ending the Bisect Session

After finding the problematic commit:

```bash
git bisect reset
```

Git returns your repository to its original branch.

---

> [!IMPORTANT]
> Always finish a Bisect session with:
>
> ```bash
> git bisect reset
> ```
>
> Otherwise, you'll remain checked out at one of the tested commits.

---

# Automatic Bisect

Sometimes testing can be automated.

Instead of manually checking every commit, Git can execute a script.

Example:

```bash
git bisect run ./test.sh
```

For each checked-out commit:

1. Git runs the script.
2. If the script succeeds (exit code 0), Git marks the commit as **good**.
3. If the script fails (non-zero exit code), Git marks the commit as **bad**.
4. Git continues until the first bad commit is found.

This is especially useful in projects with automated test suites.

---

# Real-world Example

Suppose your application suddenly crashes.

History:

```
A → B → C → D → E → F → G
```

You know:

```
Commit A

✔ Works
```

Current commit:

```
Commit G

✖ Broken
```

Run:

```bash
git bisect start
git bisect bad
git bisect good A
```

Git checks out:

```
D
```

You test it.

Suppose it works.

```bash
git bisect good
```

Git now checks:

```
F
```

Suppose it fails.

```bash
git bisect bad
```

Git now checks:

```
E
```

If **E** fails,

Git concludes:

```
E
```

is the first bad commit.

---

# When Should You Use Git Bisect?

Git Bisect is useful when:

- A bug appeared recently.
- You don't know which commit introduced it.
- The project has many commits.
- Testing each commit manually would take too long.

---

# When Should You NOT Use Git Bisect?

Git Bisect is not ideal when:

- You already know which commit caused the problem.
- The bug cannot be reproduced consistently.
- There are too few commits to justify using it.

---

# Common Mistakes

### Mistake 1

Choosing the wrong "good" commit.

If the selected good commit already contains the bug, Bisect cannot produce correct results.

---

### Mistake 2

Forgetting to reset after Bisect.

Always finish with:

```bash
git bisect reset
```

---

### Mistake 3

Changing project files while Bisect is running.

Avoid making unrelated changes during a Bisect session.

---

# Mental Model

Imagine searching for a word in a dictionary.

Instead of starting from page 1, you open the dictionary in the middle.

Depending on whether the word comes before or after that page, you eliminate half the remaining pages.

Repeat until only one page remains.

Git Bisect works exactly the same way, except it searches commits instead of pages.

---

---

# Recovery Decision Tree

When something goes wrong, it can be difficult to decide which Git command to use.

Use the following decision tree as a quick reference.

```
Something went wrong
│
├── I haven't committed yet
│   │
│   ├── Discard changes
│   │      git restore
│   │
│   └── Save for later
│          git stash
│
├── I committed on the wrong branch
│   │
│   └── git cherry-pick
│
├── I accidentally deleted commits
│   │
│   └── git reflog
│
├── I deleted a branch
│   │
│   └── git reflog
│
├── I used git reset --hard
│   │
│   └── git reflog
│
├── My detached HEAD commits disappeared
│   │
│   └── git reflog
│
└── I don't know which commit introduced a bug
    │
    └── git bisect
```

---

# Common Recovery Scenarios

This section summarizes the most common problems developers encounter and the recommended recovery approach.

---

## Scenario 1 — I accidentally ran `git reset --hard`

Symptoms:

- Recent commits appear to be missing.
- Branch moved backwards.

Solution:

```bash
git reflog
git reset --hard HEAD@{1}
```

---

## Scenario 2 — I deleted my branch

Symptoms:

```
git branch
```

does not list the branch.

Solution:

```bash
git reflog
git switch -c <branch-name> <commit-hash>
```

---

## Scenario 3 — I committed on the wrong branch

Move the commit to the correct branch.

```bash
git switch correct-branch

git cherry-pick <commit>
```

Then remove it from the wrong branch if necessary.

---

## Scenario 4 — My work disappeared after Detached HEAD

Find the commit.

```bash
git reflog
```

Create a branch.

```bash
git switch -c recovered-work <commit>
```

---

## Scenario 5 — I don't know when the bug appeared

Use Binary Search.

```bash
git bisect
```

---

## Scenario 6 — Merge introduced a problem

First identify the problematic commit.

Then:

- revert
- reset
- or use Reflog if necessary

---

# Recovery Cheat Sheet

## Recover Lost Commits

```bash
git reflog
git reset --hard HEAD@{1}
```

---

## Recover Deleted Branch

```bash
git reflog
git switch -c feature <commit>
```

---

## Copy One Commit

```bash
git cherry-pick <commit>
```

---

## Abort Cherry-pick

```bash
git cherry-pick --abort
```

---

## Continue Cherry-pick

```bash
git cherry-pick --continue
```

---

## Start Bisect

```bash
git bisect start
git bisect bad
git bisect good <commit>
```

---

## Finish Bisect

```bash
git bisect reset
```

---

## View Reflog

```bash
git reflog
```

---

# Best Practices

### Learn `git reflog`

If you remember only one recovery command, remember:

```bash
git reflog
```

It has saved countless developers from losing work.

---

### Commit Frequently

Small commits make recovery easier.

Instead of:

```
One huge commit
```

Prefer:

```
Commit 1

↓

Commit 2

↓

Commit 3

↓

Commit 4
```

---

### Use Meaningful Commit Messages

Recovery is much easier when commit messages clearly describe what changed.

Good:

```
Fix authentication timeout
```

Poor:

```
Update
```

---

### Create Branches Before Experimenting

Instead of experimenting directly on:

```
main
```

Create a new branch.

This makes recovery much safer.

---

### Don't Panic

Most Git mistakes are recoverable.

Before trying random commands:

1. Stop.
2. Inspect the repository.
3. Check:

```bash
git status
git log
git reflog
```

---

# Common Mistakes

## Mistake 1

Thinking Git immediately deletes commits.

Usually it only removes references.

---

## Mistake 2

Using `git reset --hard` without understanding the consequences.

Always double-check before executing it.

---

## Mistake 3

Ignoring Reflog.

Many developers immediately assume their work is gone.

Often, Reflog can recover it in seconds.

---

## Mistake 4

Confusing Merge, Rebase, and Cherry-pick.

Remember:

- Merge combines histories.
- Rebase rewrites history.
- Cherry-pick copies individual commits.

---

## Mistake 5

Forgetting to create a branch while working in Detached HEAD.

Detached HEAD is useful for exploration, but important work should eventually be attached to a branch.

---

# Mental Model

Git stores your project as a graph of commits.

```
A → B → C → D → E
```

Branches are **labels** pointing to commits.

```
main
 │
 ▼
 E
```

Recovery is usually not about recreating commits.

It is about restoring or creating the correct label (branch) so those commits become reachable again.

Think of Git as a library.

- Commits are books.
- Branches are bookmarks.
- `git reflog` is the librarian's notebook recording where every bookmark has been.
- Recovery means putting the bookmark back in the right place.

As long as the book still exists in the library, you can usually find it again.

---


# Key Ideas

- Recovery is different from undoing changes.
- Git usually loses pointers, not commits.
- Reflog records where HEAD has been.
- `git log` shows project history.
- `git reflog` shows reference history.
- Reflog is the first place to look when work seems lost.
- `git reflog` is the first tool to use when commits appear lost.
- Most recovery involves restoring a branch pointer.
- Deleted branches usually do not delete commits.
- Detached HEAD commits remain recoverable until Git eventually cleans them up.
- Git stores commits separately from branch names.
- Cherry-pick copies the changes from an existing commit.
- The copied commit receives a new commit hash.
- Branch histories remain separate.
- Cherry-pick is ideal for individual fixes or features.
- Merge and Rebase are better choices when entire branch histories should be combined.
- Git Bisect finds the commit that introduced a bug.
- It uses the Binary Search algorithm.
- You identify one **good** commit and one **bad** commit.
- Git repeatedly narrows the search until the first bad commit is found.
- `git bisect run` can automate the entire process using a test script.
  
# NOTE

- Recovery is different from undoing changes.
- Git usually loses references, not commits.
- `git reflog` is the primary recovery tool.
- `git cherry-pick` copies individual commits.
- `git bisect` efficiently finds the commit that introduced a bug.
- Most Git mistakes can be recovered if you act carefully and avoid unnecessary changes.
  
