#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_zone(void)
{
	char *tz = getenv("TZ");

	printf("TZ: %s\n", tz ? tz : "default EST5EDT");
	printf("\tdaylight: %d\n", daylight);
	printf("\ttimezone: %ld\n", timezone);
	printf("\ttime zone names: %s %s\n", tzname[0], tzname[1]);
}

int main(void)
{
	tzset();
	print_zone();

	setenv("TZ", "PST8PDT", 1);
	tzset();
	print_zone();

	return EXIT_SUCCESS;
}
