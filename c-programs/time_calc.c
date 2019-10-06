#include <stdio.h>
#include <time.h>
#include <string.h>

int make_time(struct tm *info)
{
	int ret;
	time_t t;
	struct tm tm;

	t = time(NULL);
	tm = *localtime(&t);
	tm.tm_sec = 1800;

	ret = mktime(&tm);
	if (ret < 0) {
		printf("Error: unable to make time using mktime\n");
	} else {
		char buf[80] = {0};

		strftime(buf, sizeof(buf), "%c", &tm);
		printf("%s\n", buf);
	}

	memcpy(info, &tm, sizeof(struct tm));

	return 0;
}

int main(void)
{
	struct tm tm = {0};

	make_time(&tm);

	printf("%d %d\n", tm.tm_hour, tm.tm_min);

	return 0;
}
