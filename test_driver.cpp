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

    openGradeBook(gbFileName);

    return 0;
}