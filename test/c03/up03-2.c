#include <stdio.h> 
#include <stdlib.h> 

enum { BASE = 10 };
int 
main(int argc, char *argv[])
{
    char *end;
    long long int sum_pos = 0, sum_neg = 0, k;
    for (int i = 1; i < argc; i++) {
        k = strtol(argv[i], &end, BASE);
        if (k < 0) {
            sum_neg += k;
        } else {
            sum_pos += k;
        }
    }
    printf("%lld\n %lld\n", sum_pos, sum_neg);
} 
