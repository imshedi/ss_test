#ifndef __LZW_HDR_H__
#define __LZW_HDR_H__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>

#define FEXT		".lzw"
#define SUCCESS         0
#define FAILURE         -1
#define MASK1		0xF
#define MASK2		0xF0
#define EXCESS		4
#define BYTESIZE	8
#define MIN_CODE_LEN    9
#define MAX_CODE_LEN    20

#define FIRST_CODE      (1 << CHAR_BIT)
#define MAX_CODES       (1 << MAX_CODE_LEN)

#if (MIN_CODE_LEN <= CHAR_BIT)
#error Code words must be larger than 1 character
#endif

#if ((MAX_CODES - 1) > INT_MAX)
#error There cannot be more codes than can fit in an integer
#endif

#define CURRENT_MAX_CODES(BITS)     ((uint32_t)(1 << (BITS)))

#define pr_err(...) \
	do { \
		fprintf(stderr, "Error: %s:%s:%d\n", \
				__FILE__, __func__, __LINE__); \
		fprintf(stderr, __VA_ARGS__); \
	} while (0)

typedef enum {
	COMPRESS,
	DECOMPRESS
} action;

typedef int32_t(*func) (FILE *, FILE *);

typedef struct decode_dict_t {
	uint8_t suf;
	uint32_t pre;
} decode_dict_t;

/* node in dictionary tree */
typedef struct dict_node_t {
	uint8_t suf;
	uint32_t pre;
	uint32_t code;
	struct dict_node_t *left;
	struct dict_node_t *right;
} dict_node_t;

void freemem(void **ptr);
void *getmem(void *ptr, int32_t size);
int32_t compress(FILE *fin, FILE *fout);
int32_t decompress(FILE *fin, FILE *fout);

#endif				/*! __LZW_HDR_H__ */
