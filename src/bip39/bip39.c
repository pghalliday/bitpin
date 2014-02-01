#include <string.h>

#include "bip39.h"
#include "hmac.h"
#include "rand.h"
#include "sha2.h"
#include "pbkdf2.h"
#include "bip39_english.h"

#define PBKDF2_ROUNDS 2048

void mnemonic_generate(char mnemonic[24 * 10], int strength)
{
	int i;
	uint32_t data[16];
	if (strength % 32 || strength < 128 || strength > 256) {
		return;
	}
	for (i = 0; i < 16; i++) {
		data[i] = random32();
	}
	mnemonic_from_data(mnemonic, (const uint8_t *)data, strength / 8);
}

void mnemonic_from_data(char mnemonic[24 * 10], const uint8_t *data, int len)
{
	int i, j;
	uint8_t hash[32];
	char bits[256 + 8];
	char buffer[BIP39_MAX_WORD_SIZE];

	if (len % 4 || len < 16 || len > 32) {
		return;
	}

	SHA256_Raw((const uint8_t *)data, len, hash);

	for (i = 0; i < len; i++) {
		for (j = 0; j < 8; j++) {
			bits[8 * i + j] = (data[i] & (1 << (7 - j))) > 0;
		}
	}

	char hlen = len / 4;
	for (i = 0; i < hlen; i++) {
		char c = (hash[0] & (1 << (7 - i))) > 0;
		bits[8 * len + i] = c;
	}

	int mlen = len * 3 / 4;

	char *p = mnemonic;
	for (i = 0; i < mlen; i++) {
		int idx = 0;
		for (j = 0; j < 11; j++) {
			idx += bits[i * 11 + j] << (10 - j);
		}
    strcpy_P(buffer, (char *) pgm_read_word(&(wordlist[idx])));
		strcpy(p, buffer);
		p += strlen(buffer);
		*p = (i < mlen - 1) ? ' ' : 0;
		p++;
	}
}

void mnemonic_to_seed(const char *mnemonic, const char *passphrase, uint8_t seed[512 / 8])
{
	uint8_t salt[8 + 256 + 4];
	int saltlen = strlen(passphrase);
	memcpy(salt, "mnemonic", 8);
	memcpy(salt + 8, passphrase, saltlen);
	saltlen += 8;
	pbkdf2((const uint8_t *)mnemonic, strlen(mnemonic), salt, saltlen, PBKDF2_ROUNDS, seed, 512 / 8);
}
