#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
// 0 читать 
// 1 писать 
int
main(int argc, char **argv)
{
    int in = 2, out[2];
    int flag;
    pid_t *pids = malloc((argc - 1) * sizeof(pid_t));
    pid_t *tmp = pids;

    for (int i = 1; i < argc; i++) {
        flag = pipe(out);
        *tmp = fork();
        if (*tmp < 0 || flag != 0) {
            tmp = pids;
            while (*tmp > 0) {
                kill(*tmp++, SIGKILL);
            }
            while (wait(NULL) > 0);
            return 1;
        } else if (!*tmp++) {
            free(pids);
            if (i != 1) {
                if (dup2(in, 0) == -1) {
                    _exit(42);
                }
            }

            if (i != argc - 1) {
                if (dup2(out[1], 1) == -1) {
                    _exit(42);
                }
            }

            close(in);
            close(out[0]);
            close(out[1]);
            execlp(argv[i], argv[i], NULL);
            _exit(42);
        }
        close(in);
        close(out[1]);
        in = out[0];
    }

    free(pids);
    while (wait(NULL) > 0);
    return 0;
}

