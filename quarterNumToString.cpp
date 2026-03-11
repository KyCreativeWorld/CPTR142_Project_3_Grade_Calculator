#include "quarterNumToString.h"

std::string quarterNumToString(int num) {
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