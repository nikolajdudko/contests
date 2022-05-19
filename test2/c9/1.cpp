#include <iomanip>
#include <iostream>

static int i = 0;

class A {
    std::string s;
public:

    A() {
        if (std::cin.eof()) {
            throw 1;
        }
        std::cin >> s;
    };

    ~A() {
        if (i++) {
            std::cout << s << std::endl;
        }
    }
};

void 
f() {
    A d;
    f();
}

int 
main() {
    try {
        f();
    } catch (...) {

    }
}
