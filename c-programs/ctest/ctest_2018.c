#include "ctest.h"

static char **genv;
static char **gargv;
static int32_t gargc;

#if 0
void write_infinte_stderr(void)
{
	int c = 0;

	while (write(fileno(stderr), &c, read(fileno(stdin), &c, 1)) == 1);
}
#endif

#if 0
void mul_without_asterisk(void)
{
	/* Multiplication algorithm */
	int32_t i;
	int32_t tmp;
	int32_t m = 12;
	int32_t n = 14;
	int32_t res = 0;

	for (i = 0; tmp = (m >> i); i++) {
		if (tmp & 1)
			res += (n << i);
	}

	printf("Product: %d\n", res);
}
#endif

#if 0
/* Vardiac macro example */
#define xyz			print
#define abc(...)	xyz(__VA_ARGS__)
#define PRINT(...)	abc(__VA_ARGS__)

void print(const char *fmt, ...)
{
	va_list args;
	char str[256] = {0};

	va_start(args, fmt);
	vsprintf(str, fmt, args);
	va_end(args);

	printf("%s\n", str);
}

void fun(void)
{
	PRINT("[%s %s, %s] %d\n", __func__, __DATE__, __TIME__, __LINE__);
}
#endif

#if 0
typedef struct _str {
	char str[32];
} str;

typedef struct _str_t {
	str st;
	void *ptr;
} str_t;

void _struct_test(void *p)
{
	str_t s = *(str_t *)p;
	str_t *st = &s;

	printf("%s\n", st->st.str);
}

int struct_test(void)
{
	str_t st = {0};

	strcpy(st.st.str, "hello world");
	st.ptr = &st.st.str;

	_struct_test(&st);

	return 0;
}
#endif

#if 0
void fizzbuzz(void)
{
	int32_t num;

	for (num = 1; num < 100; num++)
		printf("%d->%s  ", num, !(num % 15) ? "FizzBuzz" : (!(num % 3) ?
				"Fizz" : (!(num %5) ? "Buzz" : "\b\b\b")));

	printf("\n");
}
#endif

#if 0
void cool_ct_assert(void)
{
#define SIZE 4
#define ct_assert(e) ((void)sizeof(char[1 - 2 * !(e)]))

    ct_assert(sizeof(int) == SIZE);

#undef SIZE
#undef ct_assert
}
#endif

#if 0
void ice(void)
{
#define ICE_P(x) (sizeof(long) == sizeof(*(8 ? ((void *)((x) * 0l)) : (long *)1)))

#define max(a, b) (a > b ? a : b)

	int var = 1;

	printf("ICE test0: %d\n", ICE_P(1));
	printf("ICE test1: %d\n", ICE_P(1 + var));
	printf("ICE test2: %d\n", sizeof(*((void *)((1 + var) * 0l))));
	printf("ICE test2: %d\n", sizeof(*((void *)((1) * 0l))));
	printf("ICE test3: %d\n", sizeof(*(int *)0));

	scanf("%d", &var);

	char a[max(1, 2)];
	printf("%s\n", a);

#undef max
#undef ICE_P
}
#endif

#if 0
void ptr_math(void)
{
	printf("%p %p %p\n", (char *)NULL + 1, (int *)NULL + 1, (void *)NULL + 1);
}
#endif

#if 0
void ascii_rotation(void)
{
#define START	' '
#define END	'~'

	int32_t i;
	int32_t cnt = 0;

	printf("  | ");
	for (i = START; i <= END; i++) {
		printf("%c", i);
		cnt++;
	}

	printf("\n");
	for (i = 0; i < cnt; i++)
		printf("-");
	printf("\n");

	for (i = START; i <= END; i++) {
		int32_t j = i;
		int32_t tmp = cnt;

		printf("%c | ", j);
		while (tmp--) {
			printf("%c", j++);

			if (j > END)
				j = START;
		}
		printf("\n");
	}

#undef START
#undef END
}
#endif

#if 0
void sizeof_member(void)
{
	struct st {
		int a;
		int b[16];
		char c[32];
	};

	printf("%u\n", sizeof(((struct st *)0)->a));
}
#endif

#if 0
void banana_puzzle(void)
{
	uint32_t p1;
	uint32_t p2;
	uint32_t p3;
	uint32_t num;
	uint32_t monkey = 0;
	uint32_t num_solns = 0;

	for (num = 51; num < 100; num++) {
		if ((num % 3) == 1 && ((num / 3) % 3) == 1 && ((num / 9) % 3) == 1) {
			uint32_t tmp = num;

			num_solns++;
			printf("\n\nSolution number: %u\n", num_solns);
			printf("Initial number of bananas: %u\n", num);

			monkey++;
			p1 = tmp / 3;
			tmp -= p1 + 1;
			printf("Person-1 took: %u bananas\n", p1);

			monkey++;
			p2 = tmp / 3;
			tmp -= p2 + 1;
			printf("Person-2 took: %u bananas\n", p2);

			monkey++;
			p3 = tmp / 3;
			tmp -= p3 + 1;
			printf("Person-3 took: %u bananas\n", p3);


			monkey++;
			tmp--;
			tmp /= 3;
			printf("Everyone shared: %u bananas\n", tmp);

			printf("Monkey got: %u bananas\n", monkey);
			printf("As a whole: %u + %u + %u + (%u * 3) + %u = %u\n", p1, p2,
					p3,	tmp, monkey, p1 + p2 + p3 + (tmp * 3) + monkey);
			monkey = 0;
		}
	}
}
#endif

#if 0
void validate_ip(void)
{
    int32_t res;
    struct sockaddr_in sa;
    char ip[] = "127.0.0.1";

    res = inet_pton(AF_INET, ip, &sa.sin_addr);

    printf("IP address %s is %s\n", ip, res ? "valid" : "invalid");
}
#endif

#if 0
#ifndef pr_fmt
#define pr_fmt(fmt)     fmt
#endif

#define pr_info(fmt, ...)	printf(pr_fmt(fmt), ##__VA_ARGS__)

void urlunescape(void)
{
	char pbuf[] = "SHREENIDHI SHEDI";
	char *pbuffer = pbuf;
	int len = strlen(pbuf);

	pr_info("%s\n", strlwr(pbuf));

	for ( ; len > 0; pbuffer++, len--) {
		char *tmp = strstr(pbuffer, "%20");
		if (!tmp)
			break;

		*tmp++ = ' ';
		memmove(tmp, tmp + 2, len);
		len -= 2;
	}

	pr_info("%s\n", pbuf);
}
#endif

int32_t main(int32_t argc, char **argv, char **env)
{
        genv = env;
        gargc = argc;
        gargv = argv;

        fun();

        printf("\n\n");

        return EXIT_SUCCESS;
}
