#pragma once

#include "Gradebook.h"
#include <string>
#include <vector>

std::string trimWhitespace(std::string beforeStr);

Gradebook openGradeBook(std::string fileName);