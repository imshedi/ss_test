#include <stdio.h>

void print_arr(char *ptr, int size, char *ptr)
{
	int i;

	for (i = 0; i < size; i++)
		printf("%d ", ptr[i]);

	printf("\n");
}

int main(void)
{
	int i;
	// initializing an array of char
	char a[7] = { [5] = 1, [2] = 3, 2 }; //a[7] = { 0, 0, 3, 2, 0, 1, 0};

	// initializing an array of struct
	struct { int x, y; } ar[4] = { [1].x = 23, [3].y = 34, [1].y = -1, [1].x = 12 }; // results in ar[4] = {{0, 0}, {12, -1}, {0, 0}, {0, 34}};

	// interesting usage
	char forbidden[256] = { ['a'] = 1, ['e'] = 2, ['i'] = 3, ['o'] = 4, ['u'] = 5 };

	print_arr(a, sizeof(a));
	print_arr(forbidden, sizeof(forbidden));

	for (i = 0; i < 4; i++)
		printf("st(x): %d st(y): %d\n", ar[i].x, ar[i].y);

	return 0;
}
