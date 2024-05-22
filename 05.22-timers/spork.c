#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

/* For simplicity, we assume that we will only spork one child at a time. Since
 *  we need this PID in a handler, it has to be in a global. */
pid_t child;

void handler(int signum) {
    kill(child, SIGKILL);
}

/* spork: Creates a new resource-limited process. */
pid_t spork(time_t timeout) {
    struct itimerval timer;
    struct sigaction action;
    struct rlimit limit;

    if ((child = fork()) == 0) {
        /* Lower the child's soft and hard limits on the number of processes to
         *  1, so that the child cannot create any children of its own. */
        limit.rlim_cur = 1;
        limit.rlim_max = 1;
        setrlimit(RLIMIT_NPROC, &limit);

        return 0;
    }
    else {
        /* The default action for SIGALRM is to terminate the process; if we want
         *  to take some alternative action instead, we have to install a handler.
         *  Note that this must be done before starting the timer, otherwise there
         *  is theoretically a possibility that the timer could go off before the
         *  handler is installed. */
        action.sa_handler = handler;
        action.sa_flags = SA_RESTART;
        sigemptyset(&action.sa_mask);
        sigaction(SIGALRM, &action, NULL);

        /* Create a timer that will send a SIGARLM after a given timeout: */
        timer.it_value.tv_sec = timeout;
        timer.it_value.tv_usec = 0;

        /* After that 1 second, reset the timer to do nothing: */
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;

        setitimer(ITIMER_REAL, &timer, NULL);

        /* Using an infinite loop to "busy wait" for a signal is extremely poor
         *  form; if we don't plan to do anything until a signal arrives, we should
         *  instead "pause" so that the CPU can do other things.
         *
         * while (1);
         * 
         * pause(); */
        return child;
    }
}
