#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>


int
main(int argc, char **argv)
{
    int n;
    int st;
    int flag = 1;
    pid_t p = 1;

    while (scanf("%d", &n) == 1) {
        p = fork();
        if (p == -1) {
            _exit(1);
        } else if (p) {
            wait(&st);
            if (WEXITSTATUS(st) == 1) {
                if (flag) {
                    printf("-1\n");
                    return 0;
                }
                _exit(1);
            } else {
                printf("%d\n", n);
                fflush(stdout);
                _exit(0);
            }
        } 
        flag = 0;
    }
    return 0;
}
