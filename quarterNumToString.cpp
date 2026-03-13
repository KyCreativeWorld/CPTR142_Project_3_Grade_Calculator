#include "quarterNumToString.h"

// Takes a quarter number (1, 2, 3, 4) and returns the associated quarter name (Fall, etc.)
std::string quarterNumToString(int num = 1) {
    switch (num) {
        case 1:
            return "Fall";
        case 2:
            return "Winter";
        case 3:
            return "Spring";
        case 4:
            return "Summer";            
    }
    return "Fall";
}