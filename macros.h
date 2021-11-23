#ifndef __MACROS_H
#define __MACROS_H
#include <cassert> /*assert*/
#define DEBUG 2
#define DEINIT_ASSERT(X) assert("During deinit:" && X)
#define GLUE_(X, Y) X##Y
#define GLUE GLUE_

#ifdef __cplusplus
#define COUT std::cout
#define CLOG std::clog
#define CERR std::cerr
#define ENDL std::endl
#if DEBUG>0
#	define DEBUG1(X) X
#endif
#if DEBUG>1
#	define DEBUG2(X) X
#endif
#else /*not C++*/
#define CERR(X, ...) printf(X, __VA_ARGS)
#endif /*not C++*/
#define IFDEBUG(LEVEL, X) GLUE(DEBUG, LEVEL)(X)
#endif

