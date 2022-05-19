#include <iomanip>
#include <iostream>

class A {
public:
    int64_t v;
};


void
func(int64_t a, int64_t b, uint32_t k) {
    if (!k) {
        throw A(a + b);
    } else if (k > 0 and b == 1) {
        throw A(a);
    } else if (k > 0 and b > 1) {
        try {
            func(a, b - 1, k);
        } catch (A val) { 
            func(a, val.v, k - 1);
        } 
    }
}


int
main() {
    int64_t a, b;
    uint32_t k;

    std::cin >> a >> b >> k;

    while (!std::cin.eof()) {
        try {
            func(a, b, k);
        } catch (A val3) {
            std::cout << val3.v << std::endl;
        }
        std::cin >> a >> b >> k;
    }

}
