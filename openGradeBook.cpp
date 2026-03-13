#include "openGradeBook.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

// Removes whitespace at beginning and end
string trimWhitespace(string beforeStr) {
    string afterStr = beforeStr.erase(0, beforeStr.find_first_not_of(" \n"));
    afterStr = beforeStr.erase(beforeStr.find_last_not_of(" \n") + 1);
    
    return afterStr; // Return trimmed string
}

// Creates a StudentClass object from a string
StudentClass readClass(string gbLine) {
    string classLine = trimWhitespace(gbLine.substr(2)); // Trims the prefix


    // Creates the StudentClass object with the name at the start of the line
    StudentClass tempStudentClass(classLine.substr(0, classLine.find_first_of(",")));

    classLine = classLine.substr(classLine.find_first_of(",") + 1); // Trims the name from the line

    try {
        // Set the classes credits
        tempStudentClass.setClassCredits(stoi(classLine.substr(0, classLine.find_first_of("Cc,"))));
    } catch(std::invalid_argument& excp) { // If it fails
        tempStudentClass.setClassCredits(4); // Set it to a default value

        // Error code for testing
        // cout << "<2> !!ERROR!! failed stoi" << endl;
    }

    classLine = classLine.substr(classLine.find_first_of(",") + 1); // Trim the credits from line

    // Set the letter grade of the class to the trimmed string at end of the line
    tempStudentClass.setLetterGrade(trimWhitespace(classLine));

    // Print statement for testing
    // cout << "<tempStudentClass> Name: " << tempStudentClass.getClassName()
    //      << " Letter Grade: " << tempStudentClass.getLetterGrade()
    //      << " Point Grade: " << tempStudentClass.getNumberGrade()
    //      << " Class Credits: " << tempStudentClass.getClassCredits() << endl;

    return tempStudentClass; // Return the clas
}

// Opens a gradebook file and creates a Gradebook object filled with classes that come from the file
Gradebook openGradeBook(string fileName) {
    ifstream gradeBookFile(fileName); // Open the file

    Gradebook gradebook; // Create the Gradebook object

    if (!gradeBookFile) { // Makes sure file was found
        cout << "Failed to open " << fileName << endl;
        return gradebook; // Print an error and return an empty gradebook
    }

    int curQuarter = 1; // Current quarter
    char curGradeType; // Current grade type
    string curClass; // Current class name
    string curContentType; // Current content type (assignment/exam)

    int curLine = 0; // For error testing

    string gbLine; // The string for the current line

    while (getline(gradeBookFile, gbLine)) { // While there are lines to be read
        ++curLine; // Increment the line number (for error testing)

        if (gbLine.rfind("!!!", 0) == 0) { break; } // If the line starts with the break code

        try{
            if (gbLine.rfind("Year", 0) == 0) { // If the line starts with year
                gradebook.setYear(stoi(gbLine.substr(gbLine.find_first_of("0123456789")))); // Set the year
            }
        } catch(std::invalid_argument& excp) { // If that fails
            gradebook.setYear(2026); // Set the year to a default value

            // Error code for testing
            // cout << "<1> !!ERROR!! failed stoi on line " << curLine << endl;
        }

        // If the line starts with a quarter name, set the current quarter to that quarter
        if (gbLine.rfind("Fall", 0) == 0) { curQuarter = 1; }
        if (gbLine.rfind("Winter", 0) == 0) { curQuarter = 2; }
        if (gbLine.rfind("Spring", 0) == 0) { curQuarter = 3; }
        if (gbLine.rfind("Summer", 0) == 0) { curQuarter = 4; }

        // If the line starts with the class code
        if (gbLine.rfind("<>", 0) == 0) {
            // Read the class into the gradebook's classes list for the quarter
            gradebook.addClass(readClass(gbLine), curQuarter);

            // Set the current class name to this class
            curClass = gradebook.getClasses(curQuarter).back().getClassName();
        }

        // If the line start with the 
        if (gbLine.rfind("**", 0) == 0) {
            int substrStart = gbLine.find_last_of(":") + 1;
            vector<int> tempGWeights;

            unsigned int i = 0;
            int substrEnd = gbLine.find_first_of(",");
            while (substrEnd < gbLine.size() - 1 && i < 15) {
                ++i;
                try {
                    tempGWeights.push_back(stoi(gbLine.substr(substrStart, substrEnd - substrStart)));
                } catch (...) {
                    // Error code for testing
                    // cout << "Failed stoi for: [" << gbLine.substr(substrStart, substrEnd - substrStart) << "]" << endl;
                }
                substrStart = substrEnd + 1;
                substrEnd += gbLine.substr(substrEnd + 1).find_first_of(",") + 1;

                if (tempGWeights.back() == 0) {
                    break;
                }
            }

            gradebook.getClasses(curQuarter).back().setGradeWeight(tempGWeights);
        }

        if (gbLine.rfind("--", 0) == 0) {
            curContentType = trimWhitespace(gbLine.substr(gbLine.find_last_of("-") + 1));
        }
        if (gbLine.rfind("/\\", 0) == 0) {
            int substrStart = gbLine.find_last_of("-/\\") + 1;
            int substrEnd = gbLine.find_first_of(",");
            string contentItem = trimWhitespace(gbLine.substr(substrStart, substrEnd - substrStart));
            double contentWeight = 0;
            double contentGrade = -1;
            string tempContentLabel;

            stringstream contentLine(gbLine.substr(gbLine.find_first_of(",") + 1));

            contentLine >> tempContentLabel >> contentWeight;

            if (gbLine.length() > 0) {
                contentLine.ignore();
                contentLine >> tempContentLabel >> contentGrade;
            }

            gradebook.getClasses(curQuarter).back().addClassContent(contentItem, contentWeight, contentGrade, curContentType);
        }



    }
    gradeBookFile.close();
    return gradebook;
}