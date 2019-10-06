#include <stdio.h>

struct point {
	int x;
	int y;
};

void _foo(struct point p1, struct point p2)
{
	printf("x: %d y: %d\n", p1.x, p1.y);
	printf("x: %d y: %d\n", p2.x, p2.y);
}

int main(void)
{
	char **sx;
	struct point p1;
	struct point p2 = {2, 4}; // this is standard

	p1 = (struct point){1, 3}; // this is new

	_foo(p1, p2);

	// passing to the function
	_foo((struct point){10, 11}, (struct point){1, 2});

	// constructing an array
	sx = (char *[]){ "Adam", "Eva", "Simon"};
	printf("0: %s 1: %s 2: %s\n", sx[0], sx[1], sx[2]);

	return 0;
}
