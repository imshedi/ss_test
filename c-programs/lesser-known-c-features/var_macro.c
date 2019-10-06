#include <stdio.h>

#define myfunc(...)	printf(__VA_ARGS__)

int main(void)
{
	myfunc("variable number of args to macro example\n");

	printf("%d\n", __LINE__);
	printf("%s\n", __func__);
	printf("%s\n", __FUNCTION__);
	printf("%s\n", __DATE__);
	printf("%s\n", __FILE__);
	printf("%s\n", __DATE__);
	printf("%s\n", __TIME__);
	printf("%ld\n", __STDC_VERSION__);

#line 200
	printf("%d\n", __LINE__);

	return 0;
}
