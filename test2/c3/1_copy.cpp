#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace A
{
using std::cin;
using std::cout;
using std::hex;
using std::endl;
using std::string;

class complex
{
    double r;
    double i;
public:

    void
    show()
    {
        cout << std::setprecision(10) << "(" << r << "," << i << ")" << endl;
        return;
    }

    complex(double x = 0, double y = 0): r(x), i(y) {}


    complex(const complex& smp) 
    {
        r = smp.re();
        i = smp.im();
    }

    ~complex()
    {
    }

    explicit complex(const string& str) 
    {
        sscanf(str.c_str(), "(%lf,%lf)", &r, &i);
    }
    


    double re() const
    {
        return r;
    }

    double im() const
    {
        return i;
    }

    double abs2() const
    {
        return r * r + i * i;
    }
    
    double abs() const
    {
        return sqrt((*this).abs2());
    }

    void swap(complex& s)
    {
        std::swap(r, s.r);
        std::swap(i, s.i);
    }

    const complex& operator=(complex s)
    {
        swap(s);
        return *this;
    }

    const complex& operator=(const string& ss)
    {
        complex com(ss);
        swap(com);
        return *this;
    }
 
    string to_string() const
    {
        std::stringstream ss;
        ss << std::setprecision(10) << "(" << r << "," << i << ")";
        return ss.str();
    }

    const complex& operator+=(const complex& smp)
    {
        r += smp.re();
        i += smp.im();
        return *this;
    }

    const complex& operator-=(const complex& smp)
    {
        r -= smp.re();
        i -= smp.im();
        return *this;
    }

    const complex& operator*=(const complex& smp)
    {
        double a = r * smp.re() - i * smp.im();
        double b = r * smp.im() + smp.re() * i;
        r = a;
        i = b;
        return *this;
    }

    complex& operator/=(const complex& smp)
    {
        double a = (r * smp.re() + i * smp.im()) / smp.abs2();
        double b = (i * smp.re() - r * smp.im()) / smp.abs2();
        r = a;
        i = b;
        return *this;
    }

    complex operator~() const
    {
        return complex(r, -i);
    }

    complex operator-() const
    {
        return complex(-r, -i);
    }

};
    
const complex operator+(const complex& smp1, const complex& smp2)
{
    return complex(smp1) += smp2;
}
    
const complex operator-(const complex& smp1, const complex& smp2)
{
    return complex(smp1) -= smp2;
}

const complex operator*(const complex& smp1, const complex& smp2)
{
    return complex(smp1) *= smp2;
}

const complex operator/(const complex& smp1, const complex& smp2)
{
    return complex(smp1) /= smp2;
}
}
