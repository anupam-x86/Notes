# Signed Representation, Bits, Memory, and Interpretation

## Why I Made This Note

While learning signed integers in C++, I became confused about how a computer knows whether a value is:

* `-5`
* `251`
* `'A'`
* An instruction

when everything is ultimately stored as bits.

This note explains the different layers involved and the key principle that resolves the confusion.

---

# Core Idea

Everything in a computer is ultimately bits.

The only difference between numbers, characters, instructions, images, audio, and negative values is **how those bits are interpreted**.

---

# The Most Important Rule

> Bits have no meaning.
>
> Meaning comes from interpretation.

Memory stores bits.

Programs, CPUs, operating systems, and instructions decide how those bits should be interpreted.

---

# Memory Only Stores Bits

Memory does **not** store:

```text
-5
251
'A'
ADD instruction
```

Memory only stores:

```text
11111011
01000001
00000001
```

These are simply bit patterns.

Memory itself does not know what they represent.

---

# Same Bits, Different Meaning

Example:

```text
01000001
```

Can represent:

```text
65                      (integer)
'A'                     (ASCII character)
Part of an instruction
Part of an image
Part of a floating-point number
```

depending on how it is interpreted.

Another example:

```text
11111011
```

Can represent:

```text
251   (unsigned)
-5    (signed, two's complement)
```

The bits did not change.

Only the interpretation changed.

---

# Context Creates Meaning

The same bits can represent completely different things.

Example:

```text
01000001
```

As ASCII:

```text
'A'
```

As an unsigned integer:

```text
65
```

As part of machine code:

```text
An instruction byte
```

As image data:

```text
A pixel component value
```

The bits never changed.

Only the context changed.

---

# Types Give Meaning

Example:

```cpp
signed char a {-5};
unsigned char b {251};
```

Both may store:

```text
11111011
```

But:

```cpp
a
```

is interpreted as:

```text
-5
```

while:

```cpp
b
```

is interpreted as:

```text
251
```

because the type determines the interpretation.

## Important

The type itself is **not stored in RAM**.

The compiler knows the type while compiling.

The generated machine instructions determine how the CPU should interpret the bits later.

---

# Memory Does Not Store Types

Memory contains:

```text
11111011
```

It does not contain:

```text
11111011 (signed char)
```

or:

```text
11111011 (unsigned char)
```

Type information exists in:

* Source code
* Compiler decisions
* Generated machine instructions

not in RAM.

### Note

Some languages and runtime systems store type metadata alongside objects.

However, ordinary C++ variables do not.

---

# Compile Time vs Runtime

## Compile Time

You write:

```cpp
int x {-5};
```

The compiler:

1. Sees that `x` is signed.
2. Converts `-5` into the appropriate bit pattern.
3. Generates machine instructions.

The compiler's job ends here.

---

## Runtime

When the program runs:

* CPU
* Memory
* Operating System

exist.

The compiler is no longer running.

The CPU simply executes the machine instructions generated earlier.

---

# How Can the CPU Know Signed vs Unsigned?

The CPU usually does not look at memory and ask:

```text
Is this signed?
```

Instead, the machine instruction determines interpretation.

For example:

```text
Signed comparison
Unsigned comparison
```

may use different CPU instructions.

The instruction itself provides the context.

---

# Two's Complement

Modern computers represent negative numbers using:

**Two's Complement**

Examples:

```text
 5 = 00000101
-5 = 11111011
```

Negative numbers are not stored as:

```text
Minus sign + value
```

Instead, they have their own binary representation.

---

# Why Two's Complement Exists

Because binary arithmetic works naturally.

Example:

```text
11111011  (-5)
00000001  (+1)
----------------
11111100  (-4)
```

The CPU can simply add bits.

No separate negative-number arithmetic is required.

---
# How Arithmetic Works With Negative Numbers

The real reason modern computers use Two's Complement is not simply to store negative numbers.

The reason is that positive and negative numbers can use the same binary arithmetic hardware.

---

## Example: 5 + (-5)

Using 8-bit numbers:

```text
  5 = 00000101
 -5 = 11111011
```

Add them:

```text
00000101
11111011
--------
100000000
```

An 8-bit register can only store 8 bits.

The extra carry bit is discarded:

```text
00000000
```

Result:

```text
5 + (-5) = 0
```

No special logic was required.

The CPU simply performed binary addition.

---

## Example: (-5) + 1

```text
11111011
00000001
--------
11111100
```

Interpret:

```text
11111100 = -4
```

Result:

```text
-5 + 1 = -4
```

Again, ordinary binary addition produced the correct answer.

---

## Example: (-5) + (-3)

Represent both values:

```text
-5 = 11111011
-3 = 11111101
```

Add:

```text
11111011
11111101
--------
111111000
```

Discard overflow bit:

```text
11111000
```

Interpret:

```text
11111000 = -8
```

Result:

```text
-5 + (-3) = -8
```

The CPU still used the same addition circuitry.

---

## Why This Is Powerful

Imagine if negative numbers were stored as:

```text
Minus Sign + Value
```

For example:

```text
-5 = [minus][00000101]
```

The CPU would need:

* One algorithm for positive numbers
* Another algorithm for negative numbers
* Special handling for signs

Arithmetic hardware would become more complicated.

Two's Complement avoids this problem.

---

## Subtraction Is Also Addition

Computers often perform subtraction by adding a negative number.

Example:

```text
7 - 5
```

becomes:

```text
7 + (-5)
```

Represent:

```text
 7 = 00000111
-5 = 11111011
```

Add:

```text
00000111
11111011
--------
00000010
```

Result:

```text
2
```

The CPU can reuse the same adder hardware for both addition and subtraction.

---

## What About Multiplication?

Multiplication still works because Two's Complement follows consistent mathematical rules.

Example:

```text
(-3) × 2 = -6
```

The CPU uses multiplication circuits that understand Two's Complement representation.

The bits are treated according to signed arithmetic rules during the operation.

---

## What About Comparisons?

This is where signedness becomes important.

Consider:

```text
11111011
```

As unsigned:

```text
251
```

As signed:

```text
-5
```

Now compare with:

```text
00000001
```

Unsigned comparison:

```text
251 > 1
```

Signed comparison:

```text
-5 < 1
```

Same bits.

Different interpretation.

Because of this, CPUs often provide different instructions for:

* Signed comparisons
* Unsigned comparisons

---

## Overflow

Some bit patterns may produce different meanings depending on signedness.

Example:

```text
01111111
```

is:

```text
127
```

Add 1:

```text
01111111
00000001
--------
10000000
```

Unsigned interpretation:

```text
128
```

Signed interpretation:

```text
-128
```

The CPU can detect this condition and set overflow flags.

---

## Key Insight

Two's Complement allows:

* Positive numbers
* Negative numbers
* Addition
* Subtraction

to all use nearly the same binary arithmetic hardware.

This is why virtually every modern computer uses Two's Complement for signed integers.
---

# Signedness and Arithmetic

Interestingly, many CPUs use the same addition hardware for both signed and unsigned integers.

Example:

```text
11111011 + 00000001
```

produces the same bit result regardless of interpretation.

Signedness mainly matters for operations such as:

* Comparisons
* Division
* Arithmetic shifts
* Overflow detection

---

# Instructions and Data Can Use the Same Bits

Example:

```text
0001
```

Could mean:

```text
ADD instruction
```

or:

```text
Integer value 1
```

The bits themselves do not determine meaning.

Context determines meaning.

---

# Why CPU Does Not Confuse Instructions and Data

Programs are typically organized into different memory regions.

A simplified view:

```text
+---------+
|  Code   |
+---------+
|  Data   |
+---------+
|  Heap   |
+---------+
|  Stack  |
+---------+
```

### Code

Contains machine instructions.

### Data

Contains variables and objects.

### Heap

Contains dynamically allocated memory.

### Stack

Contains local variables and function call information.

Modern systems also use memory permissions.

Typically:

* Code pages are executable.
* Data pages are non-executable.

The operating system and CPU memory protection mechanisms help prevent instructions from being executed as data.

---

# Virtual Memory

A program does not directly access physical RAM.

The operating system provides a:

**Virtual Address Space**

for each process.

Simplified view:

```text
Program
    ↓
Virtual Memory
    ↓
OS + MMU
    ↓
Physical RAM
```

The operating system and Memory Management Unit (MMU) translate virtual addresses into physical memory locations.

---

# Assembly and Signed Numbers

Assembly stores bits exactly like C++.

Example:

```text
11111011
```

can represent:

```text
251
-5
```

depending on the instruction being used.

Signedness is not stored separately.

It is determined by interpretation.

---

# Common Confusion

### Question

If:

```text
11111011 = -5
```

and:

```text
11111011 = 251
```

then how does the CPU know which one it is?

### Answer

The bits alone do not determine meaning.

The instruction being executed determines how the bits are interpreted.

Example:

```text
Signed comparison:
11111011 → -5
```

```text
Unsigned comparison:
11111011 → 251
```

Same bits.

Different interpretation.

---
# Integer Ranges and Overflow

Every integer type can represent only a limited range of values.

Example:

8-bit signed integer:

```text
-128 to 127
```

8-bit unsigned integer:

```text
0 to 255
```

These limits exist because a fixed number of bits can store only a fixed number of bit patterns.

---

## What Is Overflow?

Overflow occurs when a calculation produces a value that cannot be represented by the chosen type.

Example:

```text
127 + 1
```

Mathematically:

```text
128
```

But an 8-bit signed integer cannot represent 128.

The resulting bit pattern becomes:

```text
10000000
```

which represents:

```text
-128
```

in Two's Complement.

---

## Why Overflow Is Dangerous

Overflow means information has been lost.

The mathematical result required more bits than the representation could provide.

Whenever a value might exceed a type's range, a larger type should be used.

Examples:

```cpp
std::int8_t
std::int16_t
std::int32_t
std::int64_t
```

---

## Signed Overflow

In C++, signed integer overflow is Undefined Behavior.

Example:

```cpp
int x { 2147483647 };
x = x + 1; // Undefined Behavior
```

Many modern systems appear to wrap around due to Two's Complement hardware:

```text
2147483647
→
-2147483648
```

but the C++ standard does not guarantee this behavior.

---

## Unsigned Overflow

Unsigned integers use modulo arithmetic.

Example:

```text
255 + 1 = 0
```

for an 8-bit unsigned integer.

This wraparound behavior is guaranteed by the C++ standard.

---

## Representation vs Mathematics

Mathematical values are unlimited.

Representations are limited.

>[!Note]
>Overflow happens when a mathematical result cannot fit inside the chosen representation.

---
# Layers of Abstraction

When confused, identify which layer the question belongs to.

```text
Application
    ↓
C++
    ↓
Compiler
    ↓
Machine Code
    ↓
CPU Instructions
    ↓
Logic Gates
    ↓
Transistors
    ↓
Physics
```

Many confusions happen because ideas from multiple layers are mixed together.

---

# Final Rule

Whenever confused about numbers, characters, instructions, or memory, ask:

1. What are the bits?
2. Who is interpreting them?
3. At which layer?

The answer is usually found there.

---

# One-Sentence Summary

> Computers store only bits; everything else—numbers, characters, instructions, images, audio, and negative values—exists because some layer interprets those bits in a particular way.
