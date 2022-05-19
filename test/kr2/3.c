#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

int
main(int argc, char *argv[])
{   
    unsigned long long int n = strtoll(argv[2], NULL, 0);
    int i = open(argv[1], O_RDONLY);
    int j = open("./tmp", O_RDWR, O_CREAT, 0777);
    unsigned long long int num;

    while(read(i, &num, sizeof(num)) == sizeof(num)) {
        if (num >= n) {
            write(j, &num, sizeof(num));
        }
    }

    close(i);
    i = open(argv[1], O_WRONLY, OCREAT | O_TRUNC);
    lseek(j, 0, 0);

    while (read(j, &num, sizeof(num)) == sizeof(num)) {
        write(i, &num, sizeof(num));
    }

    remove("./tmp");
    return 0;
}
