/*
 * Linux daemon creation sample program.
 * Author: Shreenidhi Shedi <yesshedi@gmail.com>
 *
 * To compile:	gcc -o daemonize daemonize.c
 * To run: ./daemonize
 * To test daemon:	ps -ef | grep daemonize
 * To test log:         tail -f /tmp/exampled.log
 * To test signal:	kill -HUP `cat /tmp/daemonize.pid`
 * To terminate:	kill `cat /tmp/daemonize.pid`
 */

#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>

typedef enum {
	LOG_EMERG,	        /* system is unusable */
	LOG_ALERT,		/* action must be taken immediately */
	LOG_CRIT,		/* critical conditions */
	LOG_ERR,		/* error conditions */
	LOG_WARN,		/* warning conditions */
	LOG_NOTICE,		/* normal but significant condition */
	LOG_INFO,		/* informational */
	LOG_DBG			/* debug-level messages */
} loglevel;

#define RUNNING_DIR	"/tmp"
#define PID_FILE	"daemonize.pid"
#define LOG_FILE	"daemonize.log"

static FILE *logfile;

#define logmsg(lvl, msg, ...) \
	do { \
		if (lvl == LOG_INFO || lvl == LOG_DBG || lvl == LOG_NOTICE) \
			_logmsg(lvl, ""msg"", ##__VA_ARGS__); \
		else \
			_logmsg(lvl, "[%s->%s:%d] "msg"", __FILE__, __func__, \
                                     __LINE__, ##__VA_ARGS__); \
	} while (0)

void _logmsg(loglevel lvl, const char *fmt, ...)
{
        time_t now;
        va_list arg;
        struct tm *sTm;
        char buf[32] = {0};
        static uint64_t linenum;
        char *logstr[] = {"EMERGENCY", "ALERT", "CRITICAL", "ERROR", "WARNING",
                          "NOTICE", "INFO", "DEBUG", "UNKNOWN"};

        if (!logfile) {
                logfile = fopen(LOG_FILE, "w");
                if (!logfile)
                        return;
        }

        if (lvl < LOG_EMERG || lvl > LOG_DBG)
                lvl = LOG_DBG + 1;

        now = time(NULL);
        //sTm = gmtime(&now);
        sTm = localtime(&now);
        strftime(buf, sizeof(buf), "[%d-%m-%Y %H:%M:%S", sTm);


        sprintf(buf + strlen(buf), ".%llu] %s", ++linenum, logstr[lvl]);
        fprintf(logfile, "%s: ", buf);

        va_start(arg, fmt);
        vfprintf(logfile, fmt, arg);
        //vfprintf(logfile, "\n", NULL);
        va_end(arg);
        fflush(logfile);
}

void signal_handler(int32_t sig)
{
        switch (sig) {
        case SIGHUP:
                logmsg(LOG_INFO, "Caught SIGHUP\n");
                break;

        case SIGTERM:
                logmsg(LOG_INFO, "Caught SIGTERM\n");
                fclose(logfile);
                exit(0);

        default:
                logmsg(LOG_INFO, "Caught signal number: %d\n", sig);
                break;
        }
}

void daemonize(void)
{
        int32_t i;
        int32_t lfp;
        char str[16] = {0};

        if (getppid() == 1)
                return;	/* already a daemon */

        i = fork();
        if (i < 0) {
                logmsg(LOG_ERR, "fork error\n");
                exit(EXIT_FAILURE);	/* fork error */
        }

        if (i > 0)
                exit(EXIT_SUCCESS);	/* parent exits */

        /* child (daemon) continues */
        setsid();		/* obtain a new process group */

        for (i = getdtablesize(); i >= 0; --i)
                close(i);	/* close all descriptors */

        i=open("/dev/null",O_RDWR);
        dup(i);	/* Redirect stdin to /dev/null */
        dup(i); /* Redirect stdout to /dev/null */
        umask(027); /* set newly created file permissions */

        chdir(RUNNING_DIR);	/* change running directory */

        lfp = open(PID_FILE, O_RDWR | O_CREAT, 0640);
        if (lfp < 0) {
                logmsg(LOG_ERR, "open error: %s\n", PID_FILE);
                goto end;
        }

        if (lockf(lfp, F_TLOCK, 0) < 0) {
                logmsg(LOG_ERR, "lockf error\n");
                goto end;
        }

        /* first instance continues */
        sprintf(str, "%d\n", getpid());
        /* record pid */
        if (write(lfp, str, strlen(str)) < 0) {
                logmsg(LOG_ERR, "write error to: %s\n", PID_FILE);
        }

        signal(SIGCHLD, SIG_IGN);	/* ignore child */
        signal(SIGTSTP, SIG_IGN);	/* ignore tty signals */
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGINT, signal_handler);	/* catch hangup signal */
        signal(SIGHUP, signal_handler);	/* catch hangup signal */
        signal(SIGTERM, signal_handler);	/* catch kill signal */

        fsync(lfp);
        close(lfp);

        return;

end:
        if (logfile) {
                fflush(logfile);
                fclose(logfile);
        }

        exit(EXIT_FAILURE);
}

int32_t main(void)
{
        daemonize();

        while (true)
                sleep(1);	/* run */

        return EXIT_SUCCESS;
}
