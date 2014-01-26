#ifndef PASTE_H
#define PASTE_H

#define _PASTE(a, b) a##b
#define PASTE(a, b) _PASTE(a, b)

#endif