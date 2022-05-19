#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <time.h>

// 0 читать 
// 1 писать 

int
main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);
    int st;
    pid_t p = fork();

    if (p < 0) {
        return 1;
    } else if (!p) {
        close(fd[0]);
        if (dup2(fd[1], 1) == -1) {
            _exit(42);
        }
        close(fd[1]);

        pid_t p1 = fork();
        if (p1 < 0) {
            _exit(43);
        } else if (!p1) {
            int i = open(argv[4], O_RDONLY);
            if (i < 0) {
                _exit(42);
            }
            if (dup2(i, 0) == -1) {
                _exit(42);
            }
            close(i);
            execlp(argv[1], argv[1], NULL);
            _exit(42);
        }

        wait(&st);
        if (WIFEXITED(st) == 0 || WEXITSTATUS(st) != 0) {
            _exit(43);
        }

        pid_t p2 = fork();

        if (p2 < 0) {
            _exit(43);
        } else if (!p2) {
            execlp(argv[2], argv[2], NULL);
            _exit(42);
        }
        
        wait(&st);
        if (WIFEXITED(st) == 0 || WEXITSTATUS(st) != 0) {
            _exit(43);
        }
        _exit(0);
    }
    close(fd[1]);



    pid_t p3 = fork();
    if (p3 < 0) {
        return 1;
    } else if (!p3) {
        int j = open(argv[5] , O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (j < 0) {
            _exit(42);
        }
        if (dup2(j, 1) == -1) {
            _exit(42);
        }
        close(j);
        if (dup2(fd[0], 0) == -1) {
            _exit(42);
        }
        close(fd[0]);
        execlp(argv[3], argv[3], NULL);
        _exit(42);
    }

    close(fd[0]);
    wait(NULL);
    wait(NULL);
    return 0;
}
