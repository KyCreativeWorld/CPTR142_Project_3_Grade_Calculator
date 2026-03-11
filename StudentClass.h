#pragma once

#include <vector>
#include <string>
#include <map>

class StudentClass {
    public:
        /**
         * A Structure that stores an assignment's or exam's name, weight, and grade.
         */
        struct ContentInfo {
            std::string contentName; // Content's name
            double contentWeight; // Content's weight
            double contentGrade; // Content's grade
        };
    
        /**
         * StudentClass constructor. Takes a string for the class's name.
         */
        StudentClass(std::string className);

        /**
         * Sets the percentage score required in this class to get a certain grade.
         * Takes a string for the letter grade and an int for the new grade score require to achieve that grade.
         * Ex: A = 94% -> setGradeWeight("A", 94);
         */
        void setGradeWeight(std::string letterGrade, int newGradeWeight);

        /**
         * Sets the percentage score required in this class to get a certain grade.
         * Takes a vector of ints that represents each grade's score require to achieve that grade.
         * Ex: A = 93%, A- = 90, etc. -> setGradeWeight({93, 90, 87, 83, 80, 77, 73, 70, 67, 63, 60, 0})
         */
        void setGradeWeight(std::vector<int> newGradeWeights);
        void setLetterGrade(std::string letterGrade) { this->letterGrade = letterGrade; setNumberGrade(letterGrade); }
        void setClassCredits(int classCredits) { this->classCredits = classCredits; }

        void addClassContent(std::string contentItem, double contentWeight, double contentGrade = -1.0, std::string contentType = "Exams");
        
        std::string getLetterGrade() { return letterGrade; }
        double getNumberGrade() { return numberGrade; }
        std::string getClassName() { return className; }
        int getClassCredits() { return classCredits; }
        std::vector<ContentInfo>& getAssignments(std::string contentType = "Assignments") {
            if (contentType == "Exams") { return exams; 
            } else { return assignments; }
        }
        std::vector<ContentInfo>& getExams() { return exams; }

        std::vector<int> getGradeWeights() const;

    private:
        std::string letterGrade;
        double numberGrade;
        int classCredits;
        std::string className;
        std::vector<int> gradeWeights;

        std::vector<ContentInfo> assignments;
        std::vector<ContentInfo> exams;
        
        void setNumberGrade(std::string letterGrade);
};