/*
Generate a text-based histogram for a quiz given to a class of students. The quiz is
graded on a scale from 0 to 5. Write a program that allows the user to enter grades
for each student. As the grades are being entered, the program should count, using
an array, the number of 0s, the number of 1s, the number of 2s, the number of
3s, the number of 4s, and the number of 5s. The program should be capable of
handling an arbitrary number of student grades.
You can do this by making an array of size 6, where each array element is initialized
to zero. Whenever a zero is entered, increment the value in the array at index 0.
Whenever a one is entered, increment the value in the array at index 1, and so on,
up to index 5 of the array.
Output the histogram count at the end. For example, if the input grades are 3, 0,
1, 3, 3, 5, 5, 4, 5, 4, then the program should output
1 grade(s) of 0
1 grade(s) of 1
0 grade(s) of 2
3 grade(s) of 3
2 grade(s) of 4
3 grade(s) of 5
*/

#include <iostream>
#include <limits>

constexpr int CLASS_SIZE = 100;
constexpr int N_GRADES = 6;

void registerGrades(int grades[], int classSize, int& nStudents,
                    int countGrades[], int nGrades);

bool validGrade(int number);

void showGrades(int countGrades[], int nGrades);

int main( ) {
    int grades[CLASS_SIZE];
    int countGrades[6];
    int nStudents;

    registerGrades(grades, CLASS_SIZE, nStudents, countGrades, N_GRADES);
    showGrades(countGrades, N_GRADES);

    std::cout << "\n";
    return 0;
}

void registerGrades(int grades[], int classSize, int& nStudents,
                    int countGrades[], int nGrades) {

    int student = 0;
    std::string result;

    while(student < classSize) {
        std::cout << "Enter result for student #" << student
                  << " (or type `end` to terminate):\n";

        if (!(std::cin >> result)) {
            std::cout << "Invalid value. Retry.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // ignore next characters
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (result == "end") break;
        int grade = std::stoi(result);

        if (!validGrade(grade)) {
            std::cout << "Not a valid grade. Retry\n";
            continue;
        }

        grades[student++] = grade;
        countGrades[grade] += 1;
    }
    nStudents = student;
}

bool validGrade(const int number) {
    if (!std::isdigit(number))
        return false;
    if (number < 0 || number > 5)
        return false;
    return true;
}

void showGrades(int countGrades[], int nGrades) {
    for (int grade = 0; grade < nGrades; ++grade)
        std::cout << countGrades[grade] << " grade(s) of "
                  << grade << "\n";
}
