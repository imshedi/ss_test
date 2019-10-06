#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _s {
	int i;
	unsigned int u;
	char end[];
} s;

int main(void)
{
	s *test;

	test = (s *)calloc(1, sizeof(s) + 32);
	if (!test) {
		perror("memory alloc failed\n");
		return EXIT_FAILURE;
	}

	test->i = 1;
	test->u = 2;
	strcpy(test->end, "hello world\n");

	printf("i: %d u: %u end: %s\n", test->i, test->u, test->end);

	free(test);

	return EXIT_SUCCESS;
}
