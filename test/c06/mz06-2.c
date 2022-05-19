#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <string.h>

int
main(int argc, char** argv)
{
    char smpl[] = ".exe";
    int LEN = strlen(smpl);
    int sum = 0;
    if (argc == 1) {
        printf("%d\n", sum);
        return 0;
    }
    struct dirent* cur;
    DIR* dr  = opendir(argv[1]);
    if (dr == NULL) {
        printf("%d\n", sum);
        return 0;
    }
    while ((cur = readdir(dr)) != NULL) {
        struct stat buf;
        char tmp[PATH_MAX];
        if (snprintf(tmp, sizeof(tmp), "%s/%s", argv[1], cur->d_name) < sizeof(tmp)
                && stat(tmp, &buf) != -1 
                && S_ISREG(buf.st_mode) 
                && !access(tmp, X_OK)) {

            char *p = cur->d_name;
            if (strlen(cur->d_name) >= LEN - 1
                    && !strcmp(p + strlen(p) - LEN, smpl)) {

                sum++;
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}
