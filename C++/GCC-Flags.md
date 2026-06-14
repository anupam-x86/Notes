# GCC / G++ Flags Cheatsheet

---

## Basic Compilation

| Flag | What it does | Example |
|---|---|---|
| `g++ file.cpp` | Compile and link, output `a.out` | `g++ main.cpp` |
| `-o name` | Set output file name | `g++ main.cpp -o app` |
| `-c` | Compile only, no linking → produces `.o` | `g++ -c main.cpp` |
| `-S` | Generate assembly → produces `.s` | `g++ -S main.cpp` |

---

## Language Standard

| Flag | What it does |
|---|---|
| `-std=c++11` | Use C++11 standard |
| `-std=c++14` | Use C++14 standard |
| `-std=c++17` | Use C++17 standard |
| `-std=c++20` | Use C++20 standard (recommended) |
| `-std=c++23` | Use C++23 standard |

> [!NOTE]
> Always specify a standard explicitly.
> Without it, GCC uses its own default which may differ from what learncpp expects.
> Recommended: `-std=c++17` or `-std=c++20`

---

## Warnings

| Flag | What it does |
|---|---|
| `-Wall` | Enable most common warnings |
| `-Wextra` | Enable additional warnings beyond `-Wall` |
| `-Wpedantic` | Enforce strict ISO C++ compliance |
| `-Wshadow` | Warn when a variable shadows another |
| `-Wconversion` | Warn on implicit type conversions |
| `-Wsign-conversion` | Warn on signed/unsigned conversions |
| `-Werror` | Treat all warnings as errors (stops compilation) |

> [!IMPORTANT]
> Recommended combo during learning:
> ```bash
> g++ -Wall -Wextra -Wpedantic -Werror -std=c++20 main.cpp -o app
> ```
> This catches most mistakes before they become runtime bugs.

---

## Debugging

| Flag | What it does |
|---|---|
| `-g` | Include debug info (needed for GDB and sanitizers) |
| `-g2` | Standard debug info (same as `-g`) |
| `-g3` | Maximum debug info including macros |

> [!NOTE]
> * Always use `-g` when debugging.
> Without it, debuggers and sanitizers give less useful output.

---

## Sanitizers — Catch Bugs At Runtime

| Flag | What it catches |
|---|---|
| `-fsanitize=address` | Memory errors (buffer overflow, use-after-free) |
| `-fsanitize=undefined` | Undefined behavior (signed overflow, null deref, etc.) |
| `-fsanitize=leak` | Memory leaks |
| `-fsanitize=thread` | Data races in multithreaded code |

> [!IMPORTANT]
> Sanitizers must be combined with `-g` for useful output.
> Recommended combo when debugging suspicious behavior:
> ```bash
> g++ -g -fsanitize=address,undefined main.cpp -o app
> ```
> These instrument your binary to detect bugs as they happen — far more useful than a regular debugger for UB.

---

## Optimization

| Flag | What it does |
|---|---|
| `-O0` | No optimization (default) — best for debugging |
| `-O1` | Basic optimization |
| `-O2` | Recommended optimization for release builds |
| `-O3` | Aggressive optimization (can cause unexpected behavior) |
| `-Os` | Optimize for binary size |

> [!NOTE]
> Never use optimization flags while debugging.
> Optimized code reorders instructions, eliminates variables, and makes debuggers misleading.
> Use `-O0 -g` for debugging, `-O2` for final builds.

---

## Viewing Internals

| Command | What it does |
|---|---|
| `g++ -S main.cpp` | Generate assembly from C++ source |
| `objdump -d main.o` | View assembly of object file |
| `objdump -d a.out` | View assembly of final executable |
| `nm main.o` | View symbols (functions, variables) in object file |
| `ldd a.out` | View shared libraries linked to executable |

---

## Multiple Files

```bash
# Compile multiple source files into one executable
g++ main.cpp math.cpp -o app

# Compile each file separately into object files
g++ -c main.cpp
g++ -c math.cpp

# Link object files into executable
g++ main.o math.o -o app
```

> [!NOTE]
> * Compiling separately (into .o files first) is faster for large projects.
> * Only changed files need recompilation — the linker combines everything at the end.

---

## Recommended Combos

```bash
# Learning / development
g++ -Wall -Wextra -Wpedantic -Werror -std=c++20 -g main.cpp -o app

# Debugging a specific bug
g++ -g -fsanitize=address,undefined -std=c++20 main.cpp -o app

# Final release build
g++ -O2 -std=c++20 main.cpp -o app

# Inspect what compiler generates
g++ -S -std=c++20 main.cpp   # produces main.s (assembly)
g++ -c -std=c++20 main.cpp   # produces main.o (object file)
objdump -d main.o             # view assembly of object file
```

---

## What I Used So Far

```bash
g++ main.cpp                          # first compilation
g++ main.cpp -o hello                 # named output
g++ -Wall -Wextra -Werror main.cpp    # warnings as errors
g++ -S main.cpp                       # generated assembly
g++ -c main.cpp                       # generated object file
objdump -d main.o                     # viewed assembly
nm main.o                             # viewed symbols
g++ --version                         # checked GCC version
```
