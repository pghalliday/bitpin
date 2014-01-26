#include "app.h"
#include "bip39.h"

char * app_init(void) {
  return mnemonic_generate(256);
}
