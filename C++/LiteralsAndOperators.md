# Literals and Operators

## Literals

A literal is a value written directly into source code.

```cpp
int age{18};
```

| Item  | Meaning  |
| ----- | -------- |
| `age` | Variable |
| `18`  | Literal  |

Examples:

```cpp
5
3.14
'A'
true
"Hello"
```

## Operators

Operators are symbols that perform operations on operands.

Examples:

```cpp
+
-
*
/
%
=
<<
```

## Operands

Operands are the values or variables an operator acts on.

```cpp
5 + 3
```

| Item | Meaning  |
| ---- | -------- |
| `5`  | Operand  |
| `+`  | Operator |
| `3`  | Operand  |

## Arity

Arity is the number of operands an operator takes.

* Unary = 1 operand
* Binary = 2 operands
* Ternary = 3 operands

Examples:

```cpp
-5        // Unary
5 + 3     // Binary
a ? b : c // Ternary
```

## Expressions

An expression is a combination of literals, variables, and operators that evaluates to a value.

```cpp
5 + 3
playerHealth - damageTaken
score
42
```

All of the above are expressions.

## Return Values

Most operators produce a return value.

```cpp
5 + 3
```

evaluates to:

```text
8
```

## Side Effects

A side effect is an observable effect beyond producing a return value.

Examples:

```cpp
x = 5;
```

Side effect:

```text
x changes to 5
```

---

```cpp
std::cout << 5;
```

Side effect:

```text
prints 5 to the console
```

## Operator Chaining

Some operators return their left operand.

Assignment:

```cpp
x = y = 5;
```

Output:

```cpp
std::cout << "Age: " << age;
```

This works because:

* `=` returns the left operand.
* `<<` returns `std::cout`.

## Key Takeaways

1. Literals are values written directly in code.
2. Operators perform operations on operands.
3. Arity is the number of operands an operator takes.
4. Expressions evaluate to values.
5. Most operators produce return values.
6. Some operators also have side effects.
7. Assignment and output operators support chaining.
