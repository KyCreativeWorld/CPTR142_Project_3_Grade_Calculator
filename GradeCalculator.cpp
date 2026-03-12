#include "GradeCalculator.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//Attempt to update

double computeWeightedAverage(const vector<StudentClass::ContentInfo>& content) {
    double weightedSum = 0.0;
    double totalWeight = 0.0;

    for (const auto& info : content) {
        //Skip anything that hasn't been graded (-1)
        if (info.contentGrade >= 0.0) {
            weightedSum += info.contentGrade * info.contentWeight;
            totalWeight += info.contentWeight;
        }
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
        cout << "Error: no ungraded exam entry found to act as the 'Final'." << endl;
        return -1.0;
    }

    //Averages
    double assignmentAvg = computeWeightedAverage(assignments);
    double gradedExamAvg = 0;
    double gradedExamWeight = 0.0;
    double assignmentWeight = 0.0;
    double totalWeight = 0.0;

    //Calculate totals for assignments
    for (const auto& info : assignments) {
        if (info.contentGrade >= 0.0) {
            assignmentWeight += info.contentWeight;
        }
        totalWeight += info.contentWeight;
    }

    //Calculate totals for exams that ARE graded
    for (const auto& info : exams) {
        if (info.contentGrade >= 0.0) {
            gradedExamAvg += (info.contentGrade * info.contentWeight);
            gradedExamWeight += info.contentWeight;
        }
        totalWeight += info.contentWeight;
    }

    // weighted average for exams already taken
    if (gradedExamWeight > 0.0) {
        gradedExamAvg = gradedExamAvg / gradedExamWeight;
    }

    //Math: (Desired - PointsAlreadyEarned) / WeightOfRemainingFinal
    double alreadyEarned = (assignmentWeight * assignmentAvg) + (gradedExamWeight * gradedExamAvg);
    double requiredFinal = ((desiredGrade * totalWeight) - alreadyEarned) / finalExamWeight;

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
    cout << "Desired Final Grade:    " << desiredGrade           << "%" << endl;
    cout << "--------------------------------" << endl;

    if (required > 100.0) {
        cout << "Required Final Exam:    " << required << "%" << endl;
        cout << "Note: This goal is mathematically impossible without extra credit." << endl;
    } else if (required <= 0.0) {
        cout << "Required Final Exam:    0% (Goal already met!)" << endl;
    } else {
        cout << "Required Final Exam:    " << required << "%" << endl;
    }
    cout << "================================" << endl;
}