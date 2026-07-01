/*
Q5 — Mini Calculator (10 marks)

Input

```
number
operator
number
```

Support

```
+
-
*
/
%
```

Handle

* divide by zero
* invalid operator
*/

#include <iostream>

double sum(const double num1, const double num2);
double difference(const double num1, const double num2);
double product(const double num1, const double num2);
double division(const double num1, const double num2);
double modulus(const int num1, const int num2);

bool denominatorValid(const int num2);
bool areValidInt(const double num1, const double num2);

void errorMsg();
int main()
{

    double num1{};
    std::cout << " WARNING: Number should be Integer type for Modulus else only Integer Part will be considered" << '\n';
    std::cout << "Enter First Number ( Numerator for Division/Modulus ): ";
    std::cin >> num1;

    double num2{};
    std::cout << " WARNING: Number should be Integer type for Modulus else only Integer Part will be considered" << '\n';
    std::cout << "Enter Second Number ( Denominator for Divison/Modulus ): ";
    std::cin >> num2;

    char operationOperator{};
    std::cout << "Enter Operation Operator ( +, -, *, /, %): ";
    std::ws(std::cin);
    std::cin.get(operationOperator);

    double operationOutput{};

    if (operationOperator == '+')
    {
        operationOutput = sum(num1, num2);
    }
    else if (operationOperator == '-')
    {
        operationOutput = difference(num1, num2);
    }
    else if (operationOperator == '*')
    {
        operationOutput = product(num1, num2);
    }
    else if (operationOperator == '/')
    {
        if (denominatorValid(static_cast<int>(num2)))
        {
            operationOutput = division(num1, num2);
        }
        else
        {
            errorMsg();
            return 1;
        }
        
    }
    else if (operationOperator == '%')
    {
        if ((denominatorValid(static_cast<int>(num2))) && (areValidInt(num1, num2)))
        {
            operationOutput = modulus(static_cast<int>(num1), static_cast<int>(num2));
        }
        else
        {
            errorMsg();
            return 1;
        }
    }
    else
    {
        std::cout << "Invalid Operation Operator" << '\n';
        return 1;
    }

    std::cout << "Output: " << operationOutput << '\n';

    return 0;
}

double sum(const double num1, const double num2)
{
    return num1 + num2;
}
double difference(const double num1, const double num2)
{
    return num1 - num2;
}
double product(const double num1, const double num2)
{
    return num1 * num2;
}
double division(const double num1, const double num2)
{
    return num1 / num2;
}
double modulus(const int num1, const int num2)
{
    return num1 % num2;
}


bool denominatorValid(const int num2)
{
    return num2 != 0;
}
bool areValidInt(const double num1, const double num2)
{
    const double originalSum{sum(num1, num2)};
    const int integralSum{static_cast<int>(num1) + static_cast<int>(num2)};
    const double validDifference{difference(originalSum, static_cast<double>(integralSum))};

    if((validDifference < 1) && (validDifference > 0))
    {
        return false;
    }
    else if((validDifference > -1) && (validDifference < 0))
    {
        return false;
    }
    return true;
}


void errorMsg()
{
    std::cout << "Something went Wrong!!" << '\n';
}
