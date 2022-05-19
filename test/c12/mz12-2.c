#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>


int
mul(unsigned int x, unsigned int y) 
{
    return x * y;
}

int
add(unsigned int x, unsigned int y)
{
    return x + y;
}  

volatile int (*p)(unsigned int, unsigned int) = NULL;

void
handler(int s)
{
    if (s == SIGQUIT) {
        p = mul;
    } else {
        p = add;
    }
}

int
main(int argc, char **argv)
{
    p = add;
    sigaction(SIGINT, 
            &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);

    sigaction(SIGQUIT, 
            &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);

    int pid = getpid();
    int n;
    int sum = 0;

    printf("%d\n", pid);
    fflush(stdout);

    while (scanf("%d", &n) == 1) {
        sum = p((unsigned)sum, (unsigned)n);
        printf("%d\n", sum);
        fflush(stdout);
    }
    return 0;
}
