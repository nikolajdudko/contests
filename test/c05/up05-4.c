#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int
parse_rwx_permissions(const char *str)
{
    const char form_ptr[] = "rwxrwxrwx";
    const char *form = form_ptr;
    int len = sizeof(form_ptr) - 1;
    unsigned int ans = 0;
    
    if (!str) {
        return -1;
    }

    for (int i = 0; i < len; i++) {
        if (*str != '-' && *str != *form) {
            return -1;
        }

        ans <<= 1;
        if (*str != '-') {
            ans++;
        }

        str++;
        form++;
    }
    if (*str == '\0') {
        return ans;
    } else {
        return -1;
    }
}
