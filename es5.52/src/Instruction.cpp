#include <iostream>
#include <stdexcept>
#include "instruction.h"
#include "cons.h"
#include "integer.h"
#include "symbol.h"
#include "register.h"
#include "conversion.h"


//(define (make-primitive-exp exp machine labels)
//  (cond ((constant-exp? exp)
//         (let ((c (constant-exp-value exp)))
//           (lambda () c)))
//        ((label-exp? exp)
//         (let ((insts
//                 (lookup-label labels
//                               (label-exp-label exp))))
//           (lambda () insts)))
//        ((register-exp? exp)
//         (let ((r (get-register machine
//                                (register-exp-reg exp))))
//           (lambda () (get-contents r))))
//        (else
//          (error "Unknown expression type -- ASSEMBLE" exp))))
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
            Register* register_ = this->machine_feedback->get_register(registerName->name());
            Value* value = register_->get();
            elements.push_back(value);
        } else if (*expressionType == Symbol("label")) {
            Symbol* labelName = dynamic_cast<Symbol *>(operand->cadr());
            int labelIndex = this->machine_feedback->get_label_index(labelName);
            elements.push_back(new Integer(labelIndex));
        } else {
            throw std::runtime_error("expressionType should be one in ['const, 'reg], but it is " + expressionType->to_string() + " `" + operand->to_string() + "`");
        }
    }

    for (int i = 0; i < elements.size(); i++) {
        if (elements.at(i) == NULL) {
            throw std::runtime_error("Operand " + std::to_string(i) + " of instruction is a NULL pointer");
        }
    }
    return elements;
}
