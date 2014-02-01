#ifndef APP_CONSTANTS_H__
#define APP_CONSTANTS_H__

#include "bip39_constants.h"

#define APP_MNEMONIC_PREFIX "mnemonic:"
#define APP_MNEMONIC_PREFIX_LENGTH (sizeof(APP_MNEMONIC_PREFIX) - 1)
#define APP_PREFIXED_MNEMONIC_MAX_SIZE (MNEMONIC_MAX_SIZE + APP_MNEMONIC_PREFIX_LENGTH)

char * app_init(void);

#endif
