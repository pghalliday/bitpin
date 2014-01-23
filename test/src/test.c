#include "test.h"
#include "cspec.h"
#include "cspec_output_verbose.h"
#include <stdio.h>

#include <string.h>

DESCRIBE(strcmp, "int strcmp ( const char * str1, const char * str2 )")

  IT( "returns 0 only when strings are equal" )
    SHOULD_EQUAL( strcmp("hello", "hello"), 2)
    SHOULD_NOT_EQUAL( strcmp("hello", "world"), 0)
  END_IT

  IT( "returns a negative integer when str1 is less than str2"  )
    SHOULD_BE_TRUE( strcmp("hello", "world") < 0 )
    SHOULD_BE_TRUE( strcmp("0123", "1321431") < 0 )
  END_IT

  IT( "returns a positive integer if str1 is greater than str2"  )
    SHOULD_BE_TRUE( strcmp("yellow", "world") < 0 )
    SHOULD_BE_TRUE( strcmp("9", "789") > 0 )
  END_IT

END_DESCRIBE

void test_run(void) {
  printf("%d tests failed\n", CSpec_Run( DESCRIPTION( strcmp ), CSpec_NewOutputVerbose() ));
}