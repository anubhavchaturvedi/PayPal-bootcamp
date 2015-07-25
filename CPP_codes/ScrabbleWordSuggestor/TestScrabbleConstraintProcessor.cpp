#include "UnitTest++.h"
#include "ScrabbleConstraintProcessor.h"

namespace{


    TEST(check_is_constraint_passed)
    {
        ScrabbleConstraintProcessor obj=new ScrabbleConstraintProcessor("*a*");
        CHECK_EQUAL(true, isConstraintPassed("cat"));

    }
    
     TEST(check_add_constraint)
    {
        ScrabbleConstraintProcessor obj=new ScrabbleConstraintProcessor();
        obj.addConstraint("t..t");
        CHECK_EQUAL(true, obj.isConstraintPassed("text"));
    }
    
    TEST(check_is_constraint_passed2)
    {
        ScrabbleConstraintProcessor obj=new ScrabbleConstraintProcessor(".*e");
        CHECK_EQUAL(false, isConstraintPassed("pain"));

    }
}
