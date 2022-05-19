#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 

enum 
{ 
    ALL = 100,
    OFFSET = 10000
};


int 
main(int argc, char *argv[])
{
    char *end;
    double s = strtod(argv[1], &end);
    double p; 
    for (int i = 2; i < argc; i++) {
        p = strtod(argv[i], &end);
        s *= 1 + p / ALL;
        s = round(s * OFFSET) / OFFSET;
    }
    printf("%.4f\n", s);
}
