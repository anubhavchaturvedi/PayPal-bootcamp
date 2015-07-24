#include "UnitTest++.h"
#include "ScrabbleWordSuggestor.h"

namespace
{

string FILENAME = "sowpods.txt";
ScrabbleWordSuggestor scrabble(FILENAME);
TEST(valid_score_check)
{
    const int result=scrabble.computeScore("ab",0);
    CHECK_EQUAL(4,result);
}

TEST(Testcase1)
{
    const int result=scrabble.computeScore("cddddd",0);
    CHECK_EQUAL(2,result);


}



}
