#include "GradeCalculator.h"
#include <iostream>

double computeWeightedAverage(const std::map<std::string, StudentClass::ContentInfo>& content) {
    double weightedSum = 0.0;
    double totalWeight = 0.0;

    std::map<std::string, StudentClass::ContentInfo>::const_iterator it;
    for (it = content.begin(); it != content.end(); it++) {
        // skip anything that hasn't been graded yet
        if (it->second.contentGrade >= 0.0) {
            weightedSum += it->second.contentGrade * it->second.contentWeight;
            totalWeight += it->second.contentWeight;
        }
    }

    if (totalWeight == 0.0) {
        return 0.0;
    }

    return weightedSum / totalWeight;
}

double calcRequiredFinalExamGrade(StudentClass& cls, double desiredGrade) {
    std::map<std::string, StudentClass::ContentInfo> exams       = cls.getExams();
    std::map<std::string, StudentClass::ContentInfo> assignments = cls.getAssignments();

    // look through exams to find the final
    double finalExamWeight = 0.0;
    std::map<std::string, StudentClass::ContentInfo>::iterator it;
    for (it = exams.begin(); it != exams.end(); it++) {
        if (it->second.contentGrade < 0.0) {
            finalExamWeight = it->second.contentWeight;
            break;
        }
    }

    if (finalExamWeight <= 0.0) {
        std::cout << "Error: no final exam entry found." << std::endl;
        std::cout << "Use addClassContent(\"Final Exam\", weight, -1.0, \"Exams\") to add it." << std::endl;
        return -1.0;
    }

    // get the average for all graded assignments
    double assignmentAvg    = computeWeightedAverage(assignments);
    double assignmentWeight = 0.0;
    for (it = assignments.begin(); it != assignments.end(); it++) {
        if (it->second.contentGrade >= 0.0) {
            assignmentWeight += it->second.contentWeight;
        }
    }

    // get the average for all graded exams
    double gradedExamAvg    = 0.0;
    double gradedExamWeight = 0.0;
    for (it = exams.begin(); it != exams.end(); it++) {
        if (it->second.contentGrade >= 0.0) {
            gradedExamAvg    += it->second.contentGrade * it->second.contentWeight;
            gradedExamWeight += it->second.contentWeight;
        }
    }

    if (gradedExamWeight > 0.0) {
        gradedExamAvg = gradedExamAvg / gradedExamWeight;
    }

    // figure out how many points are already earned
    double alreadyEarned = (assignmentWeight * assignmentAvg) + (gradedExamWeight * gradedExamAvg);

    // solve for the final exam grade needed
    double requiredFinal = (desiredGrade - alreadyEarned) / finalExamWeight;

    return requiredFinal;
}

void processGradeGoal(Gradebook& gb, int quarterNum, std::string className, double desiredGrade) {
    // search the classes in the given quarter for a matching class name
    std::vector<StudentClass>& classes = gb.getClasses(quarterNum);
    StudentClass* target = NULL;

    for (int i = 0; i < classes.size(); i++) {
        if (classes[i].getClassName() == className) {
            target = &classes[i];
            break;
        }
    }

    if (target == NULL) {
        std::cout << "Error: could not find class " << className << " in quarter " << quarterNum << std::endl;
        return;
    }

    std::map<std::string, StudentClass::ContentInfo> targetAssignments = target->getAssignments();
    std::map<std::string, StudentClass::ContentInfo> targetExams       = target->getExams();

    double assignmentAvg = computeWeightedAverage(targetAssignments);
    double examAvg       = computeWeightedAverage(targetExams);
    double required      = calcRequiredFinalExamGrade(*target, desiredGrade);

    std::cout << "\n=== Grade Calculator Results ===" << std::endl;
    std::cout << "Class:                  " << target->getClassName() << std::endl;
    std::cout << "Current Assignment Avg: " << assignmentAvg          << "%" << std::endl;
    std::cout << "Current Exam Avg:       " << examAvg                << "%" << std::endl;
    std::cout << "Desired Final Grade:    " << desiredGrade           << "%" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    if (required > 100.0) {
        std::cout << "Required Final Exam:    " << required << "%" << std::endl;
        std::cout << "Unfortunately that grade is not achievable." << std::endl;
    } else if (required < 0.0) {
        std::cout << "Required Final Exam:    You already hit your goal!" << std::endl;
    } else {
        std::cout << "Required Final Exam:    " << required << "%" << std::endl;
    }

    std::cout << "================================" << std::endl;
}