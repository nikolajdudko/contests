#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <functional>
//#include "set.cpp"

namespace numbers
{

//using set::complex;
//using set::complex_stack;

complex
eval(const std::vector<std::string> &args, const complex &z)
{
    std::map<const char, std::function<complex(complex_stack&)>> func {
            {'+', [](complex_stack& s){ complex b(+s); s = ~s; complex a(+s); ~s; return a + b;} },
            {'-', [](complex_stack& s){complex b(+s); s = ~s; complex a(+s); ~s; return a - b;} },
            {'*', [](complex_stack& s){ complex b(+s); s = ~s; complex a(+s); ~s; return a * b;} },
            {'/', [](complex_stack& s){ complex b(+s); s = ~s; complex a(+s); ~s; return a / b;} }, 
            {'#', [](complex_stack& s){ complex b(+s); s = ~s; return -b;} }, 
            {'~', [](complex_stack& s){ complex b(+s); s = ~s; return ~b;} }, };

    complex_stack s;
    for (auto i = args.begin(); i < args.end(); ++i) {
        if ((*i)[0] == '(') {
            s = s << complex(*i);
        } else if ((*i)[0] == 'z') {
            s = s << z;
        } else if ((*i)[0] == ';') {
            s = ~s;
        } else if ((*i)[0] == '!') {
            s = s << (+s);
        } else {
            s = s << func[(*i)[0]](s);
        }
    }

    return +s;
}

}
/*
int
main()
{
    complex h(5, 5);
    std::vector<std::string> v{"z", "(3,3)", "(2,2)", "*", "+"};
    std::cout << eval(v, h).to_string() << std::endl;
    //std::cout << h.to_string() << std::endl;
}
*/
