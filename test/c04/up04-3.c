#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>

enum 
{
    MASK1 = 0x000000ff,
    MASK2 = 0x0000ff00,
    MASK3 = 0x00ff0000,
    MASK4 = 0xff000000,
    S_IN_G = 17,
    K_IN_S = 29,
    SIZE_NAME_BET = 16,
    OFFSET1 = 24,
    OFFSET2 = 8
};

int
read_check_file(char* file_name, long long *m1, long long *m2)
{
    int f, fd = open(file_name, O_RDONLY);
    int bet;


    struct buff
    {
        char info[SIZE_NAME_BET];
        unsigned int bet_r;            // r for revers;
    }k;

    f = read(fd, &k, sizeof(k)); 
    while (fd != -1 && f != 0 && f != -1) {
        bet = ((k.bet_r & MASK1) << OFFSET1)
                + ((k.bet_r & MASK2) << OFFSET2)
                + ((k.bet_r & MASK3) >> OFFSET2)
                + ((k.bet_r & MASK4) >> OFFSET1);

        if (bet > *m1) {
            *m2 = *m1;
            *m1 = bet;
        } else if (bet > *m2 && bet != *m1) {
            *m2 = bet;
        }
        f = read(fd, &k, sizeof(k)); 
    }
    close(fd);
    return 0;
}


int
main(int argc, char *argv[])
{
    long long int max1 = LLONG_MIN;
    long long int max2 = LLONG_MIN;

    for (int i = 1; i < argc; i++) {
        read_check_file(argv[i], &max1, &max2);
    }

    if ( max2 == LLONG_MIN) {
        return 0;
    }

    unsigned int ans = llabs(max2);
    unsigned int g = ans / (K_IN_S * S_IN_G);
    unsigned int s = (ans % (K_IN_S * S_IN_G)) / K_IN_S;
    unsigned int k = (ans % (K_IN_S * S_IN_G)) % K_IN_S;
    

    if (max2 >= 0) {
        printf("%ug%.2us%.2uk\n", g, s, k);
    } else {
        printf("-%ug%.2us%.2uk\n", g, s, k);
    }
    return 0;
}
