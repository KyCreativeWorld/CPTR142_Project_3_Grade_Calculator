#include "openGradeBook.h"
#include <iostream>
#include <fstream>
#include <cctype>



void openGradeBook(std::string fileName, std::vector<std::string>& prevGrades, std::vector<int>& prevCredits) {
    ifstream gradeBookFile(fileName);

    if (!gradeBookFile) { // Makes sure file was found
        cout << "Failed to open " << fileName << endl;
        return 1;
    }

    int curLine = 0;

    while (getline (gradeBookFile, gbLine)) {
        ++curLine;

        if (gbLine.substring(0, 4) = "Year") {
            unsigned int i;
            for (i = 0, i < gbLine.size(), ++i) {
                if (isdigit(gbLine.at(i))) break;
            }

            if (i < gbLine.size()) {
                std::cout << "Year: " << gbLine.substring(i, gbLine.size()) << std::endl;
            }

        }

    }
}