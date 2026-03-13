#include "GradeCalculator.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//Attempt to update

double DEFAULT_GRADE = 87.0;

double computeWeightedAverage(const vector<StudentClass::ContentInfo>& content) {
    double weightedSum = 0.0;
    double totalWeight = 0.0;

    bool foundAGrade = false;
    
    for (const auto& info : content) {
        //Skip anything that hasn't been graded (-1)
        if (info.contentGrade >= 0.0) {
            foundAGrade = true;
            
            weightedSum += info.contentGrade * info.contentWeight;
            totalWeight += info.contentWeight;
        }
    }

    if (!foundAGrade) {
        return DEFAULT_GRADE;
    }
    
    if (totalWeight == 0.0) {
        return 0.0;
    }

    return weightedSum / totalWeight;
}

double calcRequiredFinalExamGrade(StudentClass& cls, double desiredGrade) {
    //Updated to return vector<ContentInfo>&
    vector<StudentClass::ContentInfo> exams = cls.getExams();
    vector<StudentClass::ContentInfo> assignments = cls.getAssignments("Assignments");
    
    double finalExamWeight = exams.back().contentWeight;

    if (finalExamWeight <= 0.0) {
        cout << "Error: no exam entry found to act as the 'Final'." << endl;
        return -1.0;
    }

    if (exams.back().contentGrade != -1) {
        return -2862.0;
    }

    //Averages
    double avgAssignmentsGrade = computeWeightedAverage(assignments);
    double avgExamsGrade = computeWeightedAverage(exams);
    double examWeight = 0.0;
    double assignmentWeight = 0.0;
    double totalWeight = 0.0;

    double alreadyEarned = 0.0;

    //Calculate totals for assignments
    for (const auto& info : assignments) {
        if (info.contentGrade >= 0.0) {
            alreadyEarned += (info.contentGrade * info.contentWeight);
        } else {
            alreadyEarned += (avgAssignmentsGrade * info.contentWeight);
        }

        totalWeight += info.contentWeight;
    }

    //Calculate totals for exams that ARE graded
    for (unsigned int i = 0; i < exams.size(); i++) {      
        if (i != exams.size() -1) {
            if (exams.at(i).contentGrade >= 0.0) {
                alreadyEarned += (exams.at(i).contentGrade * exams.at(i).contentWeight);
            } else {
                alreadyEarned += (avgExamsGrade* exams.at(i).contentWeight);
            }
        }

        totalWeight += exams.at(i).contentWeight; 
    }

    //Math: ((Desired * TotalWeightOfAssignments) - PointsAlreadyEarned) / WeightOfRemainingFinal
    double requiredFinal = ((desiredGrade * totalWeight) - alreadyEarned) / finalExamWeight;
    // cout << "(((" << desiredGrade << " * " << totalWeight << ") - " << alreadyEarned << ") / " << finalExamWeight << ")" << endl;

    return requiredFinal;
}

void processGradeGoal(Gradebook& gb, int quarterNum, const string& className, double desiredGrade) {
    vector<StudentClass>& classes = gb.getClasses(quarterNum);
    StudentClass* target = nullptr;

    for (int i = 0; i < classes.size(); i++) {
        if (classes[i].getClassName() == className) {
            target = &classes[i];
            break;
        }
    }

    if (target == nullptr) {
        cout << "Error: could not find class " << className << " in quarter " << quarterNum << endl;
        return;
    }

    double assignmentAvg = computeWeightedAverage(target->getAssignments("Assignments"));
    double examAvg       = computeWeightedAverage(target->getExams());
    double required      = calcRequiredFinalExamGrade(*target, desiredGrade);

    cout << "\n=== Grade Calculator Results ===" << endl;
    cout << "Class:                  " << target->getClassName() << endl;
    cout << "Current Assignment Avg: " << assignmentAvg          << "%" << endl;
    cout << "Current Exam Avg:       " << examAvg                << "%" << endl;
    cout << "Desired Grade:          " << desiredGrade           << "%" << endl;
    cout << "--------------------------------" << endl;

    if (required > 100.0) {
        cout << "Required Final Exam:    " << required << "%" << endl;
        cout << "Note: This goal is mathematically impossible without extra credit." << endl;
    } else if (required < -2861.9 && required > -2862.1) {
        cout << "Final Exam Grade:       " << target->getExams().back().contentGrade  << "% (FINAL ALREADY GRADED)" << endl;
    } else if (required <= 0.0) {
        cout << "Required Final Exam:    0% (Goal already met!)" << endl;
    } else {
        cout << "Required Final Exam:    " << required << "%" << endl;
    }

    if (target->getAssignments().front().contentGrade <= 0.0 && target->getExams().front().contentGrade <= 0.0) {  
        cout << "Note: No assignments or exams have been graded yet, so a default avg of " << DEFAULT_GRADE << "% has been used." << endl;  
    } else if (target->getAssignments().front().contentGrade <= 0.0) {
        cout << "Note: No assignments have been graded yet, so a default avg of " << DEFAULT_GRADE <<"% has been used." << endl;
    } else if (target->getExams().front().contentGrade <= 0.0) {
        cout << "Note: No exams have been graded yet, so a default avg of " << DEFAULT_GRADE << "% has been used." << endl;
    }
    
    cout << "================================" << endl;
}