# 2.9 — Naming Collisions and Namespaces

## The Problem: Naming Collisions

A naming collision occurs when two or more identifiers with the same name are introduced into the same scope.

### Same Scope = Error

```cpp
int main()
{
    int value {};
    int value {}; // Error: redefinition of value
}
```

Both variables are in the same scope region.

The compiler cannot determine which `value` you mean.

---

### Different Scopes = OK

```cpp
void foo()
{
    int value {};
}

void goo()
{
    int value {};
}
```

No error.

Each function creates its own scope region.

```text
foo::value
goo::value
```

These are distinct identifiers.

---

## Scope Regions

A scope region is an area of source code where identifiers must be unique.

Think of scope as a naming container.

```text
Global Scope
├── x
├── foo()
│   └── x
└── goo()
    └── x
```

The two local `x` variables do not collide because they belong to different scope regions.

---

## Naming Collisions Across Multiple Files

Consider:

```cpp
// game.cpp
int score {};
```

```cpp
// physics.cpp
int score {};
```

These variables exist in the global scope.

When the linker combines the files:

```text
::score
::score
```

it finds multiple definitions and reports an error.

---

## Namespaces

Namespaces provide a way to group related identifiers and prevent naming collisions.

```cpp
namespace Game
{
    int score {};
}
```

```cpp
namespace Physics
{
    int score {};
}
```

Now the identifiers become:

```text
Game::score
Physics::score
```

No collision occurs because they belong to different namespaces.

---

## Accessing Namespace Members

Use the scope resolution operator `::`.

```cpp
namespace Game
{
    int score { 100 };
}
```

```cpp
std::cout << Game::score;
```

Output:

```text
100
```

You can also modify namespace variables:

```cpp
Game::score = 200;
```

---

## Functions Inside Namespaces

Namespaces can contain functions as well.

```cpp
namespace Game
{
    void resetScore()
    {
        // ...
    }
}
```

Call the function with:

```cpp
Game::resetScore();
```

---

## Scope Resolution Operator (::)

The `::` operator is called the scope resolution operator.

General form:

```cpp
scope::identifier
```

Examples:

```cpp
Game::score
std::cout
std::string
```

Meaning:

```text
Find identifier inside the specified scope.
```

---

## Global Namespace

Identifiers declared outside of any namespace belong to the global namespace.

```cpp
int value { 10 };
```

Equivalent scope:

```text
::value
```

The global namespace has no name.

---

### Accessing a Global Variable

```cpp
int value { 10 };

int main()
{
    int value { 20 };

    std::cout << value << '\n';
    std::cout << ::value << '\n';
}
```

Output:

```text
20
10
```

The local variable shadows the global variable.

`::value` explicitly accesses the global one.

> [!NOTE]
> When nothing appears on the left side of `::`, the global namespace is assumed.

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

## Namespaces Can Only Contain Declarations and Definitions

Valid:

```cpp
namespace Game
{
    int score {};           // variable definition

    void reset();           // declaration

    void reset()            // function definition
    {
    }
}
```

Invalid:

```cpp
namespace Game
{
    std::cout << "Hello"; // Error
}
```

Namespaces are organizational constructs.

They do not execute code.

Executable statements must be inside a function (or another valid definition).

---

## Relationship Between Scope and Namespaces

Namespaces create their own scope regions.

```cpp
namespace Game
{
    int score {};
}

namespace Physics
{
    int score {};
}
```

Equivalent idea:

```text
Game::score
Physics::score
```

Just as:

```cpp
void foo()
{
    int x {};
}

void goo()
{
    int x {};
}
```

creates:

```text
foo::x
goo::x
```

Different scopes allow identical names to coexist.

---

## Variable Shadowing

A nested scope may define an identifier with the same name as an outer scope.

```cpp
int main()
{
    int x { 1 };

    {
        int x { 2 };

        std::cout << x << '\n';
    }

    std::cout << x << '\n';
}
```

Output:

```text
2
1
```

The inner `x` shadows the outer `x`.

> [!NOTE]
> Shadowing is legal but can make code harder to read.
> Use it sparingly.

---

## Mental Model

```text
Scope = Naming Container

Global Scope
    ::value

Namespace Scope
    Game::score

Function Scope
    foo::x
```

Names only need to be unique within the same scope region.

Different scopes allow identifiers with the same name to coexist safely.

---

## Key Takeaways

* Naming collisions occur when identical identifiers exist in the same scope.
* Scope regions act as naming containers.
* Namespaces help organize identifiers and prevent collisions.
* `::` is the scope resolution operator.
* The global namespace is referenced using `::`.
* `Game::score` is a qualified name.
* `score` is an unqualified name.
* Namespaces may contain declarations and definitions.
* Executable statements cannot exist directly inside namespaces.
* Different scopes can contain identifiers with the same name.
* Variable shadowing occurs when an inner scope reuses an outer name.
