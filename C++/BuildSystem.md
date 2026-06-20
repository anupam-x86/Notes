# Build System Terminology

## Compile

Recompiles a single source file.

```text
main.cpp
↓
Compiler
↓
main.o
```

* Produces object files (`.o`)
* Does NOT link
* Does NOT create an executable

---

## Build

Compiles all modified source files and then links them.

```text
main.cpp
math.cpp
↓
Compile
↓
main.o
math.o
↓
Linker
↓
Executable
```
```
Build
=
Compile modified files
+
Link
```
* Produces the final executable
* Skips files that haven't changed since the last build

---

## Clean

Removes generated build files.
Source files are never deleted.
Deletes things like:

```text
.o files
executables
temporary build files
```

Keeps:

```text
.cpp files
.h files
```

Purpose:

```text
Force a completely fresh build next time.
```

---

## Rebuild

Performs:

```text
Clean
↓
Build
```

Equivalent mental model:

```text
Delete everything generated
↓
Compile everything again
↓
Link again
```

Useful when build files become outdated or corrupted.

---

## Run / Start

Executes the program.

```text
Executable
↓
Operating System
↓
Program Runs
```

Some IDEs automatically perform:

```text
Build
↓
Run
```

before starting the program.

Others simply run the last built executable.

---

# Mental Model

```text
Compile
↓
Object Files

Build
↓
Compile + Link

Clean
↓
Delete Build Files

Rebuild
↓
Clean + Build

Run

↓
Execute Program
```

## Warnings vs Errors

Errors:

```text
Compilation stops.
```

Program cannot be built.

---

Warnings:

```text
Program can still build.
```

Compiler suspects something is wrong.

Warnings often reveal bugs.

---

## Recommended Warning Flags

```bash
g++ -Wall -Wextra -Wpedantic main.cpp -o main
```

Meaning:

```text
-Wall      Enable common warnings
-Wextra    Enable additional warnings
-Wpedantic  Follow standard strictly
```

---

Optional:

```bash
-Werror
```

Treat warnings as errors.

Useful later.

Can be annoying while learning.

---

## Language Standard

Check current standard:

```cpp
__cplusplus
```

Examples:

```text
199711L -> C++98
201103L -> C++11
201402L -> C++14
201703L -> C++17
202002L -> C++20
202302L -> C++23
```

---

## Debugging Build Problems

First checklist:

1. Missing semicolon?
2. Missing brace?
3. Typo in identifier?
4. Wrong file compiled?
5. Forgot to save file?
6. Build old executable?
7. Clean + Rebuild?
8. Missing include?
9. Compiler warning explains issue?

Reference:

LearnCpp 0.8 — A Few Common C++ Problems

````

---

## Key Mental Models

```text
Compiler ≠ Linker
````

```text
Source Code
↓
Compiler
↓
Object Files
↓
Linker
↓
Executable
```

```text
Build
=
Compile
+
Link
```

```text
Rebuild
=
Clean
+
Build
```

