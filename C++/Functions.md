# LearnCpp Notes — 2.1 to 2.3

## 2.1 Introduction to Functions

### What is a function?

A function is a reusable sequence of statements that performs a specific task.

```cpp
int main()
{
    return 0;
}
```

* `main()` is the entry point of a C++ program.
* Functions can call other functions.
* Using functions helps follow the DRY principle (Don't Repeat Yourself).

### DRY Principle

**DRY = Don't Repeat Yourself**

Avoid duplicating code when possible:

* Use variables to store values used multiple times.
* Use functions for reusable logic.
* Use loops for repeated execution.

> DRY is a guideline, not an absolute rule. Too many tiny functions can hurt readability.

### Placeholder names

Common placeholder names used in examples:

- foo
- bar
- baz

These names usually have no meaning and are used when the actual name is unimportant.
---
## 2.2 Function Return Values (Value-Returning Functions)

### Value-returning functions

A function can return a value to its caller.

```cpp
int getValue()
{
    return 5;
}
```

### The `return` statement

```cpp
return expression;
```

`return`:

1. Evaluates the expression.
2. Sends the value back to the caller.
3. Immediately exits the function.

Example:

```cpp
int getNumber()
{
    return 5;
    return 7; // never executes
}
```

Output:

```text
5
```

### Function calls as values

```cpp
int x { getValue() };
```

Think of:

```cpp
getValue()
```

as being replaced by:

```cpp
5
```

after the function returns.

>[!Important]
>
>`return` does two things:
>
>1. Returns a value (if any).
>2. Immediately exits the function.
>
>Any code after a `return` statement in the same execution path is unreachable.

### Status codes from `main()`

```cpp
int main()
{
    return 0;
}
```

Common status codes:

| Value          | Meaning |
| -------------- | ------- |
| `0`            | Success |
| `EXIT_SUCCESS` | Success |
| `EXIT_FAILURE` | Failure |

```cpp
#include <cstdlib>

int main()
{
    return EXIT_SUCCESS;
}
```

### Undefined Behavior Warning

```cpp
int foo()
{
}
```

If execution reaches the end of a non-`void` function without returning a value, the behavior is undefined (UB).

Exception: `main()` implicitly returns `0`.
Example:

```cpp
int getValue()
{
    int x{};
    std::cin >> x;
    // missing return
}
```

The compiler may warn:

```text
control reaches end of non-void function
```

### Special rule for `main()`

```cpp
int main()
{
}
```

is treated as:

```cpp
int main()
{
    return 0;
}
```

Only `main()` gets this special behavior.

---

## 2.3 Void Functions

### What is a void function?

A void function does not return a value.

```cpp
void printHello()
{
    std::cout << "Hello\n";
}
```

### Calling a void function

```cpp
printHello();
```

Valid because we only want the function's side effect.

### Cannot use a void function as a value

```cpp
int x { printHello() }; // Error
```

A void function does not produce a value.

### Early return in a void function

```cpp
void printNumber(int x)
{
    if (x < 0)
        return;

    std::cout << x;
}
```

`return;` exits the function immediately.

---

## Extra Notes

### `std::cout` is not a function

```cpp
std::cout << "Hello";
```

* `std::cout` is an output stream object.
* `<<` is an overloaded operator used to send data to the stream.

### Function Contract

```cpp
int foo();
```

This promises that the function will return an `int`.

Breaking that promise:

```cpp
int foo()
{
}
```

results in Undefined Behavior.

---

---




## Key Takeaways

* Functions allow code reuse.
* `return` sends a value back and exits the function.
* Non-`void` functions must return a value.
* Reaching the end of a non-`void` function without returning is UB.
* `void` functions do not return values.
* `main()` is special and implicitly returns `0`.
* `std::cout` is an object, not a function.
* Follow DRY, but don't sacrifice readability.
