/* 
Q8 — Grading System (10 marks)

User Input:
    Enter an integer representing a student's marks (0–100).

Requirements:
    1. Validate the input.
       - If the marks are less than 0 or greater than 100,
         print "Invalid Input".

    2. If the input is valid, determine the grade:
       - A : 90–100
       - B : 80–89
       - C : 70–79
       - D : 60–69
       - F : 0–59

    3. Also determine whether the student has:
       - Pass (Grade A–D)
       - Fail (Grade F)

Example Output:
    Grade: B
    Result: Pass
*/

#include <iostream>


bool isPass(int marks);
char studentGrade(int marks);

int main()
{
    std::cout << "Welcome To Student Grading Sytem!" << '\n';

    int marks {};
    std::cout << "Enter Student Marks: ";
    std::cin >> marks;


    if (marks >= 0 && marks <= 100)
    {

        std::cout << "Grade: " << studentGrade(marks) << '\n';
        std::cout << "Result: " << ( isPass(marks) ? "Pass" : "Fail" ) << '\n';

    }
    else
    {
        std::cout << "Invalid Input!" << '\n';
        std::cout << "Please Run the Program again to evaluate" << '\n';
    }

    return 0;
}

bool isPass(int marks)
{
    return marks >=60;
}


char studentGrade(int marks)
{
    if (marks >= 90)
    {
       return 'A';
    }
    if (marks >= 80)
    {
        return 'B';
    }
    if (marks >= 70)
    {
        return 'C';
    }
    if (marks >= 60)
    {
        return 'D';
    }
    return 'F';

}

