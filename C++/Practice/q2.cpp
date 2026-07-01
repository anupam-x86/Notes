/*
Q2 — Basic Arithmetic (7 marks)

Inputs: three integers.

Behaviour: Print Sum
                 Average
                 Product
                 Largest
                 Smallest

Constraints: No loops, No arrays, No STL algorithms.

Concepts: Arithmetic, comparisons, if statements
*/

#include <iostream>

// Foward Declaration 

int threeIntSum(const int firstNum, const int secondNum, const int thirdNum);
int threeIntAvg(const int firstNum, const int secondNum, const int thirdNum);
int threeIntProduct(const int firstNum, const int secondNum, const int thirdNum);

void threeIntComparison(const int firstNum, const int secondNum, const int thirdNum);


int main(){

    // Taking User Inputs

    int firstNum {};
    std::cout << "Enter Your First Number: ";
    std::cin >> firstNum;

    int secondNum {};
    std::cout << "Enter Your Second Number: ";
    std::cin >> secondNum;


    int thirdNum {};
    std::cout << "Enter Your Third Number: ";
    std::cin >> thirdNum;

    // Testing Numbers are stored Correctly

    std::cout << "You Entered (FirstNumber, SecondNumber, ThirdNumber): " << firstNum << ", " << secondNum << ", "  << thirdNum << '\n';

    // Output Presentation
    std::cout << "Sum: " << threeIntSum(firstNum,secondNum,thirdNum) << '\n';
    std::cout << "Average: " << threeIntAvg(firstNum,secondNum,thirdNum) << '\n';
    std::cout << "Product: " << threeIntProduct(firstNum,secondNum,thirdNum) << '\n';
    threeIntComparison(firstNum,secondNum,thirdNum);
    return 0;
}
int threeIntSum(const int firstNum, const int secondNum, const int thirdNum){
    return firstNum + secondNum + thirdNum;
}

int threeIntAvg(const int firstNum, const int secondNum, const int thirdNum){
    return threeIntSum(firstNum,secondNum,thirdNum) / 3;
}

int threeIntProduct(const int firstNum, const int secondNum, const int thirdNum){
    return firstNum * secondNum * thirdNum;
}

void threeIntComparison(const int firstNum, const int secondNum, const int thirdNum){
    
    int largestNum { firstNum };
    int smallestNum { firstNum };
    
    if (secondNum >= largestNum)
    {
        largestNum = secondNum;
    }
    if (thirdNum >= largestNum)
    {
        largestNum = thirdNum;
    }
    
    if (secondNum <= smallestNum)
    {
        smallestNum = secondNum;
    }
    if (thirdNum <= smallestNum)
    {
        smallestNum = thirdNum;
    }
    
    std::cout << largestNum << " is Largest" << " & ";
    std::cout << smallestNum << " is Smallest." << '\n';
    

}