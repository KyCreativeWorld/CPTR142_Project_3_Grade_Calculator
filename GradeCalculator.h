#pragma once
#include <string>
#include "Gradebook.h"
#include "StudentClass.h"


double computeWeightedAverage(const std::vector<StudentClass::ContentInfo>& content);
 
// Determines the minimum final exam grade needed to hit the desired score.
double calcRequiredFinalExamGrade(StudentClass& cls, double desiredGrade);
 
// finds the class, runs the calculation, prints results.
void processGradeGoal(Gradebook& gb, int quarterNum,
                      const std::string& className, double desiredGrade);