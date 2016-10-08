#include "perform.h"
#include <iostream>
using namespace std;

Perform::Perform(Operation* operation, std::vector<Value*> operands, Machine* machine)
{
    this->operation = operation;
    this->operands = operands;
    this->machine = machine;
}

void Perform::execute()
{
    cout << "Perform: " << this->operation->toString() << endl;
    cout << "operands length: " << this->operands.size() << endl;
    auto elements = std::vector<Value*>();
    for (std::vector<Value*>::iterator it = this->operands.begin() ; it != this->operands.end(); ++it) {
        Cons *operand = dynamic_cast<Cons *>(*it);
        if (!operand) {
            cout << "value should be a list like (const 'something'), but it is " << (*it)->toString() << endl;
            exit(-1);
        }
        auto expressionType = operand->car();
        if (expressionType->toString() == "'const") {
            elements.push_back(operand->cadr());
        } else {
            cout << "expressionType should be one in ['const], but it is " << expressionType->toString() << endl;
            exit(-1);
        }
    }
    this->operation->execute(elements);
}
