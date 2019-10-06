#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

void fibo(int32_t n)
{
	uint64_t t1 = 0;
	uint64_t t2 = 1;

	for ( ; n >= 1; n--) {
		uint64_t nextTerm = t1 + t2;

		printf("%" PRIu64 "\n", t1);
		t1 = t2;
		t2 = nextTerm;
	}
}

int32_t main(void)
{
	int32_t num = 0;

	printf("\nEnter number of terms\n");
	scanf("%d", &num);

	fibo(num);

	return EXIT_SUCCESS;
}
