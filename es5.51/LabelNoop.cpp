#include "label_noop.h"
#include <iostream>
using namespace std;

LabelNoop::LabelNoop(std::string name)
{
    this->name = name;
}

void LabelNoop::execute()
{
    cout << "Label: " << this->name << endl;
}
