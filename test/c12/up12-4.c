#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>

volatile int f = 0;





void
g(int s)
{
    f = 1;
    return;
}


void
son(int k, pid_t op, int n, int x, FILE* in, FILE* out)
{
    sigset_t s2;
    while (n != x) {
        printf("%d %d\n", k, n);
        fflush(stdout);
        fprintf(out, "%d\n", n + 1);
        fflush(out);
        kill(op, SIGUSR1);

        while (!f) {
            sigsuspend(&s2);
        }
        f = 0;

        fscanf(in, "%d", &n);
    }

    fprintf(out, "%d\n", n);
    fflush(out);
    kill(op, SIGUSR1);
    _exit(0);
}

int
main(int argc, char **argv)
{
    sigset_t s1;
    sigset_t s2;
    sigemptyset(&s1);
    sigaddset(&s1, SIGUSR1);
    sigprocmask(SIG_BLOCK, &s1, NULL);

    int fd[2];
    pid_t op;
    int n = 1;
    sigaction(SIGUSR1,
            &(struct sigaction) { .sa_handler = g, .sa_flags = SA_RESTART }, NULL);

    int x = atoi(argv[1]);
    pipe(fd);

    pid_t p1 = fork();  
    FILE* in = fdopen(fd[0], "r");
    FILE* out = fdopen(fd[1], "w");


    if (p1 < 0) {
        return 1;
    } else if (!p1) {
        // первый сын
        sigemptyset(&s2);

        fprintf(out, "%d\n", getpid());
        fflush(out);
        while (!f) {
            sigsuspend(&s2);
        }
        f = 0;
        fscanf(in, "%d", &op);


        son(1, op, n, x, in, out);        
    }

    pid_t p2 = fork();
    if (p2 < 0) {
        return 1;
    } else if (!p2) {
        // второй сын
        sigemptyset(&s2);
        
        fscanf(in, "%d", &op);
        fprintf(out, "%d\n", getpid());
        fflush(out);
        kill(op, SIGUSR1);

        while (!f) {
            sigsuspend(&s2);
        }
        f = 0;

        fscanf(in, "%d", &n);
      
        son(2, op, n, x, in, out);
    }
    

    fclose(out);
    fclose(in);
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    printf("%s", "Done\n");
    fflush(stdout);
    return 0;
}
