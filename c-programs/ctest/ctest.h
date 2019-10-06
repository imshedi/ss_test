#ifndef __CTEST_H__
#define __CTEST_H__

#define _GNU_SOURCE
#include <math.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <setjmp.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdio_ext.h>

/** For datatypes */
#define MYSIZEOF(x)	((x *)0 + 1)

/** For variables */
#define SIZEOF(x)       ((char *)(&x + 1) - (char *)&x)

/** Generic */
#define gen_sizeof(x)	({typeof(x) _tmp_; (char *)(&_tmp_ + 1) - (char *)(&_tmp_);})

#define	INC(x)		(-(~(x)))
#define	DEC(x)          ~(-(x))

/** align macro from kernel */
#define __ALIGN_MASK(x, mask)   (((x) + (mask)) & ~(mask))
#define ALIGN(x, a)             __ALIGN_MASK(x, (typeof(x))(a) - 1)

/** align macro which works on power of two */
#define ALIGN_SIZE(len, pow)	        (((len) + (pow) - 1) & ~((pow) - 1))

/** Check val is pow. of 2 */
#define IS_SIZE_ALIGNED(val, pow)       (!((val) & ((pow) - 1)))

#define FIND_MIN(x, y)	((x) >= (y) ? (y) : (x))
#define FIND_MAX(x, y)	((x) >= (y) ? (x) : (y))
#define UNUSED(param)	((void)(param))
#define CHECK(x)        assert(!(x))
#define SWAP(a, b)      do { a ^= b; b ^= a; a ^= b; } while (0)
#define SIZE(arr)       (sizeof(arr) / sizeof(arr[0]))

#define IS_LITTLE_ENDIAN()	(((*(short int *)"21") & 0XFF) == '2')
#define IS_BIG_ENDIAN()	        (((*(short int *)"21") & 0XFF) == '1')

/** Reverses the bytes of the supplied byte array */
#define REVERSE_BYTE_ARRAY(data, size) \
        do { \
                if (!IS_LITTLE_ENDIAN()) { \
                        int32_t _i; \
                        int32_t _j; \
                        char _tmp; \
                        for (_i = 0, _j = (size) - 1; _i < _j; _i++, _j--) { \
                                _tmp = ((char *)(data))[_i]; \
                                ((char *)(data))[_i] = ((char *)(data))[_j]; \
                                ((char *)(data))[_j] = _tmp; \
                        } \
                } \
        } while (0)

#define GETMEM(ptr, type, size) \
        do { ptr = (type *)malloc(sizeof(type) * (size)) } while (0)

#define FREE(mem)       do { free(mem); mem = NULL; } while (0)

#endif /** __CTEST_H__ */
