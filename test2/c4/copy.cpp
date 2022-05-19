#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cstring>


using std::string;
using std::cout;
using std::cin;
using std::endl;

std::string s;

bool
comp(std::pair<char*, int> x, std::pair<char*, int> y)
{
    return std::strcmp(x.first, y.first) < 0;
}

int main()
{
    std::getline(std::cin, s);
    size_t i, strEnd = s.find_last_not_of(' ');
    if (strEnd == std::string::npos) {
        return 0;
    }   
    while ((i = s.find(' ', strEnd)) != std::string::npos) {
        s.erase(i);
    }

    char *l = new char[s.length() + 1];
    strcpy(l, s.c_str());


    std::vector<std::pair<char*, int>> v;

    int j = 0;
    while (*l) {
        v.emplace_back(std::make_pair(l++, j++));
    }
      
    std::sort(v.begin(), v.end(), comp);    
       
    for (auto n : v) {
        cout << n.second << endl;
    }  
}
