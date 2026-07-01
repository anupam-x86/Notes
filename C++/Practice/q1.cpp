/*
Q1 — Variables & Input (5 marks)

User Interaction: first name , last name, age

Behaviour: Print Hello Anupam Mishra! 
Next year you will be 20 years old.

Concepts: input, variables, strings, output formatting

*/

#include <iostream>
#include <string>
#include <string_view>

// Declared printStrSentence which gonna define after main function for better visiblilty
// Need: to printStrSentence Easily
void printStrSentence(std::string_view firstNameView,std::string_view lastNameView); 

int main(){

    // Taking User Inputs like their FirstName, LastName, Age

    std::string firstName {};
    std::cout << "Enter Your FirstName: ";
    getline(std::cin , firstName);

    std::string lastName {};
    std::cout << "Enter Your LastName: ";
    getline(std::cin , lastName);

    int Age {};
    std::cout << "Enter Your Age: ";
    std::cin >> Age;

    // Calculating And Storing Their NextYearAge 
    const int nextYearAge { Age + 1};

    // Using the inputed data to display response!

    printStrSentence(firstName,lastName);
    std::cout << "Next year you will be " << nextYearAge << '\n';
    return 0;
}

void printStrSentence(std::string_view firstNameView, std::string_view lastNameView){
    std::cout << "Hello " << firstNameView << " " << lastNameView << "!" << '\n'; 
}