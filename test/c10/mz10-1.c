#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>



int
main(int argc, char *argv[])
{
    pid_t pid = fork();
    if (pid < 0) {
        return 1;
    } else if (!pid) {
        int fd = open(argv[2], O_RDONLY);
        if (fd < 0) {
            _exit(42);
        }
        if (dup2(fd, 0) == -1) {
            _exit(42);
        }
        close(fd);  

        fd = open(argv[3] , O_WRONLY | O_CREAT | O_APPEND, 0660); 
        if (fd < 0) {
            _exit(42);
        }
        if (dup2(fd, 1) == -1) {
            _exit(42);
        }   
        close(fd);   

        fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660); 

        if (fd < 0) {
            _exit(42);
        }

        if (dup2(fd, 2) == -1) {
            _exit(42);
        }   
        close(fd);

        execlp(argv[1], argv[1], NULL);
        _exit(42);
    }
    int st;
    wait(&st);
    printf("%d\n", st);
    return 0; 
}
