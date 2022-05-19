#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>

volatile int flag = 0;




void
g(int s)
{
    static int count = 0;
    if (count == 3 || s == SIGTERM) {
        _exit(0);
    }
    count++;
    flag = 1;
    return;
}

int
isPrime(int n)
{

    for (int i = 2; i * i < n; i++) {
        if (n % i == 0) {
            return 0;
        }   
    }
    return 1;
    }


int
main(int argc, char **argv)
{
    sigset_t p;
    sigemptyset(&p);
    sigaddset(&p, SIGINT);
    sigaddset(&p, SIGTERM);

    sigaction(SIGINT,
            &(struct sigaction) { .sa_handler = g, .sa_flags = SA_RESTART }, NULL);

    sigaction(SIGTERM,
            &(struct sigaction) { .sa_handler = g, .sa_flags = SA_RESTART }, NULL);

    int x, y;
    int tmp = 0;
    scanf("%d %d", &x, &y);
    printf("%d\n", getpid());
    fflush(stdout);
    
    if (!(x % 2)) {
        if (x == 2) {
            if (flag) {
                printf("%d\n", tmp);
                fflush(stdout);
                flag = 0;
            }
            tmp = x;
        }
        x++;
    }
    while (x < y) {
        if (isPrime(x)) {
            if(flag) {
                printf("%d\n", tmp);
                fflush(stdout);
                flag = 0;
            }
            tmp = x;
        }
        x += 2;
    }

    sigprocmask(SIG_BLOCK, &p, NULL);
    printf("-1\n");
    fflush(stdout);
    return 0;
}
