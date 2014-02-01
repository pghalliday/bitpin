#include "rand.test.h"
#include "cspec.h"
#include "cspec_output_verbose.h"

#include "rand.h"

DESCRIBE(random32, "uint32_t random32(void);");

  IT( "should generate random numbers" );
    SHOULD_PENDING("how can I test if numbers are random!!");
  END_IT;

END_DESCRIBE;

DESCRIBE(init_rand, "void init_rand(void);");

  IT( "should result in the same sequence of random numbers as the same seed is used every time" );
    int i;
    uint32_t sequence[5];
    init_rand();
    for (i = 0; i < 5; i++) {
      sequence[i] = random32();
    }
    init_rand();
    for (i = 0; i < 5; i++) {
      SHOULD_EQUAL(random32(), sequence[i]);
    }
  END_IT;

END_DESCRIBE;

int rand_test_run(void) {
  int failed = 0;
  failed += CSpec_Run( DESCRIPTION( random32 ), CSpec_NewOutputVerbose() );
  failed += CSpec_Run( DESCRIPTION( init_rand ), CSpec_NewOutputVerbose() );
  return failed;
}
