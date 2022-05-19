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
            pid_t p3 = fork();
            if (!p3) {
                time_t t = time(NULL);
                write(fd[1], &t, sizeof(t));
                write(fd[1], &t, sizeof(t));
                write(fd[1], &t, sizeof(t));
                return 0;
            }
            wait(NULL);
            time_t t;
            read(fd[0], &t, sizeof(t));
            struct tm t1;
            localtime_r(&t, &t1);
            printf("D:%02d\n", t1.tm_mday);
            fflush(stdout);
            return 0;
        }
        wait(NULL);
        time_t t;
        read(fd[0], &t, sizeof(t));
        struct tm t1;
        localtime_r(&t, &t1);
        printf("M:%02d\n", t1.tm_mon + 1);
        fflush(stdout);
        return 0;
    }
    wait(NULL);
    time_t t;
    read(fd[0], &t, sizeof(t));
    struct tm t1;
    localtime_r(&t, &t1);
    printf("Y:%d\n", t1.tm_year + 1900);
    fflush(stdout);
    return 0;
}
