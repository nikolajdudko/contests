#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>


int fd;

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

int
ans(int32_t offset)
{
    struct Node buff;
    int f;
    f = pread(fd, &buff, sizeof(buff), offset * sizeof(buff));

    if (f != sizeof(buff)) {
        return 0;
    }

    if (buff.right_idx != 0) {
        ans(buff.right_idx);
    }

    printf("%d\n", buff.key);

    if (buff.left_idx != 0) {
        ans(buff.left_idx);
    }
    return 0;
}


int
main(int argc, char *argv[]) 
{
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        return 0;
    }
    ans(0);
    return 0;
}
