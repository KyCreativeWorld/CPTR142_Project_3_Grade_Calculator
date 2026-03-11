#pragma once

#include <vector>
#include <string>
#include "StudentClass.h"

class Gradebook {
    public:
        /**
         * Gradebook constructor. No arguments.
        */
        Gradebook() {}

        /**
         * Sets the year in the Gradebook. Takes an int argument.
         */
        void setYear(int yearNum) { this->gbYear = yearNum; }

        /**
         * Sets the student's name in the Gradebook. Takes a std::string argument.
         */
        void setStudentName(std::string studentName) { this->studentName = studentName; }

        /**
         * Adds a StudentClass to the correct class vector. Takes a StudentClass and an int for quarter.
         * (1 = Fall, 2 = Winter, 3 = Spring, 4 = Summer) Defaults to 1.
         */
        void addClass(StudentClass newClass, int quarterNum);
        
        
        /**
         * Returns the year reported in the Gradebook
         */
        int getYear() const { return this->gbYear; }

        /**
         * Returns the student's name reported in the Gradebook
         */
        std::string getStudentName() const { return this->studentName; }

        /**
         * Returns a vector of StudentClasses for a specific quarter reported in the Gradebook.
         * (1 = Fall, 2 = Winter, 3 = Spring, 4 = Summer) Defaults to 1.
         */
        std::vector<StudentClass>& getClasses(int quarterNum);

    
    private:
        int gbYear; // Year
        std::string studentName; // Student's Name
        std::vector<StudentClass> fallClasses; // Vector of fall classes (StudentClass)
        std::vector<StudentClass> winterClasses; // Vector of winter classes (StudentClass)
        std::vector<StudentClass> springClasses; // Vector of spring classes (StudentClass)
        std::vector<StudentClass> summerClasses; // Vector of summer classes (StudentClass)
};