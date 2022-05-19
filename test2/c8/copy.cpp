#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <algorithm>
#include <memory>
#include <iomanip>
#include <iostream>



class Figure {
public:
    virtual double get_square() const = 0;
    virtual std::string to_string() const = 0;
    virtual ~Figure() {}
};

class Rectangle : public Figure {
    double X = 0;
    double Y = 0;
public:
    
    static Rectangle* 
    make(const std::string& s) {
        Rectangle *ptr = new Rectangle;
        sscanf(s.c_str(), "%lf %lf", &ptr->X, &ptr->Y);
        return ptr;
    }



    double get_square() const {
        return X * Y;
    }
    std::string to_string() const {
        std::stringstream ss;
        ss << std::string("R ") << X << ' ' << Y;
        return ss.str();
    }

};

class Square : public Figure {
    double X = 0;
public:
    static Square* 
    make(const std::string& s) {
        Square *ptr = new Square;
        sscanf(s.c_str(), "%lf", &ptr->X);
        return ptr;
    }


    double get_square() const {
        return X * X;
    }

    std::string to_string() const {
        std::stringstream ss;
        ss << std::string("S ") << X;
        return ss.str();
    }
};

class Circle : public Figure {
    double R = 0;
public:
    static Circle* 
    make(const std::string& s) {
        Circle *ptr = new Circle;
        sscanf(s.c_str(), "%lf", &ptr->R);
        return ptr;
    }

    double get_square() const {
        return M_PI * R * R;
    }

    std::string to_string() const {
        std::stringstream ss;
        ss << std::string("C ") << R;
        return ss.str();
    }
};

using std::istringstream;
using std::string;

class F {
public:
    static F* obj;
    F() {}
public:
    std::map<const char, std::function<Figure*(istringstream&)>> func {
            {'R', [](istringstream& s){ string s1, s2; s>>s1>>s2; return Rectangle::make(s1 + " " + s2); }},
            {'C', [](istringstream& s){ string s1; s >> s1; return Circle::make(s1); }},
            {'S', [](istringstream& s){ string s1; s >> s1; return Square::make(s1); }}
    };

    Figure* operator()(const std::string& s) {
        istringstream ist(s);
        char c;
        ist >> c;
        return func[c](ist);
    }

    static F& factory_instance() {
        if (obj) {
            return *obj;
        }
        obj = new F();
        return *obj;
    }

    static void destroy() {
        delete obj;
    }
};

F* F::obj = nullptr;

bool comp(const std::unique_ptr<Figure>& a, const std::unique_ptr<Figure>& b) {
    return a->get_square() < b->get_square();
}

int main() {
    F g = F::factory_instance();
    string s;
    std::vector<std::unique_ptr<Figure>> v;

    while (std::getline(std::cin, s)) {
        v.push_back(std::unique_ptr<Figure>(g(s)));    
    }
    F::destroy();

    std::stable_sort(v.begin(), v.end(), comp);

    for (auto& i : v) {
        std::cout << i->to_string() << std::endl;
    }
}
