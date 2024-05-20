#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/* A signal handler must take as its only argument the number of the signal
 *  which is being handled, and cannot return anything -- a handler effectively
 *  has no caller, so it makes no sense for it to return a value to its
 *  nonexistent caller. */
void handler(int signum) {

    /* This is technically unsafe; printf maintains a static buffer of
     *  partially formatted strings behind the scenes, and it is possible that
     *  the signal could occur while an ongoing call to printf was in the
     *  process of updating that buffer. In that case, calling printf within
     *  the handler would corrupt the buffer. Often, rather than performing all
     *  necessary actions inside of a handler, it is safer to have the handler
     *  set a global flag which can then be checked in the main program. */

    if (signum == SIGINT) {
        printf("But IVAN lets HIS PROCESSES stay up as long as they want!\n");
    }
    else {
        printf("But VICTORIA lets HER PROCESSES eat clock cycles before dinner!\n");
    }
}

int main(void) {
    struct sigaction action;

    action.sa_handler = handler;
    action.sa_flags = SA_RESTART;
    sigemptyset(&action.sa_mask);

    /* If we cared to restore the existing action later, we could pass as a
     *  third argument a pointer to a second structure, which would be filled
     *  with the details of that existing action. */
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);

    /* The above effectively ignores SIGINT (Ctrl+c) and SIGQUIT (Ctrl+\), but
     *  SIGSTOP (Ctrl+z) and SIGKILL cannot be blocked or ignored. */
    sigaction(SIGSTOP, &action, NULL);
    sigaction(SIGKILL, &action, NULL);

    while (1);

    return EXIT_SUCCESS;
}
