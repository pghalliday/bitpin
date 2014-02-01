#include "put_number.h"
#include <stdio.h>
#include <stdlib.h>

int put_number(int number) {
  char buffer[6];
  return fputs(itoa(number, buffer, 10), stdout);
}
