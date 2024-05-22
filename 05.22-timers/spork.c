#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

/* For simplicity, we'll assume we never spork off more than one child at the
 *  same time. Its PID needs to be global, so that it is accessible inside
 *  the handler. */
pid_t child;

void handler(int signum) {
    kill(child, SIGKILL);
}

/* spork: Creates a new resource-limited process. */
pid_t spork(time_t timeout) {
    struct sigaction action;
    struct itimerval timer;
    struct rlimit limit;

    if ((child = fork()) == 0) {
        /* Lower the child's soft and hard limits on number of processes to 1,
         *  so that it cannot create any more children of its own: */
        limit.rlim_cur = 1;
        limit.rlim_max = 1;
        setrlimit(RLIMIT_NPROC, &limit); 

        return 0;
    }
    else {
        /* Install a handler for SIGALRM -- note that this must be done before
         *  starting the timer, otherwise there is a chance that the handler
         *  is not installed until after the timer has elapsed: */
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        sigemptyset(&action.sa_mask);
        sigaction(SIGALRM, &action, NULL);

        /* After a given timeout, send a SIGALRM: */
        timer.it_value.tv_sec = timeout;
        timer.it_value.tv_usec = 0;

        /* After sending that first SIGALRM, don't send any more: */
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;

        setitimer(ITIMER_REAL, &timer, NULL);

        return child;
    }

    /* It would be very poor form to "busy wait" for a signal by doing nothing
     *  meaningful; if we don't intend to do anything until a signal arrives,
     *  we should ask the OS to pause execution.
     *
     * while (1);
     *
     * pause();
     */
}
