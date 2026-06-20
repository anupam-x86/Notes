# Compilation Pipeline

*Split from HowItWorks.md*

> [!NOTE]
> Some toolchain commands in this file (g++, objdump, nm) also appear in
> GCC-Flags.md. Kept here intentionally, since this file frames them inside
> the conceptual pipeline (why each stage exists), while GCC-Flags.md is a
> pure command reference. Worth cross-checking both if a flag's behavior
> seems unclear in one.

---

# What Is A Program?

A program is simply:

```text
A sequence of instructions
that the CPU executes.
```

Examples:

* Calculator
* Browser
* Game
* Music Player

All are ultimately instructions executed by the CPU.

---

# Source Code

Humans write:

```cpp
std::cout << "Hello";
```

This is source code.

Computers do not understand source code directly.

It must be translated.

---

# Why Assembly Is Different

Assembly is tied to a specific CPU architecture.

Example:

```text
x86 Assembly
≠
ARM Assembly
```

---

# Why C/C++ Are Portable

The source code remains the same.

Different compilers translate it.

```text
main.cpp
      ↓
Windows Compiler
      ↓
Windows Executable

main.cpp
      ↓
Linux Compiler
      ↓
Linux Executable
```

Source code stays.

Translation changes.

> [!IMPORTANT]
> See FixedWidthIntegers.md — "source code stays the same" guarantees identical
> *text*, not identical *behavior*. A type like plain `int` can still differ in
> size across compilers/platforms, so portable source code doesn't automatically
> mean identical runtime behavior unless fixed-width types are used where it matters.

---

# What Is A Compiler?

Mental model:

```text
Human Language
↓
Translator
↓
Machine Language
```

Compiler:

```text
C++ Source
↓
Compiler
↓
Assembly
↓
Assembler
↓
Machine Code
```

Different compilers exist:

* GCC
* Clang
* MSVC

All translate C++.

---

# What Happens During Compilation?

The process is longer than most beginners realize.

```text
Source Code
↓
Preprocessor
↓
Expanded Source
↓
Compiler
↓
Assembly
↓
Assembler
↓
Object File (.o)
↓
Linker
↓
Executable
```

---

# Preprocessor

Runs before compilation.

Handles:

```cpp
#include
#define
```

Example:

```cpp
#include <iostream>
```

Mental model:

```text
Copy contents of iostream
into this file
before compilation.
```

---

# Expanded Source Code

After preprocessing:

```text
Your Code
+
Library Code
```

becomes one huge source file.

This is called expanded source code.

---

# Assembly

Compiler often converts C++ into assembly first.

Assembly is much closer to hardware.

Example idea:

```text
Move data
Add values
Jump to location
```

Very primitive operations.

---

# Object Files (.o)

Object files are partially completed machine code.

They contain:

* Compiled functions
* Symbol information
* References to things not yet found

Example:

```text
main.o
```

may know:

```text
I need add()
```

but not know where it exists.

---

# Why Object Files Exist

Imagine a project contains:

```text
main.cpp
math.cpp
music.cpp
```

Without object files:

Changing one line in math.cpp
would require recompiling everything.

With object files:

```text
main.cpp  → main.o
math.cpp  → math.o
music.cpp → music.o
```

Only the changed file needs recompilation.

Then the linker combines all object files again.

Benefits:

* Faster builds
* Better organization
* Large projects become manageable

---

# Header Files (.h)

Purpose:
Tell other files what exists.

Example:

```text
math.h
```
contains declaration:

```cpp
int add(int a, int b);
```

---

# Source Files (.cpp)

Purpose:
Contain implementation.

Example:

```text
math.cpp
```
contains:

```cpp
int add(int a, int b)
{
    return a + b;
}
```

---

# What Is An Executable?

An executable contains:

* Machine code
* Addresses
* Symbol information (sometimes)
* Metadata needed by the operating system

Examples:

Linux:
```text
a.out
hello
```

Windows:
```text
hello.exe
```

Executables are what the operating system can run.

---

# What Is Linking?

Linking solves missing references.

Example:

```text
main.cpp
calls
add()
```

```text
math.cpp
contains
add()
```

Compiler processes both separately.

Linker connects them.

---

# Mental Model of Linker

Think of object files as puzzle pieces.

Compiler:

```text
Creates pieces
```

Linker:

```text
Connects pieces
```

and produces:

```text
Final executable
```

---

# What Happens To Unused Code?

Modern linkers often remove unused parts.

This helps reduce executable size.

Only necessary pieces are included.

---

# Precompiled Headers

Purpose:

```text
Compile common headers once
Reuse them many times
```

Useful:

* Large projects

Not useful:

* Beginner projects

Can safely ignore for now.

---

# Hello World

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!";
    return 0;
}
```

---

# Understanding Hello World

## #include <iostream>

Provides:

```cpp
std::cout
std::cin
```

---

## int main()

Entry point.

OS starts program execution here.

---

## std::cout

Console output stream.

Used to display text.

---

## return 0

Signals successful execution to the operating system.

---

# Important Mental Models

## Software Creation

```text
Idea
↓
Source Code
↓
Compiler
↓
Object Files
↓
Linker
↓
Executable
↓
Operating System
↓
CPU
```

---

# Important g++ Commands

> [!NOTE]
> This section overlaps with GCC-Flags.md. Kept here because it's framed
> step-by-step against the pipeline diagram above, showing *why* each command
> produces what it produces, rather than as a pure flag reference.

## Compile + Link (Normal Usage)

```bash
g++ main.cpp
```

Produces:

```text
a.out
```

Default executable name.

Run:

```bash
./a.out
```

---

## Compile + Link With Custom Executable Name

```bash
g++ main.cpp -o hello
```

Produces:

```text
hello
```

Run:

```bash
./hello
```

Mental Model:

```text
main.cpp
↓
Compiler
↓
Linker
↓
hello
```

---

## Compile Multiple Source Files

```bash
g++ main.cpp math.cpp -o calculator
```

Produces:

```text
calculator
```

Mental Model:

```text
main.cpp
math.cpp
↓
Compiler
↓
Object Files
↓
Linker
↓
calculator
```

---

## Compile Only (No Linking)

```bash
g++ -c main.cpp
```

Produces:

```text
main.o
```

No executable is created.

Mental Model:

```text
main.cpp
↓
Compiler
↓
main.o
```

---

## Compile Multiple Files Into Object Files

```bash
g++ -c main.cpp
g++ -c math.cpp
```

Produces:

```text
main.o
math.o
```

---

## Link Existing Object Files

```bash
g++ main.o math.o -o calculator
```

Produces:

```text
calculator
```

Mental Model:

```text
main.o
math.o
↓
Linker
↓
calculator
```

---

# Viewing Assembly

## Generate Assembly From C++

```bash
g++ -S main.cpp
```

Produces:

```text
main.s
```

`.s` contains assembly code.

Mental Model:

```text
main.cpp
↓
Compiler
↓
main.s
```

Useful for seeing what the compiler generated before assembly is converted into machine code.

---

# Reading Object Files

Object files contain machine code and symbol information.

They are not meant to be read directly with a text editor.

---

## View Assembly Representation Of Object File

```bash
objdump -d main.o
```

Shows machine instructions disassembled into assembly.

Mental Model:

```text
main.o
↓
objdump
↓
Assembly View
```

---

## View Symbols Inside Object File

```bash
nm main.o
```

Shows:

```text
Functions
Variables
Unresolved References
```

Useful for understanding what the linker sees.

Example:

```text
main
std::cout
std::ostream
```

---

## View Assembly Of Final Executable

```bash
objdump -d a.out
```

Shows the assembly code of the linked executable.

Mental Model:

```text
a.out
↓
objdump
↓
Assembly View
```

---

# Complete Pipeline

```bash
g++ -S main.cpp
```

```text
main.cpp
↓
main.s
```

```bash
g++ -c main.cpp
```

```text
main.s
↓
main.o
```

```bash
g++ main.o -o hello
```

```text
main.o
↓
hello
```

```bash
objdump -d hello
```

```text
hello
↓
Assembly Representation
```

---

# Key Insight

The compiler hides many steps:

```text
C++ Source
↓
Assembly
↓
Machine Code
↓
Object File
↓
Linking
↓
Executable
```

Most of the time:

```bash
g++ main.cpp -o app
```

performs all of these automatically.

---

# Key Takeaways

* A program is just instructions the CPU executes — source code is the human-readable
  recipe; it must be translated before the CPU can run it.
* Compilation is a multi-stage pipeline: preprocessor → compiler → assembler →
  object files → linker → executable. `g++ main.cpp -o app` does all of this
  silently in one command.
* Object files exist so large projects only need to recompile what changed,
  not the entire codebase, every time.
* Linking solves *missing references* — connecting a function call in one file
  to its actual definition in another.
* "Portable source code" means the same *text* compiles everywhere — it does
  NOT guarantee identical runtime behavior unless exact-size types are used
  where size actually matters (see FixedWidthIntegers.md).
