#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>

int
wt(int *s)
{
    int status;
    wait(&status);
    if (WIFEXITED(status) && !WEXITSTATUS(status)) {
        (*s)++;
        return 0;
    }
    return 1;
}


void
son(char *p)
{
    char name[PATH_MAX] = {0};
    FILE* f = fopen(p, "r");

    if (f == NULL) {
        _exit(1);
    }
    
    fgets(name, PATH_MAX, f);
    name[strlen(name) - 1] = '\0';

    execlp(name, name, NULL);
    _exit(1);
}


int
main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    int sum = 0;
    int count = (argc - 2 <= n ? argc - 2 : n);

    for (int i = 0; i < count; i++) {
        if (!fork()) {
            son(argv[i + 2]);
        }
    }

    for (int i = 0; i < count; i++) {
        wt(&sum);
    }

    if (n >= argc - 2) {
        printf("%d\n", sum);
        return 0;
    }

    for (int i = n; i < argc - 2; i++) {
        if (!fork()) {
            son(argv[i + 2]);
        }
        wt(&sum);
    }


    printf("%d\n", sum);
    return 0;
}
