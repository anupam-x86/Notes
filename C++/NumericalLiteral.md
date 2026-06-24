# Numerical Literals - 5.3

# Core Mental Model

```text
Value ≠ Representation
```

Example:

```text
42
0b101010
0x2A
052
```

Different representations.

Same value.

---

Another way to think about it:

```text
Stored Value
      ↓
Can be written as decimal
Can be written as binary
Can be written as hexadecimal
Can be written as octal
```

The value does not change.

Only the representation changes.

---

# Decimal Literals (Base 10)

This is the normal number system humans use.

```cpp
42
123
999
```

Digits:

```text
0 1 2 3 4 5 6 7 8 9
```

Decimal literals have no special prefix.

---

# Binary Literals (Base 2)

Since C++14:

```cpp
0b1010
```

Prefix:

```cpp
0b
```

means:

```text
This number is written in binary.
```

Example:

```cpp
0b1010
```

equals:

```text
10
```

Binary uses only:

```text
0
1
```

---

# Hexadecimal Literals (Base 16)

Prefix:

```cpp
0x
```

Example:

```cpp
0x2A
```

equals:

```text
42
```

Hex digits:

```text
0 1 2 3 4 5 6 7 8 9
A B C D E F
```

where:

```text
A = 10
B = 11
C = 12
D = 13
E = 14
F = 15
```

---

## Hex Digits Are Case-Insensitive

```cpp
0x2A
0x2a
```

Both mean:

```text
42
```

---

# Octal Literals (Base 8)

A leading zero means octal:

```cpp
052
```

equals:

```text
42
```

because:

```text
5×8 + 2 = 42
```

---

## Common Mistake

```cpp
010
```

means:

```text
8
```

not:

```text
10
```

---

## Modern Advice

Octal is mostly historical.

You rarely write new octal literals but should recognize them in older code.

Avoid accidental leading zeros.

---

# Why Hexadecimal Is Important

Hex is much shorter than binary.

Example:

```text
0011 1010 0111 1111 1001 1000 0010 0110
```

becomes:

```text
3A7F9826
```

because:

```text
4 bits = 1 hex digit
```

Hex is commonly used for:

* Memory addresses
* Debuggers
* Memory dumps
* Object files
* Low-level programming

---

# Hex ↔ Binary Cheat Sheet

```text
0 = 0000
1 = 0001
2 = 0010
3 = 0011
4 = 0100
5 = 0101
6 = 0110
7 = 0111
8 = 1000
9 = 1001
A = 1010
B = 1011
C = 1100
D = 1101
E = 1110
F = 1111
```

Useful to memorize.

---

# Digit Separators

Since C++14:

```cpp
1'000'000
```

instead of:

```cpp
1000000
```

or:

```cpp
0b1011'0010
```

instead of:

```cpp
0b10110010
```

Purpose:

```text
Improve readability only
```

The separator:

```cpp
'
```

does not affect the value.

---

# Integer Literal Type Selection

When you write:

```cpp
42
```

C++ automatically chooses a type.

Usually:

```text
int
```

if the value fits.

Examples:

```cpp
42       // int
42u      // unsigned int
42L      // long
42LL     // long long
```

---

# Outputting Numbers in Different Bases

By default:

```cpp
std::cout << 26;
```

outputs:

```text
26
```

(decimal)

---

Use manipulators:

```cpp
std::dec
std::hex
std::oct
```

Example:

```cpp
int x { 26 };

std::cout << std::dec << x << '\n';
std::cout << std::hex << x << '\n';
std::cout << std::oct << x << '\n';
```

Output:

```text
26
1a
32
```

---

## Important: Manipulators Persist

```cpp
std::cout << std::hex << 26 << '\n';
std::cout << 26 << '\n';
```

Output:

```text
1a
1a
```

To switch back:

```cpp
std::cout << std::dec;
```

---

# Outputting Binary with std::bitset

```cpp
#include <bitset>
```

Example:

```cpp
std::cout << std::bitset<8>{26};
```

Output:

```text
00011010
```

---

## Meaning of `<8>`

```cpp
std::bitset<8>
```

means:

```text
Display/store 8 bits
```

Example:

```cpp
std::bitset<4>{10}
```

↓

```text
1010
```

```cpp
std::bitset<8>{10}
```

↓

```text
00001010
```

---

## Compile-Time Size Requirement

Works:

```cpp
std::bitset<8> bits;
```

Does not work:

```cpp
int n { 8 };
std::bitset<n> bits; // error
```

The size must be known at compile time.

---

## Initializing a Bitset

All of these produce:

```text
00101010
```

```cpp
std::bitset<8>{42};
std::bitset<8>{0b101010};
std::bitset<8>{0x2A};
std::bitset<8>{052};
```

because all represent the same value.

---

# Modern Binary Output (C++20/C++23)

C++20:

```cpp
#include <format>

std::format("{:b}", 10);
```

Output:

```text
1010
```

With prefix:

```cpp
std::format("{:#b}", 10);
```

Output:

```text
0b1010
```

---

C++23:

```cpp
#include <print>

std::println("{:b}", 10);
```

Formats, prints, and adds a newline.

---

# Connection to Earlier Chapters

This chapter reinforces:

```text
Bits have no meaning.

Meaning comes from interpretation.
```

Earlier:

```text
65
↓
ASCII
↓
'A'
```

Now:

```text
42
↓
decimal
42

42
↓
binary
101010

42
↓
hex
2A
```

Different representations.

Same value.

---

# What You Actually Need To Remember

```cpp
42        // decimal
0b101010  // binary
0x2A      // hexadecimal
052       // octal
```

```text
4 bits = 1 hex digit
```

```cpp
1'000'000
```

is a digit separator.

```cpp
std::dec
std::hex
std::oct
```

change output representation.

```cpp
std::bitset<8>{42}
```

shows binary.

```cpp
std::format("{:b}", 42)
```

is the modern C++20 way to format binary output.

---

# Chapter Summary

```text
Value ≠ Representation
```

The same value can be written in multiple forms.

```cpp
42
0b101010
0x2A
052
```

all represent:

```text
42
```

---

```text
Decimal  = Base 10
Binary   = Base 2
Octal    = Base 8
Hex      = Base 16
```

---

```text
4 bits = 1 hex digit
```

---

```cpp
1'000'000
```

improves readability only.

---

```cpp
std::dec
std::hex
std::oct
```

change how numbers are displayed.

---

```cpp
std::bitset<N>
```

visualizes bits.

---
