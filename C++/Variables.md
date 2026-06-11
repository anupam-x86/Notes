# Variables, Objects, Values & Initialization

*LearnCpp 1.3–1.6*

---

# Core Mental Model

```text
Value
↓
Stored inside
↓
Object
↓
If object has a name
↓
Variable
```
```text
Variable = name
Object = storage
Value = data
```

```cpp
int age {18};
```

| Item                 | Meaning  |
| -------------------- | -------- |
| `age`                | Variable |
| `18`                 | Value    |
| Storage holding `18` | Object   |

> [!NOTE]
>
> Every variable is an object.
>
> Not every object is a variable.
>
> Variables are named objects.

---

# Values

A value is a piece of data.

Examples:

```cpp
5
-3
3.14
'A'
"Hello"
true
```

---

# Literals

A literal is a value written directly into source code.

```cpp
int score {100};
```

| Item    | Meaning  |
| ------- | -------- |
| `score` | Variable |
| `100`   | Literal  |

> [!TIP]
>
> Literal = value typed directly into code.

---

# Objects

An object is a region of storage capable of holding a value.

```cpp
int age {18};
```

Visualization:

```text
+------+
|  18  |
+------+
```

The storage region itself is the object.

---

# Variables

A variable is a named object.

```cpp
int age {18};
```

| Thing                | Meaning  |
| -------------------- | -------- |
| `age`                | Variable |
| `18`                 | Value    |
| Storage holding `18` | Object   |

---

# Definition

A definition creates the actual variable/object.

```cpp
int age;
```

```cpp
int age {18};
```

Both create storage.

> [!NOTE]
>
> Definition:
>
> * Creates the variable
> * Allocates storage
> * Makes the object exist

---

# Declaration

A declaration tells the compiler something exists.

```cpp
extern int age;
```

No storage is created.

Compiler learns:

```text
Something called age exists somewhere.
```

> [!IMPORTANT]
>
> Every definition is a declaration.
>
> Not every declaration is a definition.

---

# Definition vs Declaration

| Statement         | Declaration | Definition |
| ----------------- | ----------- | ---------- |
| `int age;`        | ✅           | ✅          |
| `int age {18};`   | ✅           | ✅          |
| `extern int age;` | ✅           | ❌          |

---

# Declaration → Definition Relationship

Declaration:

```cpp
extern int age;
```

Meaning:

```text
Compiler:
↓
There is a variable called age.
It exists somewhere.
```

No storage is created.

Definition:

```cpp
int age {18};
```

Meaning:

```text
Compiler:
↓
Create storage for age.
Store 18 inside it.
```

Visualization:

```text
Declaration
↓
Promise

Definition
↓
Actual Variable
```

> [!NOTE]
>
> You do not convert a declaration into a definition.
>
> A definition fulfills the declaration's promise.

---

# Initialization

Initialization gives a variable its first value.

```cpp
int age {18};
```

Process:

```text
Create variable
↓
Store first value
```

---

# Assignment

Assignment changes the value of an existing variable.

```cpp
int age {18};

age = 20;
```

Output:

```text
20
```

Process:

```text
Variable already exists
↓
Old value replaced
```

---

# Definition vs Initialization vs Assignment

| Code           | Definition | Initialization | Assignment |
| -------------- | ---------- | -------------- | ---------- |
| `int age;`     | ✅          | ❌              | ❌          |
| `int age{18};` | ✅          | ✅              | ❌          |
| `age = 20;`    | ❌          | ❌              | ✅          |

---

# Local vs Global Variables

## Local Variable

```cpp
int main()
{
    int score {100};
}
```

Lifecycle:

```text
Enter main()
↓
score created
↓
Leave main()
↓
score destroyed
```

---

## Global Variable

```cpp
int age {18};

int main()
{
}
```

Lifecycle:

```text
Program starts
↓
age created
↓
Program runs
↓
Program ends
↓
age destroyed
```

> [!WARNING]
>
> Global variables are generally discouraged unless there is a good reason to use them.

---

# Initialization Types

## Comparison Table

| Type                       | Syntax         | Value Stored  | Safe? | Modern Recommendation |
| -------------------------- | -------------- | ------------- | ----- | --------------------- |
| Default Initialization     | `int x;`       | Indeterminate | ❌     | Avoid                 |
| Copy Initialization        | `int x = 5;`   | `5`           | ✅     | Acceptable            |
| Direct Initialization      | `int x(5);`    | `5`           | ✅     | Less Common           |
| Direct-List Initialization | `int x{5};`    | `5`           | ✅     | ⭐ Preferred           |
| Copy-List Initialization   | `int x = {5};` | `5`           | ✅     | Fine                  |
| Value Initialization       | `int x{};`     | `0`           | ✅     | Very Useful           |

---

## Visual Comparison

```text
int x;
│
└── Default Initialization
    ↓
    Indeterminate Value

int x = 5;
│
└── Copy Initialization
    ↓
    x = 5

int x(5);
│
└── Direct Initialization
    ↓
    x = 5

int x{5};
│
└── Direct-List Initialization
    ↓
    x = 5

int x{};
│
└── Value Initialization
    ↓
    x = 0
```

---

# Copy vs Direct vs Brace Initialization

| Feature                 | `=`          | `()`        | `{}`        |
| ----------------------- | ------------ | ----------- | ----------- |
| Example                 | `int x = 5;` | `int x(5);` | `int x{5};` |
| Initialization Type     | Copy         | Direct      | Direct-List |
| Stores 5                | ✅            | ✅           | ✅           |
| Prevents Narrowing      | ❌            | ❌           | ✅           |
| Modern Preferred        | ⚠️           | ⚠️          | ✅           |
| LearnCpp Recommendation | Good         | Good        | Best        |

---

# Narrowing Conversions

A narrowing conversion may lose information.

```cpp
int x = 4.5;
```

Output:

```text
4
```

---

```cpp
int x(4.5);
```

Output:

```text
4
```

---

```cpp
int x{4.5};
```

Possible Error:

```text
error: narrowing conversion of '4.5'
from 'double' to 'int'
```

> [!IMPORTANT]
>
> Brace initialization protects against narrowing conversions.

---

# Value Initialization

```cpp
int x{};
```

Output:

```text
0
```

Examples:

| Code          | Value   |
| ------------- | ------- |
| `int a{};`    | `0`     |
| `double b{};` | `0.0`   |
| `bool c{};`   | `false` |
| `char d{};`   | `'\0'`  |

> [!TIP]
>
> Think:
>
> ```text
> {}
> ↓
> Give me a safe default value
> ```

---

# Why LearnCpp Cares About Initialization

Bad:

```cpp
int x;
```

```text
Variable exists
↓
No value assigned
↓
Reading variable later
↓
Undefined Behavior
```

Good:

```cpp
int x{};
```

```text
Variable created
↓
Gets safe value
↓
Program behavior predictable
```

---

# Uninitialized Variables

```cpp
int x;

std::cout << x;
```

Behavior:

```text
Undefined Behavior
```

Possible consequences:

* Random output
* Different output each run
* Crashes
* Seemingly correct behavior
* Difficult-to-find bugs

> [!WARNING]
>
> Always initialize variables unless you have a specific reason not to.

---

# Common Beginner Mistakes

> [!WARNING]
> Confusing a variable with its value.

```cpp
int age {18};
```

| Thing | Meaning  |
| ----- | -------- |
| `age` | Variable |
| `18`  | Value    |

---

> [!WARNING]
> Thinking assignment creates a variable.

Wrong:

```text
age = 20
↓
Creates variable
```

Correct:

```text
int age{18}
↓
Variable created

age = 20
↓
Value changed
```

---

# Questions I Asked & Good Revision Questions

## Q1. How is `int x(5)` different from `int x{5}`?

`{}` prevents narrowing conversions.

```cpp
int x(4.5); // Compiles, becomes 4
```

```cpp
int x{4.5}; // Error
```

---

## Q2. Is `int x = 5` the same as `int x(5)`?

For built-in types, the result is usually the same.

```cpp
int x = 5;
int y(5);
```

Output:

```text
5
5
```

Difference:

| Syntax | Initialization Type   |
| ------ | --------------------- |
| `=`    | Copy Initialization   |
| `()`   | Direct Initialization |

---

## Q3. Why does LearnCpp recommend braces?

* Prevents narrowing conversions
* Safer
* More consistent
* Fewer corner cases

Recommended:

```cpp
int x{5};
```

---

## Q4. When should I use `{}` vs `{0}`?

```cpp
int a{};
int b{0};
```

Both produce:

```text
a = 0
b = 0
```

Difference:

```text
{}
↓
Use type's default value

{0}
↓
Explicitly initialize with 0
```

Modern C++ generally prefers:

```cpp
int x{};
```

---

## Q5. Why not always use `=` initialization?

```cpp
int x = 4.5;
```

Output:

```text
4
```

Information is silently lost.

```cpp
int x{4.5};
```

Produces an error instead.

---

## Q6. Why doesn't C++ automatically initialize every variable?

Tradeoff:

```text
Performance
↓
More responsibility for programmer
```

C++ gives programmers control instead of always doing automatic initialization.

---

## Q7. Is a variable the same thing as memory?

Not exactly.

```text
Variable
↓
Name

Object
↓
Storage

Storage
↓
Memory
```

---

## Q8. How do we convert a declaration into a definition later?

```cpp
extern int age;
```

Later:

```cpp
int age {18};
```

Mental model:

```text
Declaration
↓
Promise

Definition
↓
Actual Variable
```

---

## Q9. Why did this code produce a conflict?

```cpp
int main()
{
    extern int age;
    int age {30};
}
```

Error:

```text
error: 'int age' conflicts with a previous declaration
```

Reason:

```text
extern int age;
↓
Compiler already knows age exists

int age {30};
↓
Attempt to create another age in same scope
```

> [!WARNING]
>
> `extern` is mainly useful when working with multiple source files.
---

## Q10. Why is every definition also a declaration?

Example:

```cpp
int age {18};
```

The compiler learns:

```text
There is a variable called age
```

and

```text
Create storage for age
```

at the same time.

Therefore:

```text
Definition
↓
Also a declaration
```

But:

```cpp
extern int age;
```

only tells the compiler the variable exists.

So:

```text
Definition
↓
Declaration + Storage

Declaration
↓
Information Only
```
---

# Chapter Summary

Core Mental Model:

```text
Value
↓
Stored inside
↓
Object
↓
Named Object
↓
Variable
```

Important Ideas:

✓ Value = data

✓ Object = storage

✓ Variable = named object

✓ Definition creates storage

✓ Declaration introduces a name

✓ Initialization gives the first value

✓ Assignment changes an existing value

✓ Prefer brace initialization `{}`

✓ Avoid uninitialized variables

✓ Uninitialized variables can cause Undefined Behavior

✓ `extern` declares a variable that exists elsewhere

Recommended Style:

```cpp
int age{18};
int count{};
```
