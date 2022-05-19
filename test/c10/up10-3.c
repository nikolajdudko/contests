#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>



int mysys(const char *str)
{
    pid_t pid = fork();
    if (pid < 0) {
        return 0;        
    }
    if (!pid) {
        execlp(str, str, NULL);
        _exit(1);
    }
    int status = 0;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) && !WEXITSTATUS(status);
}

int 
main(int argc, char *argv[])
{
    return !((mysys(argv[1]) || mysys(argv[2])) && mysys(argv[3]));
}
