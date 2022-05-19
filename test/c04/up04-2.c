#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>


enum 
{
    MASK_1 = 0x00000fff,
    OFFSET_1 = 12,
    OFFSET_2 = 16, 
    OFFSET_3 = 8,
    MASK_2 = 0xff
};

int
main(int argc, char *argv[])
{

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    unsigned int num;

    char buff[sizeof(int)];
    unsigned int ans;

    if (fd == -1) {
        return 1;
    }

    while (scanf("%u", &num) == 1) {

        ans = ((num >> OFFSET_1) << OFFSET_2) + (num & MASK_1);
        for (int i = 0; i < sizeof(int); i++) {
            buff[sizeof(int) - i - 1] = ans & MASK_2;
            ans >>= OFFSET_3;
        }

        if (write(fd, buff, sizeof(buff)) != sizeof(buff)) {
            return 1;
        }
    }


    close(fd);
    return 0;
}
