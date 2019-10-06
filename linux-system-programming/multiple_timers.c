#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define NUM_OF_ITER	15
#define TOTAL_TIMERS	4
#define UNUSED(var)	((void)(var))

static char pbuf[NUM_OF_ITER * 50];
static timer_t timers[TOTAL_TIMERS];
static volatile int32_t expired_timers = NUM_OF_ITER;

static char *get_time(int32_t offset)
{
        time_t t;
        static char tbuf[26];

        memset(tbuf, 0, sizeof(tbuf));
        if (time(&t) == (time_t)-1) {
                fprintf(stderr, "time error(%s)\n", strerror(errno));
                return "(null)\n";
        }

        t += offset;

        return ctime_r(&t, tbuf);
}

static void show_date_time(char *str, int32_t tnum)
{
        printf("%s of timer: %d --> %s", str, tnum, get_time(0));
}

static void _show_date_time(int32_t tnum)
{
        static int32_t idx;

        idx += sprintf(&pbuf[idx], "\nEnd of timer: %d --> %s", tnum, get_time(0));
}

static void expiration_hdlr(int32_t sig, siginfo_t *si, void *uc)
{
        int32_t i;
        timer_t *tidp;

        UNUSED(uc);
        UNUSED(sig);

        tidp = si->si_value.sival_ptr;

#define show_date_time(a, b)	_show_date_time(b)
        for (i = 0; i < TOTAL_TIMERS; i++) {
                if (*tidp == timers[i]) {
                        show_date_time("\nEnd", i + 1);
                        expired_timers--;
                        break;
                }
        }
#undef show_date_time
}

static int32_t trigger_timer(timer_t *tmid, int32_t time)
{
        struct sigevent te;
        struct sigaction sa;
        struct itimerspec its;

        /* Set up signal handler */
        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = expiration_hdlr;
        if (sigemptyset(&sa.sa_mask) || sigaction(SIGRTMIN, &sa, NULL)) {
                fprintf(stderr, "sig(emptyset | action) failed(%s)\n", strerror(errno));
                return -1;
        }

        /* Set and enable alarm */
        te.sigev_signo = SIGRTMIN;		/* SIGALRM */
        te.sigev_notify = SIGEV_SIGNAL;		/* Generate alarm upon expiration */
        te.sigev_value.sival_ptr = tmid;	/* Timer ID */

        /* Create a per_process timer using the timer ID */
        if (timer_create(CLOCK_REALTIME, &te, tmid)) {
                fprintf(stderr, "timer_create failed(%s)\n", strerror(errno));
                return -1;
        }

        /* Interval for starting again */
        its.it_interval.tv_sec = 0;
        its.it_interval.tv_nsec = 0;

        /* Timer time */
        its.it_value.tv_nsec = !time; /* if time = 0, handler isn't called. So sleep for 1 nsec */
        its.it_value.tv_sec = time;

        /* Arm/disarm a per process time */
        if (timer_settime(*tmid, 0, &its, NULL)) {
                fprintf(stderr, "timer_settime failed(%s)\n", strerror(errno));
                return -1;
        }

        return 0;
}

int32_t main(void)
{
        int32_t cnt = NUM_OF_ITER;

        srand(time(NULL));
        while (cnt--) {
                int32_t tnum;
                int32_t texpire = rand() % 5;

                do {
                        tnum = rand() % (TOTAL_TIMERS + 1);
                } while (!tnum);

                if (trigger_timer(&timers[tnum - 1], texpire) < 0) {
                        fprintf(stderr, "trigger_timer failed(%s)\n", strerror(errno));
                        return EXIT_FAILURE;
                }
                show_date_time("\nStart", tnum);

                printf("Timer: %d will expire in %d seconds at --> %s", tnum, texpire, get_time(texpire));
                sleep(rand() % 3);
        }

        while (expired_timers > 0)
                sleep(1);

        printf("%s\n", pbuf);

        return EXIT_SUCCESS;
}
