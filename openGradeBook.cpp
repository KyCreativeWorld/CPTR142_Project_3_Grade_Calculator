#include "openGradeBook.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

string trimWhitespace(string beforeStr) {
    string afterStr = beforeStr.erase(0, beforeStr.find_first_not_of(" \n"));
    afterStr = beforeStr.erase(beforeStr.find_last_not_of(" \n") + 1);
    
    return afterStr;
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
    } catch(std::invalid_argument& excp) {
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
    string curContentType;
    string curContentType2;
    int curContentTypeNum;

    int curLine = 0;

    string gbLine;

    while (getline(gradeBookFile, gbLine)) {
        ++curLine;

        if (gbLine.rfind("!!!", 0) == 0) { break; }

        try{
            if (gbLine.rfind("Year", 0) == 0) {
                gradebook.setYear(stoi(gbLine.substr(gbLine.find_first_of("0123456789"))));
            }
        } catch(std::invalid_argument& excp) {
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