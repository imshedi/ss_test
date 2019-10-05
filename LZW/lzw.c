#include <string.h>
#include <unistd.h>

#include "lzw.h"

static void print_usage(int32_t ret);
static int32_t open_file(FILE **fp, char *name, char *mode);

void freemem(void **ptr)
{
	char *tmp = (char *)*ptr;

	free(tmp);
	tmp = NULL;
}

void *getmem(void *ptr, int32_t size)
{
	ptr = malloc(size);
	if (!ptr) {
		pr_err("malloc\n");
		return NULL;
	}

	return ptr;
}

static int32_t open_file(FILE **fp, char *name, char *mode)
{
	*fp = fopen(name, mode);
	if (!*fp) {
		pr_err("fopen\n");
		return FAILURE;
	}

	return SUCCESS;
}

static void print_usage(int32_t ret)
{
	printf("\nUsage:\nlzw <command> <input file>\n\n");
	printf("<Commands>\n-c\tCompress\n-d\tDecompress\n\n");
	exit(ret);
}

int32_t main(int32_t argc, char **argv)
{
	FILE *fin;
	FILE *fout;
	int32_t opt;
	action act = -1;
	int32_t ret = EXIT_FAILURE;
	func fun[] = { compress, decompress };

	if (argc != 3)
		print_usage(EXIT_FAILURE);

	while ((opt = getopt(argc, argv, "c:d:h")) != -1) {
		switch (opt) {
		case 'c':
			if (open_file(&fin, optarg, "r")) {
				pr_err("open_file");
				return EXIT_FAILURE;
			}

			act = COMPRESS;
			strcat(optarg, FEXT);
			if (open_file(&fout, optarg, "w+b")) {
				pr_err("open_file");
				goto end;
			}

			break;

		case 'd': {
			int32_t len = strlen(optarg) + 2;

			if (len >= sizeof(FEXT))
				len -= sizeof(FEXT);

			char fname[len];

			if (open_file(&fin, optarg, "r")) {
				pr_err("open_file");
				return EXIT_FAILURE;
			}

			act = DECOMPRESS;
			memset(fname, '\0', sizeof(fname));
			strncpy(fname, optarg, sizeof(fname) - 1);

			if (open_file(&fout, fname, "w+")) {
				pr_err("open_file");
				goto end;
			}

			break;
		}

		case 'h':
			 print_usage(EXIT_SUCCESS);
			break;

		default:
			print_usage(EXIT_FAILURE);
			break;
		}
	}

	if (act == -1)
		return EXIT_FAILURE;

	ret = fun[act] (fin, fout);
	printf("%sompression %s\n", (act == COMPRESS) ? "C" : "De",
				    (!ret) ? "success" : "failed");

	fclose(fout);
end:
	fclose(fin);

	return ret;
}
