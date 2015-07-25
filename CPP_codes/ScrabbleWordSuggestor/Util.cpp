#include "Util.h"

string getSortedString(string str) {
    string sortedString = str;
    std::sort(sortedString.begin, str.begin);
    return sortedString;
}
