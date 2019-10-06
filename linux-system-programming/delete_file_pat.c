/* Use this program with extreme caution */
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <libgen.h>

static char *getextn(char *fname)
{
	char *dot;

	return (dot = strrchr(fname, '.')) ? (dot + 1) : dot;
}

static int32_t _del_pattern(char *pattern)
{
	DIR *d;
	struct dirent *entry;

	d = opendir(".");
	if (!d) {
		fprintf(stderr, "%s: Cannot open directory->(%s)\n", __func__,
				strerror(errno));
		return -errno;
	}

	for (entry = readdir(d); entry; entry = readdir(d)) {
		char *ext1 = getextn(pattern);
		char *ext2 = getextn(entry->d_name);

		if (ext1 && ext2) {
			if (strcmp(ext1, ext2))
				continue;
		}

                printf("Are you sure to delete: %s [y/n]\n", entry->d_name);
                if (getchar() != 'y')
                        continue;

		printf("Deleting: %s\n", entry->d_name);
		remove(entry->d_name);
	}
	closedir(d);

	return 0;
}

static void del_pattern(int32_t argc, char **pattern)
{
	int32_t i;
	char *dir;
	int32_t ret;

	dir = strdup(pattern[1]);
	if (!dir) {
		fprintf(stderr, "strdup failed(%s)\n", strerror(errno));
		return;
	}

	printf("Changing directory to -> %s\n", dir);
	ret = chdir(dirname(dir));
	free(dir);

	if (ret) {
		fprintf(stderr, "chdir(to %s) failed(%d:%s)\n", dir, errno,
				strerror(errno));
		return;
	}

	for (i = 1; i < argc; i++) {
		if (_del_pattern(basename(pattern[i])) < 0)
			fprintf(stderr, "Operation failed for(%s)\n", pattern[i]);
	}
}

int32_t main(int32_t argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "\nInput argument(s) err\n");
		fprintf(stderr, "\nExample:\n\n%s *.txt *.bak\n\n", argv[0]);

		return EXIT_FAILURE;
	}

	del_pattern(argc, argv);

	return EXIT_SUCCESS;
}
