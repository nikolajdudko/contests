#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <time.h>

enum
{
    SEC_IN_DAY = 86400,
    BASE_YAER = 1900,
    DIV = 3,
    INDX_OF_TH = 4
};
int
main(int argc, char** argv) {
    int year;
    scanf("%d", &year);

    struct tm tt = {0}, *tmp = &tt;
    tmp->tm_year = year - BASE_YAER;
    tmp->tm_mday = 1;
    tmp->tm_isdst = -1;
    int number = 1, tmp_mon;
    mktime(tmp);

    while (tmp->tm_year != year - BASE_YAER + 1) {
        if (tmp->tm_wday == INDX_OF_TH) {
            if (tmp->tm_mday % DIV && !(number & 1)) {
                printf("%d %d\n", tmp->tm_mon + 1, tmp->tm_mday);
            }
            number++;
        }
        tmp_mon = tmp->tm_mon;
        time_t  t = mktime(tmp) + SEC_IN_DAY;
        tmp = localtime_r(&t, tmp);
        tmp->tm_isdst = -1;

        if (tmp_mon != tmp->tm_mon) {
            number = 1;
        }

    }
    return 0;
}

