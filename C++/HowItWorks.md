# C++ Day 1

## Program Flow

Source Code (.cpp)
↓
Compiler (g++)
↓
Executable File
↓
Loaded into RAM
↓
CPU Executes Instructions

---

## Hello World

```cpp
#include <iostream>

int main() {
    std::cout << "Hello World";
    return 0;
}
```

### Understanding

#include <iostream>
- Gives access to input/output features.

main()
- Entry point of the program.
- Execution starts here.

int
- Return type of main().

return 0;
- Program finished successfully.

---

## Memory Basics

When a program runs:

Code and data are loaded into RAM.

CPU executes instructions from RAM.

---

## Variables

Example:

```cpp
int age = 18;
```

Human View:

Name = age
Value = 18

Computer View:

Memory Address
↓
18

Variable names are labels for memory locations.

---

## Important Model

Variable Name
↓
Memory Address
↓
Value

Example:

age
↓
0x1234
↓
18

After:

```cpp
age = 19;
```

Name stays same.
Address stays same.
Value changes.

---

## Key Insight

Computers work with memory addresses.

Variable names exist mainly for humans and the compiler.