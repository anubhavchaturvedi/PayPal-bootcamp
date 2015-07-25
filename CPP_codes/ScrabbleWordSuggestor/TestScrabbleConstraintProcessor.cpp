#include "UnitTest++.h"
#include "ScrabbleConstraintProcessor.h"

namespace{


    TEST(regex_generator_test)
    {
        ScrabbleConstraintProcessor obj=new ScrabbleConstraintProcessor("*a*");
        const string result=obj.
        CHECK_EQUAL(true, isConstraintPassed("cat"));

    }
    
     TEST(check_add_constraint)
    {
        ScrabbleConstraintProcessor obj=new ScrabbleConstraintProcessor();
        obj.addConstraint("t..t")
        CHECK_EQUAL(true, obj.isConstraintPassed("text"));
    }

}
