#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <malloc.h>
#include <stdint.h>

static void display_mallinfo(void)
{
	struct mallinfo mi;

	mi = mallinfo();

	printf("Total non-mmapped bytes (arena):       %d\n", mi.arena);
	printf("# of free chunks (ordblks):            %d\n", mi.ordblks);
	printf("# of free fastbin blocks (smblks):     %d\n", mi.smblks);
	printf("# of mapped regions (hblks):           %d\n", mi.hblks);
	printf("Bytes in mapped regions (hblkhd):      %d\n", mi.hblkhd);
	printf("Max. total allocated space (usmblks):  %d\n", mi.usmblks);
	printf("Free bytes held in fastbins (fsmblks): %d\n", mi.fsmblks);
	printf("Total allocated space (uordblks):      %d\n", mi.uordblks);
	printf("Total free space (fordblks):           %d\n", mi.fordblks);
	printf("Topmost releasable block (keepcost):   %d\n", mi.keepcost);
}

int32_t main(void)
{
	int *alloc;

	printf("============== Before allocating blocks ==============\n");
	display_mallinfo();

	alloc = (int *)malloc(32 * sizeof(int));
	if (!alloc) {
		perror("malloc\n");
		return EXIT_FAILURE;
	}

	printf("\n============== After allocating blocks ==============\n");
	display_mallinfo();

	free(alloc);

	printf("\n============== After freeing blocks ==============\n");
	display_mallinfo();

	return EXIT_SUCCESS;
}
