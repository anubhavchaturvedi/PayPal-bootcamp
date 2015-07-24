#include "UnitTest++.h"
#include "ScrabbleWordSuggestor.h"

namespace
{

    ScrabbleWordSuggestor obj("sowpods.txt");
    TEST(valid_score_check)
    {
        const int result=obj.computeScore("ab",0);
        CHECK_EQUAL(4,result);


    }
    TEST(inalid_score_check)
    {
        const int result=obj.computeScore("cddddd",0);
        CHECK_EQUAL(2,result);


    }

 TEST(check_string_sorting)
    {
        const string result=obj.getSortedString("dcba");
        CHECK_EQUAL("abcd",result);


    }


 TEST(regex_generator_test)
    {
        const string result=obj.generateRegExp("*b*");
        CHECK_EQUAL(".{0,1}b.{0,1}",result);


    }

    TEST(regex_comparing_test)
    {
        obj.rackRegExp = ".{0,1}a.{0,1}";
        const bool result=obj.isMatchesRegularExpression("cat");
        CHECK_EQUAL(true, result);


    }


}
