# Constants, Magic Numbers, and String Literals

## Why This Note Exists

Most variables we've created so far can change:

```cpp
int age { 18 };
age = 19;
```

However, many values in programs never change:

* Days in a week
* Pi
* Gravity on Earth
* Maximum students per classroom
* User birth year

C++ allows us to mark such values as constant.

This note also introduces literal values, magic numbers, and how string literals work in C++.

---

# Constants (`const`)

## What Is a Constant?

A constant variable is a variable whose value cannot be changed after initialization.

```cpp
const int daysPerWeek { 7 };
```

Attempting to modify it:

```cpp
daysPerWeek = 8; // error
```

---

## Mental Model

Normal variable:

```text
Variable
   ↓
Value can change
```

Constant variable:

```text
Variable
   ↓
Value locked after initialization
```

---

## Why Use Constants?

### Prevent Accidental Modification

```cpp
const double gravity { 9.8 };
```

Nobody can accidentally write:

```cpp
gravity = 10.2; // error
```

---

### Easier Reasoning

```cpp
const int maxStudents { 30 };
```

You immediately know:

```text
This value never changes.
```

---

### Compiler Optimizations

Since the compiler knows the value cannot change, it may generate more efficient code.

---

## Best Practice

Make variables constant whenever possible.

```cpp
const int age { getAge() };
```

If a value should not change after initialization, prefer `const`.

Exceptions:

* By-value function parameters
* By-value return types

These are generally not made const.

---

## Const Variables Must Be Initialized

Valid:

```cpp
const int x { 5 };
```

Invalid:

```cpp
const int x; // error
```

A constant must receive its value immediately because it cannot be assigned later.

---

## Const Is Part of the Type

```cpp
const int x { 5 };
```

Type:

```text
const int
```

not:

```text
int
```

Mental model:

```text
int
↓
Basic type

const int
↓
Different type
↓
Cannot be modified
```

---

## Const Does NOT Mean Compile-Time Constant

Many beginners assume:

```cpp
const int x { 5 };
```

always means:

```text
Known at compile time
```

Not necessarily.

Example:

```cpp
int age {};
std::cin >> age;

const int userAge { age };
```

`userAge` cannot change later:

```text
const
```

but its value was only known at runtime.

Mental model:

```text
const
↓
Cannot change

constexpr
↓
Cannot change
+
Known at compile time
```

---

## Type Qualifiers

A type qualifier modifies a type.

Common qualifiers:

```text
const
volatile
```

Example:

```cpp
const int x { 5 };
```

Here:

```text
const
```

modifies:

```text
int
```

---

# Magic Numbers

## What Is A Magic Number?

A literal whose meaning is unclear.

Bad:

```cpp
setMax(30);
```

Question:

```text
30 what?
```

---

## Why Magic Numbers Are Bad

### Lack Context

```cpp
const int totalStudents { classrooms * 30 };
```

What does 30 represent?

---

### Hard To Update

If:

```text
30 students/class
```

becomes:

```text
35 students/class
```

every occurrence must be reviewed.

---

## Solution: Named Constants

Instead of:

```cpp
const int totalStudents
{
    classrooms * 30
};
```

write:

```cpp
const int maxStudentsPerClass { 30 };

const int totalStudents
{
    classrooms * maxStudentsPerClass
};
```

Now the code explains itself.

---

## Comments vs Named Constants

Possible:

```cpp
const int totalStudents
{
    classrooms * 30
}; // students per class
```

Better:

```cpp
const int maxStudentsPerClass { 30 };
```

Names stay synchronized with code more reliably than comments.

---

## Macros vs Constants

Avoid:

```cpp
#define gravity 9.8
```

Prefer:

```cpp
const double gravity { 9.8 };
```

Reasons:

* Respect scope rules
* Easier to debug
* Behave like normal C++ code

---

## Shared Constants

Many constants are used throughout an entire program:

```cpp
const double pi { 3.14159 };
const double gravity { 9.8 };
```

Later you'll learn how headers allow constants to be shared across multiple source files.

---

## Looking Ahead: `constexpr`

Later LearnCpp recommends:

```cpp
constexpr double gravity { 9.8 };
```

Mental model:

```text
const
↓
Cannot change

constexpr
↓
Cannot change
AND
Known at compile time
```

---

# Literal Constants

## What Is A Literal?

A literal is a value written directly into source code.

Examples:

```cpp
5
3.14
'A'
true
"Hello"
```

---

## Literal vs Constant Variable

```cpp
const int daysPerWeek { 7 };
```

Here:

```text
daysPerWeek
↓
Constant variable

7
↓
Literal
```

A literal is not a variable.

A literal is the actual value written directly into code.

---

# Types Of Literals

## Integer Literal

```cpp
5
42
100
```

Default type:

```text
int
```

---

## Floating Point Literal

```cpp
3.14
```

Default type:

```text
double
```

---

## Character Literal

```cpp
'A'
'+'
'5'
'\n'
```

Type:

```text
char
```

Uses single quotes.

---

## Boolean Literal

```cpp
true
false
```

Type:

```text
bool
```

---

## String Literal

```cpp
"Hello"
```

Type:

```text
C-style string literal
```

Uses double quotes.

---

# Character Literal vs String Literal

Character:

```cpp
'A'
```

```text
One character
Type: char
```

String:

```cpp
"Hello"
```

```text
Multiple characters
C-style string literal
```

Mental model:

```text
' '
↓
One thing

" "
↓
Sequence of things
```

---

# String Literals Are NOT std::string

Many beginners assume:

```cpp
"hello"
```

creates a `std::string`.

It does not.

```text
"hello"
↓
C-style string literal
```

```cpp
"hello"s
```

creates:

```text
std::string
```

---

# C-Style String Literals

```cpp
"hello"
```

Looks like:

```text
h e l l o
```

Actually contains:

```text
h e l l o \0
```

---

# Null Terminator

Every C-style string ends with:

```cpp
'\0'
```

ASCII value:

```text
0
```

Meaning:

```text
End of string
```

Memory:

```text
+---+---+---+---+---+----+
| h | e | l | l | o | \0 |
+---+---+---+---+---+----+
```

---

## Important Consequence

```cpp
"Hello"
```

contains:

```text
5 visible characters
+
1 hidden '\0'
=
6 total characters
```

---

# Lifetime Of String Literals

```cpp
"hello"
```

is a special read-only object.

Properties:

```text
Read-only
Exists for entire program
Cannot be modified
```

---

# std::string Literals

```cpp
"hello"s
```

creates a temporary:

```cpp
std::string
```

object.

Mental model:

```text
Created
↓
Used
↓
Destroyed
```

---

# Literal Suffixes

Suffixes change a literal's type.

Examples:

```cpp
5u
```

↓

```text
unsigned int
```

```cpp
5L
```

↓

```text
long
```

```cpp
5LL
```

↓

```text
long long
```

```cpp
3.14f
```

↓

```text
float
```

```cpp
"hello"s
```

↓

```text
std::string
```

```cpp
"hello"sv
```

↓

```text
std::string_view
```

---

## Mental Model

```text
Literal
   ↓
Suffix
   ↓
Literal Type
```

---

## Best Practice

Prefer:

```cpp
123L
123LL
```

over:

```cpp
123l
123ll
```

because lowercase `l` looks like the digit `1`.

---

# Summary

```text
const
↓
Value cannot change after initialization
```

```text
constexpr
↓
Value cannot change
+
Known at compile time
```

```text
Magic Number
↓
Literal with unclear meaning
```

Replace:

```cpp
30
```

with:

```cpp
const int maxStudentsPerClass { 30 };
```

---

```cpp
'A'
```

↓

```text
char literal
```

```cpp
"Hello"
```

↓

```text
C-style string literal
```

```cpp
"Hello"s
```

↓

```text
std::string
```

---

Every C-style string ends with:

```cpp
'\0'
```

---

Core Mental Models:

1. Make values constant whenever they should not change.
2. Replace magic numbers with named constants.
3. A literal is a value written directly into code.
4. `const` means immutable, not necessarily compile-time.
5. String literals are sequences of characters ending with `'\0'`.
6. Names give values meaning; humans read names, compilers read values.
