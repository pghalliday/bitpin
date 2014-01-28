#include "app.h"
#include "bip39.h"
#include <avr/eeprom.h>
#include <string.h>

char * app_init(void) {
  static char mnemonic[24 * 10];
  char buffer[(24 * 10) + sizeof("mnemonic:") - 1];
  eeprom_busy_wait();
  eeprom_read_block(
    (void *) buffer,
    0x0,
    (24 * 10) + sizeof("mnemonic:") - 1
  );
  if (strncmp(buffer, "mnemonic:", sizeof("mnemonic:") - 1) == 0) {
    strncpy(mnemonic, buffer + sizeof("mnemonic:") - 1, 24 * 10);
  } else {
    mnemonic_generate(mnemonic, 256);
  }
  return mnemonic;
}
