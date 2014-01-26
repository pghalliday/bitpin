TREZOR_CRYPTO_DIRS := ${shell find ${TREZOR_CRYPTO_HOME} -type d -print}

TREZOR_CRYPTO_FILES := \
	bip39.c \
	hmac.c \
	sha2.c \
	pbkdf2.c

TREZOR_CRYPTO_HEADERS := \
	bip39.h \
	hmac.h \
	sha2.h \
	pbkdf2.h \
	bip39_english.h


