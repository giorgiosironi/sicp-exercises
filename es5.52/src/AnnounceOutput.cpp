#include "announce_output.h"
#include "bool.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* AnnounceOutput::execute(std::vector<Value*> elements)
{
    cout << elements.at(0)->to_string() << endl;
}

std::string AnnounceOutput::to_string() const
{
    return std::string("Operation-AnnounceOutput");
}

