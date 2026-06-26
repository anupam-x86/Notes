# 5.4–5.6 Compiler Optimization, Constant Expressions & `constexpr`

## Big Picture

These chapters answer one question:

```text
When does code execute?
```

There are two possibilities:

```text
Compile Time
        or
Runtime
```

Modern C++ tries to execute as much work as possible during compilation when it is safe and beneficial.

---

# The As-If Rule

The compiler is free to transform your program in **any way** as long as the program's **observable behavior** remains the same.

```text
Different implementation
        ↓
Same visible result
```

Observable behavior includes things such as:

- Console output
- File I/O
- User input
- Network communication

If the user cannot tell the difference, the optimization is allowed.

---

# Compiler Optimizations

An **optimizer** rewrites code into a more efficient form.

Example:

```cpp
i = i * 2;
```

may become:

```cpp
i += i;
```

or

```cpp
i <<= 1;
```

without changing the program's behavior.

Modern C++ compilers perform these optimizations automatically.

---
## Why Optimizations Matter

Optimization aims to improve one or more of the following:

- Faster execution
- Smaller executable size
- Lower memory usage
- Lower power consumption

Different optimizations may prioritize different goals. Sometimes making code faster can increase executable size, and vice versa.
---
# Common Optimizations

## Constant Folding

Evaluate expressions made entirely of constants.

```cpp
3 + 4
```

↓

```cpp
7
```

No runtime calculation needed.

---

## Constant Propagation

Replace variables known to have constant values with those values.

```cpp
int x { 7 };

std::cout << x;
```

↓

```cpp
std::cout << 7;
```

This removes unnecessary memory accesses.

---

## Dead Code Elimination

Remove code that has no effect.

```cpp
int x { 7 };

std::cout << 7;
```

↓

```cpp
std::cout << 7;
```

Variable `x` is **optimized away**.

---

# Optimization Levels

Compilers usually support multiple optimization levels.

```text
Debug Build
```

- Little or no optimization
- Easier debugging

```text
Release Build
```

- Optimizations enabled
- Faster and smaller executable

Optimizations are usually disabled while debugging because optimized code no longer closely matches the source code.

---
## Debug vs Release Builds

When learning C++, you'll often build your program in one of two modes.

### Debug Build

- Optimizations are mostly disabled.
- Easier to inspect variables while debugging.
- Generated machine code closely matches your source code.

### Release Build

- Optimizations are enabled.
- Faster execution.
- Smaller executable.
- Variables and even entire statements may disappear due to optimization.

Always test your final program in Release mode because optimized code can sometimes expose bugs hidden in Debug builds.
---
# Compile-Time Evaluation

The compiler can sometimes evaluate expressions while compiling.

This is called:

```text
Compile-time evaluation
```

instead of:

```text
Runtime evaluation
```

Compile-time evaluation makes programs:

- Faster
- Smaller
- Sometimes safer

---
# Compile-Time Evaluation Categories

Expressions generally fall into one of these categories.

## 1. Cannot be evaluated at compile time

The compiler doesn't know the value.

Example:

```cpp
int x {};
std::cin >> x;
```

---

## 2. Can be evaluated at compile time

The expression is a constant expression.

The compiler is allowed to evaluate it during compilation.

Example:

```cpp
3 + 4
```

---

## 3. Must be evaluated at compile time

Some language features require compile-time evaluation.

Example:

```cpp
constexpr int x { 5 };
```

---

## 4. Runtime evaluation

Some expressions must wait until the program is running.

Example:

```cpp
int age { getAge() };
```
---

# Compile-Time Programming

Optimization is the compiler's decision.

Compile-time programming lets **you** require compile-time evaluation.

Benefits:

- Better performance
- Predictable behavior
- Can be used where compile-time values are required
- More compile-time error checking

---

# Compile-Time Constant

A value known during compilation.

Examples:

```cpp
5
3.14
true
```

```cpp
constexpr int x { 5 };
```

---

# Runtime Constant

A value that cannot change after initialization but is only known when the program runs.

Example:

```cpp
const int age { getAge() };
```

---

# Constant Expression

A constant expression is an expression that can be fully evaluated at compile time.

Examples:

```cpp
3 + 4
```

```cpp
constexpr int x { 5 };

x * 2
```

Every part of the expression must itself be compile-time evaluatable.
---
## Literal vs Constant Expression

Every literal is a constant expression.

Examples:

```cpp
5
true
3.14
```

A constant expression can also combine multiple constant expressions.

```cpp
3 + 4 * 5
```

As long as every part can be evaluated during compilation, the whole expression is also a constant expression.
---

# Runtime Expression

Any expression that is **not** a constant expression.

Examples:

```cpp
x + 5
```

when `x` isn't compile-time.

```cpp
std::cin >> x;
```

---

# Why `const` Wasn't Enough

`const` only means:

```text
Cannot change after initialization.
```

It **does not** guarantee compile-time evaluation.

Problems:

- Hard to know whether a const variable is compile-time or runtime.
- Doesn't enforce compile-time evaluation.
- Historical exception only applied to integral types.

---

# Historical Exception

Before `constexpr`, C++ allowed:

```cpp
const int size { 5 };

int arr[size];
```

because array sizes had to be known during compilation.

This became a historical exception.

Modern C++ prefers:

```cpp
constexpr int size { 5 };
```

---

# `constexpr`

`constexpr` means:

```text
Must be usable in a constant expression.
```

Initializer **must** be known during compilation.

Example:

```cpp
constexpr int x { 5 };
```

Invalid:

```cpp
constexpr int x { getValue() };
```

if `getValue()` isn't compile-time evaluatable.

---
## constexpr Variables Are Also const

Every constexpr variable is implicitly const.

```cpp
constexpr int x { 5 };
```

is effectively a compile-time const object.

You do **not** need to write:

```cpp
const constexpr int x { 5 };
```

although writing both is allowed.
---
# `const` vs `constexpr`

## const

Means:

```text
Immutable
```

Initializer may be:

- Compile-time
- Runtime

Object can only be evaluated at runtime.

---

## constexpr

Means:

```text
Compile-time constant
```

Initializer must be known during compilation.

Object can be used both:

- Compile-time
- Runtime

---

# Type Difference

`const` is part of a variable's type.

```cpp
const int
```

is a different type than:

```cpp
int
```

`constexpr` is **not** part of the type.

```cpp
constexpr int x { 5 };
```

actually has type:

```cpp
const int
```

`constexpr` simply adds a compile-time requirement.

---

# constexpr Functions

Normal function:

```cpp
int square(int x)
```

Always executes at runtime.

---

constexpr function:

```cpp
constexpr int square(int x)
```

Can execute:

- Compile-time
- Runtime

depending on the situation.

---

Compile-time execution requires:

- constexpr function
- Constant expression arguments
- Compile-time context (when required)

---

Example:

```cpp
constexpr int square(int x)
{
    return x * x;
}
```

```cpp
constexpr int a { square(5) };
```

↓

Compile-time.

---

```cpp
int a { square(5) };
```

↓

Compile-time **or** runtime.

Compiler chooses.

---

```cpp
int x;

std::cin >> x;

square(x);
```

↓

Runtime only.

---
## constexpr Does Not Force Compile-Time Execution

A constexpr function makes compile-time evaluation **possible**, not mandatory.

```cpp
constexpr int square(int x)
{
    return x * x;
}
```

If called with compile-time values:

```cpp
constexpr int a { square(5) };
```

the function executes during compilation.

If called with runtime values:

```cpp
int x {};
std::cin >> x;

std::cout << square(x);
```

the exact same function executes normally at runtime.
---

# Function Parameters

Normal function parameters are initialized during runtime.

Therefore:

```cpp
const int x
```

inside a function is only a **runtime constant**.

Function parameters cannot be declared:

```cpp
constexpr
```

because they don't exist until the function is called.

---

# Modern Guidelines

If a constant value is known during compilation:

```cpp
constexpr
```

Use:

```cpp
constexpr int maxStudents { 30 };
```

---

If the value is only known during runtime but should never change:

```cpp
const
```

Use:

```cpp
const int age { getAge() };
```

---
# Choosing Between const and constexpr

Use `constexpr` when:

- The value is known during compilation.
- The value never changes.
- Compile-time evaluation is desirable.

Example:

```cpp
constexpr int daysPerWeek { 7 };
```

---

Use `const` when:

- The value cannot change.
- The value is only known while the program runs.

Example:

```cpp
const int age { getAge() };
```

Rule of thumb:

```text
Known during compilation?
        ↓
      Yes → constexpr

      No
        ↓
Won't change?
        ↓
      Yes → const
```
---
# Mental Models

## Compile vs Runtime

```text
Source Code

↓

Compile Time
(Compiler)

↓

Executable

↓

Runtime
(User executes program)
```

---

## const

```text
Can it change?

NO
```

---

## constexpr

```text
Must compiler know it?

YES
```

---

## Constant Expression

```text
Every ingredient
↓

Compile-time

↓

Whole expression
↓

Compile-time
```

---

## constexpr Function

```text
Normal Function

Compile ❌

Runtime ✅
```

```text
constexpr Function

Compile ✅

Runtime ✅
```

---

# Relationship Map

```text
Compile-Time Constants
        │
        ▼
Constant Expressions
        │
        ▼
constexpr Variables
constexpr Functions
        │
        ▼
Compile-Time Programming

────────────────────────────

Runtime Constants
        │
        ▼
Runtime Expressions
```
## Timeline

```text
Source Code
      │
      ▼
Compiler
      │
      ├── constexpr values evaluated here
      ▼
Executable
      │
      ▼
Program Runs
      │
      ├── const runtime values initialized here
      ▼
Output
```
---

# Key Takeaways

- The compiler may optimize code under the **as-if rule** as long as observable behavior doesn't change.
- Common optimizations include constant folding, constant propagation, and dead code elimination.
- Compile-time evaluation reduces runtime work and can improve performance.
- A **constant expression** can be evaluated during compilation.
- `const` means a value cannot change after initialization.
- `constexpr` means a value or function can participate in compile-time evaluation.
- Every `constexpr` variable is also `const`.
- `constexpr` functions can execute either at compile time or at runtime, depending on how they are used.
- Prefer `constexpr` whenever a value is known at compile time.
- Use `const` for values that are immutable but only become known at runtime.

---
