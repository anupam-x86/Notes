# Global Variables

A **global variable** (also called a **namespace-scope variable**) is a variable declared outside of all functions, classes, and blocks.

```cpp
#include <iostream>

int counter{0};

int main()
{
    ++counter;
    std::cout << counter << '\n';
}
```

The variable `counter` is declared at **namespace scope**, making it a global variable.

Unlike local variables, global variables are not owned by any function. They exist independently and can potentially be accessed from anywhere in the program, depending on their linkage.

---

# Why Use Global Variables?

Most variables are declared inside functions because they are only needed while that function executes.

Sometimes, however, data needs to exist independently of any single function.

For example:

- A program-wide configuration.
- The current application version.
- Shared counters.
- Lookup tables.
- Mathematical constants.

Global variables provide a way to store such data for the lifetime of the program.

---

# Characteristics of Global Variables

A global variable:

- Is declared at namespace scope.
- Has **static storage duration**.
- Exists for the entire lifetime of the program.
- May have **internal** or **external linkage**, depending on how it is declared.
- Is initialized before `main()` begins executing.

For example,

```cpp
int score{};
```

has:

- Namespace scope
- Static storage duration
- External linkage

whereas

```cpp
static int score{};
```

has:

- Namespace scope
- Static storage duration
- Internal linkage

The variable's **scope**, **storage duration**, and **linkage** are independent properties describing different aspects of the variable.

---

# Global vs Local Variables

| Property | Local Variable | Global Variable |
|----------|----------------|-----------------|
| Declared in | Function or block | Namespace scope |
| Scope | Block scope | Namespace scope |
| Storage duration | Automatic (usually) | Static |
| Lifetime | Until block exits | Entire program |
| Linkage | No linkage | Internal or External |

# Non-const Global Variables

A **non-const global variable** is a namespace-scope variable that is **not** declared `const` or `constexpr`.

```cpp
int counter{0};
double temperature{25.0};
std::string username{"Alice"};
```

By default, non-const global variables have **external linkage**.

This means they can be referred to from other translation units using a declaration.

---

## External Linkage by Default

Consider:

```cpp
// globals.cpp

int counter{0};
```

Another translation unit can access the same variable.

```cpp
// main.cpp

extern int counter;

int main()
{
    ++counter;
}
```

Both translation units refer to the **same** object.

---

## Shared State

Since a non-const global variable has external linkage by default, every part of the program that can access it sees the same object.

For example,

```cpp
int counter{0};

void increment()
{
    ++counter;
}

void print()
{
    std::cout << counter;
}
```

If `increment()` changes `counter`, `print()` observes the updated value because both functions refer to the same variable.

---

## Internal Linkage

If a non-const global variable is only needed within one translation unit, it should not be exposed to the rest of the program.

This can be achieved using internal linkage.

```cpp
static int counter{};
```

or, preferably in modern C++,

```cpp
namespace
{
    int counter{};
}
```

Now the variable is accessible only within the current translation unit.

---

## Problems with Non-const Global Variables

Although convenient, non-const global variables introduce several problems.

### Hidden Dependencies

Functions may rely on global variables without making those dependencies obvious.

```cpp
int score{0};

void addPoints()
{
    score += 10;
}
```

Nothing in the function's interface indicates that it modifies `score`.

---

### Shared Mutable State

Any function with access to the variable can change it.

```cpp
counter = 5;
counter = -10;
counter = 1000;
```

As programs grow, it becomes increasingly difficult to determine where a value was modified.

---

### Tight Coupling

Multiple parts of a program become dependent on the same variable.

Changing or removing the variable may require modifications throughout the codebase.

---

### Harder Testing

Functions that depend on global variables are more difficult to test in isolation because their behavior depends on external program state.

---

## When Are Non-const Globals Acceptable?

Non-const global variables should generally be avoided, but there are legitimate uses.

Examples include:

- Application-wide state.
- Logging systems.
- Resource managers.
- Singleton-like infrastructure.
- Interfacing with operating systems or legacy APIs.

Even in these situations, many projects prefer encapsulating shared state inside classes rather than exposing raw global variables.

---

## Best Practice

Prefer local variables whenever possible.

If data must be shared across functions, consider:

- Passing it as a function argument.
- Storing it as a class member.
- Encapsulating it behind an interface.

Reserve non-const global variables for situations where shared program-wide state is genuinely required.

---

# `const` and `constexpr` Global Variables

Many global variables represent values that should never change after initialization.

Examples include:

- Mathematical constants
- Configuration values
- Limits
- Application metadata

For such values, C++ provides `const` and `constexpr`.

```cpp
const int maxStudents{30};

constexpr double pi{3.141592653589793};
```

Unlike ordinary global variables, these variables are immutable after initialization.

---

## Internal Linkage by Default

Namespace-scope `const` and `constexpr` variables have **internal linkage** by default.

```cpp
const int maxStudents{30};

constexpr double pi{3.141592653589793};
```

This means each translation unit receives its own copy of the variable.

Although multiple translation units may contain variables with the same name, they are different objects and therefore do not violate the One Definition Rule (ODR).

---

## Why Internal Linkage?

Constants are commonly placed in header files.

```cpp
// constants.h

constexpr int maxStudents{30};
```

Suppose this header is included by several source files.

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

Each translation unit contains:

```cpp
constexpr int maxStudents{30};
```

Because the variable has internal linkage, every translation unit owns its own copy.

No linker conflict occurs.

---

## One Copy Per Translation Unit

Although the variables have identical names and values,

```text
Translation Unit #1
constexpr int maxStudents{30};

Translation Unit #2
constexpr int maxStudents{30};

Translation Unit #3
constexpr int maxStudents{30};
```

they are different objects.

This behavior is usually acceptable because constants are immutable.

Whether there is one copy or several copies rarely matters.

---

## Sharing a Constant

Sometimes a program requires **one shared constant object** rather than one copy per translation unit.

Before C++17, this was typically achieved using `extern`.

```cpp
// constants.h

extern const int maxStudents;
```

```cpp
// constants.cpp

const int maxStudents{30};
```

Since C++17, the preferred solution is an **inline variable**.

```cpp
inline constexpr int maxStudents{30};
```

This allows the definition to remain in the header while ensuring the entire program refers to a single object.

---

## `const` vs `constexpr`

Both can be used for global constants.

```cpp
const int a{10};
constexpr int b{20};
```

The difference is the same as for local variables:

- `const` means the object cannot be modified after initialization.
- `constexpr` additionally requires the initializer to be a constant expression, allowing the value to be used in compile-time contexts.

Whenever possible, prefer `constexpr` for compile-time constants.

---

## Best Practice

Global constants are generally acceptable because they do not introduce shared mutable state.

Prefer:

```cpp
inline constexpr double pi{3.141592653589793};
```

over

```cpp
double pi{3.141592653589793};
```

An immutable shared constant is much safer than a mutable global variable.

---

# Inline Global Variables

Before C++17, defining a shared global variable in a header file was difficult.

Consider the following header:

```cpp
// constants.h

constexpr int maxStudents{30};
```

Every translation unit including this header received its own copy of `maxStudents`.

This works because namespace-scope `constexpr` variables have **internal linkage** by default.

However, sometimes we want **one shared global variable** that is accessible throughout the entire program.

C++17 introduced **inline variables** to solve this problem.

---

## What is an Inline Global Variable?

An inline global variable is a namespace-scope variable declared with the `inline` keyword.

```cpp
inline int counter{0};
```

or

```cpp
inline constexpr double pi{3.141592653589793};
```

Unlike ordinary global variables, an inline variable may be defined in multiple translation units, provided that every definition is identical.

The linker merges those definitions into a single object.

---

## Defining Inline Variables in Headers

Inline variables are intended to be defined directly in header files.

```cpp
// constants.h

inline constexpr int maxStudents{30};
```

Every translation unit that includes the header receives the definition.

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

Normally, multiple definitions of the same global variable would violate the One Definition Rule (ODR).

However, because the variable is declared `inline`, these identical definitions are allowed.

---

## One Shared Object

Although every translation unit contains the definition,

```text
Translation Unit #1
inline constexpr int maxStudents{30};

Translation Unit #2
inline constexpr int maxStudents{30};

Translation Unit #3
inline constexpr int maxStudents{30};
```

the entire program contains only **one** `maxStudents` object.

Every translation unit refers to that same object.

---

## Inline vs Ordinary Global Variables

Ordinary global variable:

```cpp
int counter{};
```

- External linkage by default.
- Exactly one definition is permitted.
- Defining it in a header causes ODR violations.

Inline global variable:

```cpp
inline int counter{};
```

- May be defined in multiple translation units.
- The linker merges identical definitions.
- Safe to define in header files.

---

## Inline Globals vs `extern`

Before C++17:

```cpp
// constants.h

extern const int maxStudents;
```

```cpp
// constants.cpp

const int maxStudents{30};
```

Since C++17:

```cpp
// constants.h

inline constexpr int maxStudents{30};
```

The declaration and definition can now live together in the header.

This simplifies project organization and is especially useful for header-only libraries.

---

## Best Practice

For shared global constants in modern C++, prefer:

```cpp
inline constexpr int maxStudents{30};
```

For mutable shared global variables:

```cpp
inline int counter{};
```

Although legal, mutable global variables should still be used sparingly, as they introduce shared mutable state.

---

# Global Variable Initialization

Global variables have **static storage duration**, which means they exist for the entire lifetime of the program.

Before `main()` begins executing, every global variable is initialized.

Unlike local variables, whose initialization occurs when execution reaches their declaration, global variables are initialized **before any user code runs**.

---

# Stages of Initialization

Global variable initialization occurs in two stages:

1. **Static initialization**
2. **Dynamic initialization**

Every global variable undergoes one of these stages before `main()` starts.

---

# Static Initialization

**Static initialization** occurs before any dynamic initialization.

It consists of two kinds of initialization:

- Zero initialization
- Constant initialization

---

## Zero Initialization

If a global variable is not explicitly initialized, it is **zero-initialized**.

```cpp
int counter;
double temperature;
bool enabled;
```

Before `main()` begins:

```cpp
counter      == 0
temperature  == 0.0
enabled      == false
```

Unlike local variables, uninitialized global variables do **not** contain indeterminate values.

---

## Constant Initialization

If a global variable can be initialized using a **constant expression**, it is initialized during static initialization.

```cpp
const int maxStudents{30};

constexpr double pi{3.141592653589793};

int value{10};
```

These values are known before the program starts executing.

Constant initialization is:

- Fast
- Predictable
- Independent of runtime execution

Whenever possible, the compiler performs constant initialization.

---

# Dynamic Initialization

If a global variable cannot be initialized using a constant expression, it undergoes **dynamic initialization**.

For example:

```cpp
std::string username{"Alice"};
```

or

```cpp
int randomNumber{generateRandom()};
```

These initializations require executable code.

Therefore, they occur before `main()`, but **after static initialization**.

---

## Initialization Order

Within a single translation unit, global variables are dynamically initialized in the order in which they are defined.

```cpp
int a{1};
int b{a + 1};
```

Here:

1. `a` is initialized.
2. `b` is initialized.

This order is well-defined because both variables belong to the same translation unit.

However, the order between different translation units is a different story—and can lead to one of the most well-known issues in C++: the **Static Initialization Order Fiasco**, which we'll discuss next.

---

# The Static Initialization Order Fiasco

Within a single translation unit, global variables are dynamically initialized in the order in which they are defined.

Across **different translation units**, however, the order of dynamic initialization is generally **unspecified**.

This can lead to one of the most well-known pitfalls involving global variables: the **Static Initialization Order Fiasco (SIOF)**.

---

## The Problem

Consider the following project.

```text
Project
├── logger.cpp
├── config.cpp
└── main.cpp
```

`logger.cpp`

```cpp
Logger logger{};
```

`config.cpp`

```cpp
Config config{logger};
```

Suppose the constructor of `Config` uses `logger`.

The problem is that the C++ standard does **not** specify whether `logger` or `config` is dynamically initialized first.

Two outcomes are possible.

### Safe

```text
logger initialized
        ↓
config initialized
        ↓
main()
```

Everything works correctly.

---

### Unsafe

```text
config initialized
        ↓
uses logger
        ↓
logger not initialized yet
        ↓
Undefined Behavior
```

`Config` attempts to use `logger` before `logger` has been constructed.

The program now has **undefined behavior**.

---

## Why Does This Happen?

Each translation unit is compiled independently.

During linking, the linker combines the object files, but the C++ standard generally does not specify the order in which dynamic initialization occurs between different translation units.

As a result, relying on one global object to initialize another global object in a different translation unit is unsafe.

---

## What Is Affected?

The Static Initialization Order Fiasco only affects **dynamic initialization**.

Variables that undergo **constant initialization** are initialized before any dynamic initialization begins and therefore are not affected.

For example:

```cpp
constexpr int maxStudents{30};
```

is always safe.

Whereas:

```cpp
std::string username{"Alice"};
```

requires dynamic initialization and may participate in initialization order problems.

---

## How to Avoid It

### Prefer `constexpr` and Constant Initialization

Whenever possible, initialize global variables using constant expressions.

```cpp
inline constexpr int maxStudents{30};
```

Constant initialization is guaranteed to occur before any dynamic initialization.

---

### Avoid Global Object Dependencies

Try not to write global objects whose constructors depend on other global objects.

Instead of:

```cpp
Config config{logger};
```

consider constructing the objects inside `main()` or passing dependencies explicitly.

---

### Use Function-Local Static Variables

A common modern solution is the **Construct-on-First-Use Idiom**.

```cpp
Logger& getLogger()
{
    static Logger logger{};
    return logger;
}
```

The `logger` object is initialized the first time `getLogger()` is called.

Since C++11, initialization of function-local static variables is guaranteed to be thread-safe.

This approach avoids initialization order problems because the object is constructed only when it is actually needed.

---

## Best Practice

Avoid relying on the initialization order of global objects across translation units.

Prefer:

- Local variables
- Dependency injection
- `constexpr` constants
- Function-local static variables

These approaches are safer, easier to understand, and avoid the Static Initialization Order Fiasco.

---

# Why Global Variables Are Dangerous

Global variables can be convenient because they are accessible from anywhere in a program.

However, that convenience comes at a cost.

As programs grow larger, global variables often make code harder to understand, maintain, test, and debug.

For this reason, experienced C++ developers generally recommend minimizing their use.

---

# Hidden Dependencies

One of the biggest problems with global variables is that they create **hidden dependencies**.

Consider:

```cpp
int score{0};

void addPoints()
{
    score += 10;
}
```

From the function signature,

```cpp
void addPoints();
```

there is no indication that the function modifies a global variable.

Someone reading the interface cannot determine what the function depends on or what state it changes.

A better design makes dependencies explicit.

```cpp
void addPoints(int& score)
{
    score += 10;
}
```

Now the function clearly communicates that it modifies `score`.

---

# Shared Mutable State

A mutable global variable can be modified by any part of the program.

```cpp
counter = 10;
counter = -5;
counter = 1000;
```

As the codebase grows, determining **where** a variable changed becomes increasingly difficult.

This can make debugging significantly harder.

---

# Tight Coupling

Global variables tightly couple unrelated parts of a program.

Suppose several functions use the same global variable.

```cpp
int settings{};

void loadSettings();
void saveSettings();
void printSettings();
```

Each function now depends on the existence of `settings`.

Changing the representation or removing the variable may require modifying many parts of the program.

This reduces modularity.

---

# Harder Testing

Functions that depend on global variables are difficult to test independently.

```cpp
int score{100};

int calculateBonus()
{
    return score * 2;
}
```

The function's result depends on external state.

To test it properly, the test must first configure the global variable.

Functions that receive all required data through parameters are generally easier to test because they do not depend on hidden program state.

---

# Initialization Problems

As discussed previously, global objects may suffer from the **Static Initialization Order Fiasco (SIOF)**.

If one global object depends on another global object in a different translation unit, initialization order becomes unspecified, potentially leading to undefined behavior.

Local variables and function-local static variables avoid this issue.

---

# Reduced Reusability

A function that depends on global variables is harder to reuse.

For example,

```cpp
int counter{};

void increment()
{
    ++counter;
}
```

This function can only work with the global `counter`.

A more reusable design is:

```cpp
void increment(int& value)
{
    ++value;
}
```

Now the function can operate on any integer.

---

# When Are Global Variables Acceptable?

Global variables are not inherently bad.

There are situations where they are appropriate.

Examples include:

- Program-wide compile-time constants.
- Read-only configuration values.
- Logging systems.
- Resource managers.
- Interfacing with operating system APIs.
- Low-level systems programming.

Even in these situations, mutable global state should be minimized whenever possible.

---

# Best Practices

When designing a program:

- Prefer local variables over global variables.
- Pass data through function parameters instead of relying on hidden state.
- Encapsulate shared state inside classes when appropriate.
- Prefer immutable (`constexpr` or `const`) globals over mutable globals.
- Use `inline constexpr` for shared constants in modern C++.
- Keep mutable global variables to an absolute minimum.

---
# Legitimate Uses of Global Variables

Although global variables are often discouraged, they are **not inherently bad**.

Like any programming tool, they are appropriate in certain situations and inappropriate in others.

The key question is not:

> "Should global variables ever be used?"

Instead, it is:

> "Is this information truly global to the entire program?"

If the answer is yes, a global variable may be the right choice.

---

# Global Constants

One of the most common and safest uses of global variables is storing constants.

```cpp
inline constexpr double pi{3.141592653589793};

inline constexpr int maxStudents{30};
```

These variables:

- Never change.
- Have no shared mutable state.
- Can be safely accessed from anywhere.

Global constants are widely accepted in modern C++.

---

# Configuration Values

Some values describe the entire application.

For example:

```cpp
inline constexpr std::string_view appName{"Photo Editor"};

inline constexpr int defaultPort{8080};
```

These values represent application-wide configuration and naturally belong at namespace scope.

---

# Logging Systems

Many applications have a single logging system shared by every component.

```cpp
Logger logger{};
```

Instead of creating multiple independent loggers, a single shared logger may be appropriate.

In larger projects, this is often encapsulated behind a logging interface or singleton rather than exposed as a raw global variable.

---

# Resource Managers

Programs often maintain shared resources such as:

- Texture managers
- Font managers
- Audio systems
- Database connection pools

These resources may need to be accessible throughout the application.

Rather than exposing the resources directly as global variables, they are usually encapsulated inside dedicated classes.

---

# System-Level Resources

Operating systems and low-level libraries frequently expose program-wide resources.

Examples include:

- Environment information.
- Hardware interfaces.
- Operating system handles.
- Window managers.
- Graphics contexts.

In systems programming, some global state is unavoidable.

---

# Why Constants Are Preferred

Consider these two examples.

```cpp
inline constexpr double pi{3.141592653589793};
```

```cpp
double pi{3.141592653589793};
```

The first is much safer.

A constant:

- Cannot be modified accidentally.
- Has no hidden side effects.
- Introduces no shared mutable state.

Whenever possible, prefer immutable global variables over mutable ones.

---

# When Should You Avoid Globals?

A variable probably should **not** be global if:

- It is only used by one function.
- It is only needed by one class.
- It is only shared by a few functions.
- It can easily be passed as a function parameter.
- It represents temporary program state.

In these cases, local variables or class members usually provide a cleaner design.

---

# Best Practice

Ask yourself:

> **"Does this variable truly represent program-wide information?"**

If the answer is:

- **Yes** → A global variable (preferably `inline constexpr` if immutable) may be appropriate.
- **No** → Prefer local variables, function parameters, or encapsulated class members.

Global variables should be used carefully.

Modern C++ encourages minimizing global state and making dependencies explicit whenever possible.

The following guidelines are widely recommended.

---

# Prefer Local Variables

If a variable is only needed within a single function, declare it locally.

```cpp
void printArea(double radius)
{
    constexpr double pi{3.141592653589793};

    std::cout << pi * radius * radius;
}
```

A local variable:

- Limits its scope.
- Reduces accidental misuse.
- Improves readability.

---

# Prefer Passing Data Through Parameters

Instead of relying on global variables,

```cpp
int score{};

void addPoints()
{
    score += 10;
}
```

prefer making dependencies explicit.

```cpp
void addPoints(int& score)
{
    score += 10;
}
```

Anyone reading the function immediately knows what data it operates on.

---

# Prefer Encapsulation

If multiple functions share state, consider storing that state inside a class.

Instead of:

```cpp
int score{};
```

use:

```cpp
class Game
{
private:
    int m_score{};

public:
    void addPoints(int points);
};
```

Encapsulation gives better control over how shared data is accessed and modified.

---

# Prefer Immutable Globals

If a value never changes, make it immutable.

```cpp
inline constexpr double pi{3.141592653589793};
```

Immutable globals are much safer than mutable ones because they cannot introduce shared mutable state.

---

# Use `inline constexpr` for Shared Constants

Since C++17, shared constants are typically written as:

```cpp
inline constexpr int maxStudents{30};
```

This allows the constant to be defined directly in a header while remaining ODR-safe.

---

# Limit the Visibility of Globals

If a global variable is only needed within a single translation unit, give it **internal linkage**.

Prefer:

```cpp
namespace
{
    int counter{};
}
```

over exposing the variable with external linkage.

Keeping variables private reduces coupling between translation units.

---

# Avoid Global Object Dependencies

Avoid writing global objects whose constructors depend on other global objects.

```cpp
Config config{logger}; // Risky
```

Such code may suffer from the **Static Initialization Order Fiasco (SIOF)**.

Instead, consider:

- Constructing objects in `main()`.
- Using dependency injection.
- Using function-local static variables when appropriate.

---

# Use Globals Only for Truly Global Information

Ask yourself:

> **"Does every part of the program naturally need access to this data?"**

If the answer is **no**, the variable probably should not be global.

If the answer is **yes**, consider whether an immutable global constant or an encapsulated object is the better design.

---

# Summary

## Non-const Global Variables

- Are namespace-scope variables.
- Have **external linkage** by default.
- Can be shared across translation units using `extern`.
- Can be given internal linkage using `static` or an unnamed namespace.
- Introduce shared mutable state, which can make programs harder to understand and maintain.
- Should generally be avoided unless there is a clear design need.

---

## `const` and `constexpr` Global Variables

Namespace-scope `const` and `constexpr` variables:

- Represent immutable global data.
- Have **internal linkage** by default.
- Produce one object per translation unit.
- Can safely be defined in header files.
- Can be shared across translation units using `inline` (since C++17).
- `constexpr` is generally preferred over `const` when the value is known at compile time.

---

## Inline Global Variables

Inline global variables:

- Were introduced in **C++17**.
- May be defined in multiple translation units.
- Represent one shared object throughout the program.
- Can safely be defined in header files.
- Eliminate the need for separate `extern` declarations for many shared variables.
- Are the preferred modern solution for shared global constants.

---

## Global Variable Initialization

Global variables are initialized before `main()` begins.

Initialization occurs in two stages:

1. **Static initialization**
   - Zero initialization
   - Constant initialization

2. **Dynamic initialization**
   - Runtime initialization requiring executable code

Within a single translation unit, dynamic initialization follows the order of definitions. Across different translation units, the order is generally unspecified, leading to potential initialization problems.

---

## Static Initialization Order Fiasco (SIOF)

- Global variables in different translation units are dynamically initialized in an unspecified order.
- If one global object depends on another during initialization, the program may exhibit undefined behavior.
- This issue is known as the **Static Initialization Order Fiasco (SIOF)**.
- Constant initialization is not affected.
- Prefer `constexpr`, avoid global dependencies, or use function-local static variables to eliminate this problem.

---

## Why Global Variables Are Dangerous

Global variables can introduce:

- Hidden dependencies.
- Shared mutable state.
- Tight coupling between components.
- Harder testing and debugging.
- Initialization order problems.
- Reduced code reusability.

Whenever practical, prefer local variables or encapsulated state. Global variables should be reserved for situations where program-wide shared data is genuinely required.

---

## Legitimate Uses

Global variables are appropriate when they represent information that naturally belongs to the entire program, such as:

- Program-wide constants.
- Configuration values.
- Logging systems.
- Shared resource managers.
- Low-level system resources.

In modern C++, immutable global constants (`inline constexpr`) are widely accepted, while mutable global variables should be used sparingly and only when there is a clear design justification.

---

## Best Practices

When working with global variables:

- Prefer local variables whenever possible.
- Pass data through function parameters instead of relying on hidden state.
- Encapsulate shared mutable state inside classes.
- Prefer `inline constexpr` for shared constants.
- Use internal linkage for implementation details.
- Avoid dependencies between global objects.
- Reserve global variables for information that genuinely belongs to the entire program.

Following these practices leads to code that is easier to understand, maintain, test, and extend.

# Key Points

## Global Variables

- A global variable is a variable declared at **namespace scope**.
- Global variables have **static storage duration**.
- They exist for the entire lifetime of the program.
- Their linkage may be **internal** or **external**, depending on how they are declared.
- They are initialized before `main()` begins executing.

---

## Non-const Global Variables

- Non-const global variables have **external linkage** by default.
- They can be shared across translation units using `extern`.
- They introduce shared mutable state.
- Overusing them can make programs harder to understand, test, and maintain.

---

## `const` and `constexpr` Global Variables

- Namespace-scope `const` and `constexpr` variables have **internal linkage** by default.
- They can safely be defined in header files.
- Each translation unit receives its own copy.
- `constexpr` is generally preferred when the value is known at compile time.

---

## Inline Global Variables

- Introduced in **C++17**.
- May be defined in multiple translation units.
- The linker merges identical definitions into one object.
- Allow shared global constants to be defined directly in header files.
- `inline constexpr` is the preferred modern approach for shared constants.

---

## Global Variable Initialization

- Global variables are initialized before `main()`.
- Initialization occurs in two stages:
  - **Static initialization**
    - Zero initialization
    - Constant initialization
  - **Dynamic initialization**
- Within a translation unit, dynamic initialization follows the order of definitions.

---

## Static Initialization Order Fiasco (SIOF)

- Dynamic initialization order between different translation units is generally unspecified.
- Global objects that depend on other global objects may exhibit undefined behavior.
- Constant initialization is not affected.
- Prefer `constexpr`, dependency injection, or function-local static variables to avoid SIOF.

---

## Why Global Variables Are Dangerous

Global variables can introduce:

- Hidden dependencies.
- Shared mutable state.
- Tight coupling.
- Harder testing and debugging.
- Initialization order problems.
- Reduced code reusability.

---

## Legitimate Uses

Global variables are appropriate for:

- Program-wide constants.
- Configuration values.
- Logging systems.
- Resource managers.
- Low-level system resources.

Prefer immutable globals over mutable ones whenever possible.

---

## Best Practices

- Prefer local variables whenever possible.
- Pass data through function parameters instead of relying on global state.
- Encapsulate shared mutable state inside classes.
- Prefer `inline constexpr` for shared constants.
- Use internal linkage for implementation details.
- Avoid dependencies between global objects.
- Reserve global variables for information that genuinely belongs to the entire program.
