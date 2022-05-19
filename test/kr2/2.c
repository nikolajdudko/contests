#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

volatile int f = 0;

void
g(int s)
{
    f = 1;
}


int
main(int argc, char *argv[])
{
    sigset_t s1;
    sigemptyset(&s1);
    sigaddset(&s1, SIGUSR1);
    sigprocmask(SIG_BLOCK, &s1, NULL);

    sigaction(SIGUSR1,
            &(struct sigaction) { .sa_handler = g, .sa_flags = SA_RESTART }, NULL);


    unsigned int n = atoi(argv[1]);
    unsigned int l = atoi(argv[2]);
    pid_t *t = malloc(n * sizeof(*t)), *p = t;
    int *lifes = malloc(n * sizeof(*lifes)), *p1 = lifes;

    for (int i = 0; i < n; i++) {
        *p = fork();
        if (!*p) {
            sigset_t s2;
            sigemptyset(&s2);

            while (1) {
                while(!f) {
                    sigsuspend(&s2);
                }
                f = 0;
                l--;
                printf("%d %d\n", (p - t), l);
                fflush(stdout);
                if (!l) {
                    _exit(0);
                }
            }
        }
        p++;
    }

    unsigned int num;

    while(scanf("%u", &num) == 1) {
        usleep(200000);
        kill(*(t + num % n), SIGUSR1);
        *(lifes + num % n) -= 1;
    }

    usleep(200000);
    p = t;
    unsigned int sum = 0;
    for (int i = 0; i < n; i++) {
        if (*p1 + (int) l >= 1) {
            sum++;
            kill(*p, SIGKILL);
        } 
        p1++;
        p++;
    }   

    printf("%u\n", sum);
    fflush(stdout);

    while (wait(NULL) > 0);
}
