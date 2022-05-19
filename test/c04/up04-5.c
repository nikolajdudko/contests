#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>

int
main(int argc, char *argv[]) 
{
    int f, fd = open(argv[1], O_RDWR);
    long long int tmp_offset = 0, offset = 0, tmp, min;   
    if (fd == -1) {
        return -1;
    }

    f = read(fd, &tmp, sizeof(tmp));
    min = tmp;

    while (f == sizeof(tmp) 
        && read(fd, &tmp, sizeof(tmp)) == sizeof(tmp)) {
        tmp_offset += sizeof(tmp);
        if (tmp < min) {
            min = tmp;
            offset = tmp_offset;
        }
    }


    if (min != LLONG_MIN && f > 0) {
        min = -min;
        if(pwrite(fd, &min, sizeof(min), offset) != sizeof(min)) {
            return -1;
        }
    }
    return 0;
}
    

