#include "openGradeBook.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    string gbFileName;

    cin >> gbFileName;

    vector<string> prevGrades;
    vector<int> prevCredits;

    Gradebook gb = openGradeBook(gbFileName);

    for (StudentClass sClass : gb.getClasses(1)) {
        cout << sClass.getClassName() << ": " << sClass.getClassCredits() << " Credits, " << sClass.getLetterGrade() << endl;
    }

    return 0;
}