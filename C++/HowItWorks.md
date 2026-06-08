# LearnCpp + Computing Mental Models (0.1 - 0.8)

---

# Why I Am Learning C++

My goal is not merely to learn a programming language.

I want to understand:

* How software works
* How computers execute instructions
* How operating systems work
* How applications communicate with hardware
* How higher-level technologies such as AI are built

C++ is useful because it sits close enough to the hardware to reveal what is happening underneath, while still being practical for real-world software development.

---

# The Layers of Computing

Most people only see:

```text
Instagram
Chrome
Spotify
Games
```

But underneath exists a huge stack:

```text
Applications
↓
Programming Languages
↓
Libraries
↓
Operating System
↓
Drivers
↓
CPU Instructions
↓
Machine Code
↓
Transistors
↓
Electricity
```

Understanding this stack is one reason for learning C++.

---

# High-Level vs Low-Level Languages

Languages differ in how much abstraction they provide.

```text
Python
↓
JavaScript
↓
Java
↓
C++
↓
C
↓
Assembly
↓
Machine Code
```

Higher level:

* Easier to write
* More abstraction
* More convenience

Lower level:

* More control
* Closer to hardware
* More responsibility

---

# Why C++ Is Not A Low-Level Language

Many people incorrectly call C++ a low-level language.

Technically:

* C++ is a high-level language.
* It simply exposes more low-level features than many modern languages.

Example:

Python hides memory.

C++ allows you to manage memory directly.

This gives power but also responsibility.

---

# Why C Exists If C++ Exists

C++ can do almost everything C can.

However:

* C is simpler.
* C has fewer language features.
* C is easier to implement on many systems.
* C remains common in kernels, embedded systems, and low-level software.

Mental model:

```text
C
+
OOP
+
Templates
+
STL
+
Modern Features
=
C++
```

This is not perfectly accurate technically, but it is a useful beginner mental model.

---
# Why Operating Systems Are Often Written In C

Historically:

* C existed before C++
* C compilers existed everywhere
* C is simple and predictable

Today:

Many operating systems still use C because:

* Huge existing codebases
* Excellent portability
* Low-level control

However:

Modern operating systems also contain:

* C++
* Rust
* Assembly

depending on the component.

# The Philosophy of C and C++

"Trust the programmer."

The compiler assumes:

```text
If you wrote it,
you probably meant it.
```

Advantages:

* Flexibility
* Performance
* Control

Disadvantages:

* Easier to make mistakes
* Easier to create bugs

Example:

```cpp
int arr[5];
arr[100] = 10;
```

Compiler may not stop you.

This freedom is both powerful and dangerous.

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
# CPU Architectures

Different CPUs speak different machine languages.

Examples:

* x86-64
* ARM
* RISC-V

Assembly is architecture specific.

Example:

x86 Assembly
≠
ARM Assembly

This is why assembly programs are less portable than C++ source code.

Code written for one CPU often cannot run on another.

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

main.cpp
math.cpp
music.cpp

Without object files:

Changing one line in math.cpp
would require recompiling everything.

With object files:

main.cpp  → main.o
math.cpp  → math.o
music.cpp → music.o

Only the changed file needs recompilation.

Then the linker combines all object files again.

Benefits:

* Faster builds
* Better organization
* Large projects become manageable
  
# Header Files (.h)

Purpose:
Tell other files what exists.

Example:

math.h
contains declaration:

int add(int a, int b);

# Source Files (.cpp)

Purpose:
Contain implementation.

Example:

math.cpp
contains:

int add(int a, int b)
{
    return a + b;
}

# What Is An Executable?

An executable contains:

* Machine code
* Addresses
* Symbol information (sometimes)
* Metadata needed by the operating system

Examples:

Linux:
a.out
hello

Windows:
hello.exe

Executables are what the operating system can run.

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

# Libraries

Libraries are reusable code written by others.

Examples:

```cpp
<iostream>
<vector>
<string>
```

Benefits:

* Save time
* Avoid rewriting common functionality

---
# Why Libraries Exist

Without libraries:

Every programmer would need to write:

* Printing code
* File handling code
* Networking code
* Audio code
* Graphics code

for every project.

Libraries allow programmers to reuse code written by others.

Mental Model:

Library
=
Pre-written solutions
to common problems.

# Types Of Libraries

Static Library:
Copied into executable during linking.

Dynamic Library:
Loaded when program runs.

Examples:

Windows:
.dll

Linux:
.so
# Why We Can Print Text

When we write:

```cpp
std::cout << "Hello";
```

we are not directly controlling the screen.

Actual path:

```text
Program
↓
C++ Library
↓
Operating System
↓
Graphics/Terminal System
↓
Hardware
↓
Screen
```

---
# What Does The Operating System Do?

The operating system acts as a manager between:

Programs
and
Hardware

Example:

Music Player
↓
Operating System
↓
Audio Driver
↓
Sound Card
↓
Speaker

Programs usually do not talk directly to hardware.


# Why Sound Players Are Often Written In C/C++

Reasons:

* Performance
* Real-time processing
* Hardware interaction

Examples:

```text
VLC
MPV
Audacious
```

Even Python audio libraries usually rely on C/C++ underneath.

---

# VS Code vs IDE

VS Code:

* Editor
* Extensions
* Lightweight

IDE:

* Editor
* Debugger
* Build tools
* Project management

Examples:

* Visual Studio
* CLion

VS Code can become IDE-like using extensions.

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

## Hardware Stack

```text
Applications
↓
Operating System
↓
Machine Code
↓
CPU
↓
Logic Gates
↓
Transistors
↓
Electric Signals
```
# Important g++ Commands

---

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

# Questions Explored

- Why is C used for operating systems?
- Why is assembly not portable?
- How does linking work?
- Why do object files exist?
- Why are libraries needed?
- How does the CPU execute instructions?
- How do transistors create computation?
- How is the human brain different from a computer?
- How does AI relate to the brain?
- How does time dilation work?
