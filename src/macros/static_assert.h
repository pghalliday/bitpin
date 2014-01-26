#ifndef STATIC_ASSERT_H
#define STATIC_ASSERT_H

#include "paste.h"

#define STATIC_ASSERT(condition, message) typedef char PASTE(PASTE(message, __STATIC_ASSERT__), __COUNTER__)[(condition)?1:-1]

#endif