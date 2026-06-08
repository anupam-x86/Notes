# Coding Principles

## Comments

Comments are notes written for humans.

> [!Note]
> Comments should explain things that are not obvious from the code itself.

Purpose:

```text
Explain things that code alone cannot explain.
```

Comments are ignored by the compiler.

---

## Single-Line Comments

```cpp
// This is a single-line comment
```

Everything after `//` on that line is ignored.

---

## Multi-Line Comments

```cpp
/*
This is a
multi-line comment
*/
```

Useful for longer explanations.

---

## Nested Comments

Not allowed.

Example:

```cpp
/*
Outer comment

/* Inner comment */

*/
```

This will cause problems because the first `*/` closes the outer comment.

---

## Good Comments

Good comments explain:

```text
Why
Assumptions
Intentions
Non-obvious behavior
```

Example:

```cpp
// Using cache because repeated API calls were too slow
```

The code shows HOW.

The comment explains WHY.

---

## Bad Comments

Bad comments repeat what the code already says.

Example:

```cpp
age = 18; // Set age to 18
```

The code already tells us that.

The comment adds no new information.

---

## The Delete Comment Test

Mental Model:

```text
Delete the comment.

Did important information disappear?
```

If NO:

```text
Comment was probably unnecessary.
```

If YES:

```text
Comment was useful.
```

---

## Documentation

Documentation exists at a higher level than comments.

Purpose:

```text
Explain how the system works.
```

Examples:

* README.md
* Architecture notes
* API documentation
* Design documents

---

## Code vs Comments vs Documentation

```text
Code
↓
HOW

Comments
↓
WHY

Documentation
↓
How the whole system fits together
```

---

## Future Me Principle

Write notes for Future You.

Example:

```text
Today:
"I'll remember this."
```

After exams:

```text
"What was I thinking?"
```

Memory fades.

Documentation preserves context.

---

## Documentation Tools

Examples:

* Doxygen

Benefits:

* Standardized documentation
* HTML export
* Diagrams
* Cross-links
* Easier team collaboration

Mostly useful for larger projects.

---

## Learning Principles

Bad:

```text
Tutorial
↓
Tutorial
↓
Tutorial
↓
Nothing Built
```

Good:

```text
Learn
↓
Build
↓
Get Curious
↓
Learn More
↓
Build Again
```

---

## Curiosity Principle

Curiosity is useful.

But:

```text
Learn Topic A
↓
Research Topic B
↓
Research Topic C
↓
Research Topic D
```

can prevent progress.

Balance:

```text
Learn
↓
Build
↓
Investigate Questions
↓
Continue Building
```

---

## Notes Principle

If something took a long time to understand:

```text
Write it down.
```

Future You will probably forget the reasoning before forgetting the code.

---

## Key Mental Models

```text
Code explains HOW.

Comments explain WHY.

Documentation explains the SYSTEM.

The main audience for your comments is Future You.
```

```text
Memory fades.

Notes preserve context.
```

```text
Good comments add information.

Bad comments repeat information.
```

```text
Learn
↓
Build
↓
Learn More
↓
Build Again
```

