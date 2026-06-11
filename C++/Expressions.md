# 1.10 — Expressions

## What is an Expression?

An **expression** is a combination of:
- Literals (e.g. `5`, `3.14`)
- Variables (e.g. `x`, `y`)
- Operators (e.g. `+`, `-`, `*`, `/`)
- Function calls (e.g. `foo()`)

that produces a **single value** when evaluated.

---

## Examples of Expressions

```cpp
2 + 3
x * 5
y = x + 2
getValue()
```

---

## Key Points

- Expressions are **evaluated to produce a value**
- Expressions may also have **side effects**
  - Example: assignment modifies a variable

```cpp
x = 10;   // expression evaluates to 10, side effect: x becomes 10
```

---

## Types of Operators in Expressions

- Arithmetic: `+ - * / %`
- Assignment: `= += -= *= /=`
- Comparison: `== != < > <= >=`
- Logical: `&& || !`

---

## Expression Evaluation

C++ evaluates expressions based on:
- Operator precedence
- Associativity rules

Example:
```cpp
2 + 3 * 4   // 14, not 20
```

---

# 1.11 — Types of Expressions

C++ expressions are categorized based on what kind of value they produce.

---

## 1. Lvalue (Locator Value)

An **lvalue**:
- Has an address in memory
- Represents an object that persists beyond a single expression
- Can appear on the left side of assignment

### Example:
```cpp
int x = 10;
x = 20;   // x is an lvalue
```

You can think of it as: **something that has identity**

---

## 2. Rvalue (Read Value)

An **rvalue**:
- Temporary value
- Does NOT have a persistent memory address (in most cases)
- Usually appears on the right side of assignment

### Example:
```cpp
int x = 5 + 3;  // (5 + 3) is an rvalue
```

---

## Lvalue vs Rvalue Example

```cpp
int x = 10;

x = 20;     // x → lvalue, 20 → rvalue
```

---

## Quick Difference

| Feature | Lvalue | Rvalue |
|--------|--------|--------|
| Memory address | Yes | Usually no |
| Persistence | Persistent | Temporary |
| Assignable | Yes | No |

---

## Important Insight

- **Lvalue = identity (variable-like)**
- **Rvalue = value (temporary result)**

---

## Why This Matters

Understanding expression types helps in:
- Function overloading
- Move semantics (advanced C++)
- Efficient memory usage

---

# Summary

- Expressions produce values and may have side effects
- Operator rules determine evaluation order
- Expressions are mainly divided into:
  - Lvalues (have identity)
  - Rvalues (temporary values)
