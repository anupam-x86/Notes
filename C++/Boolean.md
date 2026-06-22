# Boolean Values and Conditional Execution

## Why This Note Exists

Programs often need to answer questions and make decisions.

Examples:

```text
Is the user logged in?
Does the player have enough health?
Is the file valid?
Has the game ended?
```

To represent answers to such questions, C++ provides the `bool` type.

Boolean values are commonly used with conditional statements such as `if` to control program flow.

---

# The Most Important Rule

```text
A boolean represents the answer to a question.

true  = yes
false = no
```

A boolean is not primarily a number.

It is a logical state.

---

# What Is a Boolean?

A boolean (`bool`) can store only two values:

```cpp
true
false
```

Example:

```cpp
bool isAlive { true };
bool hasLicense { false };
bool gameOver { false };
```

---

# Mental Model: A Boolean Answers a Question

```text
Is the player alive?
→ true

Does the user have a license?
→ false

Is the game over?
→ false
```

Good boolean names should read naturally as questions.

---

# Mental Model: Light Switch

```text
OFF = false = 0

ON  = true  = 1
```

or

```text
NO  = false

YES = true
```

---

# Boolean Representation

Historically, booleans are closely related to integers.

```text
false = 0
true  = 1
```

However:

```text
A bool stores a logical state,
not an arbitrary number.
```

---

# Printing Booleans

By default:

```cpp
bool b { true };

std::cout << b;
```

Output:

```text
1
```

Likewise:

```cpp
bool b { false };

std::cout << b;
```

Output:

```text
0
```

---

# std::boolalpha

To print:

```text
true
false
```

instead of:

```text
1
0
```

use:

```cpp
std::cout << std::boolalpha;
```

Example:

```cpp
bool b { true };

std::cout << std::boolalpha;
std::cout << b;
```

Output:

```text
true
```

---

# Stream Manipulators

`std::boolalpha` is a stream manipulator.

It changes how data is displayed.

Mental model:

```text
Data
  ↓
std::cout
  ↓
Formatting Settings
  ↓
Printed Characters
```

Important:

```text
The value never changes.

Only the representation changes.
```

Examples:

```cpp
std::boolalpha
std::noboolalpha

std::fixed
std::scientific
std::setprecision(...)
```

---

# Converting Values To Bool

Many types can be converted to a boolean.

General rule:

```text
0       → false
nonzero → true
```

---

## Integer → Bool

Examples:

```cpp
bool a { 0 };     // false
bool b { 1 };     // true
bool c { 42 };    // true
bool d { -7 };    // true
```

---

## Floating Point → Bool

Examples:

```cpp
bool a { 0.0 };     // false
bool b { 0.5 };     // true
bool c { 10.23 };   // true
bool d { -3.14 };   // true
```

Important:

```cpp
bool x { 0.5 };
```

becomes:

```text
0.5 → true
```

not:

```text
0.5 → 0 → false
```

The conversion happens directly.

---

# A Bool Does Not Remember The Original Value

Example:

```cpp
bool x { 10.23 };
```

Conversion:

```text
10.23
  ↓
true
```

The bool stores:

```cpp
true
```

The original value is lost.

Mental model:

```text
Original Value
      ↓
Convert To Bool
      ↓
Store true/false
      ↓
Original Value Lost
```

---

# Boolean Input

Default input mode:

```cpp
bool b {};
std::cin >> b;
```

Accepted values:

```text
0
1
```

Interpretation:

```text
0 → false
1 → true
```

---

# std::boolalpha For Input

Enable:

```cpp
std::cin >> std::boolalpha;
```

Accepted values become:

```text
true
false
```

Important:

```text
true
false
```

must be lowercase.

Examples that fail:

```text
True
FALSE
False
```

---

# Input and Output Formatting Are Independent

These streams have separate formatting states:

```cpp
std::cin
std::cout
```

Example:

```cpp
std::cin >> std::boolalpha;
std::cout << std::noboolalpha;
```

Meaning:

```text
Input:
    true / false

Output:
    0 / 1
```

Changing one stream does not affect the other.

---

# Why Conditional Statements Exist

So far, programs have mainly stored and displayed information.

Now we want programs to make decisions.

Example:

```cpp
bool isAlive { true };

if (isAlive)
{
    std::cout << "Player is alive\n";
}
```

The program behaves differently depending on a condition.

---

# Relationship Between Booleans and If Statements

```text
Boolean Value
      ↓
Answers A Question
      ↓
Used As A Condition
      ↓
Controls Program Flow
```

A boolean provides the answer.

An `if` statement decides what to do with that answer.

---

# Mental Model: An If Statement

An `if` statement asks:

```text
Should this code run?

YES → execute code
NO  → skip code
```

---

# Basic Syntax

```cpp
if (condition)
{
    statement;
}
```

---

# Conditions Ultimately Become Booleans

An `if` statement needs a boolean answer.

```text
true  → execute
false → skip
```

Examples:

```cpp
if (true)
```

Executes.

```cpp
if (false)
```

Skips.

---

# Non-Boolean Conditions

C++ automatically converts values to bool.

Rule:

```text
0       → false
nonzero → true
```

Examples:

```cpp
if (1)
if (42)
if (-7)
if (0.5)
```

Execute.

```cpp
if (0)
if (0.0)
```

Skip.

---

# The Single Statement Rule

An `if` controls only the next statement.

Example:

```cpp
if (isAlive)
    std::cout << "Alive\n";

std::cout << "Game running\n";
```

Equivalent to:

```cpp
if (isAlive)
{
    std::cout << "Alive\n";
}

std::cout << "Game running\n";
```

The second statement always executes.

---

# The Indentation Trap

This code:

```cpp
if (condition)
    if (condition)
        statement1;
        statement2;
```

looks like both statements belong to the inner `if`.

They do not.

The compiler follows syntax, not indentation.

Important rule:

```text
Never trust indentation.

Trust braces.
```

---

# Best Practice: Prefer Braces

Preferred:

```cpp
if (isAlive)
{
    std::cout << "Alive\n";
}
```

instead of:

```cpp
if (isAlive)
    std::cout << "Alive\n";
```

Braces prevent bugs when code is modified later.

---

# Early Returns

Modern C++ often uses early returns to reduce nesting.

Example:

```cpp
bool login(User user)
{
    if (!user.exists())
        return false;

    if (!user.hasPassword())
        return false;

    if (!user.isActive())
        return false;

    return true;
}
```

Mental model:

```text
Handle exceptional cases first.

Return early.

Keep the main path simple.
```

Benefits:

* Less nesting
* Easier to read
* Easier error handling

---

# Practical Rules

1. Use meaningful boolean names.
2. Prefer `if (isAlive)` over `if (isAlive == true)`.
3. Use `std::boolalpha` when printing booleans for humans.
4. Remember that `0` becomes `false` and nonzero becomes `true`.
5. Prefer braces even for single-statement `if`s.
6. Trust syntax, not indentation.
7. Use early returns when they simplify code.

---

# Chapter Summary

Booleans represent logical states:

```text
true
false
```

They answer questions and are commonly used as conditions.

An `if` statement uses those answers to control program execution.

Mental model:

```text
Question
    ↓
Boolean Answer
    ↓
If Statement
    ↓
Program Decision
```

The key idea:

```text
A boolean answers a question.

An if statement decides what to do with that answer.
```
