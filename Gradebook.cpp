#include "Gradebook.h"

void Gradebook::addClass(StudentClass newClass, int quarterNum = 1) {
    // Sees which quarter was inputted and puts the class in that quarter's vector
    switch(quarterNum) {
        case 1:
            fallClasses.push_back(newClass);
            break;
        case 2:
            winterClasses.push_back(newClass);
            break;
        case 3:
            springClasses.push_back(newClass);
            break;
        case 4:
            summerClasses.push_back(newClass);
            break;
        default:
            fallClasses.push_back(newClass);
    }
}

std::vector<StudentClass>& Gradebook::getClasses(int quarterNum = 1) {
    // Returns the vector of StudentClasses for the inputted quarter
    switch(quarterNum) {
        case 1:
            return fallClasses;
            break;
        case 2:
            return winterClasses;
            break;
        case 3:
            return springClasses;
            break;
        case 4:
            return summerClasses;
            break;
        default:
            return fallClasses;
    }

}