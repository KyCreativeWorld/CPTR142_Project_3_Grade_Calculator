#include "openGradeBook.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    string gbFileName;

    cin >> gbFileName;

    vector<string> prevGrades;
    vector<int> prevCredits;

    Gradebook gb = openGradeBook(gbFileName);

    for (unsigned int i = 1; i <= 4; ++i) {
        for (StudentClass sClass : gb.getClasses(i)) {
            cout << sClass.getClassName() << ": " << sClass.getClassCredits() << " Credits, " << sClass.getLetterGrade() << endl;

            if (sClass.getLetterGrade() == "NR") {
                for (StudentClass::ContentInfo assignment : sClass.getAssignments("Assignments")) {
                    cout << sClass.getClassName()
                    << ", Assignment Name: " << assignment.contentName
                    << ", Assignment Weight: " << assignment.contentWeight
                    << ", Assignment Grade: " << assignment.contentGrade << endl;
                }
                for (StudentClass::ContentInfo exam : sClass.getAssignments("Exams")) {
                    cout << "Exam Name: " << exam.contentName
                    << ", Exam Weight: " << exam.contentWeight
                    << ", Exam Grade: " << exam.contentGrade << endl;
                }
            }
        }
    }

    return 0;
}