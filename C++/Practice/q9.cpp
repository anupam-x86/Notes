/* 
Q9 — Geometry Helper (8 Marks)

User Input:
    Select a shape.

    1. Circle
    2. Rectangle
    3. Triangle

Requirements:
    1. Display a menu allowing the user to select a shape.

    2. Based on the selected shape, prompt for the required dimensions.

       Circle:
           - Radius

       Rectangle:
           - Length
           - Width

       Triangle:
           - Base
           - Height

    3. Calculate and print the area of the selected shape.

    4. If the user enters an invalid menu option,
       print "Invalid Selection".

Example Output:
    Area: 78.54
*/

#include <iostream>
#include <iomanip>

constexpr double PI { 3.141592653589793 };
constexpr int PRECISION { 2 };

bool isValidDimension(double number);
double areaCircle(double radius);
double areaRectangle(double length,double width);
double areaTriangle(double base,double height);

int main()
{
    std::cout << "Select a shape " << '\n';
    std::cout << "1. Circle" << '\n';
    std::cout << "2. Rectangle" << '\n';
    std::cout << "3. Triangle" << '\n';

    std::cout << "** Area Precision is till "<< PRECISION <<" digits after decimal" << '\n';
    std::cout << "Choice (1-3): ";
    int choice {};
    std::cin >> choice;

    double area {};

    if (choice == 1)
    {
        double radius {};
        std::cout << "Enter Radius: ";
        std::cin >> radius;
        
        if (!isValidDimension(radius))
        {
            std::cout << "Invalid Dimensions" << '\n';
            return 1;
        }

        area = areaCircle(radius);
    }
    
    else if (choice == 2)
    {
        double length {};
        std::cout << "Enter Longer Side (Length): ";
        std::cin >> length;
        
        double width {};
        std::cout << "Enter Shorter Side (Width): ";
        std::cin >> width;

        if (!isValidDimension(length) || !isValidDimension(width) || length < width)
        {
            std::cout << "Invalid Dimensions" << '\n';
            return 1;
        }

        area = areaRectangle(length,width);
    }
    
    else if (choice == 3)
    {
        double base {};
        std::cout << "Enter Base: ";
        std::cin >> base;
        
        double height {};
        std::cout << "Enter Height: ";
        std::cin >> height;
        
        if (!isValidDimension(height) || !isValidDimension(base))
        {
            std::cout << "Invalid Dimensions" << '\n';
            return 1;
        }

        area = areaTriangle(base,height);
    }
    
    else
    {
        std::cout << "Invalid Choice!" << '\n';
        return 1;
    }

    

    std::cout << std::fixed << std::setprecision(PRECISION) ; // xx.xxx
    std::cout << "Area: " << area << '\n';

    return 0;
}

bool isValidDimension(double number)
{
    return number >= 0;
}

double areaCircle(double radius)
{
    return PI * radius * radius; 
}

double areaRectangle(double length,double width)
{
    return  length * width; }

double areaTriangle(double base,double height)
{
    return  ( base * height ) * 0.5;
}