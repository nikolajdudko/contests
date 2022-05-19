#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

enum
{
    OWNER_OFFSET = 6,
    GROUP_OFFSET = 3
};

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

int
search(const struct Task *task, const struct stat *stb)
{
    unsigned *p = task->gids; 
    for (int i = 0; i < task->gid_count; i++) {
        if (*p++ == stb->st_gid) {
            return 1;
        }
    }
    return 0;
}

int
ans(int root, int access)
{
    return (root & access) == access;
}



int 
myaccess(const struct stat *stb, const struct Task *task, int access) 
{
    if (task->uid == 0) {
        return 1;
    }

    int mode = stb->st_mode;

    if (stb->st_uid == task->uid) {
        return ans(mode >> OWNER_OFFSET, access);
    }


    if (search(task, stb)) {
        return ans(mode >> GROUP_OFFSET, access);
    }
    return ans(mode, access);
}

