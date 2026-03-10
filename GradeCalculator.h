#ifndef GRADECALCULATOR_H
#define GRADECALCULATOR_H

class GradeCalculator {
private:
    double assignmentAvg;
    double examAvg;
    double assignmentWeight;
    double examWeight;

public:
    GradeCalculator(double aAvg, double eAvg, double aWeight, double eWeight);

    double requiredExamScore(double targetFinal);
    double requiredAssignmentScore(double targetFinal);
    double currentFinalGrade();
};

#endif
