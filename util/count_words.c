#include "count_words.h"

int count_words(const char * buffer) {
  int word_count = 0;
  char * pos = (char *) buffer;
  while (* pos) {
    if (word_count == 0) {
      word_count = 1;
    }
    if (* pos == ' ') {
      word_count++;
    }
    pos++;
  }
  return word_count;
}
