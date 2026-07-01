/*
Q3 — Temperature Converter (8 marks)

User Input: 
        1. Celsius → Fahrenheit
        2. Fahrenheit → Celsius

        Temp to Convert: 

Constraints:
        avoid duplicated code where possible
        use constants where appropriate

*/

#include <iostream>

// Forward Declareation

double celsiusToFahrenheit(const double temperature);
double fahrenheitToCelsius(const double temperature);


int main(){

    // Taking UserInputs

    int userChoice {};
    std::cout << "Temperature Converter" << '\n';
    std::cout << "1. Celsius → Fahrenheit\n2. Fahrenheit → Celsius\n" << "Choice: " ;
    std::cin >> userChoice;

    double temperature {};
    std::cout << "Enter Temperature to Change: ";
    std::cin >> temperature;

    double convertedTemperature {};
    char symbol {};
    // Checking Choices and fulfilling needs

    if (userChoice == 1)
    {
        convertedTemperature = celsiusToFahrenheit(temperature);
        symbol = 'F';
    }
    else if (userChoice == 2)
    {
        convertedTemperature = fahrenheitToCelsius(temperature);
        symbol = 'C';
    }
    else{
        std::cout << "Invalid Choice" << '\n';
        std::cout << "Run Program Again to Convert" << '\n';
        return 0;
    }
    
    std::cout << "Converted Temperature: " << convertedTemperature << " " << symbol << '\n';
    
    return 0;
}

double celsiusToFahrenheit(const double temperature){
    return (temperature * 9/5) + 32; // Formula Used: F = (C × 9/5) + 32
}
double fahrenheitToCelsius(const double temperature){
    return (temperature - 32)*5/9;  // Formula Used: C = (F - 32) × 5/9
}