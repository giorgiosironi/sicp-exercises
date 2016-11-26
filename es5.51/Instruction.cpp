#include <iostream>
#include "instruction.h"
#include "cons.h"

vector<Value*> Instruction::fetch_operands(vector<Value*> operands)
{
    auto elements = std::vector<Value*>();
    for (std::vector<Value*>::iterator it = operands.begin() ; it != operands.end(); ++it) {
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
    return elements;
}
