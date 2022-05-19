#include <iostream>
using namespace std;



void h (bool , long) { }

void h (float , int ) { }

void h (double , double) {
    std::cout << 1;
}

int main() {
    h (0, 0.5);
}
