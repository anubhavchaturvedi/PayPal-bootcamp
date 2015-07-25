#include <iostream>
#include <algorithm>

using namespace std;

const string EMPTY_TILE = "@";
const int NO_SCORE_COMPENSATION = 0;
const int MAX_RACK_LENGTH = 7;

const int ALPHABET_SCORE[] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

const string SOWPODS_FILENAME = "sowpods.txt";

string getSortedString(string str);
