#include "openGradeBook.h"
#include "quarterNumToString.h"
#include "gpaCalculator.h"
#include <iostream>

using namespace std;

int main() {
    string gbName;

    cout << "==----------------------------==" << endl;
    cout << "| Welcome to Grade Calculator! |" << endl;
    cout << "==----------------------------==" << endl << endl;
    
    cout << "Input gradebook file name: ";

    getline(cin, gbName);

    Gradebook gb = openGradeBook(gbName);

    cout << endl;
    for (unsigned int i = 1; i < 5; ++i) {
        if (gb.getClasses(i).size() < 1) { break; }

        cout << "<>-- " << quarterNumToString(i) << " --<>" << endl;

        for (StudentClass sClass : gb.getClasses(i)) {
            cout << "< " << sClass.getClassName() << " > Credits: " << sClass.getClassCredits();

            if (sClass.getLetterGrade() != "NR") {
                cout << ", Grade: " << sClass.getLetterGrade() << endl;
            } else {
                cout << " [IN-PROGRESS]" << endl;
            }
        }

        cout << endl;
    }
    // GPA
    cout << "GPA: " << calculateTotalGPA(gb) << endl;
    // Projected GPA

    string classInput;

    while(classInput != "quit" && classInput != "q" && classInput != "Quit" && classInput != "Q"){

        cout << "What class would you like to look at? (\'quit\' to quit)" << endl << "> ";
        
        getline(cin, classInput);

        bool foundClass = false;
        for (unsigned int i = 1; i < 5; ++i) {
            for (StudentClass sClass : gb.getClasses(i)) {
                if (sClass.getClassName() == classInput) {
                    foundClass = true;

                    cout << endl << sClass.getClassName() << endl;

                    cout << "[Assignments]" << endl;
                    for (StudentClass::ContentInfo assignment : sClass.getAssignments("Assignments")) {
                        cout << "< " << assignment.contentName
                             << "> Weight: " << assignment.contentWeight;
                        
                        if (assignment.contentGrade != -1) {
                            cout << ", Grade: " << assignment.contentGrade;
                        }

                        cout << endl;
                    }

                    cout << "[Exams]" << endl;
                    for (StudentClass::ContentInfo exam : sClass.getAssignments("Exams")) {
                        cout << "< " << exam.contentName
                             << " > Weight: " << exam.contentWeight;
                        
                        if (exam.contentGrade != -1) {
                            cout << ", Grade: " << exam.contentGrade;
                        }

                        cout << endl;
                    }
                    
                    string assignmentInput;

                    getline(cin, assignmentInput);
                    while(assignmentInput != "quit" && assignmentInput != "q" && assignmentInput != "Quit" && classInput != "Q") {                   
                        getline(cin, assignmentInput); // FIXME: Work in progress
                    }


                }
            }
        }

        if (!foundClass && classInput != "quit" && classInput != "q" && classInput != "Quit" && classInput != "Q") {
            cout << "Couldn't find \"" << classInput << "\"" << endl;
        }

    }
   
    return 0;
}