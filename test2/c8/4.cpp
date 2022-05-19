#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <algorithm>
#include <memory>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


namespace Game {

template<typename T>
class Coord {
public:
    T row;
    T col;
    Coord() {}
    Coord(const T& x) : row(x), col(0) {}
    Coord(const T& x, const T& y) : row(x), col(y) {}
    typedef T value_type;

};


template<typename T>
T dist(Coord<T> sz, Coord<T> a, Coord<T> b) {

    T y1 = a.row;
    T x1 = a.col;
    T y2 = b.row;
    T x2 = b.col;
    T du = x2 - x1;
    T dv = (y2 + x2 / 2) - (y1 + x1 / 2);

    if ((du >= 0 and dv >= 0) or (du < 0 and dv < 0)) {
        return std::max(abs(du), abs(dv)); 
    } else {
        return abs(du) + abs(dv);
    }
}
}

