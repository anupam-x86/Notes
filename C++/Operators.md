# Operators

> **Purpose:** Understand how operators behave, how expressions are evaluated, and common pitfalls.
>
> **Important Distinction**
> - **Precedence** → How operators are grouped.
> - **Associativity** → Grouping direction when operators have equal precedence.
> - **Evaluation Order** → When expressions are actually executed.
>
> These are **three different concepts**.

---

# Operator Precedence and Associativity

## Operator Overloading

Some operator symbols have different meanings depending on the operand types.

```cpp
5 << 1          // Bitwise left shift

std::cout << 5  // Stream insertion
```

```cpp
16 >> 2         // Bitwise right shift

std::cin >> x   // Stream extraction
```

The compiler chooses the correct operator based on **operand types**, not the symbol itself.

---

## Operator Precedence

Precedence determines **which operators bind together first**.

Example:

```cpp
2 + 3 * 4
```

Equivalent to:

```cpp
2 + (3 * 4)
```

because `*` has higher precedence than `+`.

---

## Associativity

When operators have the same precedence, associativity determines grouping.

Example:

```cpp
10 - 5 - 2
```

Equivalent to

```cpp
(10 - 5) - 2
```

because subtraction is left-associative.

---

## Evaluation Order

Evaluation order determines **when expressions execute**.

Example:

```cpp
foo(f(), g(), h());
```

The C++ standard does **not** specify the order in which function arguments are evaluated.

Possible compiler behavior:

- GCC: right → left
- Clang: left → right

Never write code that depends on evaluation order.

Prefer:

```cpp
auto a = f();
auto b = g();
auto c = h();

foo(a, b, c);
```

---

# Arithmetic Operators

## Integer Division

If both operands are integers:

```cpp
7 / 4
```

Result:

```text
1
```

The fractional part is discarded (truncated toward zero).

Examples:

```cpp
9 / 2    // 4
-7 / 4   // -1
```

---

## Floating Point Division

If either operand is floating point:

```cpp
7.0 / 4
7 / 4.0
```

Result:

```text
1.75
```

---

## Common Bug

```cpp
double x = 7 / 4;
```

Result:

```text
1.0
```

because integer division happens before assignment.

Correct:

```cpp
double x = 7.0 / 4;
```

---

## Remainder Operator (%)

`%` computes the **remainder**, not mathematical modulo.

The remainder always has the **same sign as the left operand**.

Examples:

```cpp
7 % 4      // 3
-7 % 4     // -3
7 % -4     // 3
-7 % -4    // -3
```

---

## Remainder vs Modulo

C++:

```text
-21 % 4 = -1
```

Mathematics:

```text
-21 mod 4 = 3
```

Always remember:

> `%` is the **remainder operator**, not modulo.

---

# Exponentiation

C++ has **no exponent operator**.

Incorrect:

```cpp
3 ^ 4
```

`^` means **bitwise XOR**, not exponentiation.

Correct:

```cpp
#include <cmath>

std::pow(3.0, 4.0);
```

---

## Small Integer Powers

Instead of:

```cpp
std::pow(x, 2);
```

prefer:

```cpp
x * x;
```

Benefits:

- Simpler
- Faster
- Avoids floating-point conversion

---

## Integer Exponentiation

`std::pow()` is designed for floating-point numbers.

Exact integer powers require a custom implementation (e.g. exponentiation by squaring).

Important concepts involved:

- Exponentiation by squaring
- Overflow detection
- Bitwise operations
- `assert`

---

## Overflow Detection

Before multiplication:

```cpp
result *= base;
```

a safer implementation checks:

```cpp
result > max / base
```

If true, multiplication would overflow.

Maximum value:

```cpp
std::numeric_limits<std::int64_t>::max()
```

---

## Why No Integer pow() in the Standard Library?

Integer exponentiation overflows very quickly.

Example:

```text
2^63
```

already exceeds the range of a signed 64-bit integer.

Therefore the standard library only provides floating-point `std::pow()`.

---

# Increment and Decrement Operators

## Prefix

```cpp
++x
--x
```

Behavior:

1. Modify the variable.
2. Return the modified value.

Example:

```cpp
int x{5};

int y = ++x;
```

Result:

```text
x = 6
y = 6
```

---

## Postfix

```cpp
x++
x--
```

Behavior:

1. Copy current value.
2. Modify original variable.
3. Return the old copy.

Example:

```cpp
int x{5};

int y = x++;
```

Result:

```text
x = 6
y = 5
```

`y` receives a **copy**, not a reference.

---

## Prefix vs Postfix

Prefer the prefix versions unless you specifically need the old value.

Reasons:

- Slightly more efficient.
- Avoids unnecessary copies.
- Less surprising.

---

## Side Effects

A side effect is any observable effect besides returning a value.

Examples:

```cpp
x = 5;          // modifies x
++x;            // modifies x
std::cout << x; // writes to console
```

---

## Side Effects and Evaluation Order

Avoid modifying and reading the same variable multiple times within one expression.

Bad:

```cpp
add(x, ++x);
```

Possible results differ depending on evaluation order.

Instead:

```cpp
++x;

add(x, x);
```

---

## Rule

Never use a variable that has a side effect applied to it more than once in the same statement.

Exception:

```cpp
x = x + y;
x += y;
```

These are well-defined.

---

# The Comma Operator

## What is the Comma Operator?

The comma operator evaluates multiple expressions where only one expression is allowed.

Syntax:

```cpp
expression1, expression2
```

Behavior:

1. Evaluate the left expression.
2. Discard its result.
3. Evaluate the right expression.
4. Return the value of the right expression.

Example:

```cpp
int x{1};
int y{2};

int z = (x++, y++);
```

After execution:

```text
x = 2
y = 3
z = 2
```

The expression `(x++, y++)` returns the original value of `y`.

---

## Parentheses Matter

```cpp
z = (a, b);
```

Equivalent to:

```cpp
z = b;
```

because the comma expression returns the right operand.

However,

```cpp
z = a, b;
```

is parsed as:

```cpp
(z = a), b;
```

So:

- `z` receives `a`
- `b` is evaluated then discarded

---

## Comma Operator vs Separator

Commas are often **not** the comma operator.

Examples:

```cpp
int a, b;
```

Here the comma separates declarations.

Function arguments:

```cpp
foo(a, b, c);
```

Again, separator—not comma operator.

---

## for Loops

The comma operator is commonly used inside `for` loops.

Example:

```cpp
for (int i{0}, j{10}; i < j; ++i, --j)
{
}
```

The update section uses the comma operator to evaluate both expressions.

---

## Best Practice

Avoid the comma operator except in `for` loops.

---

# 6.5 Conditional Operator (?:)

Syntax:

```cpp
condition ? expression1 : expression2
```

Meaning:

- If condition is true → evaluate `expression1`
- Otherwise → evaluate `expression2`

Example:

```cpp
int max = (a > b) ? a : b;
```

---

## Only One Branch Executes

Unlike a normal function call, only one expression is evaluated.

```cpp
condition ? foo() : bar();
```

If condition is true:

- `foo()` executes
- `bar()` is never called

---

## Common Uses

The conditional operator works well for:

- Initializing variables

```cpp
int max = (a > b) ? a : b;
```

- Assignment

```cpp
result = passed ? 100 : 0;
```

- Function arguments

```cpp
print(isAdmin ? "Admin" : "User");
```

- Return statements

```cpp
return (x > y) ? x : y;
```

- Printing

```cpp
std::cout << (x < 0 ? "negative" : "non-negative");
```

---

## Precedence Trap

Incorrect:

```cpp
std::cout << x < 0 ? "negative" : "non-negative";
```

Because `<<` has higher precedence than `?:`.

The compiler interprets:

```cpp
(std::cout << (x < 0)) ? ...
```

Always parenthesize:

```cpp
std::cout << (x < 0 ? "negative" : "non-negative");
```

---

## Matching Types

The second and third operands should have compatible types.

Good:

```cpp
int value = condition ? 10 : 20;
```

Bad:

```cpp
condition ? 5 : "hello";
```

The compiler cannot determine a common type.

---

## Best Practice

Use the conditional operator only for simple expressions.

Prefer `if` statements when logic becomes complicated.

---

# Relational Operators

Operators:

```text
<
<=
>
>=
==
!=
```

These return a `bool`.

Example:

```cpp
5 < 10
```

Result:

```text
true
```

---

## Comparing Floating Point Numbers

### Relational Operators

Comparisons such as

```cpp
a < b
```

usually work well unless the numbers are extremely close.

Tiny rounding errors may change the result.

---

### Equality Operators

Never assume floating-point values are exactly equal.

Example:

```cpp
0.1 + 0.2 == 0.3
```

may evaluate to

```text
false
```

due to floating-point representation.

---

## Safe Literal Comparisons

These are safe:

```cpp
constexpr double gravity{9.8};

if (gravity == 9.8)
{
}
```

provided both values originate from the same literal with sufficient precision.

---

## Approximate Equality

Instead of

```cpp
a == b
```

compare whether they are "close enough".

Absolute epsilon:

```cpp
std::abs(a - b) <= epsilon
```

Works well near zero.

---

Relative epsilon (Knuth):

```cpp
std::abs(a - b)
<=
std::max(std::abs(a), std::abs(b)) * relEpsilon
```

Works well for large numbers.

---

Best solution:

Use a combination of absolute and relative epsilon.

---

# Logical Operators

## Logical NOT

```cpp
!x
```

Returns:

- true if x is false
- false if x is true

---

## Logical AND

```cpp
x && y
```

True only if both operands are true.

---

## Logical OR

```cpp
x || y
```

True if at least one operand is true.

---

## Operator Precedence

Highest to lowest:

```text
!
&&
||
```

Example:

```cpp
a || b && c
```

means

```cpp
a || (b && c)
```

---

## Parenthesize Mixed Logic

Instead of relying on precedence:

```cpp
a || b && c
```

write

```cpp
a || (b && c)
```

This improves readability and prevents mistakes.

---

## Short-Circuit Evaluation

Logical operators are special.

### AND

```cpp
A && B
```

If `A` is false:

- `B` is never evaluated.

---

### OR

```cpp
A || B
```

If `A` is true:

- `B` is never evaluated.

---

Only the built-in logical operators perform short-circuit evaluation.

Overloaded `&&` and `||` behave like normal function calls.

---

## Side Effects

Avoid expressions like

```cpp
foo() && ++x;
```

or

```cpp
bar() || ++x;
```

The increment may or may not happen depending on short-circuit evaluation.

---

## De Morgan's Laws

```cpp
!(x && y)
```

Equivalent to

```cpp
!x || !y
```

---

```cpp
!(x || y)
```

Equivalent to

```cpp
!x && !y
```

Useful for simplifying logical expressions.

---

## Logical XOR

C++ does not provide a logical XOR operator.

For boolean values:

```cpp
a != b
```

behaves exactly like logical XOR.

Truth table:

| a | b | a != b |
|---|---|---------|
| F | F | F |
| F | T | T |
| T | F | T |
| T | T | F |

---

For arbitrary types:

```cpp
static_cast<bool>(a) != static_cast<bool>(b)
```

or

```cpp
!!a != !!b
```

Both convert operands to `bool`.

These expressions are less readable and should be documented if used.

---

# Chapter Summary

## Remember the Difference

- **Precedence** → grouping
- **Associativity** → grouping direction
- **Evaluation Order** → execution order

---

## Common Pitfalls

- Never rely on function argument evaluation order.
- `%` is remainder, not modulo.
- `^` is bitwise XOR, not exponentiation.
- Prefer prefix `++`/`--` unless the old value is required.
- Avoid multiple side effects in one statement.
- Avoid the comma operator except in `for` loops.
- Parenthesize conditional (`?:`) expressions when mixed with other operators.
- Do not compare floating-point numbers with `==` unless it is a known safe case.
- Prefer approximate equality for floating-point comparisons.
- Parenthesize mixed `&&` and `||` expressions.
- Avoid side effects with short-circuit operators.
- Built-in `&&` and `||` short-circuit; overloaded versions do not.

---

# Best Practices Checklist

- ✅ Write expressions for readability, not cleverness.
- ✅ Use parentheses when intent could be misunderstood.
- ✅ Keep one side effect per statement.
- ✅ Prefer prefix increment/decrement.
- ✅ Compare floating-point values using epsilon when appropriate.
- ✅ Use `if` instead of `?:` when logic becomes complex.
- ✅ Never depend on unspecified evaluation order.
