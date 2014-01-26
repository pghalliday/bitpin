#include "avr/pgmspace.h"
#include "static_assert.h"
#include "paste.h"
#include "stringify.h"

#define BIP39_MAX_WORD_SIZE 11

#define ADD_WORD(word) \
STATIC_ASSERT(sizeof(STRINGIFY(word)) <= BIP39_MAX_WORD_SIZE, PASTE(BIP39_words_should_be_less_than_, PASTE(BIP39_MAX_WORD_SIZE, _bytes))); \
static prog_char PASTE(wordlist_, word)[] PROGMEM = STRINGIFY(word);
#include "bip39_english_words.h"
#undef ADD_WORD

PROGMEM static const char * wordlist[] = {
#define ADD_WORD(word) \
PASTE(wordlist_, word),
#include "bip39_english_words.h"
0,
};
#undef ADD_WORD
