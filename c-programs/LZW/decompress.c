#include "lzw.h"
#include "bitfile.h"

static decode_dict_t dict[MAX_CODES - FIRST_CODE];

static int32_t decode(uint32_t code, FILE *fout);
static int32_t get_cword(bit_file_t *bfin, uint8_t clen);

int32_t decompress(FILE *fin, FILE *fout)
{
	uint8_t ch;
	uint32_t code;
	uint32_t lcode;
	bit_file_t *bfin;
	uint32_t ncode = FIRST_CODE;
	uint8_t clen = MIN_CODE_LEN;

	if (!fin || !fout) {
		errno = ENOENT;
		return FAILURE;
	}

	bfin = makebitfile(fin, BF_READ);
	if (!bfin) {
		perror("Making Input File a BitFile");
		return FAILURE;
	}

	lcode = get_cword(bfin, clen);
	if (lcode == EOF) {
		pr_err("get_cword\n");
		goto end;
	}

	if (fputc(lcode, fout) == EOF) {
		pr_err("fputc\n");
		goto end;
	}

	ch = lcode;
	while ((int32_t)(code = get_cword(bfin, clen)) != EOF) {

		while (((CURRENT_MAX_CODES(clen) - 1) == code) &&
				clen < MAX_CODE_LEN) {
			clen++;
			code = get_cword(bfin, clen);
		}

		if (code < ncode) {
			ch = decode(code, fout);
		} else {
			if (fputc(ch, fout) == EOF) {
				pr_err("fputc\n");
				goto end;
			}
			ch = decode(lcode, fout);
		}

		if (ncode < MAX_CODES) {
			dict[ncode - FIRST_CODE].suf = ch;
			dict[ncode - FIRST_CODE].pre = lcode;
			ncode++;
		}

		lcode = code;
	}

end:
	bitfile_to_file(&bfin);

	return SUCCESS;
}

static int32_t decode(uint32_t code, FILE *fout)
{
	int32_t idx = 0;
	int32_t *ch = NULL;

	if (code < FIRST_CODE) {
		if (fputc(code, fout) == EOF) {
			pr_err("fputc\n");
			return FAILURE;
		}

		return code;
	}

	ch = getmem(ch,	sizeof(int32_t) * (code - FIRST_CODE + 2));
	if (!ch) {
		pr_err("malloc\n");
		return FAILURE;
	}

	while (code >= FIRST_CODE) {
		ch[idx++] = dict[code - FIRST_CODE].suf;
		code = dict[code - FIRST_CODE].pre;
	}

	ch[idx] = code;
	while (idx >= 0) {
		if (fputc(ch[idx--], fout) == EOF) {
			pr_err("fputc\n");
			freemem((void *)&ch);
			return FAILURE;
		}
	}

	freemem((void *)&ch);

	return code;
}

static int32_t get_cword(bit_file_t *bfin, uint8_t clen)
{
	int32_t code = 0;

	return (getbit(bfin, &code, clen) < 0) ? EOF : code;
}
