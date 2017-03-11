#include "adjoin_arg.h"
#include "cons.h"
#include <iostream>
using namespace std;

Value* AdjoinArg::execute(vector<Value*> elements)
{
    if (elements.size() != 2) {
        cout << "Need 2 elements" << endl;
        exit(1);
    }
    auto list = dynamic_cast<List*>(elements.at(1));
    if (list == NULL) {
        cout << "Second element must be a list" << endl;
        exit(1);
    }
    return list->append(elements.at(0));
}

string AdjoinArg::toString()
{
    return string("Operation-AdjoinArg");
}

