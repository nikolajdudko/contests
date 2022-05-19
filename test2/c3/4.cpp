#include <iostream>
#include <iomanip>
#include <vector>
#include <numbers>
#include "set.cpp"
//#include "cmc_complex.h"
//#include "cmc_complex_stack.h"
//#include "cmc_complex_eval.h"


using std::numbers::pi;
using numbers::complex;
using numbers::eval;
using std::cos;
using std::sin;


int
main(int argc, char** argv)
{
    complex C(argv[1]);
    double R = std::stod(argv[2]);
    int N = std::stoi(argv[3]);
    std::vector<std::string> v;

    int j = 4;
    while (argv[j] != NULL) {
        v.push_back(argv[j++]);
    }

//    for (std::string s : v) {
//        std::cout << s << std::endl;
//    }
    //f(R*e^it + C) * i * R * e^it * dt
    //e^it=cos(t) + i * sin(t)
    //f(R * (cos(t) + i * sin(t)) + C) * i * R * (cos(t) + i * sint)

    double diam = 2 * pi / N;

    double xi = 0;
    double xi_1 = diam;

    complex i(0, 1);
    double t;
    complex ans(0, 0);

    for (int j = 0; j < N; j++) {
        t = (xi + xi_1) / 2;
        ans += eval(v, R * complex(cos(t), sin(t)) + C) * complex(cos(t), sin(t)) * diam * R * i;

        xi += diam;
        xi_1 += diam;
    }   

    std::cout << ans.to_string() << std::endl;
}
