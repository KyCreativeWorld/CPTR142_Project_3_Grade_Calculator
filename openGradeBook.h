#pragma once

#include "Gradebook.h"
#include <string>
#include <vector>

/**
 * Helper function that removes whitespace before and after a string. Returns the trimmed string.
 */
std::string trimWhitespace(std::string beforeStr);

/**
 * Opens a gradebook txt file and reads the information into a Gradebook object.
 * Takes a string for file name. Returns a Gradebook object.
 */
Gradebook openGradeBook(std::string fileName);