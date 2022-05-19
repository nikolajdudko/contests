#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

namespace numbers
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
public:

    complex(double x = 0, double y = 0): r(x), i(y) {}


    complex(const complex& smp) 
    {
        r = smp.r;
        i = smp.i;
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
        return sqrt(r * r + i * i);
    }

    void swap(complex& s)
    {
        std::swap(r, s.r);
        std::swap(i, s.i);
    }

    complex& operator=(complex s)
    {
        swap(s);
        return *this;
    }
    
    complex& operator=(string ss)
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
        r += smp.r;
        i += smp.i;
        return *this;
    }

    const complex& operator-=(const complex& smp)
    {
        r -= smp.r;
        i -= smp.i;
        return *this;
    }

    const complex& operator*=(const complex& smp)
    {
        double a = r * smp.r - i * smp.i;
        double b = r * smp.i + smp.r * i;
        r = a;
        i = b;
        return *this;
    }

    complex& operator/=(const complex& smp)
    {
        double a = (r * smp.r + i * smp.i) / (smp.r * smp.r + smp.i * smp.i);
        double b = (i * smp.r - r * smp.i) / (smp.r * smp.r + smp.i * smp.i);
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

using namespace numbers;
int
main(void)
{

    complex g;
    string j = "(1.0, 1.0)";
    g = j;
    g.show();
    complex e("(1.0, 1.0)");
    e.show();
    e += complex(1, 1);
    e.show();
    e -= complex(1, 1);
    e.show();
    complex n = e = complex(5, 5);
    n.show();
    e.show();


    
    complex a(1, 1), b(2, 2);
    (-(a + b)).show();
    (-a).show();
    a.show();
    cout << a.to_string() << endl;

    complex z;
    z = a;
    cout << z.to_string() << endl;

    z = "(1,-0.5)";

    cout << z.to_string() << endl;
    cout << (z * 1).to_string() << endl;
    cout << (z * 3.6).to_string() << endl;

}
