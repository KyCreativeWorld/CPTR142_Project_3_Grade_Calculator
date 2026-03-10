#include "GradeCalculator.h"

GradeCalculator::GradeCalculator(double aAvg, double eAvg, double aWeight, double eWeight) {
    assignmentAvg = aAvg;
    examAvg = eAvg;
    assignmentWeight = aWeight;
    examWeight = eWeight;
}

double GradeCalculator::requiredExamScore(double targetFinal) {
    return (targetFinal - (assignmentAvg *assignmentWeight)) / examWeight;
}

double GradeCalculator::requiredAssignmentScore(double targetFinal) {
    return (targetFinal - (examAvg * examWeight))/ assignmentWeight;
}

double GradeCalculator::currentFinalGrade() {
    return (assignmentAvg * assignmentWeight) +(examAvg * examWeight);
}
