#include <iostream>
#include <cmath>
#include <string>
#include <sstream>


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

/*
int
main() {
    std::string s = "10";
    std::string s1 = "10 2";
    Circle *a = Circle::make(s);
    Rectangle *b = Rectangle::make(s1);
    Square *c = Square::make(s);
    std::cout << a->get_square() << ' ' << b->get_square() << ' ' << c->get_square() << std::endl;

}

*/
