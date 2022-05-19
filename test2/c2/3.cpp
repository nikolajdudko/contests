#include <iostream>
#include <iomanip>

struct C {
    int x;

    C(...)
    {
        x = 0;
    }

    C operator++() {
        return C(x);
    }


    int operator~() const {
        return x;
    }
    

    int operator+(int a) {
        return x;
    }
    
    int operator+(int a) const {
        return x;
    }

    int operator*(const C a[2]) {
        return x;
    }
};

int operator+(int a, const C b) {
        return 0;
}
