/*
 *  cspec_output_verbose.c   :  Verbose output with color (green for OK, red for fail and yellow for pending)
 *
 * See copyright notice in cspec.h
 *
 */

#include <stdarg.h>
#include <stdio.h>
#include "cspec_output_verbose.h"
#include "put_number.h"

static CSpecOutputStruct verbose;

/* private functions */
static int getAnsiColorCode(CSpec_Color color);
static void setColor(CSpec_Color color);
static void resetColor(void);

void startDescribeFunVerbose( const char *descr) {
	fputs("Describe: ", stdout);
	fputs(descr, stdout);
	fputs("\n", stdout);
}

void endDescribeFunVerbose( ) {
	fputs("\n", stdout);
}

void startItFunVerbose( const char *descr) {
	fputs("   - it ", stdout);
	fputs(descr, stdout);
	fputs("\n", stdout);
}

void endItFunVerbose( ) {
	fputs("\n", stdout);
}

void evalFunVerbose(const char*filename, int line_number, const char*assertion, int assertionResult) {
	if(assertionResult)
	{
		setColor(CSPEC_COLOR_GREEN);
		fputs("       OK: ", stdout);
		fputs(assertion, stdout);
		fputs("\n", stdout);
		resetColor();
	}
	else
	{
		setColor(CSPEC_COLOR_RED);
		fputs("       Failed: ", stdout);
		fputs(assertion, stdout);
		fputs(" in file ", stdout);
		fputs(filename, stdout);
		fputs(" at line ", stdout);
		put_number(line_number);
		fputs("\n", stdout);
		resetColor();
	}
}

void pendingFunVerbose(const char* reason) {
	setColor(CSPEC_COLOR_YELLOW);
	fputs("       Pending: ", stdout);
	fputs(reason, stdout);
	fputs("\n", stdout);
	resetColor();
}

CSpecOutputStruct* CSpec_NewOutputVerbose() {
	CSpec_InitOutput(&verbose);
	
	verbose.startDescribeFun	= startDescribeFunVerbose;
	verbose.endDescribeFun		= endDescribeFunVerbose;
	verbose.startItFun			= startItFunVerbose;
	verbose.endItFun			= endItFunVerbose;
	verbose.evalFun				= evalFunVerbose;
	verbose.pendingFun			= pendingFunVerbose;

	return &verbose;
}

static int getAnsiColorCode(CSpec_Color color) {
	int color_code;

	switch(color)
	{
	case CSPEC_COLOR_RED:
		color_code = 31;
		break;
	case CSPEC_COLOR_GREEN:
		color_code = 32;
		break;
	case CSPEC_COLOR_YELLOW:
		color_code = 33;
		break;
	default:
		color_code = 30;
		break;
	}

	return color_code;
}

static void setColor(CSpec_Color color) {
	fputs("\033[;", stdout);
	put_number(getAnsiColorCode(color));
	fputs("m", stdout);
}

static void resetColor(void) {
	fputs("\033[0m", stdout);
}
