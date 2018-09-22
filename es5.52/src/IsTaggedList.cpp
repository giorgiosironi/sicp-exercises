#include "is_tagged_list.h"
#include "bool.h"
#include "is.h"
#include <iostream>
using namespace std;

IsTaggedList::IsTaggedList(Symbol* tag)
{
    this->tag = tag;
}

Value* IsTaggedList::execute(std::vector<Value*> elements)
{
    cerr << "[e] " << elements.at(0)->to_string() << endl;
    if (is_tagged_list(elements.at(0), this->tag)) {
        return new Bool(true);
    }
    return new Bool(false);
}

std::string IsTaggedList::to_string() const
{
    return std::string("Operation-IsTaggedList");
}

