#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Gradebook.h"
#include "StudentClass.h"
using namespace std;

//Grade values
double letterToPoints(string letter) {
    if (letter == "A") return 4.0;
    if (letter == "A-") return 3.7;
    if (letter == "B+") return 3.3;
    if (letter == "B") return 3.0;
    if (letter == "B-") return 2.7;
    if (letter == "C+") return 2.3;
    if (letter == "C") return 2.0;
    if (letter == "C-") return 1.7;
    if (letter == "D+") return 1.3;
    if (letter == "D") return 1.0;
    return 0.0; //F or unknown
}

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
                double gradePoints = letterToPoints(course.getLetterGrade());
                
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