#include "app.h"
#include "app_constants.h"
#include "bip39.h"
#include <avr/eeprom.h>
#include <string.h>

char * app_init(void) {
  static char mnemonic[MNEMONIC_MAX_SIZE];
  char buffer[APP_PREFIXED_MNEMONIC_MAX_SIZE];
  eeprom_busy_wait();
  eeprom_read_block(
    (void *) buffer,
    0x0,
    APP_PREFIXED_MNEMONIC_MAX_SIZE
  );
  if (strncmp(buffer, APP_MNEMONIC_PREFIX, APP_MNEMONIC_PREFIX_LENGTH) == 0) {
    strncpy(mnemonic, buffer + APP_MNEMONIC_PREFIX_LENGTH, MNEMONIC_MAX_SIZE);
  } else {
    mnemonic_generate(mnemonic, 256);
  }
  return mnemonic;
}
