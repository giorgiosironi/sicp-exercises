#ifndef READER_H
#define READER_H
#include <string>
#include <vector>
#include "value.h"
using namespace std;

class Reader {
    public:
        Value* parse(vector<string> input);
};

#endif
