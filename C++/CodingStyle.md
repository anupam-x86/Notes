# LearnCpp 1.7 - 1.8 Notes

## 1.7 Keywords and Naming Identifiers

### Identifier

An identifier is the name given to a variable, function, class, or other program entity.

Examples:

```cpp
int age;
int playerHealth;
double accountBalance;
```

### Naming Rules

Identifiers:

* Can contain letters, digits, and underscores (`_`)
* Cannot start with a digit
* Cannot contain spaces
* Cannot contain special characters such as `-`, `@`, `#`
* Cannot be a C++ keyword

Valid:

```cpp
int age;
int playerHealth;
int player_2;
```

Invalid:

```cpp
int 2age;
int player-health;
int while;
```
### Variable Naming Checklist

✓ Descriptive
✓ camelCase
✓ Includes units when relevant
✓ Avoid abbreviations unless common
✓ Avoid leading underscores
✓ Easy to understand after 6 months

### Keywords

Keywords are reserved words used by the C++ language.

Examples:

```cpp
int
double
if
else
while
return
class
```

Keywords cannot be used as identifiers.

### Professional Naming Practices

Use descriptive names:

```cpp
int playerHealth;
int studentCount;
double accountBalance;
```

Avoid vague names:

```cpp
int x;
int data;
int thing;
```

unless used in a very small and obvious context.

### Variable Naming Style

Prefer camelCase:

```cpp
int playerHealth;
int totalScore;
int currentLevel;
```

### Include Units When Relevant

```cpp
int heightCm;
double distanceKm;
int responseTimeMs;
```

### Boolean Naming

Booleans should read like questions or states.

```cpp
bool isLoggedIn;
bool hasPermission;
bool enemyAlive;
```

### Avoid Leading Underscores

Avoid:

```cpp
int _score;
```

Some identifiers beginning with underscores are reserved for compilers, libraries, and system implementations.

Prefer:

```cpp
int score;
```

---

## 1.8 Whitespace and Basic Formatting

### Whitespace

Whitespace includes:

* Spaces
* Tabs
* Blank lines

Whitespace usually improves readability without affecting program behavior.

Good:

```cpp
int totalScore = score + bonusPoints;
```

Less readable:

```cpp
int totalScore=score+bonusPoints;
```

### Indentation

Indentation visually shows program structure.

```cpp
if (playerHealth > 0)
{
    std::cout << "Alive\n";
}
```

### Blank Lines

Use blank lines to separate logical sections of code.

```cpp
int age = 18;
int score = 95;

std::cout << age << '\n';
std::cout << score << '\n';
```

### Style Guides

A style guide is a document containing coding conventions, formatting rules, and best practices.

Its goal is to ensure consistency across a project.

Style guides may define:

* Naming conventions
* Formatting rules
* Indentation
* File organization
* Comment style

### Why Style Guides Matter

Style guides help teams:
- Read code faster
- Review code more easily
- Reduce style-related arguments
- Maintain consistency across large codebases

### Consistency Matters

Consistency is more important than personal preference.

Bad:

```cpp
int age=18;
int score =95;
int lives= 3;
```

Good:

```cpp
int age = 18;
int score = 95;
int lives = 3;
```

### Personal C++ Style Guide

#### Naming

```cpp
int playerHealth;
bool isLoggedIn;
```

#### Formatting

```cpp
if (playerHealth > 0)
{
    std::cout << "Alive\n";
}
```

#### Indentation

* 4 spaces

#### Naming Convention

* camelCase

#### Goal

Write code that is easy for humans to read and maintain.

---

## Key Takeaways

1. Always initialize variables before using them.
2. Using uninitialized variables can cause undefined behavior.
3. Use descriptive variable names.
4. Prefer camelCase naming.
5. Include units in variable names when relevant.
6. Use meaningful names for boolean variables.
7. Avoid leading underscores in normal application code.
8. Use consistent formatting and indentation.
9. Follow a style guide when working on projects.
10. Code is written once but read many times.
