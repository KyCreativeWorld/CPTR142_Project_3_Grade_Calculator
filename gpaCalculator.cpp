#include <iostream>
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

    //Loop through each quarter
    for (int q = 1; q <= 4; ++q) {
        //Class vector for specific quarter
        vector<StudentClass> classes = gb.getClasses(q);

        for (StudentClass& course : classes) {
            int credits = course.getClassCredits();
            string grade = course.getLetterGrade();
            
            //GPA formula
            totalWeightedPoints += (letterToPoints(grade) * credits);
            totalCredits += credits;
        }
    }

    if (totalCredits == 0) return 0.0;
    
    //GPA Output
    return totalWeightedPoints / totalCredits;
}