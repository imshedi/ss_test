#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _fun(int i)
{
	return i + 1;
}

void fun(int len, char s[_fun(len + 1) << 1])
{
	int i;

	for (i = 1; i < 10; i++) {
		char s1[i + len];

                memset(s1, 0, i + len);

		snprintf(s, (len + 2) << 1, "s: hello-%d", i);
		snprintf(s1, i + len, "s1: world-%d", i);
		printf("%s\n%s\n", s, s1);
	}
}

int main(void)
{
	char s[32] = {0};

	fun(6, s);

	return EXIT_SUCCESS;
}
