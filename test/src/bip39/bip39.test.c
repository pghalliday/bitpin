#include "bip39.test.h"
#include "cspec.h"
#include "cspec_output_verbose.h"

#include "bip39.h"
#include <count_words.h>

static char mnemonic[24 * 10];
static uint32_t data[16];

DESCRIBE(mnemonic_generate, "void mnemonic_generate(char mnemonic[24 * 10], int strength);");

  IT( "should populate the mnemonic buffer" );
    int word_count = 0;
    mnemonic_generate(mnemonic, 256);
    word_count = count_words(mnemonic);

    SHOULD_EQUAL(word_count, ((256 / 8) * 3) / 4);
  END_IT;

END_DESCRIBE;

DESCRIBE(mnemonic_from_data, "void mnemonic_from_data(char mnemonic[24 * 10], const uint8_t *data, int len);");

  IT( "should populate the mnemonic buffer" );
    int word_count = 0;
    mnemonic_from_data(mnemonic, (const uint8_t *)data, 32);
    word_count = count_words(mnemonic);

    SHOULD_EQUAL(word_count, (32 * 3) / 4);
  END_IT;

END_DESCRIBE;

int bip39_test_run(void) {
  int failed = 0;
  failed += CSpec_Run( DESCRIPTION( mnemonic_generate ), CSpec_NewOutputVerbose() );
  failed += CSpec_Run( DESCRIPTION( mnemonic_from_data ), CSpec_NewOutputVerbose() );
  return failed;
}
