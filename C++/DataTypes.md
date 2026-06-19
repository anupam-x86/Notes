# Chapter 4 - Fundamental Data Types

## 4.1 Fundamental Data Types

### Fundamental Types

Fundamental (built-in) types are understood directly by the compiler.

```cpp
bool
char
int
double
void
```

---

### Categories of Fundamental Types

#### Boolean Type

```cpp
bool
```

Stores:

```cpp
true
false
```

---

#### Character Types

```cpp
char
wchar_t
char8_t
char16_t
char32_t
```

Used to store characters and text.

For now, focus on:

```cpp
char
```

---

#### Integral Types

```cpp
short
int
long
long long
```

Used to store whole numbers.

Typical modern sizes:

| Type      | Typical Size |
| --------- | ------------ |
| short     | 2 bytes      |
| int       | 4 bytes      |
| long      | 4 or 8 bytes |
| long long | 8 bytes      |

Recommendations:

* Use `int` for normal integers.
* Use `long long` for very large integers.

---

#### Floating Point Types

```cpp
float
double
long double
```

Used to store decimal numbers.

Typical sizes:

| Type        | Typical Size       |
| ----------- | ------------------ |
| float       | 4 bytes            |
| double      | 8 bytes            |
| long double | 8, 12, or 16 bytes |

Recommendation:

* Prefer `double` for most decimal values.

---

#### Void Type

```cpp
void
```

Represents:

```text
No type
No value
```

---

### Strings

Strings are not fundamental types.

They are provided by the C++ Standard Library.

```cpp
#include <string>

std::string name {"Anupam"};
```

---

### Fixed-Width Integers

Header:

```cpp
#include <cstdint>
```

Common fixed-width integer types:

```cpp
std::int8_t
std::int16_t
std::int32_t
std::int64_t
```

Use these when an exact integer size is required.

---

### _t Suffix

Many modern C++ types end with `_t`.

Examples:

```cpp
std::size_t
std::int32_t
std::nullptr_t
```

The `_t` suffix generally means "type".

---

## 4.2 Void

### What is void?

```cpp
void
```

means:

```text
No type
No value
Nothing
```

---

### Void Variables

Invalid:

```cpp
void x; // Error
```

A variable must store data, but `void` represents the absence of data.

---

### Void Functions

Most common usage:

```cpp
void printHello()
{
    std::cout << "Hello";
}
```

Meaning:

```text
Function returns nothing.
```

---

### Returning From a Void Function

Valid:

```cpp
void test()
{
    return;
}
```

This exits the function without returning a value.

---

### Incomplete Types

`void` is an incomplete type.

An incomplete type:

```text
Exists
But has no known size
```

Because `void` represents the absence of data, it can never be completed.

Invalid:

```cpp
sizeof(void); // Error
```

---

### Deprecated Syntax

Old style:

```cpp
int getValue(void);
```

Modern C++:

```cpp
int getValue();
```

Both mean:

```text
Function takes no parameters.
```

Prefer the modern form.

---

## 4.3 Object Sizes and sizeof

### Objects Occupy Memory

Example:

```cpp
int age {18};
```

An object uses memory to store its value.

---

### Type vs Object

Type:

* Blueprint or description of data.
* Does not occupy memory itself.

Object:

* Instance of a type.
* Occupies memory.
* Stores actual values.

Example:

```cpp
int age {18};
```

```text
Type   -> int
Object -> age
Value  -> 18
```

When we say:

```cpp
sizeof(int)
```

we really mean:

> The size of an object of type `int`.

---

### The sizeof Operator

Used to determine object/type size in bytes.

```cpp
sizeof(int)
sizeof(age)
```

Example:

```cpp
std::cout << sizeof(double);
```

Typical output:

```text
8
```

---

### sizeof Returns

```cpp
std::size_t
```

An unsigned integer type large enough to represent object sizes.

---

### Standard Size Guarantees

The C++ standard guarantees minimum sizes:

| Type      | Minimum Size |
| --------- | ------------ |
| char      | 8 bits       |
| short     | 16 bits      |
| int       | 16 bits      |
| long      | 32 bits      |
| long long | 64 bits      |

Important:

```text
Minimum size ≠ Exact size
```

---

### Assumptions Used in LearnCpp

For modern systems, LearnCpp assumes:

```text
1 byte = 8 bits
Memory is byte-addressable
Floating point follows IEEE-754
Architecture is 32-bit or 64-bit
```

Memory is byte-addressable:

* Every byte has its own address.
* The CPU can access individual bytes independently.

---

### Typical Sizes on Modern x86-64 Linux

| Type        | Typical Size |
| ----------- | ------------ |
| bool        | 1 byte       |
| char        | 1 byte       |
| short       | 2 bytes      |
| int         | 4 bytes      |
| long        | 8 bytes      |
| long long   | 8 bytes      |
| float       | 4 bytes      |
| double      | 8 bytes      |
| long double | 16 bytes     |

---

### Why Object Size Matters

#### 1. Larger Objects Store More Values

```text
More bytes
→ More bits
→ More possible bit patterns
→ Larger value range
```

---

#### 2. Memory Is Limited

Every object consumes memory while it exists.

Example:

```text
char   -> usually 1 byte
double -> usually 8 bytes
```

For programs with large amounts of data, memory usage matters.

---

### Portability Rule

Avoid assuming exact type sizes.

Bad:

```cpp
int // assumed to be 4 bytes
```

Better:

```cpp
sizeof(int)
```

or:

```cpp
std::int32_t
std::int64_t
```

If a specific size is required:

```cpp
static_assert(sizeof(int) >= 4);
```

Compilation will fail if the assumption is false.

---

### sizeof and Dynamic Memory

`sizeof` only measures the object itself.

It does NOT include dynamically allocated memory owned or referenced by that object.

---

### Performance Note

Smaller types are not necessarily faster.

```text
Smaller type ≠ Faster type
```

Modern CPUs are optimized for native sizes (typically 32-bit and 64-bit).

Because of this:

```cpp
int
```

is often as fast as or faster than:

```cpp
short
char
```

---

## Key Takeaways (4.1 - 4.3)

* Fundamental types are built into the language.
* `int` is the default integer type.
* `double` is the default floating-point type.
* Strings are part of the Standard Library.
* `void` means "no type" or "no value".
* `void` is an incomplete type.
* Objects occupy memory.
* Types describe objects.
* `sizeof` returns the size of an object/type in bytes.
* `sizeof` returns `std::size_t`.
* The C++ standard guarantees minimum sizes, not exact sizes.
* Use fixed-width integers when exact sizes matter.
* Use `static_assert` to enforce size assumptions.
* Smaller types save memory but are not always faster.
* `sizeof` does not include dynamically allocated memory.
