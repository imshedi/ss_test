#include <stdio.h>
#include <string.h>

void copy1(char *s1, char *s2, int n)
{
	while (n--)
		*s1++ = *s2++;
}

/*
 * The freedom of pointers in C leads sometimes to slower code.
 * The programmer can enable several optimizations by guarantying that objects
 * referred by pointers do not overlap.
 */
void copy2(char *restrict s1, char *restrict s2, int n)
{
	while (n--)
		*s1++ = *s2++;
}

int main(void)
{
	char s[32] = {0};
	char *str = "hello world!!!";

	copy1(s, str, strlen(str));
	printf("%s\n", s);

	s[0] = '\0';
	copy1(s, str, strlen(str));
	printf("%s\n", s);

	return 0;
}
