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
    scanf("%d", &n);
    pid_t p;
    printf("1");
    fflush(stdout);
    for (int i = 2; i <= n; i++) {
        p = fork();
        if (p == -1) {
            return 255;
        } else if (p != 0) {
            wait(NULL);
            return 0;
        }
        printf(" %d", i);
        fflush(stdout);
    }
    printf("\n");
    return 0;
}
