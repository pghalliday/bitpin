/*
 *  cspec_private.h
 *
 * See copyright notice in cspec.h
 *
 */
#ifndef CSPEC_PRIVATE_H
#define CSPEC_PRIVATE_H

#include "avr/pgmspace.h"
#include "paste.h"
#include "static_assert.h"

#define CSPEC_MAX_MESSAGE_SIZE 100

#ifdef __cplusplus
extern "C" {
#endif

int  CSpec_StartDescribe(const char * string_table[]);
void CSpec_EndDescribe(void);

int  CSpec_StartIt(const char * string_table[]);
void CSpec_EndIt(int memory_before, int memory_after);

void CSpec_Eval(const char * string_table[], int line_number, int assertionResult);
void CSpec_Pending(const char * string_table[]);

#ifdef __cplusplus
}
#endif

#define CSPEC_EVAL(x) { \
  STATIC_ASSERT(sizeof(__FILE__) <= CSPEC_MAX_MESSAGE_SIZE, PASTE(File_path_string_cannot_exceed_,PASTE(CSPEC_MAX_MESSAGE_SIZE,_bytes))); \
  STATIC_ASSERT(sizeof(#x) <= CSPEC_MAX_MESSAGE_SIZE, PASTE(Assertion_string_cannot_exceed_,PASTE(CSPEC_MAX_MESSAGE_SIZE,_bytes))); \
  static prog_char _filename[] PROGMEM = __FILE__; \
  static prog_char _assertion[] PROGMEM = #x; \
  PROGMEM static const char * string_table[] = { \
    _filename, \
    _assertion \
  }; \
  CSpec_Eval(string_table, __LINE__, (x)); \
}
#define CSPEC_PENDING(reason) { \
  STATIC_ASSERT(sizeof(reason) <= CSPEC_MAX_MESSAGE_SIZE, PASTE(Pending_reason_string_cannot_exceed_,PASTE(CSPEC_MAX_MESSAGE_SIZE,_bytes))); \
  static prog_char _reason[] PROGMEM = reason; \
  PROGMEM static const char * string_table[] = { \
    _reason \
  }; \
  CSpec_Pending(string_table); \
}


#endif

