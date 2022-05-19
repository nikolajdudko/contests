#include <iostream>
#include <iomanip> 
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <set>
#include <map>


template <typename T>
class Figure {
public:
    virtual T get_square() const = 0;
    virtual ~Figure() {}
};

template <typename T = double>
class Rectangle : Figure<T> {
    T X;
    T Y;
public:
    
    Rectangle() {}
    ~Rectangle() {}

    T get_square() const 
    {
        return X * Y;
    }

};

template <typename T = double>
class Square : Figure<T> {
    T X;
public:
    
    Square() {}
    ~Square(){}

    T get_square() const 
    {
        return X * X;
    }
};

template <typename T = double>
class Circle : Figure<T> {
    T R;
public:
    Circle() {}

    ~Circle() {}

    T get_square() const 
    {
        return R * R;
    }
};


int
main()
{
    Circle q;
    Rectangle w;

}
