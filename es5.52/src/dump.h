#include <iostream>
#include <sstream>
#include <vector>
#include <set>
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

template <class T> string to_string(set<T*> v)
{
    stringstream ss;
    ss << "{";
    int i = 0;
    for (typename set<T*>::iterator it = v.begin(); it != v.end(); ++it) {
        if(i != 0){ 
            ss << ",";
        }
        ss << (*it)->to_string();
        i++;
    }
    ss << "}";
    return ss.str();
}
