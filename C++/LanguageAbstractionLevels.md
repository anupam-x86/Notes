# Language Abstraction Levels

*Split from HowItWorks.md*

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

---

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

# CPU Architectures

Different CPUs speak different machine languages.

Examples:

* x86-64
* ARM
* RISC-V

Assembly is architecture specific.

Example:

```text
x86 Assembly
≠
ARM Assembly
```

This is why assembly programs are less portable than C++ source code.

Code written for one CPU often cannot run on another.

---

# Key Takeaways

* C++ is technically a high-level language — it just exposes more low-level
  control (manual memory management) than most modern languages.
* C exists alongside C++ because it's simpler, more portable to implement, and
  remains dominant in kernels and embedded systems.
* A useful (if imprecise) mental model: C++ = C + OOP + Templates + STL + modern features.
* C's "trust the programmer" philosophy trades safety for flexibility, speed, and control.
* Assembly is tied to a specific CPU architecture (x86 ≠ ARM ≠ RISC-V), which is
  why it's far less portable than C++ source code.
