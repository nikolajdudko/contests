#include <vector>
#include <iomanip>
#include <iostream>
#include <complex>
#include <utility>
#include <array>


namespace Equations {
    using namespace std::complex_literals;
    template<typename T>
    std::pair<bool, std::vector<std::complex<T>>>
    quadratic(std::array<std::complex<T>, 3>& arr) {
        std::pair<bool, std::vector<std::complex<T>>> ans;
        std::complex<T> a = arr[2]; 
        std::complex<T> b = arr[1];
        std::complex<T> c = arr[0];
        if (a == std::complex<T>(0)) {
            if (b == std::complex<T>(0)) {
                if (c == std::complex<T>(0)) {
                    ans.first = false;
                } else {
                    ans.first = true;
                }
            } else { 
                ans.first = true;
                ans.second = {-c/b};
            }
        } else {
            if (b == std::complex<T>(0)) {
                ans.first = true;
                ans.second = {sqrt(-c/a), -sqrt(-c/a)};
            } else {
                std::complex<T> D = b * b - std::complex<T>(4) * a * c;
                ans.first = true;
                ans.second = {(-b+sqrt(D))/(std::complex<T>(2) * a), 
                        (-b-sqrt(D))/(std::complex<T>(2) * a)};
            }
        }
        return ans;
    }
}





/*
int main() {
    using namespace std::complex_literals;

    std::array v1{ 1.0 + 2.0i, 2.0 + 0i, 3.0 + 1.3i };

    auto [res, v2] = Equations::quadratic(v1);
    std::cout << res;


}
*/
