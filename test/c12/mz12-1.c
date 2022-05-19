#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

enum { MAX_COUNT = 5 };

void
handler(int s)
{
    static int count = 0;
    if (count == MAX_COUNT) {
        exit(0);
    } else {
        printf("%d\n", count++);
        fflush(stdout);
    }
}

int
main(int argc, char **argv)
{
    sigaction(SIGHUP, 
            &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    int p = getpid();

    printf("%d\n", p);
    fflush(stdout);
    while (1) {
        pause();
    }
}
