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
#define CSPEC_VARIABLE PASTE(__cspec_, __COUNTER__)

#ifdef __cplusplus
extern "C" {
#endif

int  CSpec_StartDescribe(const char * string_table[]);
void CSpec_EndDescribe();

int  CSpec_StartIt(const char * string_table[]);
void CSpec_EndIt();


void CSpec_Eval(const char * string_table[], int line_number, int assertionResult);
void CSpec_Pending(const char * string_table[]);

#ifdef __cplusplus
}
#endif

#define _CSPEC_EVAL(x, filename_variable, assertion_variable, string_table_variable) { \
  STATIC_ASSERT(sizeof(__FILE__) <= CSPEC_MAX_MESSAGE_SIZE, PASTE(File_path_string_cannot_exceed_,PASTE(CSPEC_MAX_MESSAGE_SIZE,_bytes))); \
  STATIC_ASSERT(sizeof(#x) <= CSPEC_MAX_MESSAGE_SIZE, PASTE(Assertion_string_cannot_exceed_,PASTE(CSPEC_MAX_MESSAGE_SIZE,_bytes))); \
  static prog_char filename_variable[] PROGMEM = __FILE__; \
  static prog_char assertion_variable[] PROGMEM = #x; \
  PROGMEM static const char * string_table_variable[] = { \
    filename_variable, \
    assertion_variable \
  }; \
  CSpec_Eval(string_table_variable, __LINE__, (x)); \
}
#define CSPEC_EVAL(x) _CSPEC_EVAL(x, CSPEC_VARIABLE, CSPEC_VARIABLE, CSPEC_VARIABLE)
#define _CSPEC_PENDING(reason, reason_variable, string_table_variable) { \
  STATIC_ASSERT(sizeof(reason) <= CSPEC_MAX_MESSAGE_SIZE, PASTE(Pending_reason_string_cannot_exceed_,PASTE(CSPEC_MAX_MESSAGE_SIZE,_bytes))); \
  static prog_char reason_variable[] PROGMEM = reason; \
  PROGMEM static const char * string_table_variable[] = { \
    reason_variable \
  }; \
  CSpec_Pending(string_table_variable); \
}
#define CSPEC_PENDING(reason) _CSPEC_PENDING(reason, CSPEC_VARIABLE, CSPEC_VARIABLE)


#endif

