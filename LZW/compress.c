#include "lzw.h"
#include "bitfile.h"

static void freedict(dict_node_t **node);
static uint32_t makekey(uint32_t pre, uint8_t suf);
static dict_node_t *mknode(uint32_t code, uint32_t pre, uint8_t suf);
static dict_node_t *find_entry(dict_node_t *root, uint32_t pre, uint8_t ch);

int32_t compress(FILE *fin, FILE *fout)
{
	int32_t ch;
	int32_t code;
	bit_file_t *bfpout;
	dict_node_t *node;
	dict_node_t *droot = NULL;
	int32_t ret = FAILURE;
	uint32_t ncode = FIRST_CODE;
	uint8_t clen = MIN_CODE_LEN;

	code = fgetc(fin);
	if (code == EOF)
		return ret;

	ch = fgetc(fin);
	if (ch == EOF)
		return ret;

	droot = mknode(ncode++, code, ch);
	if (!droot) {
		perror("mknode\n");
		return ret;
	}

	bfpout = makebitfile(fout, BF_WRITE);
	if (!bfpout) {
		pr_err("makebitfile\n");
		goto end;
	}

	if (putbit(bfpout, &code, clen) < 0) {
		pr_err("putbit\n");
		goto end;
	}

	code = ch;
	while ((ch = fgetc(fin)) != EOF) {
		node = find_entry(droot, code, ch);
		if (node->pre == code && node->suf == ch) {
			code = node->code;
			continue;
		}

		if (ncode >= MAX_CODES) {
			pr_err("dictionary full\n");
			goto end;
		}

		dict_node_t *tmp;

		tmp = mknode(ncode, code, ch);
		if (!tmp) {
			pr_err("mknode\n");
			goto end;
		}

		if (makekey(code, ch) < makekey(node->pre, node->suf))
			node->left = tmp;
		else
			node->right = tmp;

		while (code >= (CURRENT_MAX_CODES(clen) - 1) &&
		       clen < MAX_CODE_LEN) {
			int32_t tmp;

			tmp  = (CURRENT_MAX_CODES(clen) - 1);
			if (putbit(bfpout, &tmp, clen) < 0) {
				pr_err("putbit\n");
				goto end;
			}

			clen++;
		}

		if (putbit(bfpout, &code, clen) < 0) {
			pr_err("putbit\n");
			goto end;
		}

		code = ch;
		ncode++;
	}

	if (putbit(bfpout, &code, clen)  < 0) {
		pr_err("putbit\n");
		goto end;
	}

	ret = SUCCESS;
end:
	bitfile_to_file(&bfpout);
	freedict(&droot);

	return ret;
}

static uint32_t makekey(uint32_t pre, uint8_t suf)
{
	uint32_t key;

	key = (suf & MASK2)  << MAX_CODE_LEN;
	key |= (pre << EXCESS) | (suf & MASK1);

	return key;
}

static dict_node_t *mknode(uint32_t code, uint32_t pre, uint8_t suf)
{
	dict_node_t *node = NULL;

	node = getmem(node, sizeof(dict_node_t));
	if (!node) {
		pr_err("malloc\n");
		return NULL;
	}

	node->left = NULL;
	node->right = NULL;
	node->pre = pre;
	node->suf = suf;
	node->code = code;

	return node;
}

static void freedict(dict_node_t **node)
{
	if (!*node)
		return;

	if (&(*node)->left)
		freedict(&(*node)->left);

	if (&(*node)->right)
		freedict(&(*node)->right);

	freemem((void *)node);
}

static dict_node_t *find_entry(dict_node_t *root, uint32_t pre, uint8_t ch)
{
	uint32_t skey;

	if (!root)
		return NULL;

	skey = makekey(pre, ch);

	while (root) {
		uint32_t key;

		key = makekey(root->pre, root->suf);
		if (key == skey)
			return root;

		if ((skey < key) && root->left)
			root = root->left;
		else if (root->right)
			root = root->right;
		else
			break;
	}

	return root;
}
