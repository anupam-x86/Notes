# Unsigned Integers and Why to Avoid Them

## Why This Note Exists

At first glance, unsigned integers seem better than signed integers because they can store larger positive values using the same number of bits.

For example, an 8-bit signed integer stores:

```text
-128 to 127
```

while an 8-bit unsigned integer stores:

```text
0 to 255
```

Unsigned integers appear to provide twice as many positive values.

However, they introduce several surprising behaviors and are often a source of bugs.

This note explains how unsigned integers work, their advantages, their dangers, and when they should be used.

---

# What Is an Unsigned Integer?

An unsigned integer is an integer type that stores only non-negative values.

Example:

```cpp
unsigned int score { 100 };
```

Since there is no need to represent negative numbers, all bits can be used for the magnitude.

---

# Signed vs Unsigned Range

For an integer with `n` bits:

## Signed

```text
-(2^(n-1)) to (2^(n-1) - 1)
```

Example (8-bit):

```text
-128 to 127
```

---

## Unsigned

```text
0 to (2^n - 1)
```

Example (8-bit):

```text
0 to 255
```

Notice that unsigned integers use all available bits for positive values.

---

# Unsigned Overflow

Suppose we try to store:

```text
280
```

inside an 8-bit unsigned integer.

An 8-bit unsigned integer can store:

```text
0 to 255
```

Therefore:

```text
280
```

is outside the representable range.

---

# Wraparound Behavior

Unlike signed integers, unsigned integers have defined overflow behavior.

When an unsigned value exceeds its range:

```text
Result = value mod 2^n
```

where `n` is the number of bits.

For an 8-bit unsigned integer:

```text
2^8 = 256
```

Therefore:

```text
280 mod 256 = 24
```

Result:

```text
280 → 24
```

---

# Thinking About Wraparound

Another way to view this is as a circular number line.

For an 8-bit unsigned integer:

```text
0 ... 255
```

After:

```text
255
```

comes:

```text
0
```

again.

Examples:

```text
255 + 1 = 0
256 = 0
257 = 1
280 = 24
```

This behavior is often called:

```text
Wraparound
Modulo Wrapping
Modulo Arithmetic
```

---

# Wrapping Below Zero

Wraparound also works in the opposite direction.

Example:

```text
0 - 1
```

Mathematically:

```text
-1
```

However, unsigned integers cannot represent negative values.

Therefore:

```text
0 - 1 = 255
```

for an 8-bit unsigned integer.

Additional examples:

```text
0 - 1 = 255
0 - 2 = 254
0 - 3 = 253
```

---

# Example Bug

Imagine a game:

```cpp
std::uint8_t xp { 0 };

xp -= 1;
```

Expected:

```text
0 XP
```

Actual:

```text
255 XP
```

because the value wrapped around.

This kind of behavior has caused many real-world software and game bugs.

---

# Why Unsigned Integers Are Dangerous

Programmers naturally think:

```text
5 - 10 = -5
```

Unsigned arithmetic instead produces:

```text
5 - 10 = 251
```

(for an 8-bit unsigned integer)

This often leads to unexpected behavior.

Examples:

```text
Health systems
XP systems
Money systems
Ammo counters
Timers
Lives counters
```

Many values that should logically never be negative can temporarily become negative during calculations.

Unsigned integers make these situations harder to handle correctly.

---

# Signed vs Unsigned Overflow

## Signed Overflow

Example:

```cpp
int x { 2147483647 };
++x;
```

Result:

```text
Undefined Behavior
```

The C++ standard does not define what happens.

---

## Unsigned Overflow

Example:

```cpp
unsigned int x { 4294967295 };
++x;
```

Result:

```text
0
```

The behavior is fully defined by the language.

---

# Why Modern C++ Usually Prefers int

Many beginners think:

```text
Value cannot be negative
↓
Use unsigned
```

However, experienced C++ programmers often prefer:

```cpp
int
```

because:

```text
Signed arithmetic matches human reasoning.
```

Example:

```text
3 - 5 = -2
```

is easier to understand than:

```text
3 - 5 = 4294967294
```

---

# Legitimate Uses of Unsigned Integers

Although unsigned integers are often avoided, there are important exceptions.

---

## Bit Manipulation

Unsigned integers are preferred when working directly with bits.

Examples:

```cpp
flags << 1
flags >> 1
flags & mask
flags | mask
```

In these situations, values are treated as raw bit patterns rather than positive or negative numbers.

---

## Intentional Wraparound

Some algorithms require modulo arithmetic.

Examples:

```text
Random Number Generators
Hashing Algorithms
Encryption Algorithms
Checksums
```

Unsigned wraparound is useful because it is guaranteed by the language.

---

## Array Sizes and Indexing

Some parts of the C++ standard library use:

```cpp
std::size_t
```

which is an unsigned type.

Example:

```cpp
vec.size()
```

returns:

```cpp
std::size_t
```

Therefore, interaction with arrays and containers sometimes requires unsigned integers.

---

## Embedded Systems

On small devices such as:

```text
Arduino
Microcontrollers
IoT Devices
```

memory is often extremely limited.

Example:

```cpp
std::uint8_t
```

uses:

```text
1 byte
```

while:

```cpp
int
```

may use:

```text
2 or 4 bytes
```

On systems with only a few kilobytes of memory, the savings can be significant.

---

# Practical Rule

Use:

```cpp
int
```

by default.

Use unsigned integers only when you specifically need:

```text
Bit manipulation
Modulo arithmetic
size_t compatibility
Memory-constrained systems
```

Do not choose unsigned merely because a value is expected to be non-negative.

---

# One-Sentence Summary

> Unsigned integers provide extra positive range and guaranteed wraparound behavior, but their surprising arithmetic behavior often causes bugs, which is why modern C++ generally prefers signed integers unless unsigned behavior is specifically required.
