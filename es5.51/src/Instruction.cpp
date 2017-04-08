#include <iostream>
#include <stdexcept>
#include "instruction.h"
#include "cons.h"
#include "symbol.h"
#include "register.h"
#include "conversion.h"

vector<Value*> Instruction::fetch_operands(vector<Value*> operands)
{
    auto elements = std::vector<Value*>();
    for (std::vector<Value*>::iterator it = operands.begin() ; it != operands.end(); ++it) {
        Cons *operand = convert_to<Cons>(*it);
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
            throw std::runtime_error("expressionType should be one in ['const, 'reg], but it is " + expressionType->toString());
        }
    }

    for (int i = 0; i < elements.size(); i++) {
        if (elements.at(i) == NULL) {
            throw std::runtime_error("Operand " + std::to_string(i) + " of instruction is a NULL pointer");
        }
    }
    return elements;
}
