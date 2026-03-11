#pragma once

#include <string>

/**
 * Turns a number into the associated quarter name. Takes an int for quarter.
 * Returns the name of a quarter. Ex: quarterNumToString(1) is "Fall"
 * (1 = Fall, 2 = Winter, 3 = Spring, 4 = Summer) Defaults to 1.
 */
std::string quarterNumToString(int num);