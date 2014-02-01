#ifdef F_CPU
#undef F_CPU
#endif

#define F_CPU 16000000

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>

/*
 * This demonstrate how to use the avr_mcu_section.h file
 * The macro adds a section to the ELF file with useful
 * information for the simulator
 */
#include "avr_mcu_section.h"
AVR_MCU(F_CPU, "atmega328p");

static int uart_putchar(char c, FILE *stream) {
  if (c == '\n')
    uart_putchar('\r', stream);
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
  return 0;
}

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

#include "put_number.h"

#include "rand.test.h"
#include "bip39.test.h"
#include "app.test.h"

int main() {
  int failed = 0;
  stdout = &mystdout;

  // using 2 prints so that the resulting strings
  // do not appear in output during flashing. This allows my
  // test tool to watch the output and see when tests really
  // start so that it can only output interesting logging and
  // also detect when the tests have completed
  fputs("CSPEC: ", stdout);
  fputs("starting tests\n\n", stdout);

  failed += rand_test_run();
  failed += bip39_test_run();
  failed += app_test_run();

  fputs("CSPEC: ", stdout);
  put_number(failed);
  fputs(" tests failed\n", stdout);

  // this quits the simulator, since interrupts are off
  // this is a "feature" that allows running tests cases and exit
  sleep_cpu();
}
