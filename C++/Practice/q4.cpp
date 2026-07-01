/*
Q4 — Even/Odd Analyzer (8 marks)

UserInput: one Integer.

Behaviour: Print even/odd
                 positive/negative/zero
                 multiple of 5 or not

Concepts: modulo, nested if, logical operators
*/

#include <iostream>

char intSign(const int number);
bool isNumEven(const int number);
bool isNumMultipleOf5(const int number);

int main(){

    int number {};
    std::cout << "Enter a Number: " ;
    std::cin >> number;

    const char sign {intSign(number)};
    const bool isEven {isNumEven(number)};
    const bool isMultipleOf5 {isNumMultipleOf5(number)};
    
    if (sign == '+')
    {
        std::cout << "Positive Number" << '\n';
    }
    else if(sign == '-')
    {
        std::cout << "Negative Number" << '\n';

    }
    else{
        std::cout << "Number is Zero" << '\n';
    }

    if (isEven)
    {
        std::cout << "Even Number" << '\n';
    }
    else{
        std::cout << "Odd Number" << '\n';
    }

    
    if (isMultipleOf5)
    {
        std::cout << "Multiple of 5" << '\n';
    }
    else
    {
        std::cout << "Not a Multiple of 5" << '\n';
    }

    
    
    return 0;
}

char intSign(const int number){
    if (number > 0)
    {
        return '+';
    }
    else if (number < 0){
        return '-';
    }
    return '0';
}
bool isNumEven(const int number){
    return number % 2 == 0;
}
bool isNumMultipleOf5(const int number){
    return number % 5 == 0;
}