#include <iostream>
#include "instruction.h"
#include "cons.h"
#include "symbol.h"
#include "register.h"

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
        if (*expressionType == Symbol("const")) {
            elements.push_back(operand->cadr());
        } else if (*expressionType == Symbol("reg")) {
            Symbol* registerName = dynamic_cast<Symbol *>(operand->cadr());
            //elements.push_back(operand->cadr());
            Register* register_ = this->machine_feedback->get_register(registerName->name());
            Value* value = register_->get();
            elements.push_back(value);
        } else {
            cout << "expressionType should be one in ['const, 'reg], but it is " << expressionType->toString() << endl;
            exit(-1);
        }
    }

    for (int i = 0; i < elements.size(); i++) {
        if (elements.at(i) == NULL) {
            cout << "Operand " << i << " of instruction is a NULL pointer" << endl;
            exit(1);
        }
    }
    return elements;
}
