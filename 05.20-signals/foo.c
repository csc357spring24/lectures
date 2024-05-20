#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/* A signal handler must take as its only argument an integer identifying the
 *  signal to which it is responding, and return nothing -- signals occur
 *  outside the normal control flow, so a handler effectively has no caller;
 *  it would make no sense for it to take arguments or produce return values. */
void handler(int signum) {

    /* This is technically unsafe; printf is not async-signal safe, because it
     *  maintains an internal buffer of partially formatted strings, and it is
     *  possible that a signal occurs while an existing call to printf is in
     *  the process of updating that buffer. Often, if the action to take in
     *  response to a signal is sufficiently complex, it is better to have the
     *  handler set a global flag that the main program can check later. */

    if (signum == SIGINT) {
        printf("But SHREYA lets HER PROCESSES stay up as long as they want!\n");
    }
    else {
        printf("But OWEN lets HIS PROCESSES eat clock cycles before dinner!\n");
    }
}

int main(void) {
    struct sigaction action;

    action.sa_handler = handler;
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);

    /* If we care to save any existing action (for example, if we only want to
     *  install our handler temporarily, and restore an old handler later), we
     *  could pass a pointer to a structure to be filled with that action. */
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);

    /* The above effectively ignores SIGINT (Ctrl+c) and SIGQUIT (Ctrl+\), but
     *  SIGSTOP (Ctrl+z) and SIGKILL cannot be blocked, ignored, or handled. */
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGKILL, &action, NULL);

    while (1);

    return EXIT_SUCCESS;
}
