#include "GradeCalculator.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Default grade if none is given
double DEFAULT_GRADE = 87.0;

// Returns a class's assignment or exam weighted grade
double computeWeightedAverage(const vector<StudentClass::ContentInfo>& content) {
    double weightedSum = 0.0;
    double totalWeight = 0.0;

    bool foundAGrade = false; // Have you found a grade?
    
    for (const auto& info : content) { // For each assignment/exam
        // Skip anything that hasn't been graded (-1)
        if (info.contentGrade >= 0.0) {
            foundAGrade = true;
            
            weightedSum += info.contentGrade * info.contentWeight; // Add weighted grade to sum
            totalWeight += info.contentWeight; // Add weight to total weight
        }
    }

    if (!foundAGrade) { // If no assignments/exams have been graded
        return DEFAULT_GRADE; // Return the default grade
    }
    
    if (totalWeight >= -0.01 && totalWeight <= 0.01) { // If weight is 0.0 (dividing by 0), then output 0.0
        return 0.0;
    }

    return weightedSum / totalWeight; // Returns the weighted grade
}

// Calculates what you need to get on the final to achieve your desired grade
double calcRequiredFinalExamGrade(StudentClass& cls, double desiredGrade) {
    vector<StudentClass::ContentInfo> exams = cls.getExams(); // Gets the exams for this class
    vector<StudentClass::ContentInfo> assignments = cls.getAssignments(); // Gets the assignments for this class
    
    double finalExamWeight = exams.back().contentWeight; // Gets the weight of the last exam (final)

    if (finalExamWeight <= 0.0) { // If the final doesn't have a weight
        cout << "Error: no exam entry found to act as the 'Final'." << endl;
        return -1.0; // Return an error
    }

    if (exams.back().contentGrade != -1) { // If the final is already graded
        return -2862.0; // Return an error value
    }

    //Averages
    double avgAssignmentsGrade = computeWeightedAverage(assignments); // Current average assignments grade
    double avgExamsGrade = computeWeightedAverage(exams); // Current average exams grade
    double examWeight = 0.0;
    double assignmentWeight = 0.0;
    double totalWeight = 0.0;

    double alreadyEarned = 0.0;

    // Calculate totals for assignments
    for (const auto& info : assignments) { // For all assignments
        if (info.contentGrade >= 0.0) { // If the assignment has been graded
            alreadyEarned += (info.contentGrade * info.contentWeight); // Add its grade to total
        } else { // If the assignment hasn't been graded
            alreadyEarned += (avgAssignmentsGrade * info.contentWeight); // Add the assignment average grade to total
        }

        totalWeight += info.contentWeight; // Add the weight to the total weight
    }

    // Calculate totals for exams
    for (unsigned int i = 0; i < exams.size(); i++) { // For all exams   
        if (i != exams.size() -1) { // If the exam isn't the final
            if (exams.at(i).contentGrade >= 0.0) { // If the exam has been graded
                alreadyEarned += (exams.at(i).contentGrade * exams.at(i).contentWeight); // Add its grade to total
            } else { // If the exam hasn't been graded
                alreadyEarned += (avgExamsGrade* exams.at(i).contentWeight); // Add the exam average grade to total
            }
        }

        totalWeight += exams.at(i).contentWeight; // Add the weight to the total weight
    }

    // Calculates the minimum grade you need to get on the final to achieve your desired grade
    // Math: ((Desired * TotalWeightOfAssignments) - PointsAlreadyEarned) / WeightOfRemainingFinal
    double requiredFinal = ((desiredGrade * totalWeight) - alreadyEarned) / finalExamWeight;

    // Print statement for testing
    // cout << "(((" << desiredGrade << " * " << totalWeight << ") - " << alreadyEarned << ") / " << finalExamWeight << ")" << endl;

    return requiredFinal; // Return the required final grade value
}

// Prints the calculator results
void processGradeGoal(Gradebook& gb, int quarterNum, const string& className, double desiredGrade) {
    vector<StudentClass>& classes = gb.getClasses(quarterNum);
    StudentClass* target = nullptr;

    for (int i = 0; i < classes.size(); i++) { // For every class
        if (classes[i].getClassName() == className) { // If this class is the selected class
            target = &classes[i]; // Set this class to be the target
            break;
        }
    }

    if (target == nullptr) { // If the class wasn't found
        // Print an error
        cout << "Error: could not find class " << className << " in quarter " << quarterNum << endl;
        return; // Break
    }

    double assignmentAvg = computeWeightedAverage(target->getAssignments()); // Calculate the average assignment grade
    double examAvg       = computeWeightedAverage(target->getExams()); // Calculate the average exam grade
    double required      = calcRequiredFinalExamGrade(*target, desiredGrade); // Calculate the required final grade

    // Print the information table
    cout << "\n=== Grade Calculator Results ===" << endl;
    cout << "Class:                  " << target->getClassName() << endl;
    cout << "Current Assignment Avg: " << assignmentAvg          << "%" << endl;
    cout << "Current Exam Avg:       " << examAvg                << "%" << endl;
    cout << "Desired Grade:          " << desiredGrade           << "%" << endl;
    cout << "--------------------------------" << endl;

    if (required > 100.0) { // If the required grade is more than 100%
        cout << "Required Final Exam:    " << required << "%" << endl;
        cout << "Note: This goal is mathematically impossible without extra credit." << endl; // Add a note
    } else if (required < -2861.9 && required > -2862.1) { // If the required grade is the error code
        // Print that the final has already been graded
        cout << "Final Exam Grade:       " << target->getExams().back().contentGrade  << "% (FINAL ALREADY GRADED)" << endl;
    } else if (required <= 0.0) { // If the required final grade is less than 0
        // Print that you've already achieved that grade
        cout << "Required Final Exam:    0% (Goal already met!)" << endl;
    } else { // If the required final grade is more than 0 but less than 100
        cout << "Required Final Exam:    " << required << "%" << endl; // Print the required final grade
    }

    // Print notes if no assignments and/or exams have been graded yet
    if (target->getAssignments().front().contentGrade <= 0.0 && target->getExams().front().contentGrade <= 0.0) {  
        cout << "Note: No assignments or exams have been graded yet, so a default avg of " << DEFAULT_GRADE << "% has been used." << endl;  
    } else if (target->getAssignments().front().contentGrade <= 0.0) {
        cout << "Note: No assignments have been graded yet, so a default avg of " << DEFAULT_GRADE <<"% has been used." << endl;
    } else if (target->getExams().front().contentGrade <= 0.0) {
        cout << "Note: No exams have been graded yet, so a default avg of " << DEFAULT_GRADE << "% has been used." << endl;
    }
    
    cout << "================================" << endl;
}