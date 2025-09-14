/*
Write a program to calculate the grade point average (GPA) of a student by getting
their grades for all their subjects. Grades and their grade points are
Grade S 10 points
Grade A 9 points
Grade B 8 points
Grade C 7 points
Grade D 6 points
Grade E 5 points
Grade F 0 points
The program should input the number of subjects, followed by the grade obtained
in each subject. The program should calculate the average of the grade points and
print it.
*/
#include <iostream>
using namespace std;

enum Grades {F, E = 5, D, C, B, A, S = 10};

Grades charToGrade(char gradeChar) {
    switch (gradeChar) {
        case 'S':
        case 's': return S;
        case 'a':
        case 'A': return A;
        case 'b':
        case 'B': return B;
        case 'c':
        case 'C': return C;
        case 'd':
        case 'D': return D;
        case 'e':
        case 'E': return E;
        case 'f':
        case 'F': return F;
        default: cerr << "Wrong grade. Default to F.";
                 return F;
    }
}

int main ( ) {
    int subjects;
    int sum = 0;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Insert the number of subjects:";
    cin >> subjects;

    int idx = 0;
    while (idx++ < subjects) {
        cout << "Add the grade of the " << idx << "subject:";
        char gradeChar;
        cin >> gradeChar;
        Grades grade = charToGrade(gradeChar);
        sum += grade;
    }
    float avg = static_cast<float>(sum)/static_cast<float>(subjects);
    cout << "GPA: " << avg << endl;
    return 0;
}