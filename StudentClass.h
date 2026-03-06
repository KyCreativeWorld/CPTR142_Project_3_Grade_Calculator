#pragma once

#include <vector>
#include <string>

class StudentClass {
    public:
        StudentClass(std::string className);
        void setGradeWeight(std::string letterGrade, int newGradeWeight);
        void setGradeWeight(std::vector<int> newGradeWeight);
        void setLetterGrade(std::string letterGrade) { this->letterGrade = letterGrade; setNumberGrade(letterGrade); }
        void setClassCredits(int classCredits) { this->classCredits = classCredits; }
        
        std::string getLetterGrade() { return letterGrade; }
        double getNumberGrade() { return numberGrade; }
        std::string getClassName() { return className; }
        int getClassCredits() { return classCredits; }

    private:
        std::string letterGrade;
        double numberGrade;
        int classCredits;
        std::string className;
        std::vector<std::string> assignments;
        std::vector<int> assignmentWeights;
        std::vector<std::string> exams;
        std::vector<int> examWeights;
        std::vector<int> gradeWeights;

        void setNumberGrade(std::string letterGrade);
};