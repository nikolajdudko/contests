#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>
#include <string.h>


enum 
{
    BASE = 8
};


int
just_do_it(int x)
{
    const char m[] = "rwxrwxrwx", *smpl1 = m;
    char ans[sizeof(m)], *smpl2 = ans;
    int mask = 1U << (sizeof(m) - 2);

    while (*smpl1) {
        if (x & mask) {
            *smpl2 = *smpl1;
        } else {
            *smpl2 = '-';
        }
        smpl1++;
        smpl2++;
        mask >>= 1;
    }
    *smpl2 = '\0';

    printf("%9s\n", ans);
    return 0;
}


int
main(int argc, char *argv[]) 
{
    for (int i = 1; i < argc; i++) {
        just_do_it(strtol(argv[i], 0, BASE));
    }
    return 0;
}   
