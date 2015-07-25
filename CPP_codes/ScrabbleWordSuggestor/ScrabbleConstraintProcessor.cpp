#include <iostream>
#include <regex>

using namespace std;

class ScrabbleConstraintProcessor
{

    private:

    string constraintRegExp;

    string generateConstraintRegExp(string constraint);

    public:

    ScrabbleConstraintProcessor (string constraint);
    bool isConstraintPassed(string word);

};

