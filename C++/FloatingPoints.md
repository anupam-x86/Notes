# Chapter 4.8 — Floating Point Numbers

# The Most Important Rule

```text
Floating point numbers are approximations,
not exact representations of real numbers.
```

Or even more precisely:

```text
A floating point value is usually not the exact number you wrote.

It is the closest representable approximation
that fits in the available bits.
```

---

## Why Is It Called "Floating Point"?

In fixed-point notation, the decimal point stays in a fixed location.

Example:

```text
12.34
123.4
1234.0
```

Floating point notation stores a significand and an exponent separately:

```text
1.23 × 10²
1.23 × 10⁵
1.23 × 10⁻³
```

The significand stays similar while the exponent moves the decimal point to different locations.

The decimal (or binary) point is therefore allowed to "float", which is where the term **floating point** comes from.

---

# Mental Model 1: Floating Point Is Scientific Notation In Binary

```text
6500000 = 6.5 × 10⁶
0.00065 = 6.5 × 10⁻⁴
```

Floating point numbers work similarly, except they use powers of 2.

```text
value = sign × significand × 2^exponent
```

Example:

```text
13.5
= 1101.1₂
= 1.1011₂ × 2³
```

---

# Mental Model 2: Exponent Stores Scale, Significand Stores Detail

```text
Exponent    = Zoom Level
Significand = Image Detail
```

The exponent determines how large or small the number is.

The significand determines how much precision is retained.

---

# Mental Model 3: Floating Point Trades Precision For Range

Integers:

```text
Exact values
Limited range
```

Floating Point:

```text
Approximate values
Huge range
```

---

# Floating Point Types

| Type | Typical Size | Typical Precision |
|------|------|------|
| float | 4 bytes | ~7 significant digits |
| double | 8 bytes | ~16 significant digits |
| long double | Platform dependent | 15–33+ significant digits |

---

# Why `double` Is Usually Preferred

```text
Prefer double over float.
```

Modern CPUs are heavily optimized for double precision arithmetic, so `double` often provides significantly more accuracy with little or no performance penalty.

Unless memory usage is critical, `double` is generally the best default choice.

---

# Range vs Precision

Range answers:

```text
How large or small can the number be?
```

Precision answers:

```text
How many meaningful digits can be stored?
```

A type can have enormous range while still losing accuracy.

---

# Precision Does NOT Mean Digits After The Decimal Point

Precision refers to significant digits, not digits after the decimal point.

---

# Precision Depends On Magnitude

Precision refers to approximately 15–17 significant digits in total for `double`.

```text
Floating point precision is relative.

Large numbers lose fine detail.
Small numbers keep fine detail.
```

As numbers become larger, the spacing between representable values also becomes larger.

---

# Initialization Can Cause Rounding

Rounding errors often begin during assignment.

```cpp
float f { 3.14159265358979323846 };
```

The value is rounded immediately because a `float` cannot store that many significant digits.

---

# Why 0.1 Is Not Exact

```text
0.1 = 1/10
```

In binary:

```text
0.000110011001100110011...
```

The pattern repeats forever.

A floating point type has finite storage, so it must stop and round.

```text
Stored value ≈ 0.1

The exact stored binary value is extremely close to 0.1,
but not equal to it.
```

---

# Familiar Analogy

Decimal:

```text
1/3 = 0.333333333...
```

Binary:

```text
1/10 = 0.00011001100110011...
```

The problem is not unique to computers.

---

# Exact Binary Fractions

```text
1.0
0.5
0.25
0.125
```

These are exact because their denominators are powers of 2.

---

# Common Inexact Values

```text
0.1
0.2
0.3
0.6
0.7
```

---

# Why Output Often Looks Correct

```cpp
double d { 0.1 };
std::cout << d;
```

Output:

```text
0.1
```

The stored approximation is hidden by default formatting.

---

# Output Precision vs Stored Precision

```text
Stored precision ≠ Displayed precision
```

---

# Why Python Appears Better

Python's `float` is essentially a C/C++ `double`.

The same floating point limitations still exist.

---

# Rounding Errors Accumulate

Repeated calculations can accumulate tiny rounding errors over time.

---

# Why Floating Point Comparisons Are Dangerous

```cpp
double a { 0.1 + 0.2 };
double b { 0.3 };
```

`a == b` may be false even when the values look equal mathematically.

---

# Comparing Floating Point Numbers

```cpp
std::abs(a - b) < epsilon
```

```text
Difference is tiny
→ Treat as equal
```

For Chapter 4.8, the important lesson is:

```text
Never assume floating point values can be compared exactly.
```

---

# Machine Epsilon

For `double`:

```text
≈ 2.22 × 10⁻¹⁶
```

Machine epsilon represents the smallest detectable difference near 1.0.

---

# Overflow And Underflow

## Overflow

Values that exceed the representable range may become:

```text
+Inf
```

## Underflow

Values that become too close to zero may become:

```text
0.0
```

or a very small subnormal value.

---

# Special Floating Point Values

## Infinity

```text
+Inf
-Inf
```

## NaN (Not A Number)

```text
NaN != NaN
```

## Signed Zero

```text
+0.0
-0.0
```

---

# Why Money Should Not Use Floating Point

Financial systems often use integers instead.

```text
$10.25
→
1025 cents
```

---

# Real Numbers vs Floating Point Numbers

```text
Real Numbers      = Infinite precision
Floating Point    = Finite approximation
```

```text
double ≠ real number

double ≈ approximation of a real number
```

---

# A Useful Mental Model

Integers:

```text
Every value in the range exists.
```

Floating Point:

```text
Only certain values exist.

---o----o----o----o----
```

Values between representable numbers are rounded to the nearest available value.

```text
Integer Memory

[ exact value ]

Floating Point Memory

[ nearest representable value ]
```

---

# Practical Rules

1. Use `double` by default.
2. Avoid `float` unless memory is important.
3. Avoid direct equality comparisons.
4. Expect small rounding errors.
5. Errors accumulate during repeated calculations.
6. Avoid division by zero.
7. Do not use floating point for money.
8. Remember that displayed values may hide stored inaccuracies.

---

# Chapter Summary

Floating point numbers use binary scientific notation to store extremely large and extremely small values.

Because memory is finite, many decimal values cannot be represented exactly.

As a result:

* Rounding errors occur.
* Errors accumulate during calculations.
* Equality comparisons become unreliable.
* Floating point values should be treated as approximations.

The single most important takeaway:

```text
A floating point value is usually not the exact number you wrote.

It is the closest representable approximation
that fits in the available bits.
```
