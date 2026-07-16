# C++ Practice Questions
## LearnCpp Chapters 0–7

This question set is intended to reinforce concepts covered in **LearnCpp Chapters 0–7**. Complete the questions in order and submit **one solution at a time** for review.

---

## Q1 — Personal Information (5 Marks)

### User Input

- First name
- Last name
- Age

### Requirements

1. Read the user's first name, last name, and age.
2. Print a greeting in the following format:

   ```text
   Hello <FirstName> <LastName>!
   ```

3. Print the user's age next year.

### Example Output

```text
Hello Anupam Mishra!
Next year you will be 20 years old.
```

---

## Q2 — Basic Arithmetic Analyzer (7 Marks)

### User Input

Enter three integers.

### Requirements

1. Calculate and print:
   - Sum
   - Average
   - Product

2. Determine and print:
   - Largest number
   - Smallest number

### Restrictions

- Do not use loops.
- Do not use arrays.
- Do not use STL algorithms.

### Example Output

```text
Sum: 35
Average: 11.67
Product: 900
Largest: 20
Smallest: 5
```

---

## Q3 — Temperature Converter (8 Marks)

### User Input

1. Conversion choice:
   - `1` — Celsius → Fahrenheit
   - `2` — Fahrenheit → Celsius

2. Temperature value.

### Requirements

1. Display the conversion menu.
2. Perform the selected conversion.
3. Handle invalid menu selections.
4. Avoid duplicated code where possible.

### Example Output

```text
Temperature: 25°C
Fahrenheit: 77°F
```

---

## Q4 — Number Analyzer (8 Marks)

### User Input

Enter one integer.

### Requirements

Determine and print whether the number is:

- Even or Odd
- Positive, Negative, or Zero
- Divisible by 5

### Example Output

```text
Even: Yes
Sign: Positive
Divisible by 5: No
```

---

## Q5 — Mini Calculator (10 Marks)

### User Input

- First number
- Arithmetic operator
- Second number

### Supported Operators

```text
+
-
*
/
%
```

### Requirements

1. Perform the selected operation.
2. Handle:
   - Invalid operators
   - Division by zero
   - Modulo by zero

### Example Output

```text
Result: 42
```

---

## Q6 — Billing System (8 Marks)

### User Input

- Item price
- Quantity
- Tax percentage

### Requirements

Calculate and print:

- Subtotal
- Tax amount
- Grand total

### Example Output

```text
Subtotal: 1000
Tax: 180
Grand Total: 1180
```

---

## Q7 — Number Properties (8 Marks)

### User Input

Enter one integer.

### Requirements

Print whether the number is:

- Positive
- Even
- Divisible by 3
- Divisible by 5
- Divisible by both 3 and 5

### Example Output

```text
Positive: Yes
Even: No
Divisible by 3: Yes
Divisible by 5: No
Divisible by both 3 and 5: No
```

---

## Q8 — Grading System (10 Marks)

### User Input

Enter an integer representing a student's marks (`0–100`).

### Requirements

1. Validate the input.
   - If the marks are less than `0` or greater than `100`, print:

   ```text
   Invalid Input
   ```

2. Determine the student's grade.

| Marks | Grade |
|------:|:-----:|
| 90–100 | A |
| 80–89 | B |
| 70–79 | C |
| 60–69 | D |
| 0–59 | F |

3. Determine the student's result:
   - **Pass** (Grades A–D)
   - **Fail** (Grade F)

### Example Output

```text
Grade: B
Result: Pass
```

---

## Q9 — Geometry Helper (8 Marks)

### User Input

Select a shape.

```text
1. Circle
2. Rectangle
3. Triangle
```

### Requirements

Calculate and print the area of the selected shape.

**Circle**

- Radius

**Rectangle**

- Length
- Width

**Triangle**

- Base
- Height

Handle invalid menu selections.

### Example Output

```text
Area: 78.54
```

---

## Q10 — Time Converter (8 Marks)

### User Input

Enter the total number of seconds.

### Requirements

Convert the input into:

- Hours
- Minutes
- Seconds

### Example

**Input**

```text
3675
```

**Output**

```text
Hours: 1
Minutes: 1
Seconds: 15
```

---

## Q11 — Operator Precedence Challenge (10 Marks)

### Requirements

Without executing the program:

1. Predict the result of each expression.
2. Execute the program and verify your predictions.
3. Explain each result using operator precedence and associativity.

### Expressions

```cpp
5 + 2 * 3

(5 + 2) * 3

20 / 4 * 2

20 / (4 * 2)

7 % 3

7 % 2

10 - 3 - 2

10 - (3 - 2)
```

---

## Q12 — Mini Application (10 Marks)

### Problem

Design and implement one complete console application.

### Suggested Topics

- BMI Calculator
- Currency Converter
- Fuel Cost Calculator
- Age Calculator
- Discount Calculator
- Electricity Bill Estimator

### Requirements

1. Use multiple functions.
2. Use meaningful variable names.
3. Use constants where appropriate.
4. Validate input where reasonable.
5. Produce clean and well-formatted output.
6. Follow LearnCpp best practices.

---

# Marking Scheme

| Category | Marks |
|------------------------------|------:|
| Correctness | 35 |
| LearnCpp Best Practices | 20 |
| Function Design | 10 |
| Readability | 10 |
| Variable Naming | 5 |
| Formatting | 5 |
| Logic Quality | 5 |
| Scope & Lifetime Usage | 5 |
| Edge Cases | 5 |

---

# Submission Guidelines

- Submit **one question at a time**.
- Review and improve your solution before moving to the next question.
- Prioritize correctness, readability, and maintainability.
- Follow LearnCpp naming, formatting, and coding conventions.

---

# Self Review Checklist

Before submitting, verify the following:

- [ ] All variables are initialized.
- [ ] Variables are declared in the smallest possible scope.
- [ ] `const` or `constexpr` is used where appropriate.
- [ ] Each function has a single responsibility.
- [ ] Variable and function names are descriptive.
- [ ] Duplicate code has been minimized.
- [ ] Unnecessary global variables have been avoided.
- [ ] Input validation has been considered.
- [ ] Output formatting is consistent.
- [ ] The code is readable without relying on comments.
