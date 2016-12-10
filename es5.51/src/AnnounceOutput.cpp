#include "announce_output.h"
#include "bool.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* AnnounceOutput::execute(std::vector<Value*> elements)
{
    cout << elements.at(0)->toString() << endl;
}

std::string AnnounceOutput::toString()
{
    return std::string("Operation-AnnounceOutput");
}

