#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

static char **genv;
static char **gargv;
static int32_t gargc;

static void print_argv_envs(void)
{
	int32_t i;

	for (i = 0; i < gargc; i++)
		printf("argv[%d] --> %s\n", i, gargv[i]);

	for (i = 0; genv[i]; i++)
		printf("env[%d] --> %s\n", i, genv[i]);

	printf("\n");
}

int main(int32_t argc, char **argv, char **env)
{
	genv = env;
	gargc = argc;
	gargv = argv;

	print_argv_envs();

	return EXIT_SUCCESS;
}
