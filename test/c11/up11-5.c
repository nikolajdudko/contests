#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


int
son(int *in1, int *out1, int k, int n, int x)
{
    close(in1[1]);
    close(out1[0]);
    FILE *in = fdopen(in1[0], "r");
    FILE *out = fdopen(out1[1], "w");

    while (fscanf(in, "%d", &n) != EOF && n != x) {
        printf("%d %d\n", k, n);
        fflush(stdout);
        fprintf(out, "%d\n", n + 1);
        fflush(out);
    }
    return 1;
}

int
main(int argc, char **argv)
{
    int n = 1;
    int x = atoi(argv[1]);
    int c1[2], c2[2];

    if (pipe(c1)) {
        return 1;
    }

    if (pipe(c2)) {
        return 1;
    }

    pid_t p = fork();
    if (p < 0) {
        return 1;
    } else if (!p) {
        son(c2, c1, 1, n, x);
        _exit(0);
    }   
    pid_t p1 = fork();
    if (p1 < 0) {
        return 1;
    } else if (!p1)  {
        // son 2; пишет в ch2; читатет из ch1
        son(c1, c2, 2, n, x);
        _exit(0);
    }

    FILE *in = fdopen(c2[1], "w");
    fprintf(in, "%d\n", n);
    fclose(in);


    close(c1[0]);
    close(c1[1]);
    close(c2[0]);
    close(c2[1]);
    wait(NULL);
    wait(NULL);

    printf("Done\n");
    return 0;
}

