# Using Declarations and Directives

When working with namespaces, it is common to refer to names defined in other namespaces.

For example, the C++ Standard Library places nearly all of its identifiers inside the `std` namespace.

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, World!\n";
}
```

Here, `cout` is accessed using the **scope resolution operator (`::`)** because it belongs to the `std` namespace.

Writing the namespace qualifier every time is often desirable because it makes the origin of a name explicit.

However, repeatedly writing

```cpp
std::cout
std::cin
std::string
std::vector
```

can become verbose.

C++ provides two language features that allow names from a namespace to be used without repeatedly qualifying them:

- **Using declarations**
- **Using directives**

Although they appear similar, they behave quite differently and have different use cases.

Before learning about them, it is important to understand the difference between **qualified** and **unqualified** names.

# Qualified Names

A **qualified name** is a name that is prefixed with its namespace (or class) using the **scope resolution operator (`::`)**.

For example,

```cpp
std::cout << "Hello, World!\n";
```

Here:

- `std` is the namespace.
- `cout` is the identifier.
- `std::cout` is the qualified name.

Similarly,

```cpp
std::string name{"Alice"};
std::vector<int> numbers;
std::cin >> name;
```

all use qualified names.

---

## Why Use Qualified Names?

Qualified names clearly indicate where an identifier comes from.

For example,

```cpp
std::string message{"Hello"};
```

Immediately tells the reader that `string` is defined in the `std` namespace.

This improves readability and avoids ambiguity when different namespaces contain identifiers with the same name.

---

## Advantages

Using qualified names has several benefits:

- Makes the origin of an identifier explicit.
- Prevents naming conflicts between namespaces.
- Improves readability in large projects.
- Avoids accidental collisions with user-defined names.

For these reasons, many C++ style guides recommend using qualified names unless there is a compelling reason not to.

---

# Unqualified Names

An **unqualified name** is a name used without a namespace prefix.

For example,

```cpp
cout << "Hello\n";
```

Here, `cout` is an unqualified name.

Normally, this code does **not** compile because the compiler searches the current scope but cannot find a declaration for `cout`.

Since `cout` belongs to the `std` namespace, it must ordinarily be written as:

```cpp
std::cout << "Hello\n";
```

or made visible through a using declaration or using directive.

---

## Name Lookup

When the compiler encounters an unqualified name, it performs **name lookup** to determine what the identifier refers to.

It searches for a matching declaration in a well-defined order, beginning with the innermost scope and gradually moving outward.

For example,

```cpp
int value{10};

int main()
{
    std::cout << value;
}
```

The compiler finds `value` in the global namespace because no closer declaration exists.

If a local variable is introduced,

```cpp
int value{10};

int main()
{
    int value{20};

    std::cout << value;
}
```

the local variable hides the global one, and the program prints:

```text
20
```

The details of name lookup are more extensive than this note covers, but the key idea is:

> **Qualified names specify exactly which namespace an identifier belongs to, while unqualified names rely on the compiler's name lookup rules to find the appropriate declaration.**

# Using Declarations

A **using declaration** introduces a **single name** from a namespace into the current scope.

The general syntax is:

```cpp
using namespace_name::identifier;
```

For example,

```cpp
#include <iostream>

using std::cout;

int main()
{
    cout << "Hello, World!\n";
}
```

Here,

```cpp
using std::cout;
```

allows `cout` to be used without writing the namespace qualifier `std::`.

The program is equivalent to:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, World!\n";
}
```

The only difference is that the using declaration removes the need to repeatedly write `std::`.

---

## Only One Identifier Is Introduced

A using declaration imports **only the specified identifier**.

For example,

```cpp
using std::cout;
```

makes only `cout` available.

The following code still requires qualification:

```cpp
std::cin >> value;
std::string name;
```

or additional using declarations:

```cpp
using std::cout;
using std::cin;
using std::string;
```

Each declaration introduces exactly one name.

---

## Scope Matters

A using declaration obeys normal C++ scope rules.

If it is declared inside a function,

```cpp
int main()
{
    using std::cout;

    cout << "Hello\n";
}
```

only that function can use the unqualified name.

Outside the function,

```cpp
cout << "Hi";
```

would produce a compilation error because the using declaration is no longer in scope.

Similarly, a using declaration at namespace scope is visible throughout that namespace.

---

## Advantages

Using declarations have several advantages:

- Import only the names you actually need.
- Keep the origin of most identifiers explicit.
- Reduce typing without polluting the current scope.
- Greatly reduce the risk of name conflicts.

Because they introduce only specific identifiers, using declarations are generally considered much safer than using directives.

---

## Best Practice

If you want to avoid repeatedly writing a namespace qualifier, prefer a using declaration over a using directive.

For example,

```cpp
using std::cout;
using std::cin;
using std::string;
```

is generally preferable to:

```cpp
using namespace std;
```

because only the required identifiers become visible.

# Using Directives

A **using directive** makes **all names** from a namespace available for unqualified lookup.

The general syntax is:

```cpp
using namespace namespace_name;
```

For example,

```cpp
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello, World!\n";
    cin >> value;
}
```

Here,

```cpp
using namespace std;
```

allows the compiler to find `cout`, `cin`, and every other name in the `std` namespace without writing `std::`.

The program is equivalent to:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, World!\n";
    std::cin >> value;
}
```

except that the namespace qualifier is no longer required.

---

## All Names Become Candidates

Unlike a using declaration, a using directive does **not** import a single identifier.

Instead, it makes every name in the namespace available for **unqualified name lookup**.

For example,

```cpp
using namespace std;

string name;
vector<int> numbers;

cout << "Enter your name: ";
cin >> name;
```

None of these identifiers require the `std::` qualifier.

---

## Name Conflicts

Because every name in the namespace becomes available, using directives can introduce naming conflicts.

Consider:

```cpp
namespace A
{
    void print();
}

namespace B
{
    void print();
}

using namespace A;
using namespace B;

int main()
{
    print();    // Error
}
```

The compiler cannot determine whether `print()` refers to `A::print()` or `B::print()`.

This ambiguity results in a compilation error.

---

## Why `using namespace std;` Is Discouraged

Many beginners write:

```cpp
using namespace std;
```

because it makes programs shorter.

While this is often acceptable in small examples and tutorials, it is generally discouraged in real-world code.

The `std` namespace contains thousands of identifiers.

Importing all of them into the current scope:

- Increases the chance of name collisions.
- Makes it harder to determine where identifiers originate.
- Can introduce ambiguity as projects grow.

For these reasons, most C++ style guides recommend avoiding `using namespace std;` in production code.

---

## Scope Matters

Like using declarations, using directives obey normal scope rules.

A directive inside a function affects only that function.

```cpp
int main()
{
    using namespace std;

    cout << "Hello\n";
}
```

Outside the function,

```cpp
cout << "Hello";
```

would still be an error because the directive is out of scope.

---

## Best Practice

Prefer using directives only when:

- Writing short example programs.
- Experimenting in small source files.
- Working in an interactive environment (such as a REPL).

For larger projects, prefer qualified names or using declarations instead.

# Using Declarations vs Using Directives

Although using declarations and using directives both reduce the need to repeatedly write namespace qualifiers, they behave quite differently.

Understanding the distinction is important for writing clear and maintainable code.

| Using Declaration | Using Directive |
|-------------------|-----------------|
| Introduces **one specific identifier** into the current scope. | Makes **all names** in a namespace available for unqualified lookup. |
| Syntax: `using std::cout;` | Syntax: `using namespace std;` |
| Lower risk of name conflicts. | Higher risk of name conflicts. |
| Keeps most identifiers qualified. | Removes the need to qualify any identifier from the namespace. |
| Preferred in production code. | Generally discouraged in large projects. |

---

## Example

### Using Declaration

```cpp
using std::cout;
using std::string;

int main()
{
    string name{"Alice"};
    cout << name;
}
```

Only `cout` and `string` are introduced.

Attempting to use another identifier without qualification,

```cpp
cin >> name;
```

produces an error because `cin` has not been introduced.

It must either be qualified:

```cpp
std::cin >> name;
```

or explicitly imported:

```cpp
using std::cin;
```

---

### Using Directive

```cpp
using namespace std;

int main()
{
    string name{"Alice"};

    cout << name;
    cin >> name;
}
```

Every identifier in the `std` namespace is available for unqualified lookup.

While convenient, this increases the chance of accidental name collisions.

---

## Which Should You Use?

In modern C++, the general recommendation is:

- Prefer **qualified names** whenever practical.
- If qualification becomes repetitive, use **using declarations** for the specific identifiers you need.
- Avoid **using directives** in production code unless there is a compelling reason.

This approach keeps dependencies explicit while minimizing the risk of naming conflicts.

# Why `using namespace std;` in Headers Is Bad

A common beginner mistake is placing a using directive inside a header file.

For example,

```cpp
// math.h

#pragma once

#include <iostream>

using namespace std;
```

Although this compiles, it can create unexpected problems for every source file that includes the header.

---

## Headers Are Shared

Suppose several source files include the same header.

```text
main.cpp
      │
      ├──► math.h

graphics.cpp
      │
      ├──► math.h

physics.cpp
      │
      └──► math.h
```

Because the preprocessor copies the contents of the header into every translation unit,

```cpp
using namespace std;
```

also appears in every translation unit.

As a result, every source file now has access to all names in the `std` namespace without explicitly requesting them.

This pollutes the global namespace of every file that includes the header.

---

## Increased Risk of Name Conflicts

Imagine a project defines its own function named `distance`.

```cpp
double distance(Point a, Point b);
```

The C++ Standard Library also contains functions named `distance`.

If a header contains

```cpp
using namespace std;
```

both versions become candidates during name lookup.

This can lead to ambiguity or unexpected behavior.

---

## Hidden Dependencies

Headers should expose only the declarations that are necessary for users of the header.

A using directive silently changes the name lookup behavior of every source file that includes it.

Someone including the header may not even realize that names from `std` have been imported.

This creates a hidden dependency that makes code harder to understand and maintain.

---

## Better Alternatives

Instead of writing:

```cpp
using namespace std;
```

inside a header, prefer one of the following approaches.

### Use Qualified Names

```cpp
std::string name;
std::vector<int> values;
```

This is the safest and most explicit approach.

---

### Use Using Declarations in Source Files

If repeatedly writing `std::` becomes tedious, place using declarations inside the corresponding `.cpp` file instead.

```cpp
using std::cout;
using std::string;
```

Only that translation unit is affected, leaving other files untouched.

---

## Best Practice

As a general rule:

- **Never** place a using directive in a header file.
- Prefer qualified names in headers.
- If necessary, use using declarations in source files rather than headers.

# Best Practices

Namespaces and the `using` keyword help organize code and reduce typing, but they should be used thoughtfully.

The following practices are widely recommended in modern C++.

---

## Prefer Qualified Names

The safest approach is to use qualified names whenever practical.

```cpp
std::cout << "Hello\n";
std::string name;
```

Qualified names make it immediately clear where an identifier is defined and eliminate ambiguity.

---

## Use Using Declarations Sparingly

If repeatedly writing a namespace qualifier becomes cumbersome, prefer using declarations.

```cpp
using std::cout;
using std::string;
```

This imports only the identifiers you need while keeping the rest of the namespace qualified.

---

## Avoid `using namespace std;` in Large Projects

Although

```cpp
using namespace std;
```

is convenient, it imports every name from the `std` namespace.

This can:

- Increase the risk of naming conflicts.
- Make code harder to understand.
- Hide the origin of identifiers.

For production code, qualified names or using declarations are generally better choices.

---

## Never Use `using namespace` in Header Files

Header files are shared by multiple translation units.

A using directive inside a header affects every source file that includes it.

Instead, write:

```cpp
std::string name;
```

rather than:

```cpp
using namespace std;
```

inside a header.

This prevents namespace pollution and unexpected name conflicts.

---

## Keep Using Declarations Local

When possible, place using declarations inside the smallest scope that needs them.

For example,

```cpp
int main()
{
    using std::cout;

    cout << "Hello\n";
}
```

The declaration affects only `main()`, reducing the possibility of accidental conflicts elsewhere.

---

## Use Namespace Aliases for Long Names

If a namespace has a long or deeply nested name, consider creating an alias.

```cpp
namespace fs = std::filesystem;

fs::path file{"example.txt"};
```

This improves readability without sacrificing clarity.

---

# Summary

## Qualified Names

- A qualified name includes its namespace (or class) using the scope resolution operator (`::`).
- Example: `std::cout`
- Qualified names clearly indicate where an identifier is defined.
- They reduce ambiguity and help prevent naming conflicts.
- They are the preferred way to access names in large projects.

---

## Unqualified Names

- An unqualified name is used without a namespace qualifier.
- Example: `cout`
- The compiler uses **name lookup** to determine what the identifier refers to.
- Unqualified names are convenient but may become ambiguous when multiple declarations have the same name.

---

## Using Declarations

Using declarations:

- Introduce a single identifier from a namespace.
- Use the syntax `using namespace_name::identifier;`
- Reduce typing while keeping namespace pollution to a minimum.
- Obey normal C++ scope rules.
- Are generally preferred over using directives.

Example:

```cpp
using std::cout;
using std::string;
```

---

## Using Directives

Using directives:

- Make all names in a namespace available for unqualified lookup.
- Use the syntax `using namespace namespace_name;`
- Can significantly increase the chance of name conflicts.
- Should be used sparingly in production code.

Example:

```cpp
using namespace std;
```

---

## Using Declaration vs Using Directive

- A using declaration introduces **one specific identifier**.
- A using directive makes **every identifier** in a namespace available.
- Using declarations are safer and more explicit.
- Using directives are more convenient but increase the risk of ambiguity.

---

## `using namespace std;` in Headers

- A using directive in a header affects every translation unit that includes the header.
- It pollutes the global namespace of all including source files.
- It increases the likelihood of naming conflicts.
- Header files should generally use qualified names instead.

---

## Best Practices

When working with namespaces:

- Prefer qualified names whenever practical.
- Use using declarations instead of using directives when only a few identifiers are needed.
- Avoid `using namespace std;` in production code.
- Never place a using directive in a header file.
- Keep using declarations in the smallest practical scope.
- Use namespace aliases for long namespace names.
