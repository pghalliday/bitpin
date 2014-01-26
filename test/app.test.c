#include "app.test.h"
#include "cspec.h"
#include "cspec_output_verbose.h"

#include "app.h"
#include <stdio.h>

DESCRIBE(app_init, "char * app_init();");

  IT( "should return a new mnemonic with strength 256" );
    char * mnemonic = app_init();
    int word_count = 0;

    printf("\t\tmnemonic: %s\n", mnemonic);

    while (* mnemonic) {
      if (word_count == 0) {
        word_count = 1;
      }
      if (* mnemonic == ' ') {
        word_count++;
      }
      mnemonic++;
    }

    printf("\t\tword_count: %d\n", word_count);

    SHOULD_EQUAL(word_count, ((256 / 8) * 3) / 4);
  END_IT;

END_DESCRIBE;

int app_test_run(void) {
  return CSpec_Run( DESCRIPTION( app_init ), CSpec_NewOutputVerbose() );
}
