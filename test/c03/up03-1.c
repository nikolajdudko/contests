#include <limits.h>

STYPE
bit_reverse(STYPE value)
{
    UTYPE j, ans = 0, copy_value = value;
    UTYPE size = sizeof(STYPE) * CHAR_BIT;
    for (STYPE i = 0; i < size; i++) { 
        j = copy_value & 1;
        copy_value >>=  1;
        ans <<= 1;
        ans += j;
    }

    return ans;
}
