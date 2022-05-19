#include <stdio.h> 
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

enum 
{
    BASE = 10,
    USEC_IN_SEC = 1000000
};



int 
main(int argc, char *argv[])
{
    int indx = 1;

    struct timeval time = {strtol(argv[1], NULL, BASE), strtol(argv[++indx], NULL, BASE)};

    double L = strtold(argv[++indx], NULL);

    int K = strtol(argv[++indx], NULL, BASE);

    unsigned int S = strtoul(argv[++indx], NULL, BASE);
    srand(S);

    double U;
    long tmp;

    for (int i = 0; i < K; i++) {

        U = (double) rand() / RAND_MAX;
        tmp = (long) floor(-log(U) / L);
        time.tv_usec += tmp;

        time.tv_sec += time.tv_usec / USEC_IN_SEC;
        time.tv_usec %= USEC_IN_SEC;

        printf("%ld %ld\n", time.tv_sec, time.tv_usec);
    }
    return 0;
}   
