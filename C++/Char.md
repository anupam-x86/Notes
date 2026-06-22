# Characters, ASCII, and Unicode

## Why This Note Exists

Computers store everything as numbers.

However, programs often need to work with text:

```text
A
B
C
a
b
c
0
1
?
!
```

The `char` type allows us to store and work with individual characters.

This note introduces:

* `char`
* ASCII
* Character literals
* Character input/output
* Character arithmetic
* Unicode and UTF-8
* The relationship between numbers and characters

---

# The Most Important Mental Model

```text
Bits have no meaning.

Meaning comes from interpretation.
```

For characters:

```text
Stored Number
      ↓
Character Encoding Rules
      ↓
Displayed Character
```

Example:

```text
65
 ↓
ASCII
 ↓
'A'
```

The computer stores a number.

We interpret that number as a character.

---

# What Is a char?

`char` is a fundamental C++ type used to store a single character.

Example:

```cpp
char letter { 'A' };
char digit { '5' };
char symbol { '+' };
```

Unlike what many beginners assume:

```text
char is an integral type.
```

A character is stored internally as a number.

---

# ASCII

ASCII stands for:

```text
American Standard Code for Information Interchange
```

ASCII defines 128 code points:

```text
0 - 127
```

and maps numbers to characters.

Examples:

| Number | Character |
| ------ | --------- |
| 65     | A         |
| 66     | B         |
| 67     | C         |
| 97     | a         |
| 98     | b         |
| 99     | c         |
| 48     | 0         |
| 49     | 1         |
| 50     | 2         |

Mental model:

```text
Number
   ↓
ASCII Lookup
   ↓
Character
```

---

# Characters Are Stored As Numbers

Example:

```cpp
char c { 'a' };
```

ASCII says:

```text
'a' → 97
```

Conceptually:

```cpp
char c { 97 };
```

The stored value is numeric.

The interpretation is textual.

---

# Same Value, Different Interpretation

Suppose memory contains:

```text
65
```

Interpret it as:

| Type | Meaning |
| ---- | ------- |
| int  | 65      |
| bool | true    |
| char | 'A'     |

Mental model:

```text
Same Bits
      ↓
Different Interpretation
      ↓
Different Meaning
```

The bits do not change.

Only the interpretation changes.

---

# Viewing A Character As An Integer

Example:

```cpp
char c { 'A' };

std::cout << c << '\n';
std::cout << static_cast<int>(c) << '\n';
```

Output:

```text
A
65
```

Mental model:

```text
Character View
'A'

Integer View
65
```

Same underlying value.

Different interpretation.

---

# Character Literals

Text inside single quotes is a character literal.

Examples:

```cpp
'A'
'5'
'+'
'\n'
```

Each represents exactly one character.

---

# Character vs Number

These are different:

```cpp
5
```

and

```cpp
'5'
```

Integer:

```text
5
```

Character:

```text
'5' → ASCII 53
```

Example:

```cpp
char c { '5' };
```

stores:

```text
53
```

not:

```text
5
```

---

# Character vs Variable Name

These are different:

```cpp
A
```

and

```cpp
'A'
```

```text
A
↓
Identifier / Variable Name

'A'
↓
Character Literal
↓
ASCII 65
```

---

# Single Quotes vs Double Quotes

Single quotes:

```cpp
'A'
'5'
'+'
'\n'
```

represent:

```text
One Character
```

Double quotes:

```cpp
"A"
"Hello"
"123"
```

represent:

```text
Text (String)
```

Mental model:

```text
' '
 ↓
Character Literal

" "
 ↓
String Literal
```

Example:

```cpp
char c { 'A' };   // OK
```

```cpp
char c { "A" };   // Error
```

Different types.

---

# Character Arithmetic

Because `char` is an integral type, characters can participate in arithmetic.

Example:

```cpp
char c { 'A' };

++c;

std::cout << c;
```

Output:

```text
B
```

Why?

```text
'A' = 65

65 + 1 = 66

66 = 'B'
```

Mental model:

```text
Characters are numbers.

Character arithmetic is integer arithmetic.
```

---

# Character Classification

ASCII places related characters together.

Digits:

```text
'0' = 48
...
'9' = 57
```

Example:

```cpp
if (c >= '0' && c <= '9')
```

Meaning:

```text
Is c a digit?
```

Likewise:

```cpp
if (c >= 'a' && c <= 'z')
```

Meaning:

```text
Is c a lowercase letter?
```

This works because ASCII stores these characters in consecutive numeric ranges.

---

# Printable And Unprintable Characters

ASCII code points are divided into:

```text
0 - 31     Control Characters
32 - 126   Printable Characters
127        DEL
```

---

## Printable Characters

Examples:

```text
A
B
C
0
1
2
!
@
#
```

---

## Control Characters

Examples:

```cpp
'\n'
'\t'
```

These perform actions rather than displaying symbols.

Mental model:

```text
Printable Character
    ↓
Displays Symbol

Control Character
    ↓
Performs Action
```

---

# Character Output

```cpp
char c { 'A' };

std::cout << c;
```

Output:

```text
A
```

---

# Character Input

```cpp
char c {};

std::cin >> c;
```

Input:

```text
A
```

Result:

```cpp
c == 'A'
```

---

# Only One Character Is Read

Input:

```text
hello
```

Result:

```cpp
c == 'h'
```

Remaining characters stay in the input buffer.

---

# Input Buffer Mental Model

```text
Keyboard
    ↓
Input Buffer
    ↓
std::cin
```

Example:

```text
[h][e][l][l][o][\n]
 ^
 next character
```

Each extraction removes characters from the front.

---

# std::cin.get()

Normal extraction:

```cpp
std::cin >> c;
```

skips leading whitespace.

Example:

```text
    A
```

Result:

```cpp
c == 'A'
```

---

## Using get()

```cpp
std::cin.get(c);
```

Result:

```cpp
c == ' '
```

(first space)

Mental model:

```text
operator>>
    ↓
Skip Whitespace
    ↓
Read Character
```

```text
get()
    ↓
Read Exact Next Character
```

---

# Multicharacter Literals

Examples:

```cpp
'AB'
'56'
'XYZ'
```

These are called multicharacter literals.

They are:

```text
Compiler-dependent
Implementation-defined
Non-portable
```

Avoid them.

---

# Unicode

ASCII only defines:

```text
128 code points
```

This is not enough for modern languages and symbols.

Examples:

```text
你
ह
猫
😀
€
```

Unicode extends the same idea:

```text
Number
   ↓
Character
```

to hundreds of thousands of characters.

Examples:

```text
65      → A
20320   → 你
128512  → 😀
```

---

# UTF-8

UTF-8 is the most common Unicode encoding.

Examples:

```text
A  → 1 byte
é → 2 bytes
你 → 3 bytes
😀 → 4 bytes
```

Why UTF-8 became dominant:

* Supports all Unicode characters
* Compatible with ASCII
* Efficient for English text
* Standard encoding of the web

Important:

```text
ASCII is not obsolete.

ASCII is effectively the first
128 Unicode code points.
```

---

# Unicode Character Types

Modern C++ provides:

```cpp
char8_t
char16_t
char32_t
```

for Unicode support.

For now:

```cpp
char
```

and ASCII are sufficient.

---

# Practical Rules

1. Use `char` for characters.
2. Remember that characters are stored as numbers.
3. Use single quotes for character literals.
4. Use double quotes for strings.
5. Avoid multicharacter literals.
6. Understand that ASCII maps numbers to characters.
7. Remember that modern software typically uses UTF-8.

---

# Summary

```text
char is an integral type.

Characters are stored as numbers.
```

ASCII maps:

```text
65 → A
97 → a
48 → 0
```

Character literals:

```cpp
'A'
'5'
'+'
'\n'
```

represent one character.

String literals:

```cpp
"A"
"Hello"
```

represent text.

The most important takeaway:

```text
Stored Number
      ↓
Character Encoding
      ↓
Displayed Character
```

Just like previous chapters:

```text
Bits have no meaning.

Meaning comes from interpretation.
```

For `char`, that interpretation is usually ASCII or Unicode.
