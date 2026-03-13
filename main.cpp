#include "openGradeBook.h"
#include "quarterNumToString.h"
#include "gpaCalculator.h"
#include "GradeCalculator.h"
#include <iostream>
#include <iomanip>
#include <typeinfo>

using namespace std;

double getValidDouble() {
    double d;

    if (cin >> d) {
        return d;
    } else {
        cin.clear();
        cin.ignore();

        return -1.0;
    }
}

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

        cout << "=== " << quarterNumToString(i) << " ===" << endl;

        for (StudentClass sClass : gb.getClasses(i)) {
            cout << "" << sClass.getClassName() << " | Credits: " << sClass.getClassCredits();

            if (sClass.getLetterGrade() != "NR") {
                cout << ", Grade: " << sClass.getLetterGrade() << endl;
            } else {
                cout << " [IN-PROGRESS]" << endl;
            }
        }

        cout << endl;
    }
    //GPA

    //Calls GPA calculator function
    double cumulativeGPA = calculateTotalGPA(gb, 1);

    for (unsigned int i = 2; i < 5; ++i) {
        calculateTotalGPA(gb, i);
    }

    cout << "Overall Cumulative GPA: " << fixed << setprecision(2) << cumulativeGPA << endl;

    // CRITICAL: Clear buffer before the 'while' loop starts using getline
    //cin.ignore(1000, '\n');

    string classInput;

    while(classInput != "quit" && classInput != "q" && classInput != "Quit" && classInput != "Q"){

        cout << "What class would you like to look at? (\'quit\' to quit)" << endl << "> ";
        
        getline(cin, classInput);

        bool foundClass = false;
        for (unsigned int i = 1; i < 5; ++i) {
            for (StudentClass sClass : gb.getClasses(i)) {
                if (sClass.getClassName() == classInput) {
                    foundClass = true;

                    cout << endl << "= " << left << setfill('=') << setw(51) << (sClass.getClassName() + " ") << endl;
                    cout << "|               Name               | Weight | Grade |" << endl;

                    cout << "| " << left << setfill('-') << setw(33) << "ASSIGNMENTS" << right << "|"
                         << setfill('-') << setw(9) << "|" << setfill('-') << setw(8) << "|" << endl;

                    for (StudentClass::ContentInfo assignment : sClass.getAssignments("Assignments")) {
                        cout << "| " << left << setfill(' ') << setw(33) << assignment.contentName << "|"
                             << right << setfill(' ') << setw(7) << noshowpoint << static_cast<int>(assignment.contentWeight) << " | ";
                        
                        if (assignment.contentGrade != -1) {
                            cout << right << setfill(' ') << setw(5) << noshowpoint << static_cast<int>(assignment.contentGrade);
                        } else {
                            cout << setfill(' ') << setw(5) << "";
                        }

                        cout << " |" << endl;
                    }



                    cout << "| " << left << setfill('-') << setw(33) << "EXAMS" << right << "|"
                         << setfill('-') << setw(9) << "|" << setfill('-') << setw(8) << "|" << endl;

                    for (StudentClass::ContentInfo exam : sClass.getAssignments("Exams")) {
                        cout << "| " << left << setfill(' ') << setw(33) << exam.contentName << "|"
                             << right << setfill(' ') << setw(7) << noshowpoint << static_cast<int>(exam.contentWeight) << " | ";
                        
                        if (exam.contentGrade != -1) {
                            cout << right << setfill(' ') << setw(5) << noshowpoint << static_cast<int>(exam.contentGrade);
                        } else {
                            cout << setfill(' ') << setw(5) << "";
                        }

                        cout << " |" << endl;
                    }
                    cout << setfill('=') << setw(53) << "";

                    // Grade Calculator
                    double desiredGrade;

                    cout << "\nWhat grade are you aiming for in " << sClass.getClassName() << "? (e.g. 90) (-1 to exit)" << endl << "> ";
                    desiredGrade = getValidDouble();
                    cin.ignore();
                    while(desiredGrade > 0.0) {  
                        processGradeGoal(gb, i, sClass.getClassName(), desiredGrade);

                        cout << "\nWhat grade are you aiming for in " << sClass.getClassName() << "? (e.g. 90) (-1 to exit)" << endl << "> ";
                        desiredGrade = getValidDouble();
                        cin.ignore();
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