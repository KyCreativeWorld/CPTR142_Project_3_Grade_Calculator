#pragma once

#include <vector>
#include <string>
#include <map>

class StudentClass {
    public:
        struct ContentInfo {
            double contentWeight;
            double contentGrade;
        };
    
        StudentClass(std::string className);
        void setGradeWeight(std::string letterGrade, int newGradeWeight);
        void setGradeWeight(std::vector<int> newGradeWeights);
        void setLetterGrade(std::string letterGrade) { this->letterGrade = letterGrade; setNumberGrade(letterGrade); }
        void setClassCredits(int classCredits) { this->classCredits = classCredits; }

        void addClassContent(std::string contentItem, double contentWeight, double contentGrade = -1.0, std::string contentType = "Exams");
        
        std::string getLetterGrade() { return letterGrade; }
        double getNumberGrade() { return numberGrade; }
        std::string getClassName() { return className; }
        int getClassCredits() { return classCredits; }
        std::map<std::string, ContentInfo>& getAssignments(std::string contentType = "Assignments") {
            if (contentType == "Exams") { return exams; 
            } else { return assignments; }
        }
        std::map<std::string, ContentInfo>& getExams() { return exams; }

    private:
        std::string letterGrade;
        double numberGrade;
        int classCredits;
        std::string className;
        std::vector<int> gradeWeights;

        std::map<std::string, ContentInfo> assignments;
        std::map<std::string, ContentInfo> exams;
        
        void setNumberGrade(std::string letterGrade);
};