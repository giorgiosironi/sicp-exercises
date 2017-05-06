#include "reader.h"
#include "symbol.h"
using namespace std;

// https://igor.io/2012/12/08/sexpr-reader.html
Value* Reader::parse(vector<string> input)
{
    return new Symbol(input.at(0));
}
