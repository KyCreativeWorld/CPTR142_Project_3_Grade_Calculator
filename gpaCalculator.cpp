#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Gradebook.h"
#include "StudentClass.h"
#include "quarterNumToString.h"

using namespace std;

//Still trying to update
//Selected quarter
double calculateTotalGPA(Gradebook& gb, int selectedQuarter) {
    double totalWeightedPoints = 0.0;
    int totalCredits = 0;
    
    double targetQuarterPoints = 0.0;
    int targetQuarterCredits = 0;

    for (int q = 1; q <= 4; ++q) {
        vector<StudentClass>& classes = gb.getClasses(q);

        for (StudentClass& course : classes) {
            if (course.getLetterGrade() != "NR" && course.getLetterGrade() != "") {
                int credits = course.getClassCredits();
                double gradePoints = course.getNumberGrade();
                
                double weighted = gradePoints * credits;

                //Saves asked for quarter separately
                if (q == selectedQuarter) {
                    targetQuarterPoints += weighted;
                    targetQuarterCredits += credits;
                }

                //Add everything to cumulative
                totalWeightedPoints += weighted;
                totalCredits += credits;
            }
        }
    }

    //Output the specific quarter requested
    // cout << "\n--- " << quarterNumToString(selectedQuarter) << " Quarter Results ---" << endl;
    if (targetQuarterCredits > 0) {
        // cout << "Quarter GPA: " << fixed << setprecision(2) 
        //      << (targetQuarterPoints / targetQuarterCredits) << endl;
        cout << quarterNumToString(selectedQuarter) << " GPA: " << fixed 
             << setprecision(2) << (targetQuarterPoints / targetQuarterCredits) << endl;
    }
    // } else {
    //     cout << "No grades found for this quarter." << endl;
    // }

    //Output the cumulative GPA
    if (totalCredits == 0) return 0.0;
    
    double cumulativeGPA = totalWeightedPoints / totalCredits;
    //cout << "Overall Cumulative GPA: " << fixed << setprecision(2) << cumulativeGPA << endl;
    
    return cumulativeGPA;
}