#include <iomanip>
#include <iostream>
#include <utility>

class S {
    int a = 0;
public:

    S() {
        int k;
        std::cin >> k;
        while (!std::cin.eof()) {
            a += k;
            std::cin >> k;
        }
    };

    operator bool() {
        return false;
        
    }

    ~S() {
        std::cout << a << std::endl;
    }
};


using namespace std;
void func(S v)
{
    if (v) {
        func(move(v));
    }
}

int main()
{
    func(S());
}
