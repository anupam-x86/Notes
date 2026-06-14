# LearnCpp Notes — 2.1 to 2.5

## 2.1 Introduction to Functions

### What is a function?

A function is a reusable sequence of statements that performs a specific task.

```cpp
int main()
{
    return 0;
}
```

* `main()` is the entry point of a C++ program.
* Functions can call other functions.
* Using functions helps follow the DRY principle (Don't Repeat Yourself).

### DRY Principle

**DRY = Don't Repeat Yourself**

Avoid duplicating code when possible:

* Use variables to store values used multiple times.
* Use functions for reusable logic.
* Use loops for repeated execution.

> [!NOTE]
> * DRY is a guideline, not an absolute rule. Too many tiny functions can hurt readability.
> * DRY applies to logic, not just code.
> * If you find yourself writing the same sequence of steps in two places,
> that's a sign a function is needed.
### Placeholder names

Common placeholder names used in examples:

- foo
- bar
- baz

These names usually have no meaning and are used when the actual name is unimportant.
---
## 2.2 Function Return Values (Value-Returning Functions)

### Value-returning functions

A function can return a value to its caller.

```cpp
int getValue()
{
    return 5;
}
```

### The `return` statement

```cpp
return expression;
```

`return`:

1. Evaluates the expression.
2. Sends the value back to the caller.
3. Immediately exits the function.

Example:

```cpp
int getNumber()
{
    return 5;
    return 7; // never executes
}
```

Output:

```text
5
```

### Function calls as values

```cpp
int x { getValue() };
```

Think of:

```cpp
getValue()
```

as being replaced by:

```cpp
5
```

after the function returns.

>[!Important]
>
>`return` does two things:
>
>1. Returns a value (if any).
>2. Immediately exits the function.
>
>Any code after a `return` statement in the same execution path is unreachable.

### Status codes from `main()`

```cpp
int main()
{
    return 0;
}
```

Common status codes:

| Value          | Meaning |
| -------------- | ------- |
| `0`            | Success |
| `EXIT_SUCCESS` | Success |
| `EXIT_FAILURE` | Failure |

```cpp
#include <cstdlib>

int main()
{
    return EXIT_SUCCESS;
}
```

### Undefined Behavior Warning

```cpp
int foo()
{
}
```

If execution reaches the end of a non-`void` function without returning a value, the behavior is undefined (UB).

Exception: `main()` implicitly returns `0`.
Example:

```cpp
int getValue()
{
    int x{};
    std::cin >> x;
    // missing return
}
```

The compiler may warn:

```text
control reaches end of non-void function
```
> [!IMPORTANT]
> Tested this personally — compiled a function with no return statement.
> Result: "Illegal instruction (core dumped)"
> Not a wrong value. A full crash.
> This is why missing return = undefined behavior, not just "wrong output".

### Special rule for `main()`

```cpp
int main()
{
}
```

is treated as:

```cpp
int main()
{
    return 0;
}
```

Only `main()` gets this special behavior.

---

## 2.3 Void Functions

### What is a void function?

A void function does not return a value.

```cpp
void printHello()
{
    std::cout << "Hello\n";
}
```

### Calling a void function

```cpp
printHello();
```

Valid because we only want the function's side effect.

### Cannot use a void function as a value

```cpp
int x { printHello() }; // Error
```

A void function does not produce a value.

### Early return in a void function

```cpp
void printNumber(int x)
{
    if (x < 0)
        return;

    std::cout << x;
}
```

`return;` exits the function immediately.

> [!NOTE]
> Early return in void functions is useful for guard clauses —
> check a condition at the top, exit immediately if it fails,
> then write the main logic without nested ifs.
> You'll use this pattern constantly in real code.

---

## Extra Notes

### `std::cout` is not a function

```cpp
std::cout << "Hello";
```

* `std::cout` is an output stream object.
* `<<` is an overloaded operator used to send data to the stream.

### Function Contract

```cpp
int foo();
```

This promises that the function will return an `int`.

Breaking that promise:

```cpp
int foo()
{
}
```

results in Undefined Behavior.



## Key Takeaways

* Functions allow code reuse.
* `return` sends a value back and exits the function.
* Non-`void` functions must return a value.
* Reaching the end of a non-`void` function without returning is UB.
* `void` functions do not return values.
* `main()` is special and implicitly returns `0`.
* `std::cout` is an object, not a function.
* Follow DRY, but don't sacrifice readability.

# 2.4 Function Parameters and Arguments

---

## Parameters vs Arguments

A **parameter** is a variable declared in a function definition.

```cpp
int add(int x, int y)
{
    return x + y;
}
```

`x` and `y` are **parameters**.

An **argument** is the value passed when the function is called.

```cpp
add(3, 4);
```

`3` and `4` are **arguments**.

> [!NOTE]
> Easy way to remember:
> **Parameter** = Placeholder (in definition)
> **Argument** = Actual value (in call)

---

## Pass By Value

When a function is called:

1. Parameters are created as local variables.
2. Argument values are **copied** into the parameters.
3. The function works with those copies.
4. Originals are never touched.

```cpp
void printValue(int x)
{
    x = 10; // only changes the copy
}

int main()
{
    int a { 5 };
    printValue(a);

    std::cout << a; // still 5 — a was never changed
}
```

### Mental Model

```
int a { 5 };
printValue(a);

// is roughly equivalent to:

int x { a }; // copy made inside function
```

> [!IMPORTANT]
> Changing a parameter inside a function does **not** affect the original variable.
> The function only has a copy.
> This is why `a` stays 5 even after `printValue` sets `x = 10`.

---

## Arguments Can Be Any Expression

Arguments are essentially initializers for parameters.

```cpp
add(1 + 2, 8 - 4);     // expressions
add(getValue(), 10);    // function calls
add(x * 2, y + 3);     // variable expressions
```

Anything that produces a value can be an argument.

---

## Parameter Count Must Match

```cpp
add(1, 2);     // OK
add(1);        // Error — too few
add(1, 2, 3);  // Error — too many
```

> [!NOTE]
> There are exceptions (default parameters, variadic functions) but those come later.
> For now: argument count must exactly match parameter count.

---

## Function Parameters Are Local Variables

Parameters behave like local variables defined at the start of the function.

```cpp
int add(int x, int y)
{
    int result { x + y };
    return result;
}
```

`x`, `y`, and `result` all:
- Exist only inside `add()`
- Are created when `add()` is called
- Are destroyed when `add()` returns

---

## Unnamed Parameters

Parameter names are optional.

```cpp
void doSomething(int)       // valid but undocumented
void doSomething(int /*count*/)  // preferred — documents intent
```

> [!NOTE]
> Why would you have a parameter you don't use?
> - Backward compatibility (old callers pass a value, new code ignores it)
> - Required function signatures (certain callbacks, operator overloads)
> You'll see this more once you learn operator overloading.

---

## Return Values — Also Passed By Value

Return values work the same way as parameters — a **copy** is sent back.

```cpp
int getValue()
{
    int input { 5 };
    return input; // copy of input's value is sent back
}
```

Flow:

```
input = 5 (local variable)
↓
return input → copy of 5 is made
↓
input is destroyed (function ends)
↓
caller receives the copy
```

> [!IMPORTANT]
> The original variable (`input`) is gone.
> The caller only ever gets a copy.
> This is safe because the copy carries the value out before destruction.

---

## Temporary Objects

When a return value is not stored in a named variable, the compiler creates a **temporary object** to hold it.

```cpp
std::cout << getValue() << '\n';
```

Flow:

```
getValue() runs
↓
Returns copy of value
↓
Compiler creates unnamed temporary object
↓
std::cout uses temporary
↓
Temporary is destroyed
```

> [!NOTE]
> Temporary objects exist just long enough to be used.
> You never name them. The compiler manages them automatically.
> This is why you can use a return value directly without storing it first.

---

## What I Noticed

- The learncpp example `getValueFromUser(int val)` had an unnecessary parameter — the function takes user input anyway, so passing a value in serves no purpose. Learncpp confirmed this later.
- Parameters and local variables feel the same from inside the function — they're both just local variables with scope limited to the function body.

---

# 2.5 Introduction to Local Scope

---

## Core Idea

Variables only exist where they're defined.

**Curly braces `{}` define the boundary.**

```cpp
{
    int x { 5 }; // x created here
}
// x destroyed here — cannot be accessed outside
```

---

## Local Variables

Variables declared inside a function or block are **local variables**.

```cpp
int main()
{
    int x { 5 }; // local to main
}
```

---

## Scope vs Lifetime — Not The Same Thing

This is one of the most important distinctions in C++.

| Concept | Question it answers | When it applies | Violation result |
|---|---|---|---|
| **Scope** | Where can I access this variable? | Compile time | Compile error |
| **Lifetime** | When does this variable exist in memory? | Runtime | Undefined behavior |

> [!IMPORTANT]
> Scope and lifetime look similar but are fundamentally different.
> Scope is a compile-time rule enforced by the compiler.
> Lifetime is a runtime property — the compiler cannot always protect you.

---

## The Key Insight — Alive But Invisible

A variable can be **alive** (in memory) but **invisible** (out of scope).

```cpp
int main()
{
    int x { 5 };    // x created

    otherFunc();    // x still EXISTS in memory during this call
                    // but x is NOT accessible inside otherFunc()

    std::cout << x; // x accessible again
}                   // x destroyed here
```

```
Timeline of x:

main() starts
    → x created (alive + visible)
    → otherFunc() called
        → x still alive, but invisible inside otherFunc
    → otherFunc() ends
    → x alive + visible again
main() ends
    → x destroyed
```

> [!NOTE]
> This is why scope and lifetime are different concepts.
> Scope controls visibility. Lifetime controls existence.

---

## Anonymous Blocks

You can create a block `{}` anywhere inside a function.
Variables inside live and die within that block.

```cpp
int main()
{
    int x { 5 };

    {
        int y { 10 }; // y created
        std::cout << y; // fine
    } // y destroyed here

    std::cout << x; // fine
    std::cout << y; // COMPILE ERROR — y is out of scope
}
```

> [!NOTE]
> Anonymous blocks are used intentionally to control when a variable is destroyed.
> Useful later with objects that manage resources (file handles, locks, etc.)

---

## Scope Violation vs Lifetime Violation

### Scope Violation — Compiler catches it

```cpp
{
    int x { 5 };
}

std::cout << x; // ERROR: 'x' was not declared in this scope
```

Result: **Compile error** — safe, caught before your program even runs.

---

### Lifetime Violation — You must catch it

```cpp
int* ptr {};

{
    int x { 5 };
    ptr = &x;     // ptr points to x
}                 // x is destroyed here

std::cout << *ptr; // UNDEFINED BEHAVIOR — x no longer exists
```

Result: **Undefined behavior** — no compile error, but the program is broken.

> [!IMPORTANT]
> Scope violations: compiler is your safety net.
> Lifetime violations: YOU are your own safety net.
> The compiler cannot always detect when you access a destroyed object.

---

## What Happens When a Variable is Destroyed

```
Scope ends (closing brace reached)
↓
Destructor runs (if the type has one)
↓
Object is destroyed
↓
Memory becomes available for reuse
```

> [!NOTE]
> The memory doesn't vanish immediately — it just becomes "available."
> Like a hotel room after checkout: belongings might still be there,
> but a new guest could arrive at any moment.
> This is why accessing a destroyed variable is undefined — sometimes
> the old value is still there, sometimes it's been overwritten.

---

## Out of Scope vs Going Out of Scope

These sound similar but refer to different things:

| Term | Refers to | Meaning |
|---|---|---|
| **Out of scope** | The identifier (name) | The name can no longer be used |
| **Going out of scope** | The object (variable) | The object is being destroyed |

```cpp
{
    int x { 5 };
} // x goes out of scope (object destroyed)

std::cout << x; // x is out of scope (name inaccessible)
```

---

## Variable Lifetime Flow

```
Definition reached at runtime
↓
Variable created and initialized
↓
Variable exists and is usable
↓
End of scope reached (closing brace)
↓
Variable destroyed
↓
Memory available for reuse
```

---

## Modern C++ Style — Define Close to First Use

Old C style (avoid):

```cpp
int main()
{
    int x;
    int y;
    int sum;

    // 50 lines of code...

    x = 5;
    y = 10;
    sum = x + y;
}
```

Modern C++ (prefer):

```cpp
int main()
{
    int x { 5 };
    int y { 10 };
    int sum { x + y };

    std::cout << sum;
}
```

> [!NOTE]
> The old C style existed because older compilers required all variables at the top.
> This restriction was lifted in C99.
> In modern C++: define variables as close to their first use as possible.
> Smaller scope = easier to read = fewer bugs.

---

## Parameters vs Local Variables — When to Use Which

```
Use a parameter when:
    → the caller will provide the value

Use a local variable when:
    → the function creates or calculates the value itself
```

```cpp
int add(int x, int y)   // x and y are parameters — caller provides them
{
    int result { x + y }; // result is local — function creates it
    return result;
}
```

---

## What I Noticed

- Scope violations give compile errors — safe and obvious.
- Lifetime violations give undefined behavior — dangerous and silent.
- A variable can be alive in memory but completely invisible from where you're writing code.
- Anonymous blocks can be used intentionally to force early destruction of a variable.
- The "out of scope" vs "going out of scope" distinction is subtle but matters — one is about the name, one is about the object.

---
