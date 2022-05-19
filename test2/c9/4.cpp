#include <iomanip>
#include <iostream>

struct Result {
    uint32_t v;
};


void
A(uint32_t m, int32_t n) {
    if (!m) {
        throw Result(n + 1);
    } else if (m > 0 and n == 0) {
        A(m - 1, 1);
    } else if (m > 0 and n > 0) {
        try {
            A(m, n - 1);
        } catch (Result val) { 
            A(m - 1, val.v);
        } 
    }
}


int
main() {
    uint32_t a, b;

    std::cin >> a >> b;

    try {
        A(a, b);
    } catch (Result val3) {
        std::cout << val3.v << std::endl;
    }
}
