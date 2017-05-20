#ifndef READER_H
#define READER_H
#include <string>
#include <vector>
#include <tuple>
#include "value.h"
using namespace std;

class Reader {
    public:
        Value* parse(vector<string> input);
    private:
        tuple<vector<string>,int> extract_list_tokens(vector<string> tokens, int i);
};

#endif
