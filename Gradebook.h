#pragma once

#include <vector>
#include <string>
#include "StudentClass.h"

class Gradebook {
    public:
        Gradebook() {}
        void setYear(int yearNum) { this->gbYear = yearNum; }
        void setStudentName(std::string studentName) { this->studentName = studentName; }
        void addClass(StudentClass newClass, int quarterNum);
        
        int getYear() { return this->gbYear; }
        std::string getStudentName() { return this->studentName; }
        std::vector<StudentClass> getClasses(int quarterNum);

    
    private:
        int gbYear;
        std::string studentName;
        std::vector<StudentClass> fallClasses;
        std::vector<StudentClass> winterClasses;
        std::vector<StudentClass> springClasses;
        std::vector<StudentClass> summerClasses;

        std::vector<StudentClass> prevClasses;

};