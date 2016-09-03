#include "perform.h"
#include <iostream>
using namespace std;

Perform::Perform(Operation* operation)
{
    this->operation = operation;
}

void Perform::execute()
{
    cout << "Perform: " << this->operation->toString() << endl;
}
