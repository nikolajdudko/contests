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
    pid_t p = fork();

    if (p < 0) {
        return 1;
    } else if (p == 0) {
        pid_t p1 = fork();
        if (p1 < 0) {
            return 1;
        } else if (p1 == 0) {
            printf("3 ");
            return 0;
        } else { 
            wait(NULL);
            printf("2 ");
            return 0;
        }
    } else {
        wait(NULL);
        printf("1\n");
        return 0;
    }
}
