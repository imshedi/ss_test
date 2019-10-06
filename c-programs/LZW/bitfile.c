#include "lzw.h"
#include "bitfile.h"

static uint8_t do_math(int32_t ch, bit_file_t *stream);

bit_file_t *makebitfile(FILE *stream, BF_MODES mode)
{
	bit_file_t *bf = NULL;

	bf = getmem(bf, sizeof(bit_file_t));
	if (!bf)
		return NULL;

	bf->fp = stream;
	bf->bitcnt = 0;
	bf->bitbuf = 0;
	bf->mode = mode;

	return bf;
}

void bitfile_to_file(bit_file_t **stream)
{
	if (((*stream)->mode != BF_WRITE && (*stream)->mode != BF_APPEND) ||
	     !(*stream)->bitcnt)
		goto end;

	(*stream)->bitbuf <<= BYTESIZE - (*stream)->bitcnt;

	if (fputc((*stream)->bitbuf, (*stream)->fp) == EOF)
		pr_err("fputc\n");

end:
	freemem((void *)stream);
}

static uint8_t do_math(int32_t ch, bit_file_t *stream)
{
	uint8_t ret;

	ret = ((uint8_t)ch) >> stream->bitcnt;
	ret |= stream->bitbuf << (BYTESIZE - stream->bitcnt);
	stream->bitbuf = ch;

	return ret;
}

int32_t bitfile_getchar(bit_file_t *stream)
{
	int32_t ret;

	ret = fgetc(stream->fp);
	if (!stream->bitcnt || ret == EOF)
		return ret;

	return do_math(ret, stream);
}

int32_t bitfile_putchar(int32_t ch, bit_file_t *stream)
{
	if (!stream->bitcnt)
		return fputc(ch, stream->fp);

	if (fputc(do_math(ch, stream), stream->fp) == EOF)
		return EOF;

	return SUCCESS;
}

int32_t bitfile_getbit(bit_file_t *stream)
{
	int32_t ret;

	if (!stream->bitcnt) {
		ret = fgetc(stream->fp);
		if (ret == EOF)
			return EOF;

		stream->bitbuf = ret;
		stream->bitcnt = BYTESIZE;
	}

	stream->bitcnt--;
	ret = stream->bitbuf >> stream->bitcnt;

	return (ret & 0x1);
}

int32_t bitfile_putbit(int32_t ch, bit_file_t *stream)
{
	stream->bitcnt++;
	stream->bitbuf <<= 0x1;

	if (ch)
		stream->bitbuf |= 0x1;

	/* write bit buffer if we have 8 bits */
	if (stream->bitcnt != BYTESIZE)
		return SUCCESS;

	if (fputc(stream->bitbuf, stream->fp) == EOF)
		return EOF;

	/* reset buffer */
	stream->bitcnt = 0;
	stream->bitbuf = 0;

	return SUCCESS;
}

int32_t getbit(bit_file_t *stream, void *code, uint32_t cnt)
{
	int32_t off;
	int32_t ret;
	uint8_t *bytes = code;

	for (off = 0; cnt >= BYTESIZE; off++, cnt -= BYTESIZE) {
		ret = bitfile_getchar(stream);
		if (ret == EOF)
			return FAILURE;

		bytes[off] = (uint8_t)ret;
	}

	while (cnt--) {
		ret = bitfile_getbit(stream);
		if (ret == EOF)
			return FAILURE;

		bytes[off] = (bytes[off] << 0x1) | (ret & 0x1);
	}

	return SUCCESS;
}

int32_t putbit(bit_file_t *stream, void *code, uint32_t cnt)
{
	int32_t ret;
	int32_t off;
	uint8_t *bytes = code;

	for (off = 0; cnt >= BYTESIZE; off++, cnt -= BYTESIZE) {
		if (bitfile_putchar(bytes[off], stream) == EOF)
			return FAILURE;
	}

	for (ret = 0; cnt; ret <<= 0x1, cnt--) {
		if (!ret)
			ret = bytes[off] << (BYTESIZE - cnt);

		if (bitfile_putbit(ret & 0x80, stream) == EOF)
			return FAILURE;
	}

	return SUCCESS;
}
