#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Gradebook.h"
#include "StudentClass.h"
#include "quarterNumToString.h"

using namespace std;

// Calculates and returns cumulative GPA and prints quarter GPA if that quarter has been graded already
double calculateTotalGPA(Gradebook& gb, int selectedQuarter) {
    double totalWeightedPoints = 0.0;
    int totalCredits = 0;
    
    double targetQuarterPoints = 0.0;
    int targetQuarterCredits = 0;

    for (int q = 1; q <= 4; ++q) { // For every quarter
        vector<StudentClass>& classes = gb.getClasses(q); // This quarter's classes

        for (StudentClass& course : classes) { // For every class this quarter
            // If it has a grade
            if (course.getLetterGrade() != "NR" && course.getLetterGrade() != "") {
                int credits = course.getClassCredits();
                double gradePoints = course.getNumberGrade();
                
                double weighted = gradePoints * credits;

                // Saves asked for quarter separately
                if (q == selectedQuarter) {
                    targetQuarterPoints += weighted;
                    targetQuarterCredits += credits;
                }

                // Adds everything to cumulative
                totalWeightedPoints += weighted;
                totalCredits += credits;
            }
        }
    }

    // Output the specific quarter requested
    if (targetQuarterCredits > 0) {
        cout << quarterNumToString(selectedQuarter) << " GPA: " << fixed 
             << setprecision(2) << (targetQuarterPoints / targetQuarterCredits) << endl;
    }

    if (totalCredits == 0) return 0.0; // If there are no credits (dividing by 0), outputs 0.0
    
    double cumulativeGPA = totalWeightedPoints / totalCredits;
    
    // Output the cumulative GPA
    return cumulativeGPA;
}