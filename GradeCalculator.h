// GradeCalculator.h
#pragma once
#include <string>
#include "Gradebook.h"
#include "StudentClass.h"

// from chat becuse i am not familuir with maps and hw to work with them
double computeWeightedAverage(const std::map<std::string, StudentClass::ContentInfo>& content);

// Determines the minimum final exam grade needed to hit the desired score.
//
// Formula used from google:   desiredGrade = (assignmentWeightTotal * assignmentAvg)+ (examWeightTotal * examAvg) + (finalExamWeight * finalGrade)
//   Solving for finalGrade: finalGrade = (desiredGrade - assignmentContribution - examContribution)/ finalExamWeight
double calcRequiredFinalExamGrade(StudentClass& cls, double desiredGrade);

// finds the class, runs the calculation, prints results.
void processGradeGoal(Gradebook& gb, int quarterNum,
                      const std::string& className, double desiredGrade);