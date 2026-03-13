#include "openGradeBook.h"
#include "quarterNumToString.h"
#include "gpaCalculator.h"
#include "GradeCalculator.h"
#include <iostream>
#include <iomanip>
#include <typeinfo>

using namespace std;

// Returns a double from input. Returns -1.0 if the cin input isn't a double.
double getValidDouble() {
    double d;

    if (cin >> d) {
        cin.clear();
        cin.ignore(10000, '\n');
        
        return d;
    } else {
        cin.clear();
        cin.ignore(10000, '\n');

        return -1.0;
    }
}

// Main program
int main() {
    string gbName; // File name

    // Titlex
    cout << "==----------------------------==" << endl;
    cout << "| Welcome to Grade Calculator! |" << endl;
    cout << "==----------------------------==" << endl << endl;
    
    cout << "Input gradebook file name: ";

    getline(cin, gbName); // Gets file name from input

    Gradebook gb = openGradeBook(gbName); // Opens the file and puts info in gb

    cout << endl;
    for (unsigned int i = 1; i < 5; ++i) { // For every quarter
        if (gb.getClasses(i).size() < 1) { break; } // If there are no classes, break.

        // Quarter title
        cout << "=== " << quarterNumToString(i) << " ===" << endl;

        for (StudentClass sClass : gb.getClasses(i)) { // For every class
            // Print class name and credits
            cout << "" << sClass.getClassName() << " | Credits: " << sClass.getClassCredits();

            if (sClass.getLetterGrade() != "NR") { // If the class has a grade
                cout << ", Grade: " << sClass.getLetterGrade() << endl; // Print the grade
            } else { // If the class doesnt have a grade
                cout << " [IN-PROGRESS]" << endl; // Print [IN-PROGRESS]
            }
        }

        cout << endl;
    }
    //GPA

    // Calculates cumulative GPA and prints fall GPA (if the classes are graded)
    double cumulativeGPA = calculateTotalGPA(gb, 1);

    for (unsigned int i = 2; i < 5; ++i) { // For the rest of the quarters
        calculateTotalGPA(gb, i); // Print that quarter's GPA (if the classes are graded)
    }

    // Prints the cumulative GPA
    cout << "Overall Cumulative GPA: " << fixed << setprecision(2) << cumulativeGPA << endl;



    string classInput;

    // Loop to get the specific class user wants to look at
    while(classInput != "quit" && classInput != "q" && classInput != "Quit" && classInput != "Q"){

        cout << "What class would you like to look at? (\'quit\' to quit)" << endl << "> ";
        
        getline(cin, classInput); // Gets the user's class choice

        bool foundClass = false; // Bool for if it found the input class
        for (unsigned int i = 1; i < 5; ++i) { // For every quarter
            for (StudentClass sClass : gb.getClasses(i)) { // For every class in that quarter
                if (sClass.getClassName() == classInput) { // If this class is the input class
                    foundClass = true; // Found the class

                    // Title
                    cout << endl << "= " << left << setfill('=') << setw(51) << (sClass.getClassName() + " ") << endl;
                    cout << "|               Name               | Weight | Grade |" << endl;

                    // ASSIGNMENTS title
                    cout << "| " << left << setfill('-') << setw(33) << "ASSIGNMENTS" << right << "|"
                         << setfill('-') << setw(9) << "|" << setfill('-') << setw(8) << "|" << endl;

                    // For each assignment in this class
                    for (StudentClass::ContentInfo assignment : sClass.getAssignments("Assignments")) {
                        // Print the assignment and its weight
                        cout << "| " << left << setfill(' ') << setw(33) << assignment.contentName << "|"
                             << right << setfill(' ') << setw(7) << noshowpoint << static_cast<int>(assignment.contentWeight) << " | ";
                        
                        if (assignment.contentGrade != -1) { // If it has been graded
                            // Print the grade
                            cout << right << setfill(' ') << setw(5) << noshowpoint << static_cast<int>(assignment.contentGrade);
                        } else { // If it hasn't been graded
                            cout << setfill(' ') << setw(5) << ""; // Print blank space
                        }

                        cout << " |" << endl;
                    }



                    // EXAMS title
                    cout << "| " << left << setfill('-') << setw(33) << "EXAMS" << right << "|"
                         << setfill('-') << setw(9) << "|" << setfill('-') << setw(8) << "|" << endl;

                    // For each exam in this class
                    for (StudentClass::ContentInfo exam : sClass.getAssignments("Exams")) {
                        // Print the exam and its weight
                        cout << "| " << left << setfill(' ') << setw(33) << exam.contentName << "|"
                             << right << setfill(' ') << setw(7) << noshowpoint << static_cast<int>(exam.contentWeight) << " | ";
                        
                        if (exam.contentGrade != -1) { // If it has been graded
                            // Print the grade
                            cout << right << setfill(' ') << setw(5) << noshowpoint << static_cast<int>(exam.contentGrade);
                        } else { // If it hasn't been graded
                            cout << setfill(' ') << setw(5) << ""; // Print blank space
                        }

                        cout << " |" << endl;
                    }
                    cout << setfill('=') << setw(53) << ""; // Bottom line

                    // Grade Calculator
                    double desiredGrade;

                    cout << "\nWhat grade are you aiming for in " << sClass.getClassName() << "? (e.g. 90) (-1 to exit)" << endl << "> ";
                    desiredGrade = getValidDouble(); // Gets a double value from input
                    //cin.ignore();
                    while(desiredGrade > 0.0) { // While that value is positve
                        // Calculate and print the required final grade to get the desired grade
                        processGradeGoal(gb, i, sClass.getClassName(), desiredGrade);

                        cout << "\nWhat grade are you aiming for in " << sClass.getClassName() << "? (e.g. 90) (-1 to exit)" << endl << "> ";
                        desiredGrade = getValidDouble(); // Gets a double value from input
                        //cin.ignore(1000);
                    }


                }
            }
        }

        // If the input class wasn't found
        if (!foundClass && classInput != "quit" && classInput != "q" && classInput != "Quit" && classInput != "Q") {
            cout << "Couldn't find \"" << classInput << "\"" << endl; // Print error
        }

    }
   
    return 0;
}