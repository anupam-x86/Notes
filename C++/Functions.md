# LearnCpp Notes — 2.1 to 2.8

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
# LearnCpp Notes — 2.6 to 2.8

---

# 2.6 — Why Functions Are Useful

## The Core Reason

Functions exist to avoid repeating yourself and to break complex problems into manageable pieces.

```cpp
// Without functions — repeated logic everywhere
std::cout << "Enter a number: ";
int x{};
std::cin >> x;
// ... same block repeated 3 times in the program

// With functions — write once, use anywhere
int getInput()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
    return x;
}
```

---

## Three Main Benefits

```
1. Reusability
   Write once, call many times.
   Change once, fixed everywhere.

2. Readability
   main() reads like a summary of what the program does.
   Details are hidden inside named functions.

3. Testability
   A small focused function is easy to test in isolation.
   A 300-line main() is nearly impossible to test.
```

---

## Refactoring

When a function becomes too long, too complicated, or hard to understand — split it.

This is called **refactoring**.

```cpp
// Too much in one function:
void doEverything()
{
    // get input
    // validate input
    // process data
    // format output
    // print output
}

// Refactored:
int getInput() { ... }
bool isValid(int x) { ... }
int process(int x) { ... }
void printResult(int x) { ... }
```

> [!NOTE]
> Rule of thumb: a function should do **one thing**.
> If you find yourself putting "and" in the description of what a function does,
> it probably needs to be split into two functions.

---

## DRY — Don't Repeat Yourself

```
Use variables    → for values used multiple times
Use functions    → for logic used multiple times
Use loops        → for repeated execution
```

> [!NOTE]
> DRY is a guideline, not an absolute rule.
> Too many tiny functions can hurt readability.
> Use judgment — split when it genuinely helps clarity.

---

# 2.7 — Forward Declarations and Definitions

## The Problem

The compiler reads files top to bottom. If you call a function before defining it, the compiler doesn't know it exists.

```cpp
int main()
{
    add(1, 2); // ERROR — compiler hasn't seen add() yet
}

int add(int x, int y) { return x + y; } // defined too late
```

---

## Forward Declaration — The Solution

Tell the compiler a function exists before you define it.

```cpp
int add(int x, int y); // forward declaration — just the signature

int main()
{
    add(1, 2); // compiler trusts the declaration
}

int add(int x, int y) // actual definition — can be anywhere
{
    return x + y;
}
```

> [!NOTE]
> Parameter names in declarations are optional for the compiler:
> `int add(int x, int y);` and `int add(int, int);` are both valid.
> But always include names — they document what the parameters mean.

---

## Order-Agnostic Programming

Forward declarations let you define functions in whatever order makes sense for a human reader — group related functions together, most important logic first — without worrying about compiler order requirements.

```
Without forward declarations:
    Functions must be defined before they are used
    → order is forced by the compiler

With forward declarations:
    Define functions in any order
    → order is chosen for readability
```

---

## Declaration vs Definition

| | Declaration | Definition |
|---|---|---|
| **What it does** | Tells compiler something exists | Actually creates it |
| **Memory** | No memory allocated | Memory allocated |
| **Function** | Signature only, no body | Has full body |
| **Variable** | `extern int x;` (rare) | `int x {};` |

```
Every definition is also a declaration.
Not every declaration is a definition.
```

> [!IMPORTANT]
> For variables — declaration and definition almost always happen together.
> For functions — you can declare without defining (forward declaration).
> This distinction matters more for functions than variables.

---

## What Happens With a Missing Definition

```cpp
int add(int x, int y); // declared

int main()
{
    add(1, 2); // compiler is fine — trusts declaration
}

// add() never defined anywhere
```

```
Compiler: OK — declaration exists ✓
Linker:   ERROR — definition not found ✗
→ "undefined reference to add(int, int)"
```

> [!IMPORTANT]
> Missing declaration → compile error
> Missing definition  → linker error
> These are different errors at different stages.

---

## The One Definition Rule (ODR)

### Within one file, one scope:
Everything — variables, functions, types, templates — can only be defined once.

### Across the whole program:
- Variables and functions → only ONE definition across all files
- Types and templates → CAN appear in multiple files, but must be identical in every file

> [!NOTE]
> The type/template exception is what makes header files possible.
> A struct defined in a header gets copied into every file that includes it.
> ODR allows this as long as every copy is identical.

### Function Overloading — Not an ODR Violation

Functions with the same name but different parameters are considered distinct functions.

```cpp
int add(int x, int y);         // function 1
int add(int x, int y, int z);  // function 2 — different parameters, not a violation
```

---

## Variable Shadowing

A local variable with the same name as an outer variable hides the outer one.

```cpp
int x = 10; // global

void foo()
{
    int x = 3; // local — shadows global x
    return x;  // returns 3, not 10
}
```

> [!NOTE]
> Use `-Wshadow` flag to get compiler warnings when shadowing occurs.
> It's a common source of subtle bugs.

---

# 2.8 — Programs With Multiple Code Files

## Why Multiple Files

- Keeps code organized
- Only changed files need recompilation
- Reduces naming conflicts
- Enables teamwork (different people own different files)

---

## The Problem Without Headers

```cpp
// add.cpp
int add(int x, int y) { return x + y; }

// main.cpp
int main()
{
    add(1, 2); // ERROR — compiler doesn't know add exists
}
```

Compiler sees each file in isolation. It has no memory of other files.

---

## Solution 1 — Manual Forward Declaration

```cpp
// main.cpp
int add(int x, int y); // manually forward declared

int main()
{
    add(1, 2); // now compiler knows
}
```

Works but doesn't scale. 10 functions = 10 manual declarations in every file that uses them. Change a signature = update every file manually.

---

## Solution 2 — Header Files (Correct Way)

```
add.h   → declarations only
add.cpp → definitions
main.cpp → #include "add.h"
```

```cpp
// add.h
int add(int x, int y);

// add.cpp
#include "add.h"   // verify definition matches declaration
int add(int x, int y)
{
    return x + y;
}

// main.cpp
#include "add.h"   // gets the declaration automatically

int main()
{
    add(1, 2);     // works
}
```

> [!IMPORTANT]
> Always include the corresponding `.h` in the `.cpp` file.
> This lets the compiler catch mismatches between declaration and definition immediately.
> Without it, mismatches may only show up as runtime bugs.

---

## Header Files Are Table of Contents

```
.h file  = table of contents (what exists, what types/signatures are)
.cpp file = actual content (how it works)
```

---

## Never #include .cpp Files

```cpp
#include "add.cpp"  // WRONG
#include "add.h"    // CORRECT
```

Including `.cpp` copies the entire definition into your file. If `add.cpp` is also compiled separately, the linker sees two definitions of `add()` — ODR violation.

> [!IMPORTANT]
> `#include` only `.h` files.
> `.cpp` files are compiled separately and linked, never included.

---

## Compiling Multiple Files

```bash
# All at once (fine for small projects)
g++ main.cpp add.cpp -o app

# Separately then link (correct for large projects)
g++ -c main.cpp       # produces main.o
g++ -c add.cpp        # produces add.o
g++ main.o add.o -o app  # linker combines
```

> [!NOTE]
> Separate compilation is faster for large projects.
> Only the changed file needs recompilation — the linker recombines everything.
> Build systems like `make` and `cmake` automate this process.

---

## How the Compiler Resolves Identifiers

```
Identifier used in expression
↓
Compiler looks for declaration or definition in same file
↓ not found → compile error

↓ found
Compiler happy, generates object file

Linker looks for definition across all object files
↓ not found → linker error: "undefined reference to..."

↓ found
Links it, produces executable
```

```
Compiler = sees one file at a time
Linker   = sees all object files together
```

---

## What I Noticed

- Compiler and linker are completely separate — different jobs, different visibility, different errors.
- Including a header in its own `.cpp` file is a self-consistency check, not just convention.
- Never include `.cpp` files — include only `.h` files.
- Manual forward declarations work but don't scale — headers are the real solution.
- ODR violation from including `.cpp` directly is a real and common beginner mistake.
