#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define RBUF_SIZE		128
#define SWAP(a, b)		do { a ^= b; b ^= a; a ^= b; } while (0)
#define ARRSIZEOF(arr)          (sizeof(arr) / sizeof(arr[0]))

static int32_t huge_multpn(const char *s1, const char *s2, int32_t *res,
						   const int32_t res_size)
{
	int32_t i;
	int32_t j;
	int32_t l1;
	int32_t l2;
	int32_t *a;
	int32_t *b;
	int32_t ret = -1;

	if (!s1 || !s2 || !*s1 || !*s2 || !res || (res_size <= 0))
		return -1;

	if (!s1[strspn(s1, "0")] || !s2[strspn(s2, "0")]) {
		res[0] = 0;
		return 1;
	}

	l1 = strlen(s1);
	l2 = strlen(s2);

	a = (int32_t *)calloc(l1, sizeof(int32_t));
	b = (int32_t *)calloc(l2, sizeof(int32_t));
	if (!a || !b)
		goto err;

	memset(res, 0, res_size * sizeof(int32_t));

	for (i = l1 - 1, j = 0; i >= 0; i--, j++)
		a[j] = s1[i] - '0';

	for (i = l2 - 1, j = 0; i >= 0; i--, j++)
        b[j] = s2[i] - '0';

	for (i = 0; i < l2; i++) {
		for (j = 0; j < l1; j++)
			res[i + j] += b[i] * a[j];
	}

	l1 += l2;
	for (i = 0; i < l1; i++) {
		res[i + 1] += res[i] / 10;
		res[i] %= 10;
	}

	while ((i >= 0) && !res[i] &&  i--) { }

	ret = i;
	for (j = 0; j < i; j++, i--)
		SWAP(res[j], res[i]);

err:
	if (a)
		free(a);

	if (b)
		free(b);

	return ret;
}

void gen_rand_num_str(char *s, int32_t len)
{
	int32_t i;
	static uint32_t seed = 0;
	const char num[10] = "0123456789";

	if (len <= 0 || !s)
		return;

	/*
	 * Needed because, gen_rand_num_str can be called with very
	 * little delay so using srand(time(NULL)) generates same random numbers
	 * again
	 */
	seed = !seed ? (uint32_t)time(NULL) : (seed + 1);

	len--;
	srand(seed);
	for (i = 0; i < len; ++i)
		s[i] = num[rand() % (sizeof(num) - 1)];

	s[len] = '\0';
}

int32_t main(void)
{
	int32_t i;
	int32_t cnt;
	int32_t ret;
	int32_t res[RBUF_SIZE] = {0};

	printf("Product of 123456789 and 123456789 is: ");
	ret = huge_multpn("123456789", "123456789", res, ARRSIZEOF(res));
	for (i = 0; i <= ret; i++)
		printf("%d", res[i]);

	printf("\n");

	printf("Product of 999999999 and 999999999 is: ");
	ret = huge_multpn("999999999", "999999999", res, ARRSIZEOF(res));
	for (i = 0; i <= ret; i++)
		printf("%d", res[i]);

	printf("\n");

	srand(time(NULL));
	for (cnt = 0; cnt < 10; cnt++) {
		char s1[16] = {0};
		char s2[16] = {0};

		gen_rand_num_str(s1, rand() % sizeof(s1));
		gen_rand_num_str(s2, rand() % sizeof(s2));

		printf("Product of %s and %s is: ", s1, s2);
		ret = huge_multpn(s1, s2, res, ARRSIZEOF(res));

		for (i = 0; i <= ret; i++)
			printf("%d", res[i]);

		printf("\n");

		memset(res, 0, sizeof(res));
	}

	return 0;
}
