#include <iostream>
#include <iomanip>

class Arena
{
    Item *ptr;
    bool *emp;
    size_t sz;
public:

    explicit Arena(size_t size)
    {
        size_t t = size / sizeof(Item);
        if (!t) {
            ptr = nullptr;
            emp = nullptr;
            sz = 0;
            return;
        }
            ptr = new Item[t];
            emp = new bool[t];
            sz = t;
            for (int i = 0; i < (int)sz; i++) {
                emp[i] = true;
            }
    }

    ~Arena()
    {
        delete[] ptr;
        delete[] emp;
    }

    Item* 
    get()
    {
        if (!sz) {
            return nullptr;
        }
        int i = 0;
        while (!emp[i]) {
            i++;
            if (i == (int)sz) {
                return nullptr;
            }
        }
        emp[i] = false;
        return &ptr[i];
    }

    void 
    put(Item *x) 
    {
        int i = 0;
        Item *j = ptr;
        while (j != x) {
            i++;
            j++;
        }
        emp[i] = true;
    }



    Arena(const Arena&) = delete;
    Arena(Arena&) = delete;
    Arena& operator=(const Arena&) = delete;
    Arena& operator=(Arena&) = delete;
};
