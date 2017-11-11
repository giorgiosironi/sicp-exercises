#include "dump.h"

using namespace std;

// TODO: generalize to vector<Value*>
string to_string(vector<Symbol*> v)
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
