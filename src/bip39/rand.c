// TODO: this is not a cryptographically secure way to generate
// 32 bit random numbers sa far as I know. As such it should not be used
// in any production implementation

#include <stdlib.h>

#include "rand.h"

void init_rand(void) {
  srandom(1);
}

uint32_t random32(void) {
  return (uint32_t) random();
}
