#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>

int
main(void) 
{
    enum { 
        AMOUNT_NUM = 10,
        BUFF = 2000
    };
    
    char tmp, name[PATH_MAX + 1];
    char *pointer = name;
 

    tmp = getchar();
    while (tmp != '\n' 
        && tmp != '\r'
        && tmp != EOF 
        && pointer != PATH_MAX + name) {
        *pointer++ = tmp;
        tmp = getchar(); 
    }
    *pointer = '\0';

    unsigned long long int frequences[AMOUNT_NUM] = {0};
    char info[BUFF] = {0};
    pointer = info;

    int fd = open(name, O_RDONLY);

    int f;
    while ((f = read(fd, info, sizeof(info))) > 0) {
        for (int i = 0; i < f; i++) {
            if (*pointer >= '0' && *pointer <= '9') {
                frequences[*pointer - '0']++;
            }
            pointer++;
        }   
        pointer = info;
    }  

    for (int i = 0; i < AMOUNT_NUM; i++) { 
        printf("%d %llu\n", i, frequences[i]);
    }

    close(fd);
    return 0;
}
