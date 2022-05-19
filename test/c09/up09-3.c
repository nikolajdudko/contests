#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>

enum 
{ 
    COUNT = 3,
    SIZE = 8 
};

int
main(int argc, char **argv)
{

    pid_t p;
    int i = 1;
    while (i <= COUNT) {
        p = fork();
        if (p < 0) {
            return 1;
        } else if (!p) {
            char a[SIZE];
            int c;
            if((c = read(0, &a, sizeof(a))) < 0){
                return -1;
            }
            a[c - 1] = '\0';
            int num = strtol(a, NULL, 0);
            printf("%d %u\n", i, num * num);
            fflush(stdout);
            _exit(0);
        }
        i++;
    }

    while (wait(NULL) > 0);
}
