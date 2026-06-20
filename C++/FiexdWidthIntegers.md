# 4.6 — Fixed-width integers and size_t

## The problem: `int`'s size isn't guaranteed

`int` only guarantees a **minimum** size (≥ 16 bits) — actual size depends on platform/compiler.
Code that assumes a specific size can overflow silently and incorrectly on a different
machine — same source code, different behavior, no error or warning.

```cpp
int x { 32767 };
x = x + 1; // fine if int is 32-bit, overflows to -32768 if int is 16-bit
```

> [!WARNING]
> This isn't a crash. Overflow doesn't error out — it silently produces the *wrong*
> answer that looks completely normal. That's what makes it dangerous: the bug
> doesn't announce itself.

> [!NOTE]
> **Common mistake to watch for:** don't mix up ranges between sizes. A 16-bit
> signed int's range is **-32,768 to 32,767**. A 32-bit signed int's range is
> **-2,147,483,648 to 2,147,483,647** — over 2 billion, not 32,767.
> `int32_t x {32767}; x = x + 1;` does **not** overflow — 32768 fits easily.

### Range comparison

| Size    | Signed range                              |
| ------- | ------------------------------------------ |
| 8-bit   | -128 to 127                                |
| 16-bit  | -32,768 to 32,767                          |
| 32-bit  | -2,147,483,648 to 2,147,483,647            |
| 64-bit  | ~ -9.2×10¹⁸ to 9.2×10¹⁸                     |

---

## Why isn't size just decided per-variable or per-platform RAM?

The CPU needs to know exactly how many bytes to read at a memory address **before**
reading — there's no built-in "label" on stored data saying how big it is. Every
instruction like "read 4 bytes at this address" must be correct every time, so all
variables of a given type must be the same fixed size.

> [!NOTE]
> **Another way to think about this:** the compiler already knows the size of
> every type while generating machine code. Conceptually, it emits instructions like:
>
> ```text
> Read 4 bytes from address X
> ```
>
> or
>
> ```text
> Read 8 bytes from address X
> ```
>
> The CPU follows the instruction. It does not inspect memory and determine type
> sizes on its own. Because of this, every object of a given type must have a
> consistent size.

Available RAM doesn't change this either — more RAM just means more *room for more
variables*, not a reason to make each one bigger. Fixed sizes = fast, predictable
memory access, matched to how the CPU's circuitry actually moves data.

> [!TIP]
> **Why C never picked one universal size:** in the 1970s, different hardware was
> fastest at different word sizes. If C had hardcoded "`int` is always 32-bit,"
> programs would run *worse* on hardware that preferred a different size. So the
> standard set a **minimum guarantee only**, and let each compiler pick whatever's
> fastest on its specific platform — flexibility as a deliberate performance
> choice, not an oversight.

### Who actually decides the real size?

```
C++ Standard        → sets minimum guarantees only ("int >= 16 bits")
        ↓
Platform ABI         → the real agreed-upon sizes for a given OS + CPU
        ↓
Compiler             → implements the ABI's choices when generating machine code
```

> [!NOTE]
> **Source code vs. compiled binary (own insight from this session):** a compiled
> binary is locked — `int`'s size is already decided once a specific build exists.
> The portability risk only exists when the *source code* gets recompiled on a
> different machine/compiler. "My program" (the binary) and "my source code"
> (the recipe) are different things with different portability properties — the
> binary itself never misbehaves from this, only a *recompile* elsewhere can.

---

## The fix — fixed-width integers (`<cstdint>`)

`std::int8_t / int16_t / int32_t / int64_t` (+ `uint` versions) guarantee an
**exact** size everywhere.

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    std::int32_t x { 32767 }; // always exactly 32 bits
    x = x + 1;                 // always fits — no overflow
    std::cout << x << '\n';    // 32768

    return 0;
}
```

They are **aliases, not new types** — defined via `typedef`/`using` to whichever
existing built-in type matches that exact size on the current platform
(e.g. `int32_t` → `int` on most systems, `long` on others).

> [!IMPORTANT]
> **Concrete example of platform-dependent aliasing:** on a platform where `int`
> is 32-bit, `std::int32_t` is an alias for `int`. On a platform where `int` is
> 16-bit (and `long` is 32-bit), `std::int32_t` is an alias for `long` instead.
> Same type name, different underlying alias — the *guarantee* (32 bits) stays
> constant, the *mechanism* doesn't.

> [!NOTE]
> **`typedef` vs. `using`:** `typedef unsigned long size_t;` and
> `using size_t = unsigned long;` do the exact same thing — give an existing type
> a second name, no new type is created. `typedef` is the older syntax; `using`
> is the modern, preferred one.

### Gotcha: the 8-bit types print as characters, not numbers

`int8_t` **and** `uint8_t` are usually just aliases for `signed char` (and unsigned
char, respectively), since `char` is the only native 8-bit integral type available
on most platforms — there's nothing else for them to alias.

```cpp
std::int8_t x { 65 };
std::cout << x; // prints 'A', not 65 — std::cout treats char-like types as characters
```

> [!CAUTION]
> **Tested this myself — ASCII 0–31 are invisible control characters.** Tried
> values 1 through 18: no visible output for any of them. This checks out — ASCII
> codes 0–31 are non-printable control characters (leftover terminal/teletype
> signals: `7` = bell, `9` = tab, `10` = newline, `13` = carriage return, etc).
> The first printable character is `32` (space); recognizable symbols start
> around `33`.

> [!NOTE]
> **Rare exception:** on a platform that happens to have its own
> implementation-specific 8-bit signed integral type (separate from `char`), the
> implementation may alias `int8_t` to *that* type instead — in which case it
> would behave more like a number than a character. Doesn't come up on normal
> modern hardware (x86/ARM), but it's why the char-printing behavior is described
> as "usually," not "always."

> [!TIP]
> `std::int8_t` and `std::uint8_t` are perfectly valid numeric types. The main
> annoyance is that they are usually aliases for character types, which can lead
> to surprising behavior when printing or streaming them. For this reason, many
> programmers prefer 16-bit or larger integer types unless an 8-bit range is
> specifically required.

### Downsides of fixed-width types themselves

> [!WARNING]
> **1. Not guaranteed to exist on every architecture.** If an implementation
> cannot provide a fixed-width type with the requested width, that alias simply
> does not exist. Code that depends on it will therefore fail to compile. In
> practice: unlikely to matter unless targeting exotic mainframes/embedded chips —
> modern architectures have standardized around 8/16/32/64-bit.

> [!WARNING]
> **2. May be slower than a wider type on some architectures.** Guaranteeing a
> size doesn't guarantee speed. `std::int32_t` might be slower to process than a
> 64-bit type on a CPU that natively prefers 64-bit operations. But faster CPU
> processing ≠ automatically faster program — modern programs are often
> memory-bound rather than CPU-bound, and a larger memory footprint can slow a
> program down more than faster per-operation processing speeds can speed it up.
> **Hard to know without actually measuring.**

These concerns are largely what motivated the creation of the `least` and `fast` families:

* `least` types guarantee a type with at least the requested width and are
  guaranteed to exist.
* `fast` types provide the fastest type that has at least the requested width,
  even if that means choosing a wider type.

Neither provides the exact-size guarantee that fixed-width types do.

---

## `fast` / `least` types — mostly avoid

| Type              | Guarantees                                              |
| ------------------ | -------------------------------------------------------- |
| `int_fast#_t`      | **fastest** type that's *at least* # bits (may be wider) |
| `int_least#_t`     | **smallest** type that's *at least* # bits, always exists |

```cpp
#include <cstdint> // for fast and least types
#include <iostream>

int main()
{
    std::cout << "least 8:  " << sizeof(std::int_least8_t)  * 8 << " bits\n";
    std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
    std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
    std::cout << '\n';
    std::cout << "fast 8:  "  << sizeof(std::int_fast8_t)   * 8 << " bits\n";
    std::cout << "fast 16: "  << sizeof(std::int_fast16_t)  * 8 << " bits\n";
    std::cout << "fast 32: "  << sizeof(std::int_fast32_t)  * 8 << " bits\n";

    return 0;
}
```

Tested output on one machine:

```
least 8:  8 bits      fast 8:  8 bits
least 16: 16 bits      fast 16: 32 bits   <- compiler decided 32-bit is faster here
least 32: 32 bits      fast 32: 32 bits
```

`least16` gives exactly 16 bits (smallest that satisfies "at least 16"). `fast16`
jumped to 32 bits — on that CPU, 32-bit operations are faster than 16-bit ones, even
though a 16-bit type exists and would technically satisfy the request. This is
implementation/platform-specific — a different machine could print different numbers.

> [!CAUTION]
> **Avoid these in practice — three separate downsides:**
> 1. **Reintroduces the portability problem.** Actual size still isn't fixed across
>    platforms, which is the exact risk fixed-width types were created to eliminate
>    in the first place.
> 2. **Not many programmers use them.** Low familiarity → easy to misread what a
>    type actually guarantees, which leads to mistakes.
> 3. **`fast` types can waste memory.** Their real size may be significantly larger
>    than what the name implies (e.g. `int_fast16_t` silently becoming 32 or 64 bits) —
>    invisible cost if you're allocating many of them.

---

## Best practices — the actual decision rule

> [!IMPORTANT]
> **Prefer:**
> - **`int`** when the size doesn't matter (the number will obviously fit even in a
>   2-byte signed range). e.g. asking the user's age, counting 1 to 10. Covers the
>   vast majority of everyday cases.
> - **`std::int#_t`** when storing a quantity that needs a **guaranteed range**.
> - **`std::uint#_t`** when doing bit manipulation, or well-defined wraparound
>   behavior is actually required (e.g. cryptography, random number generation).

| Use this...     | When...                                                                  |
| ---------------- | -------------------------------------------------------------------------- |
| `int`           | Value will obviously fit regardless of size (counters, ages, small inputs) |
| `std::int#_t`   | You need a **guaranteed range** (file formats, protocols, exact-size math) |
| `std::uint#_t`  | Bit manipulation / crypto / cases where wraparound is *wanted*            |
| `std::size_t`   | Sizes, array lengths, anything holding a `sizeof()` result               |

> [!WARNING]
> **Avoid when possible:**
> - `short` and `long` → prefer a fixed-width type instead
> - `fast` and `least` integral types → prefer a fixed-width type instead
> - Unsigned types for holding general quantities → prefer signed instead
> - The 8-bit fixed-width types → prefer a 16-bit fixed-width type instead
> - Compiler-specific fixed-width integers (e.g. Visual Studio's `__int8`, `__int16`)

> [!TIP]
> **Why unsigned ≠ "obviously safer" for counts:** unsigned seems like the natural
> choice for things that can't be negative (item counts, ages), but it makes
> subtraction dangerous: `unsigned_a - unsigned_b` where `b > a` doesn't go
> negative — it wraps to a huge positive number instead. Signed types let
> "negative" exist as a safe, correct result instead of a silent bug. Unsigned is
> the right choice specifically when wraparound is *desired* (bit manipulation,
> crypto) — not as a general default for quantities.
>
> ```cpp
> unsigned a { 5 };
> unsigned b { 10 };
> std::cout << a - b; // 4294967291, not -5
> ```
> Unsigned arithmetic wraps around the top of its range instead of going negative —
> `5 - 10` becomes "5 - 10 + 2³²" under the hood, since there's no sign bit to hold
> a negative result.

---

## `std::size_t`

- The type `sizeof()` always returns.
- A **typedef/alias** for some implementation-defined **unsigned** type — unsigned
  because a size can never be negative (no wraparound risk here, since negative
  would be meaningless anyway — a box can't have "-4 bytes" of space).
- The exact underlying type is left to the compiler for the same reason `int`'s size
  is: it needs to be big enough to represent the size of the *largest possible
  object* on that specific platform.

```cpp
#include <cstddef>  // needed only if you name std::size_t yourself
#include <iostream>

int main()
{
    std::size_t s = sizeof(int); // explicit use of std::size_t -> needs <cstddef>
    std::cout << s << '\n';
    return 0;
}
```

> [!NOTE]
> **`sizeof` itself needs no `#include`.** `sizeof` is a built-in **operator**,
> part of the core language (like `+` or `==`) — it works with zero includes. But
> if *you* write `std::size_t` explicitly to declare a variable or parameter,
> that's naming a standard-library type, which needs `<cstddef>` included
> directly (don't rely on getting it indirectly via another header).

> [!NOTE]
> **Optional / not yet read:** `size_t`'s width sets a theoretical upper limit on
> object size — in practice the real limit is often smaller (some compilers cap
> it at half `size_t`'s max value; available contiguous memory also matters).
> Revisit later if working with huge arrays/datasets.

---

## Summary — the three-tier mental model

1. **`int`** — flexible, minimum-guarantee-only size. Use for everyday values.
2. **Fixed-width (`int32_t` etc.)** — exact guarantee, the main workhorse when size matters.
3. **`fast`/`least`** — niche, usually avoid; reintroduces the portability problem
   fixed-width types exist to solve.
