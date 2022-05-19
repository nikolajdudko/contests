#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <time.h>

int
main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);

    pid_t p1 = fork();
    if (!p1) {
        pid_t p2 = fork();
        if (!p2) {
            close(fd[1]);
            int k;
            long long int sum = 0;
            while (read(fd[0], &k, sizeof(k)) != 0) {
                sum += k;
            }
            printf("%lld\n", sum);
            fflush(stdout);
            return 0;
        }
        close(fd[0]);
        close(fd[1]);
        wait(NULL);
    }
    close(fd[0]);
    int n;
    while (scanf("%d", &n) != EOF) {
        write(fd[1], &n, sizeof(n));
    }
    close(fd[1]);
    wait(NULL);
    return 0;
}
