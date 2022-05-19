#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

enum
{
    SIZE = 32,
    CHANGE_SIGN = -1
};
int 
main(void)
{
    uint32_t s, tmp = 0, max, u_copy;
    unsigned int w, n, k = 1;
    scanf("%d%" SCNd32 "%d", &n, &s, &w);

    if (n == SIZE) {
        max = UINT_MAX;
    } else {
        max = (k << n) - 1;
    }

    uint32_t sign_mask = k << (n - 1);


    while (tmp <= max) {
        u_copy = tmp & (sign_mask - 1);
        if (tmp & sign_mask) {
            u_copy *= -1;
        }

        printf("|%*" PRIo32 "|%*" PRIu32 "|%*" PRId32 "|\n", w, tmp, w, tmp, w, u_copy);

        if (UINT_MAX - tmp < s) {
            break;
        }
        tmp += s;
    }
}
