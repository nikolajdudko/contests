#include <iostream>


class Sum {
    int x;
public:
    Sum(int a, int b) 
    {
        x = a + b;
    }


    Sum(Sum a, int b) 
    {
        x = a.x + b;
    }

    explicit operator int() 
    {
        return x;
    }

    int get() const 
    {
        return x;
    }
};

int main() {
    
    std::cout << Sum(10, 5) + 1 < std::endl;

    return 0;
}
