/*
 *  cspec_private.c  :   Private functions
 *
 * See copyright notice in cspec.h
 *
 */

#include <stdio.h>
#include <string.h>
#include "cspec_private.h"
#include "cspec_output.h"

static CSpecOutputStruct* CSpec_output = 0;

int CSpec_StartDescribe(const char * string_table[]) {
	if( CSpec_output->startDescribeFun != NULL) {
		char descr_buffer[CSPEC_MAX_MESSAGE_SIZE];
    strcpy_P(descr_buffer, (char *) pgm_read_word(&(string_table[0])));
		CSpec_output->startDescribeFun(descr_buffer);
	}
  return 0;
}

void CSpec_EndDescribe(void) {
	if( CSpec_output->endDescribeFun != NULL) {
		CSpec_output->endDescribeFun();
	}
}

int CSpec_StartIt(const char * string_table[]) {
	if(CSpec_output->startItFun != NULL) {
		char descr_buffer[CSPEC_MAX_MESSAGE_SIZE];
    strcpy_P(descr_buffer, (char *) pgm_read_word(&(string_table[0])));
		CSpec_output->startItFun(descr_buffer);
	}
  return 0;
}

void CSpec_EndIt(int memory_before, int memory_after) {
	if(CSpec_output->endItFun != NULL) {
		CSpec_output->endItFun(memory_before, memory_after);
	}
}

void CSpec_Eval(const char * string_table[], int line_number, int assertionResult) {
	if(CSpec_output->evalFun != NULL) {
		char filename_buffer[CSPEC_MAX_MESSAGE_SIZE];
		char assertion_buffer[CSPEC_MAX_MESSAGE_SIZE];
    strcpy_P(filename_buffer, (char *) pgm_read_word(&(string_table[0])));
    strcpy_P(assertion_buffer, (char *) pgm_read_word(&(string_table[1])));
		CSpec_output->evalFun(filename_buffer, line_number, assertion_buffer, assertionResult);
	}
   
	if (!assertionResult) {
		CSpec_output->failed++;
	}
}

void CSpec_Pending(const char * string_table[]) {
	if(CSpec_output->pendingFun != NULL) {
		char reason_buffer[CSPEC_MAX_MESSAGE_SIZE];
    strcpy_P(reason_buffer, (char *) pgm_read_word(&(string_table[0])));
		CSpec_output->pendingFun(reason_buffer);
	}
}

void CSpec_SetOutput(CSpecOutputStruct* output) {
	CSpec_output = output;
}
