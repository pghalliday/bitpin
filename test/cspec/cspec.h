/*
 *  cspec.h   :   the main header file
 *
 * See copyright notice at the end of this file
 *
 */
 
#ifndef CSPEC_H
#define CSPEC_H

/* Include private macros and function definitions */
#include "cspec_config.h"
#include "cspec_private.h"
#include "cspec_output.h"
#include "paste.h"
#include "static_assert.h"

/*               */
/* Public macros */
/*               */


/* Structural macros */

#define DEFINE_DESCRIPTION(foo)				  void foo ## _describe();
#define DESCRIPTION(foo)					  foo ## _describe

#define _DESCRIBE(foo, caption, caption_variable, string_table_variable) \
void foo ## _describe () { \
  STATIC_ASSERT(sizeof(caption) <= CSPEC_MAX_MESSAGE_SIZE, PASTE(Description_caption_string_cannot_exceed_,PASTE(CSPEC_MAX_MESSAGE_SIZE,_bytes))); \
  static prog_char caption_variable[] PROGMEM = caption; \
  PROGMEM static const char * string_table_variable[] = { \
    caption_variable \
  }; \
  CSpec_StartDescribe(string_table_variable); \
  {
#define DESCRIBE(foo, caption) _DESCRIBE(foo, caption, CSPEC_VARIABLE, CSPEC_VARIABLE)
#define _IT(caption, caption_variable, string_table_variable) \
    { \
      STATIC_ASSERT(sizeof(caption) <= CSPEC_MAX_MESSAGE_SIZE, PASTE(It_caption_string_cannot_exceed_,PASTE(CSPEC_MAX_MESSAGE_SIZE,_bytes))); \
      static prog_char caption_variable[] PROGMEM = caption; \
      PROGMEM static const char * string_table_variable[] = { \
        caption_variable \
      }; \
      CSpec_StartIt(string_table_variable); \
      {
#define IT(caption) _IT(caption, CSPEC_VARIABLE, CSPEC_VARIABLE)
#define END_IT \
      } \
      CSpec_EndIt(); \
    }
#define END_DESCRIBE \
  } \
  CSpec_EndDescribe(); \
}

/* Expectation macros */

#define SHOULD_BE_TRUE(x)					  CSPEC_EVAL( (x) ) 
#define SHOULD_EQUAL(x, y)                    CSPEC_EVAL( (x) == (y) ) 
#define SHOULD_EQUAL_DOUBLE(x, y, delta)      CSPEC_EVAL( cspec_fabs( (x) - (y) ) <= delta )
#define SHOULD_MATCH(x, y)                    CSPEC_EVAL( cspec_strcmp(x, y) ==  0   )
#define SHOULD_BE_NULL(x)                     CSPEC_EVAL( (x) == 0 )

#define SHOULD_BE_FALSE(x)					  CSPEC_EVAL( !(x) )
#define SHOULD_NOT_EQUAL(x, y)                CSPEC_EVAL( (x) != (y) ) 
#define SHOULD_NOT_EQUAL_DOUBLE(x, y, delta)  CSPEC_EVAL( cspec_fabs( (x) - (y) ) > delta )
#define SHOULD_NOT_MATCH(x, y)                CSPEC_EVAL( cspec_strcmp(x, y) != 0   )
#define SHOULD_NOT_BE_NULL(x)                 CSPEC_EVAL( (x) != 0 )

#define SHOULD_PENDING(reason)			      CSPEC_PENDING(reason)

#ifdef __cplusplus
extern "C" {
#endif


/* Public function definition */

typedef void ( * CSpecDescriptionFun ) ( );
int CSpec_Run( CSpecDescriptionFun fun, CSpecOutputStruct* output);

#ifdef __cplusplus
}
#endif

#endif


/*
 * Copyright 2008 Arnaud Brejeon.
 *
 * Cspec is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as 
 * published by the Free Software Foundation, version 3.
 *
 * CSpec is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 */

