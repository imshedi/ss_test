#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void listFiles(const char *path);
void listFilesRecursively(char *path);
void tree(char *basePath, const int root);

/*
 * Lists all files and sub-directories at given path.
 */
void listFiles(const char *path)
{
	DIR *dir;
	struct dirent *dp;

	dir = opendir(path);
	if (!dir)
		return;

	while ((dp = readdir(dir)))
		printf("%s\n", dp->d_name);

	closedir(dir);
}

/*
 * Lists all files and sub-directories recursively
 * considering path as base path.
 */
void listFilesRecursively(char *basePath)
{
	DIR *dir;
	struct dirent *dp;
	int total_size = 0;

	dir = opendir(basePath);
	if (!dir)
		return;

	while ((dp = readdir(dir))) {
		if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
			char path[1024] = {0};

			printf("%s\n", dp->d_name);
			sprintf(path, "%s/%s", basePath, dp->d_name);
			listFilesRecursively(path);
		}
	}

	closedir(dir);
}

/*
 * Tree, prints all files and sub-directories of a given
 * directory in tree structure.
 *
 * @param basePath Base path to traverse directory
 * @param root     Integer representing indention for current directory
 */
void tree(char *basePath, const int root)
{
	DIR *dir;
	struct dirent *dp;

	dir = opendir(basePath);
	if (!dir)
		return;

	while ((dp = readdir(dir))) {
		if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
			int i;
			char path[1024] = {0};

			for (i = 0; i < root; i++)
				printf("%c", !(i & 1) ? '|' : ' ');

			printf("|-%s\n", dp->d_name);
			sprintf(path, "%s/%s", basePath, dp->d_name);
			tree(path, root + 2);
		}
	}

	closedir(dir);
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Usage --> ./exec <path>\n");
		return -1;
	}

	//tree(argv[1], 0);
	//listFiles(argv[1]);
	listFilesRecursively(argv[1]);

	return 0;
}
