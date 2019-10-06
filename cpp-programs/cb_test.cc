#include <iostream>

using namespace std;

typedef struct test {
	int x;
} test;

typedef int(*cbtest)(struct test *);

class car {
	public:
		static int getdata(struct test *t);
};

int car::getdata(struct test *t)
{
	printf("%s: I'm summoned, %d\n", __func__, t->x);

	return 0;
}

static int test1(cbtest cb, int x)
{
	struct test x1 = {.x = x};

	printf("%s: invoking callback\n", __func__);

	cb(&x1);

	return 0;
}

int main(void)
{
	printf("addr1: %p\taddr2: %p\n", car::getdata, &car::getdata);

	printf("Ret: %d\n", test1(car::getdata, 10));

	return 0;
}
