#ifndef __BITFILE_H__
#define __BITFILE_H__

typedef enum {
	BF_READ,
	BF_WRITE,
	BF_APPEND,
	BF_NO_MODE
} BF_MODES;

typedef struct bit_file_t {
	FILE *fp;		/* file pointer used by stdio functions */
	uint8_t bitbuf;	/* bits waiting to be read/written */
	uint8_t bitcnt;	/* number of bits in bitbuf */
	BF_MODES mode;		/* open for read, write, or append */
} bit_file_t;

void bitfile_to_file(bit_file_t **stream);
int32_t bitfile_getbit(bit_file_t *stream);
int32_t bitfile_getchar(bit_file_t *stream);
bit_file_t *makebitfile(FILE *stream, BF_MODES mode);
int32_t bitfile_putbit(int32_t ch, bit_file_t *stream);
int32_t bitfile_putchar(int32_t ch, bit_file_t *stream);
int32_t getbit(bit_file_t *stream, void *code, uint32_t cnt);
int32_t putbit(bit_file_t *stream, void *code, uint32_t cnt);

#endif	/* __BITFILE_H__ */
