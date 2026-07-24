# Linkage

Linkage is one of the fundamental concepts in C++ that explains how names (identifiers) are shared across a program.

Understanding linkage requires first understanding how a C++ program is built. Concepts such as `static`, `extern`, global variables, `inline` variables, and the One Definition Rule (ODR) all depend on this foundation.

---

# Why Does Linkage Exist?

Simple C++ programs often consist of a single source file.

```cpp
#include <iostream>

int square(int x)
{
    return x * x;
}

int main()
{
    std::cout << square(5);
}
```

As programs grow larger, keeping everything in one file becomes impractical.

Instead, programs are split into multiple source files.

```text
Project
├── main.cpp
├── math.cpp
├── math.h
├── graphics.cpp
├── graphics.h
└── physics.cpp
```

Each source file is compiled separately.

This introduces an important question:

> **If two different source files both refer to the identifier `square`, how does the compiler know whether they refer to the same function or to different functions?**

Similarly,

- Can one source file access a variable defined in another?
- Can two files have variables with the same name?
- How does the compiler avoid name conflicts?

These questions are answered by **linkage**.

---

# The C++ Build Process

Before understanding linkage, it's important to understand how a C++ program is transformed into an executable.

Unlike interpreted languages, a C++ program is **compiled** before it can run.

The build process consists of several stages.

```text
Source Files
      │
      ▼
Preprocessor
      │
      ▼
Translation Units
      │
      ▼
Compiler
      │
      ▼
Object Files
      │
      ▼
Linker
      │
      ▼
Executable
```

Each stage has a specific responsibility.

---

## 1. Source Files

A typical C++ project consists of multiple source and header files.

Example:

```text
Project
├── main.cpp
├── math.cpp
├── math.h
└── graphics.cpp
```

- **Source files (`.cpp`)** contain function and variable definitions.
- **Header files (`.h` or `.hpp`)** typically contain declarations that are shared between multiple source files.

---

## 2. Preprocessor

Before the compiler begins compiling your program, each source file is passed through the **preprocessor**.

The preprocessor handles directives beginning with `#`, such as:

```cpp
#include
#define
#ifdef
#ifndef
```

The most important directive is `#include`.

For example:

```cpp
// main.cpp

#include "math.h"

int main()
{
}
```

Suppose `math.h` contains:

```cpp
int square(int x);
```

Before compilation, the preprocessor literally replaces the `#include` directive with the contents of the header file.

```cpp
int square(int x);

int main()
{
}
```

The compiler never sees the `#include` directive—it only sees the expanded source code produced by the preprocessor.

---

## 3. Translation Units

After preprocessing, each source file becomes a **translation unit**.

A translation unit is simply:

> **A source file after all preprocessing has been completed.**

For example,

```text
main.cpp
    │
#include "math.h"
    │
    ▼
Translation Unit
```

Every `.cpp` file produces its own translation unit.

At this stage, each translation unit is completely independent of the others.

The compiler compiles one translation unit at a time.

## 4. Compiler

The **compiler** processes each translation unit independently and translates it into machine code.

For example:

```text
main.cpp
     │
     ▼
Translation Unit
     │
     ▼
Compiler
     │
     ▼
main.o
```

Similarly,

```text
math.cpp
     │
     ▼
Translation Unit
     │
     ▼
Compiler
     │
     ▼
math.o
```

The compiler does **not** compile the entire project at once.

Instead, it compiles **one translation unit at a time**.

This means the compiler has **no knowledge of other translation units** while compiling the current one.

For example,

```text
main.cpp
```

cannot directly see what exists inside

```text
math.cpp
```

unless it has been informed through declarations (usually provided by a header file).

This independence is one of the reasons forward declarations and header files are necessary.

---

## 5. Object Files

The output of the compiler is an **object file**.

Common extensions include:

- `.o` (Linux/macOS)
- `.obj` (Windows)

An object file contains:

- Compiled machine code
- Symbol information (functions and variables)
- References to symbols defined elsewhere

It is **not** an executable program.

Instead, it represents one compiled translation unit that is waiting to be combined with others.

For example:

```text
main.cpp  ─────► main.o

math.cpp  ─────► math.o

graphics.cpp ─► graphics.o
```

Each source file produces its own object file.

---

## 6. Linker

After every translation unit has been compiled, the **linker** combines all object files into a single executable program.

```text
main.o
      │
math.o
      ├────► Linker ─────► program.exe
graphics.o
```

The linker's responsibilities include:

- Combining object files.
- Resolving references between translation units.
- Detecting duplicate definitions.
- Producing the final executable.

For example,

Suppose `main.cpp` calls:

```cpp
square(5);
```

but the function is actually defined in `math.cpp`.

During compilation, the compiler only knows that a function named `square` exists.

The linker later finds the actual definition in `math.o` and connects the function call to the correct implementation.

---

## Why This Matters

Because each translation unit is compiled independently, the compiler cannot determine whether an identifier in another translation unit refers to the same entity.

That responsibility belongs to the **linker**.

The rules that determine whether identical names in different translation units refer to the same entity are called **linkage**.

The next section introduces translation units in more detail before exploring the different types of linkage.

# Translation Units

A **translation unit** is the basic unit of compilation in C++.

Formally, a translation unit is:

> A source file after it has been processed by the preprocessor.

This means that all preprocessing directives have already been handled before the compiler sees the code.

For example,

```cpp
// main.cpp

#include "math.h"

int main()
{
    return square(5);
}
```

Suppose `math.h` contains:

```cpp
int square(int);
```

After preprocessing, the compiler effectively sees:

```cpp
int square(int);

int main()
{
    return square(5);
}
```

This expanded source code is the **translation unit**.

---

## One Source File, One Translation Unit

Every source file (`.cpp`) produces its own translation unit.

For example:

```text
Project
├── main.cpp
├── math.cpp
└── graphics.cpp
```

After preprocessing:

```text
main.cpp
      │
      ▼
Translation Unit #1

math.cpp
      │
      ▼
Translation Unit #2

graphics.cpp
      │
      ▼
Translation Unit #3
```

Each translation unit is compiled independently into its own object file.

---

## Translation Units Are Independent

One of the most important ideas in C++ is that **translation units are completely independent during compilation**.

When the compiler is compiling:

```text
main.cpp
```

it has **no knowledge** of what exists inside:

```text
math.cpp
```

unless that information has been provided through declarations.

For example,

```cpp
// main.cpp

int main()
{
    square(5); // Error
}
```

The compiler has never seen a declaration of `square`, so it reports an error.

If we include the header:

```cpp
#include "math.h"

int main()
{
    square(5); // OK
}
```

the compiler now knows that `square` exists, even though its definition is located in another translation unit.

---

## Why Header Files Exist

Since translation units are compiled independently, the compiler needs a way to learn about functions and variables defined elsewhere.

Header files provide this information by containing **declarations** that can be shared across multiple translation units.

```text
math.h
        ▲
        │
 ┌──────┴──────┐
 │             │
main.cpp    math.cpp
```

Both source files include the same header, ensuring they agree on the declarations of shared functions and variables.

---

## Why Translation Units Matter

Translation units are the foundation of several important C++ concepts, including:

- Forward declarations
- Header files
- Linkage
- The One Definition Rule (ODR)
- `extern`
- `inline` variables

# What is Linkage?

When multiple translation units are compiled into a single program, they may contain identifiers with the same name.

For example, suppose two source files both contain a function named `print`.

```text
main.cpp
└── print()

utility.cpp
└── print()
```

Do these two `print` functions refer to the **same function**, or are they **completely unrelated**?

Similarly, consider two global variables with the same name.

```text
main.cpp
└── int value;

utility.cpp
└── int value;
```

Are these two declarations referring to one shared variable, or are they two separate variables?

The rules that answer these questions are determined by **linkage**.

---

## Definition

**Linkage** determines whether declarations of an identifier in different scopes or translation units refer to the **same entity**.

In other words, linkage answers the question:

> **If two declarations have the same name, do they refer to the same object or function?**

If they do, the declarations are said to be **linked**.

If they don't, they represent different entities, even though they have the same name.

---

## The Three Types of Linkage

Every identifier in C++ has one of three kinds of linkage:

| Linkage | Meaning |
|---------|---------|
| **No linkage** | The identifier cannot be referred to outside its own scope. |
| **Internal linkage** | The identifier can be referred to anywhere within the same translation unit. |
| **External linkage** | The identifier can be referred to from any translation unit in the program. |

These three categories determine how widely an identifier is visible throughout a program.

---

## Linkage vs Scope

Although they are related, **scope** and **linkage** describe different properties.

| Concept | Answers |
|---------|---------|
| **Scope** | Where can this identifier be used? |
| **Storage Duration** | How long does the object exist? |
| **Linkage** | Can declarations in different scopes or translation units refer to the same entity? |

For example,

```cpp
int value{};
```

This variable has:

- Namespace (global) scope
- Static storage duration
- External linkage

Each property describes a different aspect of the variable.

---

## An Intuitive View

You can think of the three linkage types like this:

- **No linkage** → "Only this scope knows me."
- **Internal linkage** → "Only this translation unit knows me."
- **External linkage** → "The entire program knows me."

# No Linkage

An identifier with **no linkage** can only be referred to within the scope in which it is declared.

Even if another scope or translation unit declares an identifier with the same name, the two declarations refer to **different entities**.

---

## Local Variables

The most common examples of identifiers with **no linkage** are local variables.

```cpp
void foo()
{
    int x{10};
}

void bar()
{
    int x{20};
}
```

Although both variables are named `x`, they are completely unrelated.

The `x` inside `foo()` exists only within the scope of `foo()`, and the `x` inside `bar()` exists only within the scope of `bar()`.

These variables do **not** refer to the same object.

---

## Function Parameters

Function parameters also have **no linkage**.

```cpp
void print(int value)
{
    std::cout << value;
}

void square(int value)
{
    std::cout << value * value;
}
```

The two parameters named `value` are independent.

Each exists only within its own function.

---

## Block Scope Variables

Variables declared inside nested blocks also have no linkage.

```cpp
int main()
{
    {
        int count{1};
    }

    {
        int count{2};
    }
}
```

Although both variables are named `count`, they are different objects because each belongs to a different block scope.

---

## Name Hiding vs Linkage

It's important to distinguish **name hiding** from **linkage**.

```cpp
int value{100};

int main()
{
    int value{50};

    std::cout << value << '\n';   // 50
    std::cout << ::value << '\n'; // 100
}
```

The local `value` hides the global `value`, but they are still two different variables.

This behavior is a consequence of **scope**, not linkage.

The local variable has **no linkage**, while the global variable has **external linkage**.

---
# Internal Linkage

An identifier with **internal linkage** can be referred to anywhere within the **same translation unit**, but it cannot be referred to from other translation units.

In other words:

> An identifier with internal linkage is **private to its translation unit**.

This allows multiple translation units to use the same identifier name without conflicting with one another.

---

## Visualizing Internal Linkage

Suppose a program consists of two translation units.

```text
Translation Unit #1
┌──────────────────────────┐
│ helper()                 │
│ counter                  │
└──────────────────────────┘

Translation Unit #2
┌──────────────────────────┐
│ helper()                 │
│ counter                  │
└──────────────────────────┘
```

If both `helper()` and `counter` have **internal linkage**, then:

- Code in Translation Unit #1 can access its own `helper()` and `counter`.
- Code in Translation Unit #2 can access its own `helper()` and `counter`.
- The two translation units **cannot** access each other's identifiers.
- Even though the names are identical, they refer to **different entities**.

---

## Why Internal Linkage Exists

Not every function or global variable is meant to be shared across an entire program.

Many are implementation details used only within a single source file.

Internal linkage allows you to hide these implementation details from the rest of the program.

This provides several benefits:

- Prevents accidental name collisions.
- Reduces unnecessary global visibility.
- Improves encapsulation.
- Makes code easier to maintain.

---

## Identifiers with Internal Linkage

Several kinds of identifiers have internal linkage, including:

- Global variables declared with `static`
- Functions declared with `static`
- Namespace-scope `const` variables (by default)
- Namespace-scope `constexpr` variables (by default)
- Members of an unnamed namespace

Each of these will be discussed in the following sections.

---

## Example

Suppose `math.cpp` contains:

```cpp
static int counter{0};

static void increment()
{
    ++counter;
}
```

Both `counter` and `increment` have **internal linkage**.

Any code inside `math.cpp` can use them.

However, another source file cannot access them.

For example:

```cpp
// main.cpp

extern int counter; // Error: no matching external definition
```

Even though `counter` exists in `math.cpp`, it is invisible outside that translation unit because it has internal linkage.

---

## Internal Linkage Is Not Local Scope

Internal linkage is often confused with local scope, but they describe different things.

A local variable:

```cpp
void foo()
{
    int x{};
}
```

has:

- Block scope
- No linkage

A namespace-scope variable declared `static`:

```cpp
static int x{};
```

has:

- Namespace (global) scope
- Internal linkage

The variable is visible throughout the translation unit, but not outside it.

---

# `static` and Internal Linkage

The `static` keyword has several meanings in C++, depending on where it is used.

In this section, we are concerned only with **namespace-scope** (`global`) variables and functions.

> **Note:** The meaning of `static` for local variables is different and is discussed with **storage duration**, not linkage.

---

## `static` Global Variables

A global variable declared with `static` has **internal linkage**.

```cpp
static int counter{0};
```

This means:

- Any code within the same translation unit can access `counter`.
- Other translation units cannot access it.

For example:

```cpp
// math.cpp

static int counter{0};

void increment()
{
    ++counter;
}
```

The following is valid because both declarations are in the same translation unit.

```cpp
// math.cpp

void print()
{
    std::cout << counter;
}
```

However, another translation unit cannot access it.

```cpp
// main.cpp

extern int counter; // Error
```

Although `counter` exists, it has internal linkage, so no external declaration can refer to it.

---

## `static` Functions

Functions can also be declared `static`.

```cpp
static void helper()
{
    std::cout << "Helper\n";
}
```

Like `static` global variables, a `static` function has **internal linkage**.

It can be called anywhere within the same translation unit but cannot be called from another translation unit.

```cpp
// math.cpp

static void helper()
{
}

void calculate()
{
    helper(); // OK
}
```

```cpp
// main.cpp

helper(); // Error
```

The `helper` function is invisible outside `math.cpp`.

---

## Why Use `static`?

Suppose two source files each define a helper function.

```cpp
// math.cpp

static void helper()
{
}
```

```cpp
// graphics.cpp

static void helper()
{
}
```

Although both functions have the same name, they belong to different translation units.

Because they have **internal linkage**, they refer to different functions and do not conflict with one another.

Without internal linkage, both functions would have external linkage, causing a multiple-definition error during linking.

---

## Limitations of `static`

Historically, `static` was the primary way to give namespace-scope variables and functions internal linkage.

Modern C++ provides a better alternative:

- **Unnamed namespaces**

They achieve the same goal while avoiding some of the limitations of `static`.

For this reason, modern C++ generally prefers unnamed namespaces over `static` for internal linkage.

We'll discuss unnamed namespaces later in this note.

---

## Summary

At namespace scope:

```cpp
static int value{};
```

- Namespace scope
- Static storage duration
- Internal linkage

```cpp
static void helper()
{
}
```

- Namespace scope
- External lifetime (exists for the duration of the program)
- Internal linkage

The `static` keyword hides a variable or function from other translation units, making it private to the current translation unit.

# `const` and `constexpr` Global Variables

Namespace-scope `const` and `constexpr` variables have **internal linkage by default**.

```cpp
const int maxStudents{30};

constexpr double pi{3.141592653589793};
```

Unlike ordinary global variables, these identifiers are visible only within their own translation unit.

---

## Why?

Constants are commonly placed in header files so that multiple source files can use them.

For example:

```cpp
// constants.h

constexpr int maxStudents{30};
```

This header might be included by several source files.

```text
main.cpp
      │
      ├──► constants.h

math.cpp
      │
      ├──► constants.h

graphics.cpp
      │
      └──► constants.h
```

After preprocessing, each translation unit contains its own copy of the constant.

Because the constant has **internal linkage**, each translation unit owns a separate object.

This prevents multiple-definition errors during linking.

---

## Example

Suppose `constants.h` contains:

```cpp
constexpr int maxStudents{30};
```

Both source files include it.

```cpp
// main.cpp

#include "constants.h"
```

```cpp
// math.cpp

#include "constants.h"
```

After preprocessing:

```text
Translation Unit #1
constexpr int maxStudents{30};

Translation Unit #2
constexpr int maxStudents{30};
```

These are **not** the same object.

Each translation unit has its own copy.

Because the variable has internal linkage, the linker does not treat this as an ODR violation.

---

## Why Not External Linkage?

Imagine if namespace-scope `constexpr` variables had external linkage by default.

Every translation unit including the header would define the same variable.

```text
main.cpp
constexpr int maxStudents{30};

math.cpp
constexpr int maxStudents{30};

graphics.cpp
constexpr int maxStudents{30};
```

The linker would encounter multiple definitions of `maxStudents`, violating the One Definition Rule (ODR).

Giving `const` and `constexpr` variables internal linkage by default avoids this problem.

---

## Sharing a Constant Across Translation Units

Sometimes you want every translation unit to refer to the **same** constant object.

Internal linkage cannot provide this because each translation unit receives its own copy.

Historically, this was done using `extern`.

Since C++17, the preferred solution is **inline variables**, which we'll discuss later in this note.

---

## Summary

Namespace-scope `const` and `constexpr` variables:

- Have **internal linkage** by default.
- Can safely be defined in header files.
- Produce one object per translation unit.
- Do not cause multiple-definition errors.
- Can be shared across translation units using `inline` (C++17) when a single shared object is required.# `const` and `constexpr` Global Variables

Namespace-scope `const` and `constexpr` variables have **internal linkage by default**.

```cpp
const int maxStudents{30};

constexpr double pi{3.141592653589793};
```

Unlike ordinary global variables, these identifiers are visible only within their own translation unit.

---

## Why?

Constants are commonly placed in header files so that multiple source files can use them.

For example:

```cpp
// constants.h

constexpr int maxStudents{30};
```

This header might be included by several source files.

```text
main.cpp
      │
      ├──► constants.h

math.cpp
      │
      ├──► constants.h

graphics.cpp
      │
      └──► constants.h
```

After preprocessing, each translation unit contains its own copy of the constant.

Because the constant has **internal linkage**, each translation unit owns a separate object.

This prevents multiple-definition errors during linking.

---

## Example

Suppose `constants.h` contains:

```cpp
constexpr int maxStudents{30};
```

Both source files include it.

```cpp
// main.cpp

#include "constants.h"
```

```cpp
// math.cpp

#include "constants.h"
```

After preprocessing:

```text
Translation Unit #1
constexpr int maxStudents{30};

Translation Unit #2
constexpr int maxStudents{30};
```

These are **not** the same object.

Each translation unit has its own copy.

Because the variable has internal linkage, the linker does not treat this as an ODR violation.

---

## Why Not External Linkage?

Imagine if namespace-scope `constexpr` variables had external linkage by default.

Every translation unit including the header would define the same variable.

```text
main.cpp
constexpr int maxStudents{30};

math.cpp
constexpr int maxStudents{30};

graphics.cpp
constexpr int maxStudents{30};
```

The linker would encounter multiple definitions of `maxStudents`, violating the One Definition Rule (ODR).

Giving `const` and `constexpr` variables internal linkage by default avoids this problem.

---

## Sharing a Constant Across Translation Units

Sometimes you want every translation unit to refer to the **same** constant object.

Internal linkage cannot provide this because each translation unit receives its own copy.

Historically, this was done using `extern`.

Since C++17, the preferred solution is **inline variables**, which we'll discuss later in this note.

---

# Unnamed Namespaces

Another way to give identifiers **internal linkage** is to place them inside an **unnamed namespace**.

An unnamed namespace is a namespace without a name.

```cpp
namespace
{
    int counter{0};

    void helper()
    {
        ++counter;
    }
}
```

Everything declared inside an unnamed namespace has **internal linkage**.

---

## Why Unnamed Namespaces?

Unnamed namespaces were introduced as a modern alternative to using `static` at namespace scope.

Instead of writing:

```cpp
static int counter{0};

static void helper()
{
}
```

modern C++ prefers:

```cpp
namespace
{
    int counter{0};

    void helper()
    {
    }
}
```

Both approaches give `counter` and `helper` **internal linkage**, making them accessible only within the current translation unit.

---

## How They Work

Although the namespace has no name, its members can still be used normally within the same translation unit.

```cpp
namespace
{
    int value{42};
}

int main()
{
    std::cout << value; // OK
}
```

The compiler treats the unnamed namespace as a unique namespace that cannot be referred to from any other translation unit.

Effectively, every translation unit gets its own private unnamed namespace.

---

## Multiple Translation Units

Suppose two source files both contain:

```cpp
namespace
{
    int counter{};
}
```

```text
main.cpp
┌─────────────────────┐
│ namespace {         │
│     int counter;    │
│ }                   │
└─────────────────────┘

math.cpp
┌─────────────────────┐
│ namespace {         │
│     int counter;    │
│ }                   │
└─────────────────────┘
```

Even though both variables are named `counter`, they belong to different unnamed namespaces.

Therefore, they are completely independent objects and do not conflict during linking.

---

## `static` vs Unnamed Namespace

Both provide internal linkage.

| `static` | Unnamed Namespace |
|----------|-------------------|
| Applies to one declaration at a time. | Applies to every declaration inside the namespace. |
| Older C-style approach. | Modern C++ approach. |
| Still valid. | Generally preferred in modern C++. |

For example:

Using `static`:

```cpp
static int counter{};
static void helper() {}
static void print() {}
```

Using an unnamed namespace:

```cpp
namespace
{
    int counter{};
    void helper() {}
    void print() {}
}
```

The unnamed namespace groups related implementation details together and makes it clear that they are private to the translation unit.

---

## Best Practice

In modern C++, prefer **unnamed namespaces** over `static` for namespace-scope variables and functions.

They provide the same internal linkage while grouping related private declarations into a single namespace, resulting in cleaner and more maintainable code.

---

# External Linkage

An identifier with **external linkage** can be referred to from **any translation unit** in the program.

In other words:

> An identifier with external linkage represents the **same entity** everywhere it is declared.

Unlike internal linkage, external linkage allows multiple translation units to share the same variable or function.

---

## Visualizing External Linkage

Suppose a project contains two translation units.

```text
Translation Unit #1
┌─────────────────────────────┐
│ extern int counter;         │
│ helper();                   │
└──────────────┬──────────────┘
               │
               │
               ▼
        Same Variable
        Same Function
               ▲
               │
               │
┌──────────────┴──────────────┐
│ int counter{0};             │
│ void helper() { ... }       │
└─────────────────────────────┘
Translation Unit #2
```

Both translation units refer to the **same** variable and the **same** function.

---

## Global Variables

By default, a **non-const namespace-scope variable** has external linkage.

```cpp
int counter{0};
```

This variable may be referred to from another translation unit using an appropriate declaration.

For example,

```cpp
// counter.cpp

int counter{0};
```

```cpp
// main.cpp

extern int counter;

int main()
{
    ++counter;
}
```

Both files refer to the **same** object.

---

## Functions

Functions also have **external linkage by default**.

```cpp
void print()
{
    std::cout << "Hello\n";
}
```

The function can be called from another translation unit after a declaration has been provided.

```cpp
// print.h

void print();
```

```cpp
// main.cpp

#include "print.h"

int main()
{
    print();
}
```

Although the definition exists in another translation unit, both declarations refer to the same function.

---

## Why External Linkage Exists

External linkage allows programs to be divided into multiple source files.

For example:

```text
Project
├── main.cpp
├── math.cpp
├── graphics.cpp
└── audio.cpp
```

Without external linkage, every source file would be isolated.

Functions and variables defined in one translation unit could never be used by another.

External linkage enables different parts of a program to communicate while still being compiled independently.

---

## External Linkage Does Not Mean Multiple Definitions

Having external linkage does **not** mean you can define the identifier multiple times.

For example,

```cpp
// file1.cpp

int counter{};
```

```cpp
// file2.cpp

int counter{};
```

Both variables have external linkage.

However, they are separate **definitions** of the same externally linked variable.

When the linker encounters both definitions, it reports a **multiple-definition error**, violating the **One Definition Rule (ODR)**.

We'll examine the ODR in detail later in this note.

---

# Forward Declarations

As we've seen, each translation unit is compiled independently.

This creates an important problem:

> **How can the compiler compile code that refers to a function or variable whose definition is located in another translation unit?**

The answer is **forward declarations**.

---

## What is a Forward Declaration?

A **forward declaration** introduces an identifier to the compiler before its complete definition is seen.

It tells the compiler:

> "This identifier exists. You'll see its full definition later."

This allows the compiler to type-check code without needing the complete implementation immediately.

---

## Forward Declaration of a Function

Suppose we have:

```cpp
// math.cpp

int square(int x)
{
    return x * x;
}
```

We want to call `square()` from `main.cpp`.

Without a declaration:

```cpp
// main.cpp

int main()
{
    square(5); // Error
}
```

The compiler has never heard of `square`.

We solve this by providing a forward declaration.

```cpp
int square(int);
```

Now:

```cpp
int square(int);

int main()
{
    square(5); // OK
}
```

The compiler knows:

- the function exists,
- its return type,
- its parameter types.

The actual implementation can be found later by the linker.

---

## Forward Declaration of a Variable

Variables can also be forward declared.

Suppose one translation unit contains:

```cpp
// globals.cpp

int counter{0};
```

Another translation unit can declare it as:

```cpp
// main.cpp

extern int counter;
```

This declaration tells the compiler:

> There is an `int` named `counter`, but its definition exists somewhere else.

The linker later finds that definition.

---

## Declaration vs Definition

This distinction is extremely important.

A **declaration** introduces a name.

A **definition** actually creates the object or function.

For example:

```cpp
int square(int);   // Declaration
```

```cpp
int square(int x)  // Definition
{
    return x * x;
}
```

Similarly,

```cpp
extern int counter; // Declaration
```

```cpp
int counter{0};     // Definition
```

A definition is also a declaration, but a declaration is not necessarily a definition.

---

## Why Header Files Mostly Contain Declarations

Imagine writing:

```cpp
int square(int);
```

in every source file that needs it.

That would quickly become difficult to maintain.

Instead, we place declarations in a header.

```cpp
// math.h

int square(int);
```

Every source file simply includes the header.

```cpp
#include "math.h"
```

This ensures every translation unit sees the same declaration.

The function definition remains in a single source file.

---

# The `extern` Keyword

The `extern` keyword is used to declare that a variable or function is **defined elsewhere**.

It tells the compiler:

> "This declaration does not create the object. Its definition exists in another translation unit."

`extern` is primarily used with **variables**, since functions already have external linkage by default.

---

# `extern` Variables

Suppose we define a global variable in one source file.

```cpp
// globals.cpp

int counter{0};
```

Another translation unit can access the same variable using:

```cpp
// main.cpp

extern int counter;

int main()
{
    ++counter;
}
```

Here,

```cpp
extern int counter;
```

is only a declaration.

It does **not** create another variable.

Instead, both translation units refer to the **same** `counter`.

---

## Declaration vs Definition

One of the most common beginner mistakes is confusing these two.

```cpp
extern int counter;
```

This is a **declaration**.

No storage is allocated.

---

```cpp
int counter{0};
```

This is a **definition**.

Storage is allocated for the variable.

---

Think of it this way:

- Declaration → "This variable exists."
- Definition → "Create the variable."

---

## `extern` Does Not Allocate Memory

Consider:

```cpp
extern int counter;
```

This line introduces the name `counter` to the compiler.

However, no object is created.

Memory is allocated only when the definition is encountered.

```cpp
int counter{0};
```

Regardless of how many `extern` declarations exist, there is still only **one** object.

---

## Multiple Declarations

A variable may be declared multiple times.

```cpp
// file1.cpp

extern int counter;
```

```cpp
// file2.cpp

extern int counter;
```

```cpp
// globals.cpp

int counter{0};
```

All three declarations refer to the same variable.

The program contains:

- Multiple declarations
- One definition

This is perfectly valid.

---

## `extern` with Initialization

Adding an initializer changes the meaning.

```cpp
extern int counter{0};
```

Although it contains `extern`, this is a **definition**, because the variable is initialized.

It allocates storage exactly like:

```cpp
int counter{0};
```

The `extern` keyword no longer prevents the declaration from becoming a definition.

---

## `extern` Functions

Functions normally have external linkage by default.

Therefore, writing

```cpp
void print();
```

and

```cpp
extern void print();
```

are equivalent.

The `extern` keyword is optional for function declarations and is rarely written explicitly.

---

## Common Mistakes

### Forgetting the Definition

```cpp
// main.cpp

extern int counter;

int main()
{
    ++counter;
}
```

If no translation unit defines

```cpp
int counter;
```

the program compiles, but the linker reports an **undefined reference** (or similar linker error).

The compiler only checks that the declaration exists.

The linker is responsible for finding the actual definition.

---

### Defining the Variable Multiple Times

```cpp
// file1.cpp

int counter{};
```

```cpp
// file2.cpp

int counter{};
```

Both are definitions.

The linker now finds two definitions of the same externally linked variable, violating the **One Definition Rule (ODR)**.

---

# The One Definition Rule (ODR)

As we've seen, multiple translation units can refer to the same function or variable through **external linkage**.

This raises an important question:

> **How many times may an object or function be defined in a program?**

The answer is given by the **One Definition Rule (ODR)**.

---

## What is the One Definition Rule?

The **One Definition Rule (ODR)** is a set of rules that determines how many definitions of an entity may exist in a C++ program.

In general:

> **Every object or function with external linkage must have exactly one definition in the entire program.**

Multiple declarations are allowed.

Multiple definitions are generally **not**.

---

## Declarations vs Definitions

Consider:

```cpp
extern int counter;
```

This is only a declaration.

You may write this declaration in many translation units.

```cpp
// main.cpp

extern int counter;
```

```cpp
// math.cpp

extern int counter;
```

```cpp
// graphics.cpp

extern int counter;
```

This is perfectly valid because none of these declarations creates the object.

Now suppose one translation unit contains:

```cpp
// globals.cpp

int counter{0};
```

This is the single definition of `counter`.

All `extern` declarations refer to this same object.

---

## Violating the ODR

Suppose two source files both define the same global variable.

```cpp
// file1.cpp

int counter{};
```

```cpp
// file2.cpp

int counter{};
```

Both variables have external linkage.

The linker now finds two definitions of the same object.

Since the ODR requires exactly one definition, the linker reports a **multiple-definition error**.

---

The same applies to functions.

```cpp
// file1.cpp

void print()
{
}
```

```cpp
// file2.cpp

void print()
{
}
```

Both functions have external linkage.

Again, the linker finds two definitions of the same function and reports an error.

---

## Why the Rule Exists

Imagine if multiple definitions were allowed.

```cpp
// file1.cpp

int counter{5};
```

```cpp
// file2.cpp

int counter{100};
```

Which value should the program use?

Should `counter` be `5` or `100`?

There is no sensible answer.

The ODR prevents this ambiguity by requiring exactly one definition.

---

## Internal Linkage and the ODR

The ODR applies differently to identifiers with **internal linkage**.

Consider:

```cpp
// file1.cpp

static int counter{};
```

```cpp
// file2.cpp

static int counter{};
```

Although both variables have the same name, they have **internal linkage**.

They are different objects belonging to different translation units.

Therefore, they do **not** violate the ODR.

The linker never considers them to be the same entity.

The same is true for declarations inside unnamed namespaces.

---

## Common Linker Errors

Violating the ODR typically results in linker errors such as:

```text
multiple definition of 'counter'
```

or

```text
duplicate symbol 'print'
```

The exact wording depends on the compiler and linker, but the cause is usually the same: more than one definition of the same externally linked entity.

---

## ODR Exceptions

Although the ODR generally requires one definition, there are a few exceptions.

For example:

- Inline functions
- Inline variables (since C++17)
- Templates (under certain conditions)

These entities are allowed to have identical definitions in multiple translation units.

We'll discuss **inline variables** later in this note.

---

# Inline Variables (C++17)

Before C++17, defining a global variable in a header file often caused problems.

Consider the following header:

```cpp
// constants.h

constexpr int maxStudents{30};
```

If multiple source files included this header, each translation unit would receive its own copy of `maxStudents`.

This works because namespace-scope `constexpr` variables have **internal linkage** by default.

However, sometimes you want **one shared variable** for the entire program rather than one copy per translation unit.

Before C++17, achieving this required using `extern`, which separated the declaration from the definition.

C++17 introduced **inline variables** to solve this problem.

---

## What is an Inline Variable?

An inline variable is declared using the `inline` keyword.

```cpp
inline int counter{0};
```

or

```cpp
inline constexpr double pi{3.141592653589793};
```

Unlike ordinary global variables, an inline variable may be **defined in multiple translation units**, provided that **every definition is identical**.

The linker treats all of these definitions as referring to the **same object**.

---

## Why Were Inline Variables Introduced?

Suppose you want to place a shared constant in a header.

Without `inline`:

```cpp
// constants.h

int value{10};
```

If three source files include this header:

```text
main.cpp
math.cpp
graphics.cpp
```

each translation unit contains:

```cpp
int value{10};
```

The linker now encounters three definitions of the same externally linked variable, violating the ODR.

---

With `inline`:

```cpp
inline int value{10};
```

Every translation unit still contains the definition.

However, this is now legal.

The linker merges the identical definitions into a single variable.

---

## Memory Model

Although an inline variable may appear in multiple translation units,

```text
Translation Unit #1
inline int counter{};

Translation Unit #2
inline int counter{};

Translation Unit #3
inline int counter{};
```

the program still contains only **one object**.

All references point to the same memory location.

The multiple definitions exist only to satisfy compilation of separate translation units.

---

## Inline Variables and the ODR

Normally, the ODR allows only one definition of an externally linked variable.

Inline variables are an exception.

The following is valid:

```cpp
// constants.h

inline constexpr int maxStudents{30};
```

Every translation unit including the header defines `maxStudents`.

Because the definitions are identical and marked `inline`, the ODR permits them.

---

## `extern` vs `inline`

Before C++17:

```cpp
// constants.h

extern const int value;
```

```cpp
// constants.cpp

const int value{10};
```

The declaration and definition must be kept in separate files.

---

Since C++17:

```cpp
// constants.h

inline constexpr int value{10};
```

The declaration and definition can both live in the header.

No separate `.cpp` file is required.

---

## When Should You Use Inline Variables?

Inline variables are particularly useful for:

- Shared global constants.
- Configuration values.
- Header-only libraries.
- Variables that should exist exactly once but are defined in a header.

They are especially common with `constexpr`.

```cpp
inline constexpr int maxStudents{30};
inline constexpr double pi{3.141592653589793};
```

---

# Best Practices

As programs grow larger, managing linkage correctly becomes increasingly important.

The following practices are widely recommended in modern C++.

---

## Prefer Internal Linkage When Possible

If a variable or function is used only within a single translation unit, give it **internal linkage**.

This hides implementation details from the rest of the program and reduces the chance of name collisions.

For example:

```cpp
namespace
{
    void helper()
    {
        // ...
    }
}
```

instead of exposing `helper()` to the entire program.

---

## Minimize Global Variables

Global variables with external linkage create dependencies between translation units.

They make programs harder to understand, maintain, and test.

Whenever practical:

- Prefer local variables.
- Pass data through function parameters.
- Encapsulate shared state inside classes.

---

## Prefer `inline constexpr` for Shared Constants

Since C++17, shared constants intended for use in multiple translation units should usually be written as:

```cpp
inline constexpr int maxStudents{30};
```

This allows the constant to be defined directly in a header without violating the ODR.

---

## Use `extern` Only When Necessary

`extern` is useful when multiple translation units must access the same global variable.

However, shared mutable global state should generally be avoided unless there is a clear design reason.

If you only need to share a constant, prefer an `inline constexpr` variable instead.

---

## Prefer Unnamed Namespaces Over `static`

For namespace-scope variables and helper functions that should remain private to a translation unit, modern C++ generally prefers an unnamed namespace.

```cpp
namespace
{
    void helper()
    {
    }
}
```

instead of

```cpp
static void helper()
{
}
```

Both provide internal linkage, but unnamed namespaces scale better when multiple related declarations are involved.

---

## Keep Declarations and Definitions Consistent

Place declarations in header files and definitions in source files.

A common project layout is:

```text
math.h
    └── Function declarations

math.cpp
    └── Function definitions
```

This allows multiple translation units to share declarations while maintaining a single definition.

---

## Avoid ODR Violations

Remember:

- Multiple **declarations** are usually fine.
- Multiple **definitions** of an externally linked entity are usually not.

If you encounter linker errors such as:

```text
multiple definition of ...
duplicate symbol ...
```

check whether the same variable or function has been defined in more than one translation unit.

---

# Summary

## No Linkage

Identifiers with **no linkage**:

- Cannot be referred to outside their own scope.
- Do not represent the same entity as declarations with the same name elsewhere.
- Are typically local variables, function parameters, and other block-scope declarations.

---

## Internal Linkage

Identifiers with **internal linkage**:

- Can be referred to anywhere within the same translation unit.
- Cannot be referred to from other translation units.
- Help hide implementation details.
- Reduce naming conflicts across a program.

### `const` and `constexpr`

Namespace-scope `const` and `constexpr` variables:

- Have **internal linkage** by default.
- Can safely be defined in header files.
- Produce one object per translation unit.
- Do not cause multiple-definition errors.
- Can be shared across translation units using `inline` (C++17) when a single shared object is required.

### Unnamed Namespaces

Declarations inside an unnamed namespace:

- Have **internal linkage**.
- Are accessible only within their own translation unit.
- Do not conflict with declarations in other translation units.
- Are the preferred modern alternative to `static` for namespace-scope variables and functions.

---

## External Linkage

Identifiers with **external linkage**:

- Can be referred to from any translation unit.
- Represent the same object or function throughout the program.
- Include non-const global variables and ordinary functions by default.
- Allow separate source files to share data and functionality.
- Must obey the One Definition Rule (ODR).

---

## Forward Declarations

Forward declarations:

- Introduce identifiers before their definitions are seen.
- Allow translation units to be compiled independently.
- Are commonly placed in header files.
- Exist for both functions and variables.
- Do **not** create objects or generate executable code.

---

## `extern`

- `extern` declares that a variable is defined elsewhere.
- `extern` declarations do **not** allocate storage.
- The actual object is created by exactly one definition.
- Multiple `extern` declarations may refer to the same object.
- Initializing an `extern` variable makes it a definition.
- `extern` is rarely needed for functions because they already have external linkage by default.

---

## One Definition Rule (ODR)

- The One Definition Rule (ODR) governs how many definitions an entity may have.
- Objects and functions with external linkage generally require exactly one definition in the entire program.
- Multiple declarations are allowed.
- Multiple definitions usually produce linker errors.
- Identifiers with internal linkage do not conflict because each translation unit owns a separate entity.
- Inline functions and inline variables are important exceptions to the ODR.

---

## Inline Variables (C++17)

- Inline variables were introduced in **C++17**.
- They allow identical variable definitions in multiple translation units.
- The linker merges those definitions into one object.
- They are an exception to the One Definition Rule.
- They eliminate the need for separate `extern` declarations and `.cpp` definitions for many shared variables.
- They are the preferred modern way to define shared constants in header files.

# Key Points

- A C++ program is compiled one translation unit at a time.
- A translation unit is a source file after preprocessing.
- Linkage determines whether declarations refer to the same entity.
- There are three kinds of linkage:
  - No linkage
  - Internal linkage
  - External linkage
- Local variables have no linkage.
- `static`, unnamed namespaces, and namespace-scope `const`/`constexpr` variables have internal linkage.
- Ordinary global variables and functions have external linkage by default.
- `extern` declares a variable that is defined elsewhere.
- The One Definition Rule (ODR) generally allows only one definition of an externally linked entity.
- Inline variables (since C++17) are an exception to the ODR and allow identical definitions in multiple translation units.
- Prefer internal linkage for implementation details and `inline constexpr` for shared constants in modern C++.
