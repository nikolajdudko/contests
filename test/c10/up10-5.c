#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

enum
{
    BASE = 10,
    INDX_1 = 6,
    INDX_2 = 11 
};

int
main(int argc, char *argv[])
{
    char p[] = "/tmp/@------@.c";
    char p1[] = "/tmp/@------@";
    int i;
    unsigned int n, t;


    i = open("/dev/urandom", O_RDONLY);
    read(i, &n, sizeof(n));
    read(i, &t, sizeof(t));

    for (int j = INDX_1; j < INDX_2; j++) {
        p[j] = (n % BASE) + '0';
        p1[j] = (t % BASE) + '0';
        n /= BASE; 
    } 
    close(i); 






    if ((i = open(p, O_RDWR | O_CREAT | O_EXCL, 0600)) == -1) {
        return 1;
    }
    
    char f[] = "#include <stdlib.h>\n\
#include <stdio.h>\n\
char *summon = \"summon\",*disqualify = \"disqualify\", *reject = \"reject\";\n\
int\n\
main(int argc, char *argv[])\n\
{\n\
    int x = atoi(argv[1]);\n\
    printf(\"%s\\n\", ";
        
    write(i, f, strlen(f));
    if (write(i, argv[1], strlen(argv[1])) != strlen(argv[1])) {
        return 1;
    }

    char f2[] = ");\n}";
    if (write(i, f2, strlen(f2)) != strlen(f2)) {
        return 1;
    }

    close(i);
    int pid = fork();

    if (pid < 0) {
        return 1;
    } else if (pid == 0) {
        execlp("gcc", "gcc", p, "-o", p1, NULL); 
        return 1;
    }   
    int st;   
    wait(&st);
    if (!(WIFEXITED(st) && !WEXITSTATUS(st))) {
        return 1;
    }
    

    char num[100];
    while (scanf("%s", num) != EOF) {
        pid = fork();
        if (pid < 0) {
            return 1;
        } else if (!pid) {
            execlp(p1, p1, num, NULL);
            return 1;
        }
        wait(NULL);
    }

    remove(p);
    remove(p1);
    return 0;
}

