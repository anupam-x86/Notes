# 4.7 — Scientific notation and floating point numbers

## Scientific notation refresher

> [!NOTE]
> This is the same scientific notation from 11th-class physics — C++ doesn't
> invent a new system, it borrows this one because it maps directly onto how
> `float` and `double` are stored internally.

**Procedure to convert a decimal number to scientific notation:**

* Exponent starts at zero.

* If the number has no explicit decimal point (e.g. `123`), it's implicitly on
  the right end (`123.`).

* Slide the decimal point left or right until there is exactly **one non-zero
  digit before the decimal point**.

  * Each slide **left** → exponent **+1**
  * Each slide **right** → exponent **-1**

* Trim leading zeros (left end of the significand).

* Trim trailing zeros (right end) only if:

  * the original number had no decimal point
  * those zeros are not known to be significant

### Worked examples

| Original     | Step                                                                    | Result     |
| ------------ | ----------------------------------------------------------------------- | ---------- |
| `123`        | implicit decimal: `123.` → slide 2 left                                 | `1.23e2`   |
| `0.045`      | slide decimal 2 right (exponent becomes negative)                       | `4.5e-2`   |
| `93,000,000` | slide 7 left, trailing zeros not known significant                      | `9.3e7`    |
| `0.0003120`  | slide 4 right; trailing zero kept (decimal point present → significant) | `3.120e-4` |

> [!WARNING]
> **Where this trips people up:**
>
> The exponent changes in the opposite direction from what many people expect.
>
> Sliding the decimal point to the **left** makes the written number look
> smaller, so the exponent must become **more positive** to compensate.
>
> Sliding the decimal point to the **right** makes the written number look
> larger, so the exponent must become **more negative** to compensate.
>
> If your exponent sign feels backwards, you probably moved the decimal in the
> wrong direction.

---

## Significant figures (and why they matter here)

> [!IMPORTANT]
> **The core idea:** the number of digits written communicates confidence, not
> just value.
>
> `87.0 g` and `87.000 g` represent the same measured quantity, but they do not
> communicate the same level of precision.
>
> * `87.0 g` implies precision to roughly the nearest tenth.
> * `87.000 g` implies precision to roughly the nearest thousandth.

> [!NOTE]
> LearnCpp introduces significant figures primarily as background knowledge for
> floating-point precision. Scientific and engineering disciplines often apply
> these rules much more rigorously than everyday programming.

### Rules for trailing zeros

| Case                                      | Trailing zeros are...         | Example                   |
| ----------------------------------------- | ----------------------------- | ------------------------- |
| Number has a decimal point                | Significant — keep them       | `87.000` → `8.7000e1`     |
| Number has no decimal point               | Assumed not significant       | `2100` → `2.1e3`          |
| No decimal point, but known precise       | Significant — keep them       | `2100` (±0.5) → `2.100e3` |
| Explicit trailing decimal point (`2100.`) | Signals zeros are significant | `2100.` → `2.100e3`       |

> [!TIP]
> Scientific notation is useful because it makes significance explicit and
> unambiguous.
>
> You can't accidentally lose or gain implied precision the way you can with
> ordinary decimal notation.

### Where this commonly trips people up

> [!CAUTION]
> **Mixing up "no decimal point" with "no zeros to worry about."**
>
> `2100` and `2100.` look almost identical but communicate different things.
>
> * `2100` → trailing zeros are assumed to be placeholders → `2.1e3`
> * `2100.` → trailing zeros are explicitly significant → `2.100e3`
>
> It's easy to skim past the trailing decimal point and miss that it changes the
> interpretation completely.

> [!CAUTION]
> **Forgetting that a decimal point makes trailing zeros significant by default.**
>
> `87` and `87.0` are not making the same precision claim.
>
> The instinct to ignore trailing zeros only applies when there is no decimal
> point at all.

### Why this matters for floating point

Scientific notation stores numbers conceptually as:

```text
significand × 10^exponent
```

Floating-point numbers use the same overall structure:

```text
significand × 2^exponent
```

The only difference is the base:

* Scientific notation → base 10
* Floating point → base 2

The significand (often called the mantissa) is where precision lives.

On paper you can keep adding digits forever:

```text
2.100000000000000...
```

Hardware cannot.

A floating-point type has a fixed-size significand field, which means it has a
fixed limit on how many significant digits can be stored accurately.

> [!NOTE]
> Future connection:
>
> Scientific notation in base 10 can represent values such as:
>
> ```text
> 1.25 × 10⁻¹
> ```
>
> exactly.
>
> Floating-point numbers use base 2:
>
> ```text
> 1.01₂ × 2⁻³
> ```
>
> Because many decimal fractions do not have a finite binary representation,
> rounding becomes unavoidable.
>
> This is the root cause of most floating-point precision surprises.

---

## The gotcha: C++ does not preserve this distinction

> [!WARNING]
> **`87.0` and `87.000` are stored identically in memory.**
>
> Once a value is stored, C++ keeps only the numerical value.
>
> There is no way to recover:
>
> * how many digits were originally written
> * how many significant figures were intended
> * how confident the original measurement was
>
> Significant figures are a human/scientific convention attached to written
> notation. They are not stored as part of the floating-point value itself.

```cpp
#include <iostream>

int main()
{
    double a { 87.0 };
    double b { 87.000 };

    std::cout << a << '\n';        // 87
    std::cout << b << '\n';        // 87
    std::cout << (a == b) << '\n'; // true

    return 0;
}
```

> [!CAUTION]
> **This is setting up the classic floating-point surprise:**
>
> ```cpp
> 0.1 + 0.2 != 0.3
> ```
>
> Binary cannot represent most decimal fractions exactly.
>
> Just as `1/3` has no finite decimal representation:
>
> ```text
> 0.333333333...
> ```
>
> many decimal values have no finite binary representation.
>
> Small rounding errors therefore appear silently.
>
> This is very similar to the silent-overflow problem from 4.6:
>
> * Integers lose correctness when range runs out.
> * Floating-point numbers lose correctness when precision runs out.

### So why learn significant figures at all if C++ discards them?

#### 1. Scientific notation is the blueprint

Scientific notation:

```text
significand × 10^exponent
```

Floating point:

```text
significand × 2^exponent
```

The structure is the same.

This section is building the mental model needed to understand how floating-point
numbers are represented internally.

#### 2. Precision tracking becomes your responsibility

C++ does not track how many digits are trustworthy.

You must understand the limits yourself.

Approximate precision:

| Type     | Significant digits |
| -------- | ------------------ |
| `float`  | ~6–9               |
| `double` | ~15–17             |

Once you exceed that precision, the language does not automatically warn you.

---

## Summary

* Scientific notation is not just mathematical shorthand; it is the conceptual
  model that floating-point hardware is built around.

* Scientific notation and floating-point numbers share the same overall shape:

  ```text
  significand × base^exponent
  ```

* Significant figures communicate confidence and precision in written notation.

* Significant-figure information does **not** survive storage in a C++ variable.

* Floating-point types have a fixed amount of available precision.

* The real takeaway: once a value is stored in a `float` or `double`,
  precision-tracking becomes the programmer's responsibility.
