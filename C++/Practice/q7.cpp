/* 
7 — Number Properties (8 marks)

UserInput: One integer.

Print whether it is
    * positive
    * even
    * divisible by 3
    * divisible by 5
    * divisible by both 3 and 5: 
*/

#include <iostream>
#include <string>

// Forward declarations

bool iseven(int number);
bool ispositive(int number);
bool isdivby3(int number);
bool isdivby5(int number);


int main()
{
    int number {};
    std::cout << "Enter Number: ";
    std::cin >> number;
    
    std::string numEven {iseven(number) ? "Yes" : "No"};
    std::string numPositive {ispositive(number)};
    std::string numDivBy2 {numEven}; // Even Number are always Divisible by 2
    std::string numDivBy3 {isdivby3(number) ? "Yes" : "No"};
    std::string numDivBy5 {isdivby5(number) ? "Yes" : "No"};
    std::string numDivBy3And5 { (isdivby3(number) && isdivby5(number)) ? "Yes" : "No" };

    std::cout << "Number: " << number << '\n';
    std::cout << "Is Even: " << numEven << '\n';
    std::cout << "Is Positive: " << numPositive << '\n';
    std::cout << "Is Divisible By 2: " << numDivBy2 << '\n';
    std::cout << "Is Divisible By 3: " << numDivBy3 << '\n';
    std::cout << "Is Divisible By 5: " << numDivBy5 << '\n';
    std::cout << "Is Divisible By 3 & 5: " << numDivBy3And5 << '\n';

    return 0;
}


bool iseven(int number)
{
    return ( number % 2 == 0 );
}

bool ispositive(int number)
{
   return number > 0;
}

bool isdivby3(int number)
{
    return ( number % 3 == 0 );
}

bool isdivby5(int number)
{
    return ( number % 5 == 0 );
}