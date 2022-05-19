#include <stdio.h> 
#include <stdlib.h> 

int
satsum(int v1, int v2)
{
    unsigned int int_max = 0, i = 0;
    int int_min = 0;
    i++;
    int_max = ~0U >> i;
    int_min = int_max + i;
    if (v1 > 0 && v2 > 0) {
        int_max -= v1;
        if (int_max < v2) {
            return int_max + v1;
        }
    } else if (v1 < 0 && v2 < 0) {
        int_min -= v1;
        if (int_min > v2) {
            return int_min + v1;
        }
    }
    return v1 + v2;
}
