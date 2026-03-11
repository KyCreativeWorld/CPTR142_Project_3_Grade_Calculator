#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Gradebook.h"
#include "StudentClass.h"
using namespace std;


double calculateTotalGPA(Gradebook& gb) {
    double totalWeightedPoints = 0.0;
    int totalCredits = 0;

    for (int q = 1; q <= 4; ++q) {
        //Specific quarter
        double quarterPoints = 0.0;
        int quarterCredits = 0;

        vector<StudentClass>& classes = gb.getClasses(q);

        for (StudentClass& course : classes) {
            //Only calculate for courses with grades
            if (course.getLetterGrade() != "NR" && course.getLetterGrade() != "") {
                int credits = course.getClassCredits();
                double gradePoints = course.getNumberGrade();
                
                //Add to specific quarter bucket
                quarterPoints += (gradePoints * credits);
                quarterCredits += credits;
            }
        }

        //Output for current quarter
        if (quarterCredits > 0) {
            cout << "Quarter " << q << " GPA: " << fixed << setprecision(2) 
                 << (quarterPoints / quarterCredits) << endl;
        }

        //Combine quarter totals
        totalWeightedPoints += quarterPoints;
        totalCredits += quarterCredits;
    }

    if (totalCredits == 0) return 0.0;
    
    //Return overall cumulative GPA
    return totalWeightedPoints / totalCredits;
}