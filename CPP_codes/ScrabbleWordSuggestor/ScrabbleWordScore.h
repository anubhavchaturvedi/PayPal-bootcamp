#include <iostream>
#include "util.h"
using namespace std;

class ScrabbleWordScore
{
    private:
            int score;
    public:

        ScrabbleWordScore();
        int getLetterScore(char letter);
        int computeWordScore(string word);
        int computeWordScore(string word, string lettersToIgnore);


};
