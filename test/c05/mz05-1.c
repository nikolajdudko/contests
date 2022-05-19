#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>

enum { SIZE = 1024 };

int
main(int argc, char *argv[]) {

    unsigned long long int sum = 0;
    struct stat buff;
    int flag;
    for (int i = 1; i < argc; i++) {
        flag = lstat(argv[i], &buff);
        if (!flag 
                && buff.st_nlink == 1 
                && buff.st_size % SIZE == 0 
                && S_ISREG(buff.st_mode)) {
            sum += buff.st_size;
        }
    }
    printf("%llu\n", sum);
}
