# Type Conversions and `static_cast`

## Why This Note Exists

Programs often need to move values between different types:

```cpp
int x { 5 };
double y { x }; // int -> double
```

```cpp
double d { 5.7 };
int i { static_cast<int>(d) }; // double -> int
```

This process is called **type conversion**.

Understanding type conversion is important because:

* Conversions happen automatically all the time.
* Some conversions are safe.
* Some conversions lose information.
* C++ supports both implicit and explicit conversions.

---

# The Big Idea

> Variables have fixed types.
>
> Values can be converted between types.

Example:

```cpp
int y { 5 };

print(y); // print(double)
```

Many beginners imagine:

```text
y becomes a double
```

This is incorrect.

Instead:

```text
y (int, value 5)
        ↓
evaluate
        ↓
value 5
        ↓
convert
        ↓
temporary double 5.0
        ↓
pass to function
```

`y` remains an `int`.

---

# The Most Important Mental Model

```text
Variable
    ↓ evaluate
Value
    ↓ convert
Converted temporary value
```

Conversions happen to **values**, not variables.

---

# Implicit Type Conversion

An implicit conversion is performed automatically by the compiler.

Example:

```cpp
double d { 5 };
```

Conceptually:

```text
5 (int)
    ↓
5.0 (double)
```

The compiler performs the conversion for us.

---

# Function Parameter Conversion

```cpp
void print(double x)
{
    std::cout << x << '\n';
}

int main()
{
    int y { 5 };

    print(y);
}
```

Conceptually:

```text
y
 ↓
5
 ↓
convert to double
 ↓
5.0
 ↓
pass to print()
```

Output:

```text
5
```

The variable `y` never changes type.

---

# Safe Conversions

A conversion is generally safe when no information is lost.

Example:

```cpp
int x { 5 };

double d { x };
```

Result:

```text
5
 ↓
5.0
```

The value is preserved exactly.

---

# Narrowing Conversions

A narrowing conversion is a conversion that may lose information.

Example:

```cpp
double d { 5.7 };

int x { static_cast<int>(d) };
```

Result:

```text
5.7
 ↓
5
```

The fractional portion is discarded.

Information is lost.

---

# Why The Compiler Warns

Example:

```cpp
void print(int x)
{
    std::cout << x;
}

print(5.5);
```

Conversion:

```text
5.5
 ↓
5
```

Since information may be lost, the compiler will usually issue a warning.

Many modern projects treat warnings as errors.

---

# Implicit vs Explicit Conversion

## Implicit

Compiler performs the conversion automatically.

```cpp
double d { 5 };
```

---

## Explicit

Programmer explicitly requests the conversion.

```cpp
static_cast<double>(5)
```

Explicit conversions make intent clear.

---

# `static_cast`

The most common explicit conversion tool.

Syntax:

```cpp
static_cast<new_type>(expression)
```

Example:

```cpp
double d { 5.7 };

int x { static_cast<int>(d) };
```

Result:

```text
5.7
 ↓
5
```

---

# Reading `static_cast`

```cpp
static_cast<int>(d)
```

Read as:

```text
Convert d to int
```

Examples:

```cpp
static_cast<int>(5.7)
```

↓

```text
Convert 5.7 to int
```

```cpp
static_cast<double>(5)
```

↓

```text
Convert 5 to double
```

```cpp
static_cast<char>(65)
```

↓

```text
Convert 65 to char
```

---

# `static_cast` Does Not Modify Variables

Example:

```cpp
char ch { 'A' };

std::cout << static_cast<int>(ch) << '\n';
std::cout << ch << '\n';
```

Output:

```text
65
A
```

Process:

```text
ch
 ↓
'A'
 ↓
convert value
 ↓
65
```

The original variable remains unchanged.

---

# Expressions Can Be Converted

The argument to `static_cast` can be any expression.

```cpp
int x { 2 };
int y { 3 };

std::cout << static_cast<double>(x + y);
```

Process:

```text
x + y
 ↓
5
 ↓
convert to double
 ↓
5.0
```

---

# Understanding The Syntax

```cpp
static_cast<int>(x)
```

Mental model:

```text
<int>
 ↓
Target type

(x)
 ↓
Value / expression
```

Rule of thumb:

```text
<>
 ↓
Type information

()
 ↓
Value information
```

---

# Integer Type Conversions

## Signed → Unsigned

```cpp
int x { -1 };

unsigned int y { static_cast<unsigned int>(x) };
```

Typical result on a 32-bit system:

```text
4294967295
```

---

## Unsigned → Signed

```cpp
unsigned int u { 4000000000u };

int s { static_cast<int>(u) };
```

Typical modern result:

```text
-294967296
```

Important:

```text
The exact result depends on the representation and type sizes.
```

---

# Integer Literal Suffixes

```cpp
123u      // unsigned
123L      // long
123LL     // long long
123.0f    // float
```

Example:

```cpp
4000000000u
```

The `u` means:

```text
unsigned integer literal
```

---

# The Bits Usually Stay The Same

Consider:

```cpp
int x { -1 };
```

Typical two's complement bit pattern:

```text
11111111 11111111 11111111 11111111
```

Interpret as signed:

```text
-1
```

Interpret as unsigned:

```text
4294967295
```

Same bits.

Different interpretation.

---

# The Fundamental Rule

```text
Bits have no meaning.

Meaning comes from interpretation.
```

Example:

```text
11111111

signed interpretation
    ↓
-1

unsigned interpretation
    ↓
255
```

The bits are identical.

Only the interpretation changes.

---

# Safe vs Potentially Unsafe Conversions

```text
Usually Safe
------------

int    -> double
char   -> int
bool   -> int
```

```text
May Lose Information
--------------------

double -> int
int    -> char
int    -> bool
unsigned -> signed
signed -> unsigned
```

Always ask:

```text
Can the destination type represent the source value?
```

If not:

```text
Information may be lost.
```

---

# Conversion Flowchart

```text
Expression
     ↓
Evaluate expression
     ↓
Get value
     ↓
Convert value
     ↓
Create converted temporary
     ↓
Use converted value
```

---

# Practical Guidelines

1. Prefer implicit conversions when they are safe and obvious.
2. Use `static_cast` when information loss is possible or intent should be explicit.
3. Be careful converting floating point values to integers.
4. Be careful converting between signed and unsigned types.
5. Remember that conversions affect values, not variables.
6. Think about whether the destination type can represent the source value.

---

# Summary

Type conversion allows values to be represented as different types.

Key ideas:

```text
Variables have fixed types.

Values can be converted between types.
```

```text
Variable
    ↓ evaluate
Value
    ↓ convert
Temporary converted value
```

Conversions may happen automatically (implicit conversion) or be requested explicitly using:

```cpp
static_cast<type>(expression)
```

Finally, remember:

```text
Bits have no meaning.

Meaning comes from interpretation.
```

This principle explains why the same bit pattern can represent different values depending on the type used to interpret it.

```
```
