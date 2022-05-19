#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>

enum 
{
    BUFF_SIZE = 256,
    PARTIES = 6,
    VALUE_IN_PREF = 2,
    BYTE_IN_SHORT = 2,
    PARTY1 = 0,
    PARTY2 = 1,
    PARTY3 = 2,
    PARTY4 = 3,
    PARTY5 = 4,
    PARTY6 = 5
};

int
main(int argc, char *argv[]) {

    unsigned short pref[VALUE_IN_PREF];
    unsigned short bulletins[BUFF_SIZE];
    long long int votes[PARTIES] = {0};
    int block_sum = 0;
    unsigned short *g = bulletins;
    int f, fd = open(argv[1], O_RDONLY);


    if (fd != -1) { 
        f = read(fd, &pref, sizeof(pref));
    } else {
        f = -1;
    }    

    while (pref[0] != 0 && f >= 0) {

        block_sum = 0;
        int block_votes[PARTIES] = {0};
        f = read(fd, bulletins, pref[0] * BYTE_IN_SHORT);
        g = bulletins;
        
        for (int i = 0; i < pref[0]; i++) {
            block_votes[*g - 1]++;
            block_sum += *g++;
        }

        f = read(fd, &pref, sizeof(pref));
        if (pref[1] == block_sum) {
            for (int i = 0; i < PARTIES; i++) {
                votes[i] += block_votes[i];
            }
        } else {
            int k = pref[1] - block_sum - (block_votes[PARTY2] 
                    + block_votes[PARTY3] 
                    + block_votes[PARTY4] 
                    + block_votes[PARTY5]);
            votes[PARTY6] += block_votes[PARTY5];
            votes[PARTY5] += block_votes[PARTY4];
            votes[PARTY4] += block_votes[PARTY3];
            votes[PARTY3] += block_votes[PARTY2];
            votes[PARTY2] += k; 
            votes[PARTY1] += block_votes[PARTY1] - k;
        }
    }
    

    for (int i = 0; i < PARTIES; i++) {
        printf("%lld\n", votes[i]); 
    }
    close(fd);
    return 0;
}
