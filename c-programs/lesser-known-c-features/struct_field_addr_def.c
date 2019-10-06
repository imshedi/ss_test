#include <stdio.h>

struct fops {
	int open;
	int read;
	int write;
	int close;
};

int main(void)
{
	// Old span
	struct fops f1 = { open: 0, close: 1, read: 2 };

	// New span
	struct fops f2 = { .open = 0, .close = 1, .read = 2 };

	printf("o: %d r: %d w: %d c: %d\n", f1.open, f1.read, f1.write, f1.close);
	printf("o: %d r: %d w: %d c: %d\n", f2.open, f2.read, f2.write, f2.close);

	return 0;
}
