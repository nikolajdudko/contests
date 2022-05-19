#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <functional>
//#include "set.cpp"

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



struct item
{
    complex value;
    item *next;
    item *prev;
};

class complex_stack
{
    item *bot;
    item *top;
    size_t sz;

    void
    push(const complex& s)
    {
        if (top == NULL) {
            bot = top = new item;
            top->prev = NULL;
        } else {
            top->next = new item;
            top->next->prev = top;
            top = top->next;
        }
        top->next = NULL;
        top->value = s;
        sz++;
    }

public:

    void
    show() {
        item *tmp = bot;
        std::cout << std::endl;
        while (tmp != NULL && tmp->next != NULL) {
            std::cout << tmp->value.to_string() << std::endl;
            tmp = tmp->next;
        }
        std::cout << tmp->value.to_string() << std::endl;
        std::cout << std::endl;
    }

    complex_stack()
    {
        sz = 0;
        bot = NULL;
        top = NULL;
    }

    complex_stack(const complex& s): complex_stack()
    {
        (*this).push(s);
    }

    complex_stack(const complex_stack& smp): complex_stack()
    {
        for (int i = 0; i < (int)smp.sz; i++) {
            (*this).push(smp[i]);
        }
    }

    ~complex_stack() {
        while (bot != NULL && bot->next != NULL) {
            bot = bot->next;
            delete bot->prev;
        }
        if (bot != NULL) {
            delete bot; 
        }
    }
    
    const size_t size() const 
    {
        return sz;
    }

    const complex operator[](const int& i) const
    {
        item *tmp = bot;
        for (int j = i; j > 0; j--) {
            tmp = tmp->next;
        }
        return tmp->value;
    }
    
    const complex_stack operator<<(complex s) const
    {
        complex_stack a(*this);
        a.push(s);
        return a;
    }

    const complex operator+() const
    {
        return top->value;
    }

    const complex_stack operator~() const
    {
        complex_stack a(*this);
        item *tmp = a.top;
        if (a.sz == 1) {
            a.bot = a.top = NULL;    
        } else {
            a.top = a.top->prev;
            a.top->next = NULL;
        }
        a.sz--;
        delete tmp;
        return a;
    }

//copy-and-swap
    const complex_stack operator=(complex_stack smp)
    {
        (*this).swap(smp);
        return *this;
    } 

private:
    void
    swap(complex_stack& smp) {

        item *tmp = bot;
        bot = smp.bot;
        smp.bot = tmp;

        tmp = top;
        top = smp.top;
        smp.top = tmp;

        size_t t = sz;
        sz = smp.sz;
        smp.sz = t;
    }
};


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
