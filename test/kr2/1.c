#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int
main(int argc, char *argv[])
{
    unsigned int arr[256];
    int i = 0;
    unsigned int max = 0;
    while (scanf("%u", &arr[i]) == 1) {
        if (arr[i] > max) {
            max = arr[i];
        }
        i++;
    }

    while (i--) {
        if (arr[i] && max % arr[i] == 0) {
            printf("%u\n", arr[i]);
        }
    }
}
