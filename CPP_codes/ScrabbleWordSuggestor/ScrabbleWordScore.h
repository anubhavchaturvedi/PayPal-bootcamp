#include <iostream>
using namespace std;

class ScrabbleWordScore
{
    private:
           const int ALPHABET_SCORE[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
            int score;
    public:

        ScrabbleWordScore();
        int getLetterScore(char letter);
        int computeWordScore(string word);
        int computeWordScore(string word, string lettersToIgnore);


};
