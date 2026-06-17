# Preprocessor, Headers & Header Guards
## Chapters 2.10, 2.11, 2.12 — learncpp

---

## Preprocessor (2.10)

### What is the Preprocessor?
Runs **before** the compiler. It is a dumb text find-and-replace engine — it does not understand C++ at all. No types, no scope, no expressions.

The `#` symbol is the signal — anything starting with `#` is a preprocessor directive.

### Translation Unit
After the preprocessor finishes processing a `.cpp` file, the result is called a **translation unit**. This is what the compiler actually compiles.

```
your .cpp file
  + all #included headers (pasted in recursively)
  - all preprocessor directives (consumed/replaced)
─────────────────────────────────────────────────
= translation unit
```

One `.cpp` file = one translation unit.

### #include
Literally copy-pastes the content of the file in place. Nothing more.

```cpp
#include <iostream>   // search standard/system directories
#include "myheader.h" // search current directory first, then system
```

### #define — Macros
Two types:

**Object-like macro** — simple text substitution:
```cpp
#define PI 3.14159
// every PI in code becomes 3.14159
```

**Function-like macro** — takes arguments:
```cpp
#define SQUARE(x) x*x
// dangerous: SQUARE(2+3) becomes 2+3*2+3 = 11, not 25
```

Macros are **avoided in modern C++** — replaced by:
- `const` / `constexpr` instead of object-like macros
- `inline functions` / `templates` instead of function-like macros

### #define with no substitution text
```cpp
#define MY_FLAG  // defines a flag with no value
```
Used for existence checking, not substitution. The point is whether it's defined or not.

### Conditional Compilation
```cpp
#ifdef MY_FLAG    // if MY_FLAG is defined
#ifndef MY_FLAG   // if MY_FLAG is NOT defined
#endif            // closes the block
```

Common uses:
```cpp
// Debug mode
#ifdef DEBUG
    std::cout << "x = " << x;
#endif

// Platform specific
#ifdef _WIN32
    // windows code
#else
    // linux/mac code
#endif
```

### #if 0 — Disabling Code
```cpp
#if 0
    // this code is completely ignored by compiler
    // useful for temporarily disabling code during debugging
    // better than comments when code has nested comments inside
#endif
```
`#if 1` = always compiles, signals experimental/testing code.

### Important: Preprocessor Has No Scope
`#define` inside a function is NOT scoped to that function. Once defined, it's defined for the **entire rest of the file**. Curly braces mean nothing to the preprocessor.

### Important: Macros Don't Cross Translation Units
`#define` in `main.cpp` has zero effect on `function.cpp`. Each file gets its own independent preprocessor run.

---

## Header Files (2.11)

### Why Headers Exist
To share forward declarations across multiple `.cpp` files without copy-pasting.

```
add.h    → contains: int add(int a, int b);
add.cpp  → includes add.h, contains the actual definition
main.cpp → includes add.h, uses add()
```

### Header File Contents
Header files contain two parts:
1. Header guard (see 2.12)
2. Declarations — forward declarations, type definitions, constants

**Do NOT put in headers:**
- Function definitions (causes ODR violations)
- Regular variable definitions

**OK to put in headers:**
- Function declarations
- Type definitions (structs, classes, enums)
- Constants

### Where Standard Library Lives
Standard library headers ship pre-compiled with GCC:
```
/usr/include/          → header files (declarations)
/usr/lib64/libstdc++.so → pre-compiled implementation (shared library)
/usr/lib64/libstdc++.a  → pre-compiled implementation (static library)
```

The header gives declarations. The linker pulls in the pre-compiled implementation.

### .so vs .a
| | `.a` (static) | `.so` (shared/dynamic) |
|---|---|---|
| Like | local tar — bundled inside your binary | system RPM — installed once, shared by all |
| Binary size | larger | smaller |
| RAM | each program has own copy | one copy shared by all programs |
| Portability | self contained | needs library installed on system |

Check what `.so` files your program needs:
```bash
ldd ./your_program
```

### Include Order Convention
```cpp
#include "myheader.h"        // your own headers first
#include <thirdparty/lib.h>  // third party next
#include <iostream>          // standard library last
```

Why: putting your headers first exposes hidden transitive dependencies immediately.

### Transitive Includes — Dangerous
```
main.cpp includes a.h
a.h includes b.h internally
main.cpp accidentally uses something from b.h
→ works fine until someone refactors a.h and removes b.h
→ your code breaks even though you never touched it
```

**Rule:** Every file should explicitly include everything it directly uses. Never rely on transitive includes.

### Headers Including Headers
Headers can include other headers — same rules apply. Every header should include what it directly needs, not rely on transitive includes.

### Multiple Include Directories
```bash
g++ main.cpp -I./utils -I./math -I./networking
```
`-I` flag adds directories to the compiler's header search path. Better than relative paths in `#include` statements.

---

## Header Guards (2.12)

### The Problem
If `square.h` gets included twice in the same translation unit (directly or through transitive includes) — duplicate declarations → compiler error.

### Solution: Header Guards
```cpp
#ifndef SQUARE_H
#define SQUARE_H

// header content here
int square(int x);

#endif
```

**How it works:**
- First include: `SQUARE_H` not defined → define it, include content
- Second include: `SQUARE_H` already defined → skip everything

Works for any number of includes — the flag stays defined for the entire translation unit.

### Naming Convention
Use full filename in all caps with underscores:
```cpp
// square.h
#ifndef SQUARE_H

// add_utils.h
#ifndef ADD_UTILS_H

// For large projects use full path to avoid collisions:
// directoryA/config.h
#ifndef PROJECTNAME_DIRA_CONFIG_H
```

### Header Guards Do NOT Prevent Cross-File Inclusion
Header guards only protect within **one translation unit**. Including `square.h` in both `main.cpp` and `add.cpp` is **correct and intended** — each translation unit needs the declarations.

### #pragma once — Modern Alternative
```cpp
#pragma once

// header content here
// no #endif needed
```

Cleaner — one line, no naming, no closing directive.

**How it differs from header guards:**
- `#ifndef` → checks macro name table
- `#pragma once` → checks included files table (by file path/identity)

**Edge case where `#pragma once` fails:**
If the same header is copied to two different locations on disk and both get included — compiler sees two different files, includes both. `#ifndef` guards would catch this since both copies share the same macro name.

**`#pragma` in general:**
Compiler vendor extension directive — not standardized. Unknown pragmas are silently ignored. `#pragma once` is the one exception that all major compilers (GCC, Clang, MSVC) support.

**For your own projects:** `#pragma once` is fine and cleaner.

---

## Full Pipeline Summary

```
your .cpp file
    ↓ preprocessor (text substitution, per file)
translation unit (.cpp + all included headers merged)
    ↓ compiler (compiles each translation unit independently)
object file (.o)
    ↓ linker (connects all .o files + pre-compiled libraries)
executable (.exe / binary)
```

Each stage knows nothing about other files — only the linker sees the whole picture.
