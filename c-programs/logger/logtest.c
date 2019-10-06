#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "logger.h"

int32_t write_to_file(bool is_close)
{
	static FILE *fp = NULL;

	if (is_close && fp) {
		fclose(fp);
		return 0;
	}

	fp = fopen("app.log", "w+");
	if (!fp) {
		log_err("fopen error\n");
		return -1;
	}

	log_set_fp(fp);

	return 0;
}

int32_t main(void)
{
	printf("start: logtest\n\n");

	log_set_quiet(true);
	write_to_file(false);

	log_dbg("%s: log_dbg\n", __func__);
	log_err("%s: log_err\n", __func__);
	log_info("%s: log_info\n", __func__);
	log_warn("%s: log_warn\n", __func__);
	log_trace("%s: log_trace\n", __func__);
	log_fatal("%s: log_fatal\n", __func__);

	write_to_file(true);
	printf("end: logtest\n");

	return EXIT_SUCCESS;
}
