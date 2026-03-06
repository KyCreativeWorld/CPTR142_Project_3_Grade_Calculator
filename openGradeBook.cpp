#include "openGradeBook.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cctype>

using namespace std;

string trimWhitespace(string beforeStr) {
    return beforeStr.substr(beforeStr.find_first_not_of(" \t\n"), beforeStr.find_last_not_of(" \t\n"));
}

void readToDos(string gbLine, string asgnOrExam) {

}

StudentClass readClass(string gbLine) {
    string classLine = trimWhitespace(gbLine.substr(2));

    // cout << "<1> prevClassLine: " << prevClassLine << endl;

    StudentClass tempStudentClass(classLine.substr(0, classLine.find_first_of(",")));
    // cout << "tempStudentClass class name: " << prevClassLine.substr(0, prevClassLine.find_first_of(",")) << endl;

    classLine = classLine.substr(classLine.find_first_of(",") + 1);
    // cout << "<2> prevClassLine: " << prevClassLine << endl;

    try {
        tempStudentClass.setClassCredits(stoi(classLine.substr(0, classLine.find_first_of("Cc,"))));
    } catch(std::invalid_argument excp) {
        cout << "<2> !!ERROR!! failed stoi" << endl;
    }

    classLine = classLine.substr(classLine.find_first_of(",") + 1);

    tempStudentClass.setLetterGrade(trimWhitespace(classLine));

    // cout << "<tempStudentClass> Name: " << tempStudentClass.getClassName()
    //      << " Letter Grade: " << tempStudentClass.getLetterGrade()
    //      << " Point Grade: " << tempStudentClass.getNumberGrade()
    //      << " Class Credits: " << tempStudentClass.getClassCredits() << endl;

    return tempStudentClass;
}

Gradebook openGradeBook(string fileName) {
    ifstream gradeBookFile(fileName);

    Gradebook gradebook;

    if (!gradeBookFile) { // Makes sure file was found
        cout << "Failed to open " << fileName << endl;
        return gradebook;
    }

    int curQuarter = 1;
    char curGradeType;
    string curClass;

    int curLine = 0;

    string gbLine;

    while (getline(gradeBookFile, gbLine)) {
        ++curLine;

        if (gbLine.rfind("!!!", 0) == 0) { break; }

        try{
            if (gbLine.rfind("Year", 0) == 0) {
                gradebook.setYear(stoi(gbLine.substr(gbLine.find_first_of("0123456789"))));
            }
        } catch(std::invalid_argument excp) {
            cout << "<1> !!ERROR!! failed stoi on line " << curLine << endl;
        }

        if (gbLine.rfind("Fall", 0) == 0) { curQuarter = 1; }
        if (gbLine.rfind("Winter", 0) == 0) { curQuarter = 2; }
        if (gbLine.rfind("Spring", 0) == 0) { curQuarter = 3; }
        if (gbLine.rfind("Summer", 0) == 0) { curQuarter = 4; }

        if (gbLine.rfind("<>", 0) == 0) {
            gradebook.addClass(readClass(gbLine), curQuarter);
            curClass = gradebook.getClasses(curQuarter).back().getClassName();
        }
        if (gbLine.rfind("--", 0) == 0) {
            if (trimWhitespace(gbLine.substr(gbLine.find_last_of("-") + 1)) == "Assignments") {

            }
        }



    }

    return gradebook;
}