#include <iostream>
#include <iomanip>
#include <cmath>

int main() {

    int i = 0;
    double avg = 0;
    double avg_2 = 0;
    double x;

    while (std::cin >> x) {
        avg += x;
        avg_2 += x * x;
        i++;
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(10) << avg / i << std::endl;
    std::cout << std::setprecision(10) << sqrt(avg_2 / i - avg * avg / i / i) << std::endl;


    return 0;
}
