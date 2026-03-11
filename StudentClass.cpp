#include "StudentClass.h"

StudentClass::StudentClass(std::string className) {
    this->className = className;

    gradeWeights = {93, 90, 87, 83, 80, 77, 73, 70, 67, 63, 60, 0};
}

void StudentClass::setGradeWeight(std::string letterGrade, int newGradeWeight) {
    if (letterGrade == "A") { gradeWeights.at(0) = newGradeWeight; }
    if (letterGrade == "A-") { gradeWeights.at(1) = newGradeWeight; }
    if (letterGrade == "B+") { gradeWeights.at(2) = newGradeWeight; }
    if (letterGrade == "B") { gradeWeights.at(3) = newGradeWeight; }
    if (letterGrade == "B-") { gradeWeights.at(4) = newGradeWeight; }
    if (letterGrade == "C+") { gradeWeights.at(5) = newGradeWeight; }
    if (letterGrade == "C") { gradeWeights.at(6) = newGradeWeight; }
    if (letterGrade == "C-") { gradeWeights.at(7) = newGradeWeight; }
    if (letterGrade == "D+") { gradeWeights.at(8) = newGradeWeight; }
    if (letterGrade == "D") { gradeWeights.at(9) = newGradeWeight; }
    if (letterGrade == "D-") { gradeWeights.at(10) = newGradeWeight; }
    if (letterGrade == "F") { gradeWeights.at(11) = newGradeWeight; }
}

void StudentClass::setGradeWeight(std::vector<int> newGradeWeights) {
    gradeWeights = newGradeWeights;
}

void StudentClass::setNumberGrade(std::string letterGrade) {
    if (letterGrade == "A") { this->numberGrade = 4.0; }
    if (letterGrade == "A-") { this->numberGrade = 3.7; }
    if (letterGrade == "B+") { this->numberGrade = 3.3; }
    if (letterGrade == "B") { this->numberGrade = 3.0; }
    if (letterGrade == "B-") { this->numberGrade = 2.7; }
    if (letterGrade == "C+") { this->numberGrade = 2.3; }
    if (letterGrade == "C") { this->numberGrade = 2.0; }
    if (letterGrade == "C-") { this->numberGrade = 1.7; }
    if (letterGrade == "D+") { this->numberGrade = 1.3; }
    if (letterGrade == "D") { this->numberGrade = 1.0; }
    if (letterGrade == "D-") { this->numberGrade = 0.7; }
    if (letterGrade == "F") { this->numberGrade = 0; }
    if (letterGrade == "NR") { this->numberGrade = -1; }
}

void StudentClass::addClassContent(std::string contentItem, double contentWeight, double contentGrade, std::string contentType) {
    if (contentType == "Exams") {
        exams.push_back({contentItem, contentWeight, contentGrade});
    } else {
        assignments.push_back({contentItem, contentWeight, contentGrade});
    }
}

std::vector<int> StudentClass::getGradeWeights() const {
    return gradeWeights;
}