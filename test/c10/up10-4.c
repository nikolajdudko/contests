#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>

enum
{
    BASE = 10,
    INDX_1 = 6,
    INDX_2 = 12
};


void
ch(int x, int y, int i, char *p)
{
    if (x != y) {
        close(i);
        remove(p);  //удалим созданный файл
        exit(1);
    }
}



int
main(int argc, char *argv[])
{
    char p[] = "/tmp/@------@"; //шаблон имени файла
    int i;

    unsigned int n;
    i = open("/dev/urandom", O_RDONLY);

    read(i, &n, sizeof(n));
    for (int j = INDX_1; j < INDX_2; j++) {
        p[j] = (n % BASE) + '0';
        n /= BASE; 
    } 

    close(i);
    if ((i = open(p, O_RDWR | O_CREAT | O_TRUNC, 0700)) == -1) {
        return 1;
    }
    
    char f[] = "#!/usr/bin/python3\nimport os\nimport sys\nprint(";
    ch(write(i, f, strlen(f)), strlen(f), i, p);
    
    ch(write(i, argv[1], strlen(argv[1])), strlen(argv[1]), i, p);

    for (int j = 2; j < argc; j++) {
        ch(write(i, "*", 1), 1, i, p);
        ch(write(i, argv[j], strlen(argv[j])), strlen(argv[j]), i, p);
    }
    

    char f2[] = ")\nos.system(\"rm \" + sys.argv[0])" ;
    ch(write(i, f2, strlen(f2)), strlen(f2), i, p);

    close(i);
    execlp(p, p, NULL);
    return 1;   
}
