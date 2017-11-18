#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "symbol.h"
using namespace std;

template <class T> string to_string(vector<T*> v)
{
    stringstream ss;
    ss << "<";
    for (size_t i = 0; i < v.size(); ++i) {
        if(i != 0){ 
            ss << ",";
        }
        ss << v[i]->to_string();
    }
    ss << ">";
    return ss.str();
}
