# Blocks, Scope & Namespaces

## Compound Statements (Blocks)

A **compound statement** (commonly called a **block**) is a group of zero or more statements enclosed in curly braces (`{}`).

```cpp
{
    int x{10};
    std::cout << x << '\n';
}
```

A block can be used anywhere C++ expects a single statement.

Common examples:

- `if`
- `else`
- loops
- function bodies

This allows multiple statements to be grouped together and treated as one unit.

For example:

```cpp
if (true)
{
    std::cout << "Hello\n";
    std::cout << "World\n";
}
```

Without the block:

```cpp
if (true)
    std::cout << "Hello\n";

std::cout << "World\n";
```

Only the first statement belongs to the `if`.

> **Note:** A block itself is **not** followed by a semicolon.

---

## Empty Blocks

A block may contain **zero statements**.

```cpp
{
}
```

Although uncommon, empty blocks are valid C++.

---

## Nested Blocks

Blocks may contain other blocks.

```cpp
{
    std::cout << "Outer block\n";

    {
        std::cout << "Inner block\n";
    }
}
```

The outer block contains the inner block.

---

## Function Bodies Are Blocks

The body of a function is also a block.

```cpp
int add(int x, int y)
{
    return x + y;
}
```

The statements inside the function body belong to that block's scope.

---


## Outer and Inner Blocks

Consider:

```cpp
{
    // Outer block

    {
        // Inner block
    }
}
```

- The enclosing block is the **outer block**.
- The block inside it is an **inner block** (or **nested block**).

A program can contain many nested blocks.

---

## Nesting Level

The **nesting level** (or **nesting depth**) is the number of blocks inside other blocks.

Example:

```cpp
{
    // Level 1

    {
        // Level 2

        {
            // Level 3
        }
    }
}
```

Deeply nested code becomes difficult to read and maintain.

> **Best Practice:** Keep nesting depth to **three levels or fewer** whenever practical.

---

# Scope

A **scope** determines where an identifier (such as a variable, function, or type name) can be accessed.

Blocks create scopes.

```cpp
{
    int x{10};

    std::cout << x << '\n';
}

std::cout << x << '\n'; // Error: x is outside its scope
```

Variables declared inside a block have block scope.

They can be accessed:

- Inside the block where they are declared.
- Inside nested blocks.

They cannot be accessed after the block ends.

---

# The Problem Namespaces Solve

Large programs often contain many functions, classes, and variables.

Different parts of a program may accidentally use the same name.

Example:

```cpp

// Math code
int add(int x, int y)
{
    return x + y;
}

// Physics code
int add(int x, int y)
{
    return x + y;
}
```
Both functions have the same name, causing a naming conflict.

Namespaces solve this problem by placing identifiers inside separate scopes.

```cpp
namespace Math
{
    int add(int x, int y)
    {
        return x + y;
    }
}

namespace Physics
{
    int add(int x, int y)
    {
        return x + y;
    }
}
```
---

# What is a Namespace?

A **namespace** is a named scope used to organize code and prevent naming conflicts.

It allows multiple identifiers with the same name to exist in different namespaces.

```cpp
namespace Math
{
    int add(int x, int y)
    {
        return x + y;
    }
}

namespace Physics
{
    int add(int x, int y)
    {
        return x + y;
    }
}

Math::add(1, 2);
Physics::add(1, 2);
```

Without namespaces, both `add()` functions would conflict.

---

# Why Use Namespaces?

Namespaces help:

- Prevent naming collisions.
- Organize related code.
- Separate reusable libraries from application-specific code.
- Structure large projects into logical modules.

Example project organization:

```text
Game
├── Graphics
├── Physics
├── Audio
└── UI
```

Equivalent namespaces:

```cpp
namespace Game::Graphics {}
namespace Game::Physics {}
namespace Game::Audio {}
namespace Game::UI {}
```

---

# Scope Resolution Operator (`::`)

The **scope resolution operator (`::`)** specifies the scope in which an identifier should be found.

Think of `::` as **"look inside."**

```cpp
Math::add(2, 3);
std::cout << "Hello";
std::string name;
```

Read as:

- `Math::add` → Find `add` inside `Math`.
- `std::cout` → Find `cout` inside `std`.
- `std::string` → Find `string` inside `std`.

General form:

```cpp
Namespace::Identifier
```

---

## Qualified vs Unqualified Names

### Qualified Name

A qualified name includes scope information.

```cpp
Game::score
std::cout
std::string
::value
```

These names explicitly specify where the identifier is located.

---

### Unqualified Name

```cpp
score
cout
value
```

No scope information is provided.

The compiler must search for the identifier using name lookup rules.

> [!NOTE]
> Qualified names are generally easier to understand because they clearly indicate which identifier is being referenced.

---

# Global Scope

When nothing appears before `::`, it refers to the **global namespace**.

```cpp
int x{10};

int main()
{
    int x{20};

    std::cout << x << '\n';    // 20 (local variable)
    std::cout << ::x << '\n';  // 10 (global variable)
}
```

`::x` means **"look for `x` in the global namespace."**

The scope resolution operator can also access global functions.

```cpp
void print()
{
    std::cout << "Global print\n";
}

namespace Game
{
    void print()
    {
        std::cout << "Game print\n";
    }
}

int main()
{
    Game::print(); // Calls Game::print()
    ::print();     // Calls global print()
}
```

---

# Namespace Naming Convention

**Convention (not a language rule):**

- Program-defined namespaces → **PascalCase**
- Program-defined classes and structs → **PascalCase**

```cpp
namespace Math {}
namespace Graphics {}

class Player {};
struct Vector2 {};
```

Reasons:

- Consistent with the C++ Core Guidelines.
- Helps distinguish user-defined names from library names.
- Improves readability.
- Reduces naming collisions.

> **Note:** Existing libraries may follow different naming styles (for example, `std` is lowercase). When contributing to a project, follow that project's coding style.

---

# Declaring Namespaces

Namespaces can be declared:

- At **global scope**
- Inside another namespace

Valid:

```cpp
namespace Math
{
}

namespace Engine
{
    namespace Graphics
    {
    }
}
```

Invalid:

```cpp
int main()
{
    namespace Math
    {
    } // Error
}
```

Namespaces cannot be declared inside functions or blocks.

---

# Forward Declarations in Namespaces

Forward declarations for namespace members must be placed inside the same namespace.

```cpp
// math.h
namespace Math
{
    int add(int x, int y);
}
```

```cpp
// math.cpp
namespace Math
{
    int add(int x, int y)
    {
        return x + y;
    }
}
```

Usage:

```cpp
std::cout << Math::add(2, 3);
```

The declaration and definition must belong to the same namespace.

---

# Open Namespaces

Unlike classes or functions, a namespace can be defined multiple times.

Each namespace definition contributes to the same namespace.

```cpp
namespace Math
{
    int add(int x, int y)
    {
        return x + y;
    }
}

namespace Math
{
    int subtract(int x, int y)
    {
        return x - y;
    }
}
```

The compiler treats this as:

```cpp
namespace Math
{
    int add(int x, int y)
    {
        return x + y;
    }

    int subtract(int x, int y)
    {
        return x - y;
    }
}
```

This works even when namespace definitions are separated into different source files.

Example:

```text
Math.h
Math.cpp
main.cpp
```

All files can contribute members to:

```cpp
namespace Math
{
}
```

The compiler combines them into one namespace.

Open namespaces allow large libraries to be split across many files while still belonging to the same namespace.

For example, standard library headers such as:

```text
<iostream>
<string>
<vector>
<algorithm>
```

all contribute declarations to:

```cpp
namespace std
{
    // ...
}
```

The compiler merges them into one namespace.

---

# Never Add to `std`

Although C++ allows reopening the `std` namespace:

```cpp
namespace std
{
    // ...
}
```

**Do not add your own functions, classes, or variables to `std`.**

The C++ Standard reserves `std` for the standard library. Adding your own declarations results in **undefined behavior** in almost all cases.

Instead, create your own namespace:

```cpp
namespace MyProject
{
}
```

---

# Nested Namespaces

A namespace can contain another namespace.

Traditional syntax:

```cpp
namespace Foo
{
    namespace Goo
    {
        int add(int x, int y)
        {
            return x + y;
        }
    }
}
```

Usage:

```cpp
Foo::Goo::add(1, 2);
```

Read as:

> Go inside `Foo`, then `Goo`, then call `add`.

---

## C++17 Nested Namespace Syntax

Since C++17, nested namespaces can be written more compactly.

Instead of:

```cpp
namespace Foo
{
    namespace Goo
    {
    }
}
```

write:

```cpp
namespace Foo::Goo
{
}
```

Both forms are completely equivalent.

Prefer the C++17 syntax in modern C++.

---

## Reopening Parent Namespaces

Since namespaces are open, you can later add members to a parent namespace without redefining its nested namespaces.

```cpp
namespace Foo::Goo
{
    void add() {}
}

namespace Foo
{
    void print() {}
}
```

Now both are valid:

```cpp
Foo::print();
Foo::Goo::add();
```

---

# Namespace Lookup

When an identifier is used **without** the scope resolution operator (`::`), C++ performs **unqualified name lookup**.

The compiler searches outward until it finds a matching declaration.

Lookup order:

1. Local scope
2. Current namespace
3. Parent namespace(s)
4. Global namespace

Example:

```cpp
int z{10};

namespace A
{
    int x{20};

    namespace B
    {
        int y{30};

        void print()
        {
            std::cout << y; // Found in B
            std::cout << x; // Found in A
            std::cout << z; // Found in global namespace
        }
    }
}
```

The compiler stops searching as soon as it finds the first matching declaration.

---

## Name Hiding

A declaration in a closer scope hides declarations with the same name in outer scopes.

```cpp
int x{100};

namespace A
{
    int x{50};

    namespace B
    {
        int x{10};

        void print()
        {
            std::cout << x; // Prints 10
        }
    }
}
```

Lookup finds the nearest `x`, so the outer declarations are ignored.

---

## Why Use Namespace Aliases?

Aliases are useful for long namespace names.

Without an alias:

```cpp
namespace Engine::Graphics::OpenGL
{
    void compile()
    {
    }
}

int main()
{
    Engine::Graphics::OpenGL::compile();
}
```

The full namespace name must be repeated every time.

A namespace alias creates a shorter name:

```cpp

namespace Engine::Graphics::OpenGL
{
    void compile()
    {
    }
}

namespace GL = Engine::Graphics::OpenGL;

int main()
{
    GL::compile();
}
```

`GL` is simply another name for `Engine::Graphics::OpenGL`.

These two calls are equivalent:

```cpp
GL::compile();

Engine::Graphics::OpenGL::compile();
```

A namespace alias:

- Does not create a new namespace.
- Does not copy anything.
- Only creates another name for an existing namespace.

Aliases also make refactoring easier.

If the implementation later changes:
```cpp
namespace GL = RendererV2;
```

Existing code using:

```cpp
GL::compile();
```

does not need to change.

---

## Alias Scope

Namespace aliases follow normal scope rules.

A global alias:

```cpp
namespace Engine::Graphics::OpenGL
{
    void compile()
    {
    }
}

namespace GL = Engine::Graphics::OpenGL;

int main()
{
    GL::compile();
}
```

can be used throughout the translation unit.

An alias declared inside a smaller scope only exists there:

```cpp
int main()
{
    namespace GL = Engine::Graphics::OpenGL;

    GL::compile();
}
```

---

# Organizing Large Projects

Namespaces help organize large codebases into logical modules.

Common patterns include:

```text
Project::Module

Company::Project

Company::Project::Module
```

Examples:

```cpp
namespace Game::Graphics {}
namespace Game::Physics {}

namespace MyCompany::Engine {}
namespace MyCompany::Engine::Renderer {}
```

A common approach is to place reusable code in its own namespace.

```cpp
namespace Math
{
    // Reusable library
}

namespace Game
{
    // Game-specific code
}
```

This keeps reusable libraries separate from application-specific code.

Avoid excessively deep namespace hierarchies.

Good:

```text
Game::Graphics
Engine::Physics
Company::Engine::Renderer
```

Avoid:

```text
Company::Project::Engine::Graphics::Renderer::OpenGL::Shader
```

Deep nesting reduces readability and makes code harder to maintain.

---

# Best Practices

- Use namespaces to organize related code.
- Keep reusable libraries separate from application-specific code.
- Use namespaces for libraries and large projects.
- Prefer the C++17 nested namespace syntax.
- Use namespace aliases for long namespace names.
- Avoid excessively deep namespace hierarchies.
- Do not add declarations to `std`.
- Follow your project's naming conventions consistently.

---

# Key Points

- A **block** is a compound statement enclosed in `{}`.
- Blocks introduce a new scope.
- A **scope** determines where an identifier can be accessed.
- A **namespace** is a named scope.
- Namespaces prevent identifier collisions.
- Use the scope resolution operator (`::`) to access namespace members.
- `::identifier` refers to the global namespace.
- Namespaces can only be declared at global scope or inside another namespace.
- Forward declarations must be placed inside the correct namespace.
- Namespaces are **open** and may be defined multiple times.
- The compiler merges namespace definitions with the same name.
- Never add your own declarations to `std`.
- Namespaces can be nested.
- Prefer the C++17 nested namespace syntax (`namespace A::B {}`).
- Unqualified name lookup searches from the innermost scope outward.
- The nearest matching declaration hides outer declarations.
- Namespace aliases are shortcuts, not copies.
- Organize code into logical namespaces and avoid excessive nesting.
