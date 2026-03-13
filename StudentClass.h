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

        /**
         * Sets the class's letter grade. Sets the number grade automatically.
         * Takes a string as the letter grade.
         * Ex: setLetterGrade("A") -> Class grade is A.
         */
        void setLetterGrade(std::string letterGrade) { this->letterGrade = letterGrade; setNumberGrade(letterGrade); }

        /**
         * Sets the class's credits. Takes an int for the credits.
         */
        void setClassCredits(int classCredits) { this->classCredits = classCredits; }



        /**
         * Adds content (assignment/exam) to the class. Takes a string as the name,
         * double as the weight, double as the grade (default/no grade = -1), and
         * content type ("Assignments"/"Exams") (defaults to "Assignments").
         * Ex: addClassContent("Exam 1", 15.0, 89.0, "Exams")
         * Creates an exam called 'Exam 1' with weight 15.0 and grade 89.0.
         */
        void addClassContent(std::string contentItem, double contentWeight, double contentGrade = -1.0, std::string contentType = "Assignments");
        

        
        /**
         * Returns the class's letter grade.
         */
        std::string getLetterGrade() { return letterGrade; }

        /**
         * Returns the class's numbe grade.
         */
        double getNumberGrade() { return numberGrade; }

        /**
         * Returns the class's name.
         */
        std::string getClassName() { return className; }

        /**
         * Returns the class's credits.
         */
        int getClassCredits() { return classCredits; }

        /**
         * Returns the class's vector of content ("Assignments"/"Exams").
         * Ex: vector<ContentInfo> examsList = getAssignments("Exams") -> list of exams in examsList.
         */
        std::vector<ContentInfo>& getAssignments(std::string contentType = "Assignments") {
            if (contentType == "Exams") { return exams; 
            } else { return assignments; }
        }

        /**
         * Returns the class's vector of exams
         * Ex: vector<ContentInfo> examsList = getExams() -> list of exams in examsList.
         */
        std::vector<ContentInfo>& getExams() { return exams; }

        /**
         * Returns grade weights. Weights are in a vector of ints.
         */
        std::vector<int> getGradeWeights() const{ return gradeWeights; }

    private:
        std::string letterGrade; // Class's letter grade
        double numberGrade; // Class's number grade
        int classCredits; // Class's credits
        std::string className; // Class's name
        std::vector<int> gradeWeights; // Grade weights

        std::vector<ContentInfo> assignments; // Class's assignments vector
        std::vector<ContentInfo> exams; // Class's exams vector
        
        // Helper function that sets the number grade based on the letter grade inputted.
        void setNumberGrade(std::string letterGrade); 
};