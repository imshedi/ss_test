#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#define LOG_VERSION "0.1.0"

typedef void (*log_LockFn)(void *udata, int32_t lock);

enum {
	LOG_TRACE = 0,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL
};

#define log_err(...)	logger(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_dbg(...)	logger(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)	logger(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)	logger(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_trace(...)	logger(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...)	logger(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

void log_set_fp(FILE *fp);
void log_set_quiet(bool enable);
void log_set_udata(void *udata);
void log_set_lock(log_LockFn fn);
void log_set_level(int32_t level);
void logger(int32_t level, const char *file, int32_t line, const char *fmt, ...);

#endif /* __LOGGER_H__ */
