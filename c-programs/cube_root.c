#include <stdio.h>
#include <stdint.h>

int32_t croot(int32_t num)
{
	uint32_t beg;
	uint32_t end;

	if (num < 2)
		return (num < 0) ? -1 : num;

	/*
	 * Cube root of a number can't exceed 2^(n/2)
	 * Example:
	 * (999 * 999 * 999)  = 997,002,999 [0011 1011 0110 1101 0000 1110 1111 0111]
	 * Highest set bit is 29, so cube root can't exceed 2^(29/2) = (1 << 14)
	 * This is an optimization, by seeing 8(1000 in binary) cuberoot being 2(0010)
	 */
	for (beg = 31; !(num & (1 << beg)); beg--) { }
	end = 1 << (beg >> 1);

	for (beg = 2; beg <= end; ) {
		uint64_t mid = (beg + end) >> 1; // Try using uint32_t for mid, magic.
		uint64_t cube = mid * mid * mid;

		if (cube == (uint64_t)num)
			return (int32_t)mid;

		(cube > (uint64_t)num) ? (end = mid - 1) : (beg = mid + 1);
	}

	return -1;
}

int32_t main(void)
{
	int32_t i;

	printf("\n*** Cube Root using Binary Search ***\n");
	for (i = 0; i < 1001; i++) {
		uint32_t n = i * i * i;
		int32_t res = croot(n);

		printf("Cube root of (%d)%u is: %d\n", i, n, res);
		if (res != i)
			break;
	}

	return 0;
}
