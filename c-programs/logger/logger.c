#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"

static struct {
	FILE *fp;
	int32_t level;
	int32_t quiet;
	void *udata;
	log_LockFn lock;
} L;

static const char *level_names[] = {
	"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

static void xlock(bool val)
{
	if (L.lock)
		L.lock(L.udata, val);
}

void log_set_udata(void *udata)
{
	L.udata = udata;
}

void log_set_lock(log_LockFn fn)
{
	L.lock = fn;
}

void log_set_fp(FILE *fp)
{
	L.fp = fp;
}

void log_set_level(int level)
{
	L.level = level;
}

void log_set_quiet(bool enable)
{
	L.quiet = enable;
}

void logger(int level, const char *file, int line, const char *fmt, ...)
{
	time_t t;
	FILE *stream;
	va_list args;
	struct tm *lt;
	char buf[32] = {0};

	if (level < L.level)
		return;

	/* Acquire lock */
	xlock(true);

	/* Get current time */
	t = time(NULL);
	lt = localtime(&t);
	buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';

	/* Log to stderr */
	if (!L.quiet)
		stream = stderr;

	/* Log to file */
	if (L.fp)
		stream = L.fp;

	fprintf(stream, "%s %-5s %s:%d: ", buf, level_names[level], file, line);
	va_start(args, fmt);
	vfprintf(stream, fmt, args);
	va_end(args);
	fprintf(stream, "\n");
	fflush(stream);

	/* Release lock */
	xlock(false);
}
