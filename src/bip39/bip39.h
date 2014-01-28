#ifndef __BIP39_H__
#define __BIP39_H__

#include <stdint.h>

void mnemonic_generate(char mnemonic[24 * 10], int strength);	// strength in bits

void mnemonic_from_data(char mnemonic[24 * 10], const uint8_t *data, int len);

void mnemonic_to_seed(const char *mnemonic, const char *passphrase, uint8_t seed[512 / 8]);

#endif
