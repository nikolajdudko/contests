#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>

enum
{
    MASK1 = 0xFF,
    MASK2 = 0xFF00,
    OFFSET = 8
};


int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    char buff[sizeof(unsigned short)];
    unsigned short tmp;
    unsigned int min = INT_MAX;
    int flag = 0;


    while (read(fd, buff, sizeof(buff))) {
        tmp = ((unsigned)buff[0] << OFFSET) + (buff[1] & 0xff);

        if (!(tmp % 2) && tmp < min) {
            min = tmp;
            flag = 1;
        }

        if (min == 0) {
            printf("%d\n", min);
            return 0;
        }
    }

    if (flag && min != INT_MAX) {
        printf("%d\n", min);
    }
    return 0;
}
