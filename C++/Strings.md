# 5.7 — C-style Strings, `std::string`, and `std::string_view`

# Table of Contents

1. Chapter Goal
2. The Big Picture
3. Ownership
4. C-style Strings
5. `std::string`
6. Capacity and Dynamic Memory
7. Performance
8. `std::string_view`
9. Lifetime Rules
10. Input (`>>`, `getline`, `ws`)
11. String Length
12. String Literals
13. `constexpr`
14. Choosing the Right String Type
15. Common Beginner Mistakes
16. Cheat Sheet
17. Final Summary
    
# Chapter Goal

Before this chapter, you've mostly worked with numbers (`int`, `double`, `bool`, etc.).

Now you're learning how C++ stores **text**.

Although text looks simple:

```cpp
"Hello"
```

there are actually **three different ways** to represent it in C++.

Each has different rules for:

* memory
* ownership
* performance
* safety

Understanding these differences is one of the foundations of modern C++.

---

# The Big Picture

C++ has three primary string types.

| Type               | Owns Memory? | Modifiable? | Performance | Safety                    |
| ------------------ | ------------ | ----------- | ----------- | ------------------------- |
| C-style string     | ❌ No         | Sometimes   | ⭐⭐⭐⭐⭐       | ⭐                         |
| `std::string`      | ✅ Yes        | ✅ Yes       | ⭐⭐⭐         | ⭐⭐⭐⭐⭐                     |
| `std::string_view` | ❌ No         | ❌ Read-only | ⭐⭐⭐⭐⭐       | ⭐⭐⭐ (depends on lifetime) |

The **biggest difference** between them is **ownership**.

Everything else follows from that.

---

# Mental Model #1 — Ownership

Imagine a book.

There are three possibilities.

## `std::string`

You **own** the book.

```cpp
std::string name{"Alex"};
```

```
You
 │
 ▼
+----------------+
| A l e x        |
+----------------+
```

Since you own it:

* you may modify it
* you may replace it
* you decide when it is destroyed
* it automatically manages its memory
  
> [!NOTE]
> When a std::string goes out of scope, it automatically frees its memory.
---

## `std::string_view`

You **borrow** someone else's book.

```cpp
std::string_view view{name};
```

```
Owner
 │
 ▼
+----------------+
| A l e x        |
+----------------+

      ▲
      │
 string_view
```

The view **does not own anything.**

It only knows

* where the text begins
* how many characters it contains

If the owner throws away the book,

the view becomes invalid.

---

## C-style string

A C-style string is simply raw memory.

```cpp
const char* ptr{"Alex"};
```

```
ptr
 │
 ▼

A l e x \0
```

There is no automatic memory management.

Everything is manual.


>[!NOTE]
>No ownership → no safety guarantees → you are responsible for correctness.

---

# The Three Mental Models

Remember these sentences.

## `std::string`

> **"I own this text."**

---

## `std::string_view`

> **"I'm only looking at this text."**

---

## C-style string

> **"This is raw memory ending with a null terminator."**

If you remember only one thing from this chapter,

remember these three sentences.

---

# C-style Strings

## What are they?

A C-style string is simply an array of characters.

```cpp
char name[]{"Alex"};
```

Memory:

```
A
l
e
x
\0
```

Notice the final character.

```
'\0'
```

called the **null terminator**.

---

## Why is the null terminator needed?

Unlike arrays,

the computer has no idea where the string ends.

It must search until it finds

```
'\0'
```

Example:

```
A l e x \0
        ^
      stop here
```

Without the null terminator,

functions would continue reading random memory.

---

## String literals

This:

```cpp
"Hello"
```

is **not** a `std::string`.

Its type is approximately

```cpp
const char[6]
```

Why six?

```
H
e
l
l
o
\0
```

Five visible characters

plus

one hidden null terminator.

---

>[!IMPORTANT]
>This section explains why modern C++ avoids raw C-strings

# Problems with C-style Strings

Although fast,

they have many problems.

## 1. Manual memory management

You must ensure enough memory exists.

```cpp
char name[5];
```

Trying to store

```
Hello
```

doesn't fit because

```
H e l l o \0
```

needs **6 characters**.

> [!WARNING]
> Writing past the allocated size of a C-style string leads to undefined behavior and memory corruption.

---

## 2. Cannot easily assign

```cpp
char name[]{"Alex"};

name = "John";     // Error
```

Arrays cannot be reassigned.

---

## 3. Easy to overflow

Writing beyond the array's bounds causes undefined behavior.

---

## 4. Length is slow

To find length,

the computer scans until

```
'\0'
```

Time complexity:

```
O(n)
```

---

## Why do C-style strings still exist?

Mostly because

* C language compatibility
* operating system APIs
* embedded systems
* legacy code

Modern C++ generally prefers

```
std::string
```

or

```
std::string_view
```

---

# `std::string`

Include

```cpp
#include <string>
```

Create one:

```cpp
std::string name{"Alex"};
```

Unlike a C-style string,

this is a **class object**.

---

# What is a class?

A class is a user-defined type.

Just like

```cpp
int
double
bool
```

are types,

so is

```cpp
std::string
```

The difference is that

`std::string`

contains both

* data
* functions

Those functions are called **member functions**.

---

Example:

```cpp
name.length();
```

Instead of

```cpp
length(name);
```

because

```
object.function()
```

is the syntax for calling member functions.

---

# Internal Structure of `std::string`

Although implementation differs,

a string roughly contains

```cpp
class string
{
    char* data;
    size_t size;
    size_t capacity;
};
```

Think of it as

```
Stack

+-----------------------+
| pointer ------------+ |
| size = 4            | |
| capacity = 15       | |
+---------------------|-+
                      |
                      ▼

Heap

+------------------------+
| A l e x               |
+------------------------+
```

Notice

the characters live in **heap memory**,

while the object itself stores

* pointer
* size
* capacity

---

# Is it an array or linked list?

A common beginner question:

> Does `std::string` store characters in a linked list?

No.

Internally,

characters are stored **contiguously**

just like an array.

```
A l e x
```

not

```
A -> l -> e -> x
```

This makes indexing extremely fast.

```cpp
name[2]
```

works immediately.

---

# Why store the length?

A C-style string must search for

```
'\0'
```

every time.

A `std::string`

already knows

```
size = 4
```

Therefore

```cpp
name.length()
```

returns immediately.

Time complexity:

```
O(1)
```

instead of

```
O(n)
```

---

# Strings Can Grow

Unlike arrays,

a string can become larger.

```cpp
std::string name{"Alex"};

name += " Smith";
```

No manual memory allocation needed.

The string manages everything automatically.

---

# Strings Can Be Assigned

Unlike arrays,

this is perfectly valid.

```cpp
std::string name{"Alex"};

name = "John";

name = "Emily";
```

Ownership stays with the string object,

which automatically replaces its contents.

---

# Strings Can Store Text That Looks Like Numbers

Example:

```cpp
std::string id{"45"};
```

This is **text**.

Not an integer.

```
"45"
```

is completely different from

```cpp
45
```

You cannot do

```cpp
id + 10
```

because `"45"` is not a numeric value.

It must first be converted to an integer.

---

# Empty Strings

An empty string is completely valid.

```cpp
std::string s{};
```

Its length is

```
0
```

Printing it simply prints nothing.

---

# Capacity vs Size

One of the biggest differences between an array and a `std::string` is that a string can **grow**.

To avoid allocating memory every time you add a character, a string usually reserves **extra space**.

A `std::string` keeps track of two important values:

* **Size** — how many characters are currently stored.
* **Capacity** — how many characters can be stored before more memory must be allocated.

Example:

```cpp
std::string s{"Hello"};
```

```
Characters

H e l l o _ _ _ _ _ _ _ _ _ _

Size     = 5
Capacity = 15 (example)
```

Notice the unused space.

The string reserves it for future growth.

> [!TIP]
> Think of size as "used space" and capacity as "allocated space".

---

# Why Have Extra Capacity?

Suppose you repeatedly append characters.

```cpp
std::string s{"Hello"};

s += "!";
```

Without extra capacity, the string would have to

1. allocate new memory
2. copy every character
3. delete the old memory

every single time.

That would be very slow.

Instead, it reserves extra space in advance.

> [!WARNING]
> Reallocation invalidates all pointers, iterators, and std::string_view objects referring to the string.

---

# What Happens When Capacity Runs Out?

Imagine this:

```
Current capacity = 15

Need = 16
```

Now the string has no choice.

It performs a **reallocation**.

The steps are roughly:

### Step 1

Allocate a larger block of memory.

```
Old

+-------------+
| Hello       |
+-------------+

↓

New

+-----------------------------+
|                             |
+-----------------------------+
```

---

### Step 2

Copy all existing characters.

```
Hello

↓

Hello
```

---

### Step 3

Delete the old memory.

```
Old memory

❌ destroyed
```

---

### Step 4

Update the internal pointer.

```
Before

pointer
   │
   ▼
0x1000

After

pointer
   │
   ▼
0x3500
```

The string now points to the new memory.

---

# Important Consequence of Reallocation

Because the old memory is deleted,

its address changes.

Before:

```
0x1000

Hello
```

After:

```
0x3500

Hello World...
```

Anything pointing to the old memory becomes invalid.

This includes

* pointers
* iterators
* `std::string_view`s

This is an important rule that appears throughout modern C++.

---

# Why Doesn't the String Just Expand in Place?

A common beginner question:

> "Why can't it simply make the existing memory block bigger?"

Memory doesn't work that way.

Example:

```
Heap

+---------+---------+---------+
| Hello   | ObjectA | ObjectB |
+---------+---------+---------+
```

If another object is immediately after the string,

there is no room to expand.

The string must move somewhere else.

---

# Copying a `std::string`

Consider:

```cpp
std::string a{"Hello"};
std::string b{a};
```

What happens?

A **new copy** of the characters is created.

```
a

Hello

↓

copy

↓

b

Hello
```

The two strings own completely separate memory.

---

# Why Not Just Copy the Pointer?

Imagine this:

```
a

↓

Hello

b

↓

Hello
```

Now both strings think they own the same memory.

When one is destroyed,

```
delete memory
```

the other points to deleted memory.

Then when the second string is destroyed,

it tries to delete the same memory again.

This causes undefined behavior.

Therefore, each `std::string` owns **its own copy**.

---

# Performance of Copying

Copying a string means copying every character.

Example:

```cpp
std::string longText = "...";
std::string another = longText;
```

If the string contains

```
100,000 characters
```

all of them must be copied.

Time complexity:

```
O(n)
```

where **n** is the number of characters.

---

# Why is `std::string` Slower Than a C-style String?

A common question:

> "Is `std::string` slower?"

Generally:

**Yes—but for good reasons.**

`std::string` provides:

* automatic memory management
* dynamic resizing
* safe copying
* size tracking
* many useful member functions

These features add a little overhead.

In exchange,

you write much safer and cleaner code.

For most applications,

the safety is worth the tiny performance cost.

---

# Passing Strings to Functions

Suppose you write

```cpp
void print(std::string text)
{
}
```

Calling

```cpp
print(bigString);
```

copies the entire string.

For very large strings,

this can be expensive.

---

# Returning `std::string`

Beginners often think:

> "Copying is expensive, so I should never return a string."

Not true.

Modern C++ performs optimizations such as **copy elision** and **move semantics**.

Returning a string by value is usually perfectly fine.

Example:

```cpp
std::string getName()
{
    return "Alex";
}
```

Don't prematurely optimize by avoiding returned strings.

---

# Introducing `std::string_view`

Include

```cpp
#include <string_view>
```

Create one:

```cpp
std::string_view name{"Alex"};
```

Unlike `std::string`,

it **does not own the text**.

---

# What Does a `string_view` Store?

Roughly,

it stores

```cpp
class string_view
{
    const char* data;
    size_t length;
};
```

Notice what's missing.

There is

* no allocation
* no ownership
* no capacity

It only stores

* a pointer
* a length

---

# Memory Model

Suppose:

```cpp
std::string owner{"Hello"};
std::string_view view{owner};
```

```
owner

+----------------+
| H e l l o      |
+----------------+

      ▲
      │
 string_view

pointer → first character
length  → 5
```

The view is simply looking at the owner's data.

---

# Why Use `std::string_view`?

Imagine this function:

```cpp
void print(std::string text);
```

Calling it copies the string.

Instead,

```cpp
void print(std::string_view text);
```

copies only

* one pointer
* one length

Not the characters.

This is much cheaper.

---

# Conversions

## C-style string → `std::string`

```cpp
std::string s = "Hello";
```

A copy is created.

---

## `std::string` → `std::string_view`

```cpp
std::string s{"Hello"};

std::string_view sv = s;
```

No copy occurs.

The view simply points at the string.

---

## `std::string_view` → `std::string`

```cpp
std::string_view sv{"Hello"};

std::string s{sv};
```

A new string is created.

Characters are copied.

---

# The Lifetime Rule

This is **the single most important rule** when using `std::string_view`.

A view **must never outlive the object it views**.

> [!WARNING]
> std::string_view does NOT extend the lifetime of the string. If the original string is destroyed, the view becomes dangling.

---

## Safe Example

```cpp
std::string s{"Hello"};

std::string_view sv{s};
```

```
s exists

↓

sv is valid
```

Everything works.

---

## Dangerous Example

```cpp
std::string_view sv;

{
    std::string temp{"Hello"};
    sv = temp;
}

std::cout << sv;
```

When the block ends,

```
temp

↓

destroyed
```

But

```
sv

↓

still points there
```

The view now points to memory that no longer belongs to it.

This is called a **dangling view**.

Accessing it is **undefined behavior**.

---

# Rule of Thumb

Think of `std::string_view` like a library book.

You may read it.

You do **not** own it.

If the library throws the book away,

your bookmark is useless.

---

# When Should You Use `std::string_view`?

Use it when:

* You only need to **read** text.
* You don't need to modify it.
* You want to avoid unnecessary copying.
* You know the original string will stay alive.

Common example:

```cpp
void print(std::string_view text);
```

This accepts

* C-style strings
* string literals
* `std::string`
* other `std::string_view`s

without making unnecessary copies.

> [!TIP]
> Prefer std::string_view for function parameters when you only need to read data and do not require ownership.

---

# When Should You Use `std::string` Instead?

Use `std::string` when:

* You need ownership.
* You need to modify the text.
* You want to store it for later.
* The text needs its own lifetime.

Example:

```cpp
std::string username;
```

---

# Why Doesn't the Compiler Just Optimize Everything?

A common question is:

> "If everything becomes machine code anyway, why do these differences matter?"

Because C++ defines **language guarantees**, not specific optimizations.

The compiler **may** optimize away copies.

It **may not** change the meaning of your program.

For example,

`std::string` promises ownership.

`std::string_view` promises **no ownership**.

The compiler cannot silently change one into the other because that would change the program's behavior.

Optimizations are optional.

Language rules are not.

---

# Reading Strings from Input

There are **two common ways** to read text from the keyboard.

```cpp
std::cin >>
```

and

```cpp
std::getline()
```

They behave differently, and understanding the difference is important.

---

# `std::cin >>`

Example:

```cpp
std::string name;

std::cin >> name;
```

Input:

```text
Alex
```

Output:

```text
Alex
```

This works perfectly for a **single word**.

---

# The Problem with Whitespace

Suppose the user enters

```text
John Doe
```

What happens?

```cpp
std::cin >> name;
```

Only reads

```text
John
```

The extraction operator (`>>`) stops reading when it encounters **whitespace**.

Whitespace includes

* space (`' '`)
* tab (`'\t'`)
* newline (`'\n'`)

Everything after the first space remains in the input buffer.

---

# Visualizing the Input Buffer

Suppose the user types

```text
John Doe
```

and presses Enter.

The input buffer contains

```text
J o h n _ D o e \n
```

(where `_` represents a space)

After

```cpp
std::cin >> name;
```

the buffer becomes

```text
      D o e \n
```

`"John"` was extracted.

`"Doe\n"` remains.

---

# Why Is This a Problem?

Suppose we do

```cpp
std::string first;
std::string last;

std::cin >> first;
std::cin >> last;
```

Input:

```text
John Doe
```

Output:

```text
first = "John"
last  = "Doe"
```

No second prompt is needed because `"Doe"` was already waiting in the input buffer.

---

# Reading an Entire Line

If we want to read

```text
John Doe
```

as a **single string**,

we use

```cpp
std::getline(std::cin, name);
```

Now

```text
John Doe
```

is stored exactly as typed.

`getline()` keeps reading until it encounters a newline (`'\n'`).

---

# Comparing `>>` and `getline()`

| Feature             | `std::cin >>` | `std::getline()` |
| ------------------- | ------------- | ---------------- |
| Reads one word      | ✅             | ❌                |
| Reads spaces        | ❌             | ✅                |
| Stops at whitespace | ✅             | ❌                |
| Stops at Enter      | ❌             | ✅                |

Rule of thumb:

* Use `>>` for **single words**.
* Use `getline()` for **full sentences**.

---

# Mixing `>>` and `getline()`

One of the most common beginner mistakes is mixing them.

Example:

```cpp
int age;
std::string name;

std::cin >> age;
std::getline(std::cin, name);
```

Input:

```text
18
Alex
```

Unexpectedly,

`name` becomes an empty string.

Why?

---

# The Leftover Newline

After reading

```text
18
```

the input buffer actually looks like

```text
\n
```

The newline is still waiting.

Then

```cpp
std::getline(...)
```

runs.

It immediately sees

```text
\n
```

and thinks

> "The line is already finished."

So it returns an empty string.

---

# The Solution: `std::ws`

Before calling `getline()`,

consume any leading whitespace.

```cpp
std::getline(std::cin >> std::ws, name);
```

`std::ws`

means

> **"Discard leading whitespace before reading."**

This removes the leftover newline from the input buffer.

Now `getline()` works correctly.

> [!WARNING]
> Mixing std::cin >> and std::getline without std::ws often causes empty input due to leftover newline characters.
---

# String Length

Suppose

```cpp
std::string s{"Hello"};
```

Then

```cpp
s.length()
```

returns

```text
5
```

because there are five visible characters.

---

# `.length()` vs `.size()`

For `std::string`

these are equivalent.

```cpp
s.length()
```

and

```cpp
s.size()
```

return the same value.

Use whichever you find more readable.

---

# Why Doesn't `length()` Count `'\0'`?

Internally,

the memory may look like

```text
H e l l o \0
```

However,

the logical string is only

```text
Hello
```

The null terminator exists for compatibility,

but it is **not part of the string's logical content**.

Therefore,

```cpp
s.length()
```

returns

```text
5
```

not

```text
6
```

---

# What Type Does `length()` Return?

It returns

```cpp
size_t
```

instead of `int`.

---

# What is `size_t`?

`size_t` is an **unsigned integer type** used to represent

* sizes
* lengths
* array indices

Since a length cannot be negative,

using an unsigned type makes sense.

Example:

```cpp
std::string s{"Hello"};

auto len = s.length();
```

Here,

`len`

has type

```cpp
size_t
```

---

# Why Can `size_t` Cause Problems?

Suppose

```cpp
int x = -1;

if (x < s.length())
```

This comparison may not behave as expected because

```cpp
x
```

is signed,

while

```cpp
length()
```

returns an unsigned value.

Mixed signed/unsigned comparisons can produce surprising results.

> [!TIP]
> size_t is unsigned, so mixing it with signed integers can lead to subtle comparison issues.
---

# Converting to `int`

If you really need an `int`,

use

```cpp
int len = static_cast<int>(s.length());
```

The cast clearly tells the compiler

that you intentionally want a signed integer.

---

# `std::ssize()` (C++20)

Modern C++ also provides

```cpp
std::ssize(s)
```

which returns a **signed** integer type.

This is useful when

* subtracting lengths
* looping backwards
* avoiding signed/unsigned issues

---

# String Literals

A common misconception is that

```cpp
"Hello"
```

is a `std::string`.

It is **not**.

Its type is approximately

```cpp
const char[6]
```

because it contains

```text
H e l l o \0
```

---

# The `"s"` Suffix

Consider

```cpp
using namespace std::string_literals;

auto s = "Hello"s;
```

The suffix

```text
s
```

tells the compiler

> Create a `std::string`.

This is roughly equivalent to

```cpp
std::string{"Hello", 5}
```

Notice again,

only the visible characters belong to the string.

The null terminator is not counted.

> [!NOTE]
> "Hello" is a C-style string literal, while "Hello"s creates a std::string.

---

# `constexpr` and Strings

A common beginner question:

> Why doesn't this work?

```cpp
constexpr std::string s{"Hello"};
```

The answer is that

`std::string`

typically performs dynamic memory allocation,

which traditionally cannot be used in constant expressions in the way introduced at this stage of the language.

---

# Why Does `std::string_view` Work?

This is perfectly valid:

```cpp
constexpr std::string_view sv{"Hello"};
```

Why?

Because

`string_view`

doesn't allocate memory.

It simply stores

```text
pointer
+
length
```

The string literal already exists in static memory,

so the view can safely point to it at compile time.

---

# Compile-Time vs Runtime

One recurring theme in this chapter is

**compile time** vs **runtime**.

Think of it like this:

### Compile Time

The compiler is preparing the program.

It can work with

* constants
* types
* fixed information

---

### Runtime

The program is actually executing.

Objects can now

* allocate memory
* grow
* shrink
* receive user input

---

`std::string`

is primarily a runtime object.

`std::string_view`

can often be used at compile time because it owns nothing.

---

# Connecting Everything

By now,

you've seen how several earlier concepts fit together.

From previous chapters:

* compile-time vs runtime
* copying
* temporary objects
* references (preview)
* object lifetimes

Now they all apply to strings.

This chapter isn't just about text—

it's introducing ideas that will appear throughout modern C++.

---

# Choosing the Right String Type

Most beginners ask:

> "Which one should I use?"

The answer depends on **ownership**.

---

## Use `std::string` when...

You need to **own** the text.

Examples:

* storing a username
* modifying text
* concatenating strings
* keeping text for later
* returning owned text from a function

```cpp
std::string username;
```

Think:

> **"This text belongs to me."**

---

## Use `std::string_view` when...

You only need to **look at** existing text.

Examples:

* printing
* searching
* comparing
* reading function parameters

```cpp
void print(std::string_view text);
```

Think:

> **"I'm only borrowing this text."**

---

## Use C-style strings when...

Usually only for

* C libraries
* operating system APIs
* embedded systems
* legacy code

Example:

```cpp
printf("%s", name);
```

For modern C++ code,

prefer

```cpp
std::string
```

or

```cpp
std::string_view
```

---

# Comparison Table

| Feature       | C-style String | `std::string`        | `std::string_view`            |
| ------------- | -------------- | -------------------- | ----------------------------- |
| Owns memory   | ❌              | ✅                    | ❌                             |
| Dynamic size  | ❌              | ✅                    | ❌                             |
| Modifiable    | Usually        | ✅                    | ❌                             |
| Safe          | ❌              | ✅                    | Depends on lifetime           |
| Stores length | ❌              | ✅                    | ✅                             |
| Allocation    | Manual         | Automatic            | None                          |
| Copy cost     | Low            | Higher               | Very Low                      |
| Typical use   | Legacy C APIs  | General-purpose text | Read-only function parameters |

---

# Mental Models

These three sentences summarize the entire chapter.

## C-style string

> **"I am raw characters ending with `'\0'`."**

---

## `std::string`

> **"I own my text."**

---

## `std::string_view`

> **"I only point to someone else's text."**

If you understand these three ideas,

you understand most of this chapter.

---

# Common Beginner Mistakes

---

## ❌ Mistake 1

Thinking

```cpp
"123"
```

is a number.

It isn't.

It's text.

```cpp
std::string s{"123"};
```

You cannot perform arithmetic on it without converting it first.

---

## ❌ Mistake 2

Using

```cpp
std::cin >>
```

to read a full sentence.

```cpp
std::cin >> name;
```

Input:

```
John Doe
```

Result:

```
John
```

Only the first word is read.

Use

```cpp
std::getline()
```

instead.

---

## ❌ Mistake 3

Mixing

```cpp
std::cin >>
```

and

```cpp
std::getline()
```

without

```cpp
std::ws
```

Wrong:

```cpp
std::cin >> age;
std::getline(std::cin, name);
```

Correct:

```cpp
std::getline(std::cin >> std::ws, name);
```

---

## ❌ Mistake 4

Passing large strings by value.

Instead of

```cpp
void print(std::string text);
```

prefer

```cpp
void print(std::string_view text);
```

when you only need read-only access.

---

## ❌ Mistake 5

Returning or storing a `std::string_view` that refers to destroyed data.

Wrong:

```cpp
std::string_view get()
{
    std::string s{"Hello"};
    return s;
}
```

After the function returns,

`s` no longer exists.

The returned view is **dangling**.

---

## ❌ Mistake 6

Thinking `std::string` never changes memory addresses.

Appending may cause **reallocation**.

Pointers,

references,

iterators,

and `std::string_view`s that refer to the old buffer may become invalid.

---

## ❌ Mistake 7

Thinking

```cpp
"Hello"
```

is a `std::string`.

It isn't.

It is a string literal.

To create a `std::string` literal,

use

```cpp
using namespace std::string_literals;

auto s = "Hello"s;
```

---

## ❌ Mistake 8

Thinking

```cpp
.length()
```

returns an `int`.

It returns

```cpp
size_t
```

which is an unsigned integer type.

---

# Performance Summary

| Operation   | C-style                                     | `std::string` | `std::string_view` |
| ----------- | ------------------------------------------- | ------------- | ------------------ |
| Find length | O(n)                                        | O(1)          | O(1)               |
| Copy        | Cheap pointer/array copy (manual semantics) | O(n)          | O(1)               |
| Allocation  | Manual                                      | Automatic     | None               |
| Resize      | Manual                                      | Automatic     | Not possible       |

---

# Frequently Asked Questions

## Why is `std::string` slower?

Because it provides

* ownership
* dynamic memory
* automatic resizing
* safety
* convenient member functions

The small performance cost buys much safer and more expressive code.

---

## Is `std::string` stored as a linked list?

No.

Characters are stored **contiguously** in memory,

like a dynamic array.

---

## Why can't the compiler optimize everything?

The compiler may optimize your code,

but it must preserve the language's guarantees.

For example,

`std::string`

promises ownership.

`std::string_view`

promises **no ownership**.

Changing one into the other would change the program's behavior,

so the compiler cannot do that automatically.

---

## Why have both `std::string` and `std::string_view`?

Because they solve different problems.

`std::string`

owns text.

`std::string_view`

avoids unnecessary copying.

Neither replaces the other.

---

# Connections to Future LearnCpp Chapters

This chapter quietly introduces ideas you'll revisit many times.

### References

You'll later learn why

```cpp
const std::string&
```

and

```cpp
std::string_view
```

are commonly used as function parameters.

---

### Dynamic Memory

Understanding capacity and reallocation prepares you for

* `new`
* `delete`
* heap allocation
* vectors

---

### Move Semantics

Later you'll learn why returning a

```cpp
std::string
```

is efficient despite ownership.

---

### Classes

`std::string`

is your first real class.

Soon you'll create your own classes with

* member variables
* member functions
* constructors

---

### Containers

`std::vector`

works similarly.

It also has

* size
* capacity
* reallocation

Many of the concepts from this chapter directly transfer to vectors.

---

# Chapter Cheat Sheet

## C-style string

```cpp
const char* text = "Hello";
```

✔ Very fast

✔ Compatible with C

✘ Manual

✘ Error-prone

---

## `std::string`

```cpp
std::string text{"Hello"};
```

✔ Owns memory

✔ Easy to modify

✔ Dynamic size

✔ Safe

---

## `std::string_view`

```cpp
std::string_view text{"Hello"};
```

✔ No allocation

✔ No copying

✔ Very fast

✘ Doesn't own data

---

## Read one word

```cpp
std::cin >> name;
```

---

## Read an entire line

```cpp
std::getline(std::cin, name);
```

---

## Fix mixed input

```cpp
std::getline(std::cin >> std::ws, name);
```

---

## Get length

```cpp
name.length();
```

or

```cpp
name.size();
```

---

## Create a `std::string`

```cpp
std::string s{"Hello"};
```

---

## Create a `std::string_view`

```cpp
std::string_view sv{"Hello"};
```

---

## Convert string → string_view

```cpp
std::string s{"Hello"};

std::string_view sv = s;
```

No copy.

---

## Convert string_view → string

```cpp
std::string s{sv};
```

Copies characters.

---

## Compile-time string

```cpp
constexpr std::string_view sv{"Hello"};
```

---

# Final Summary

This chapter is **not really about strings**.

It's your introduction to several core C++ ideas:

* **Ownership** — Who is responsible for the data?
* **Lifetime** — How long does the data remain valid?
* **Dynamic memory** — Objects can allocate and manage memory automatically.
* **Performance** — Avoid unnecessary copying when possible.
* **Compile time vs. Runtime** — Some objects exist only at runtime, while others can be used in constant expressions.

These concepts appear repeatedly throughout modern C++, especially with containers, classes, references, pointers, move semantics, and the Standard Library.

If you understand **ownership**, **lifetime**, and **memory layout**, you've learned the most important lessons of this chapter.

---

# One-Page Memory Aid

```
C-style string
----------------------------
Raw characters + '\0'
Manual
Legacy
Error-prone

std::string
----------------------------
Owns memory
Dynamic
Safe
Can modify
May allocate
May reallocate

std::string_view
----------------------------
Doesn't own memory
Pointer + Length
Read-only
No allocation
Very fast
Lifetime must be valid
```

---

# Key Takeaways

## C-style Strings

* A C-style string is an array of characters ending with a **null terminator (`'\0'`)**.
* The null terminator marks the end of the string.
* Finding the length requires scanning until `'\0'` (`O(n)` complexity).
* C-style strings are low-level, manually managed, and prone to errors such as buffer overflows.
* Today, they are mainly used when working with legacy C code or C APIs.

---

## `std::string`

* `std::string` is a **class**, not a built-in type.
* It **owns its memory** and manages it automatically.
* Internally, it typically stores:

  * a pointer to the character data
  * the current size (number of characters)
  * the capacity (allocated storage)
* Characters are stored **contiguously**, like a dynamic array.
* Since the size is already stored, `.length()` and `.size()` are **O(1)** operations.
* Strings can grow dynamically without manual memory management.
* Growing beyond the current capacity triggers **reallocation**.
* Reallocation changes the underlying memory address and invalidates pointers, iterators, and existing `std::string_view`s.
* Copying a `std::string` copies all of its characters, making it more expensive than copying a pointer.
* Returning a `std::string` by value is usually efficient in modern C++ thanks to compiler optimizations (copy elision and move semantics).
* `"45"` is **text**, not the integer `45`.
* An empty string (`std::string{}`) is perfectly valid.

---

## `std::string_view`

* `std::string_view` **does not own** the string it refers to.
* It stores only:

  * a pointer to the first character
  * the length of the string
* It performs **no allocation** and **no copying**.
* Creating a `std::string_view` from a `std::string` is inexpensive.
* Converting a `std::string_view` back to a `std::string` creates a copy.
* A `std::string_view` must **never outlive** the object whose data it references.
* Use `std::string_view` for efficient **read-only** function parameters and temporary views.

---

## Input

* `std::cin >>` reads only until the first whitespace character.
* `std::getline()` reads an entire line, including spaces.
* Mixing `>>` and `getline()` often leaves a newline (`'\n'`) in the input buffer.
* Use `std::ws` before `getline()` to discard leading whitespace.

---

## Length and Types

* `.length()` and `.size()` return the same value for `std::string`.
* Both return `size_t`, which is an **unsigned integer** type.
* Use `static_cast<int>()` or `std::ssize()` (C++20) when a signed value is needed.

---

## String Literals

* `"Hello"` is a **C-style string literal**, not a `std::string`.
* `"Hello"s` creates a `std::string` object (after enabling the string literal suffix).
* Internally, string literals include a null terminator, but the logical string length does **not** count it.

---

## Compile-Time vs Runtime

* `std::string` is primarily a **runtime** object because it may allocate dynamic memory.
* `std::string_view` is lightweight enough to be used in many `constexpr` contexts because it does not own or allocate memory.

---

# Ultimate Takeaways

If you remember only four ideas from this chapter, make them these:

1. **`std::string` owns its data; `std::string_view` does not.**
2. **Growing a `std::string` may reallocate memory and invalidate pointers, iterators, and existing `std::string_view`s.**
3. **Use `std::getline()` when reading text with spaces, and use `std::ws` when mixing `>>` with `getline()`.**
4. **Think in terms of ownership, lifetime, and memory layout—not just syntax.**

These four ideas form the foundation for understanding strings, containers, references, pointers, and many other features you'll encounter throughout modern C++.


These principles will continue to appear throughout the rest of LearnCpp and modern C++ development.
