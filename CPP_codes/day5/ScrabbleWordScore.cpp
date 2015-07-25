#include "ScrabbleWordScore.h"

ScrabbleWordScore::ScrabbleWordScore()
{
    score=0;
}

int ScrabbleWordScore::getLetterScore(char letter)
{
    return ALPHABET_SCORE[ letter - 'a' ];
}

int ScrabbleWordScore::computeWordScore(string word)
{

        for ( int i = 0; i < word.length(); i++ )
        {
            char ch = word[i];
            if ( 'a' <= ch && ch <= 'z' )
            {
                score += getLetterScore(ch);
            }
        }

        return score;
}

int ScrabbleWordScore::computeWordScore(string word, string lettersToIgnore)
{
    int word_score = computeWordScore(word);
    int lettersToIgnore_score = computeWordScore(lettersToIgnore);

    return word_score-lettersToIgnore_score;

}
