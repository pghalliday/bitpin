#include "app.test.h"
#include "cspec.h"
#include "cspec_output_verbose.h"

#include "app.h"
#include <stdio.h>
#include <avr/eeprom.h>
#include <count_words.h>

DESCRIBE(app_init, "char * app_init();");

  IT( "should return a new mnemonic with strength 256" );
    int word_count = 0;
    char * mnemonic = app_init();
    word_count = count_words(mnemonic);

    SHOULD_EQUAL(word_count, ((256 / 8) * 3) / 4);
  END_IT;

  IT( "should read the mnemonic from eeprom if there is one" );
    char * mnemonic;
    static char test_mnemonic[(24 * 10) + sizeof("mnemonic:") - 1] = "mnemonic:This is a test";

    eeprom_busy_wait();
    eeprom_write_block(
      (void *) test_mnemonic,
      0x0,
      (24 * 10) + sizeof("mnemonic:") - 1
    );

    mnemonic = app_init();

    SHOULD_MATCH(mnemonic, "This is a test");
  END_IT;

END_DESCRIBE;

int app_test_run(void) {
  return CSpec_Run( DESCRIPTION( app_init ), CSpec_NewOutputVerbose() );
}
