#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "openGradeBook.h"
#include "GradeCalculator.h"

using namespace std;

int main() {
    //Load Gradebook
    string fileName;
    cout << "Enter gradebook filename: ";
    cin >> fileName;

    Gradebook gb = openGradeBook(fileName);

    const string quarterNames[4] = {"Fall", "Winter", "Spring", "Summer"};
    const vector<string> gradeLabels = {
        "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-", "F"
    };

    // Completed Classes
    cout << "\n========================================" << endl;
    cout << "  COMPLETED CLASSES" << endl;
    cout << "========================================" << endl;

    for (int q = 1; q <= 4; ++q) {
        vector<StudentClass>& classes = gb.getClasses(q);
        for (StudentClass& sc : classes) {
            if (sc.getLetterGrade() == "NR") continue;
            cout << "  " << quarterNames[q-1]
                 << " | " << sc.getClassName()
                 << " | Grade: " << sc.getLetterGrade()
                 << " | Credits: " << sc.getClassCredits() << endl;
        }
    }

    // In-Progress Classes 
    cout << "\n=====================================" << endl;
    cout << "  IN-PROGRESS CLASS CALCULATOR" << endl;
    cout << "========================================" << endl;

    for (int q = 1; q <= 4; ++q) {
        vector<StudentClass>& classes = gb.getClasses(q);

        for (StudentClass& sc : classes) {
            if (sc.getLetterGrade() != "NR") continue;

            GradeCalculator grade(sc.calcAssignmentAvg(), sc.calcExamAvg(),
                                  sc.calcAssignmentTotalWeight(), sc.calcExamTotalWeight());

            cout << "\n----- " << quarterNames[q-1] << " | " << sc.getClassName() << " -----" << endl;

            cout << "Current Final Grade: "
                 << fixed << setprecision(2) << grade.currentFinalGrade() << "%" << endl;

            for (int i = 0; i < (int)sc.getGradeWeights().size()
                         && i < (int)gradeLabels.size(); ++i) {

                cout << "Exam score needed for " << gradeLabels[i]
                     << " (" << sc.getGradeWeights()[i] << "%): "
                     << fixed << setprecision(1)
                     << grade.requiredExamScore(sc.getGradeWeights()[i]) << "%" << endl;
            }

            cout << endl;

            for (int i = 0; i < (int)sc.getGradeWeights().size()
                         && i < (int)gradeLabels.size(); ++i) {

                cout << "Assignment score needed for " << gradeLabels[i]
                     << " (" << sc.getGradeWeights()[i] << "%): "
                     << fixed << setprecision(1)
                     << grade.requiredAssignmentScore(sc.getGradeWeights()[i]) << "%" << endl;
            }
        }
    }

    return 0;
