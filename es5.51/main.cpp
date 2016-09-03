#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "data_structures.h"
#include "is.h"
#include "operation.h"
#include "is_self_evaluating.h"
#include "initialize_stack.h"


Value* build_list(std::vector<Value*> elements) {
    Value *head = NIL;
    for (int i = elements.size() - 1; i >= 0; i--) {
        head = new Cons(elements.at(i), head);
    }
    return head;
}

Value* explicit_control_evaluator()
{
    return build_list({
        new Symbol("start-of-machine"),
        new Symbol("read-eval-print-loop"),
        build_list({
            new Symbol("perform"),
            build_list({
                new Symbol("op"),
                new Symbol("initialize-stack"),
            })
        })/*,
        build_list({
            new Symbol("perform"),
            build_list({
                new Symbol("op"),
                new Symbol("prompt-for-input"),
            }),
            build_list({
                new Symbol("const"),
                new String(";;; EC-Eval input:")
            })
        })
        */
    });
}

/**
 * Try to define Operation : Value
 * http://stackoverflow.com/questions/20835534/function-pointer-without-arguments-types
 * that stores a pointer to a function that takes any parameters and then
 * returns a *Value
 * Should have a method apply(std::vector<Value*>)
 * and when we implement apply we can pass the arguments in
 * It should probably have a case on the number of arguments (from 0 to 3-4)
 * so that it can then cast the general pointer to the correct one and call
 * it.
 * This should become a map from String representing the name to the Operation then.
 */
std::map<Symbol,Operation*> machine_operations()
{
    auto operations = std::map<Symbol,Operation*>();
    operations.insert(std::make_pair(
        Symbol("is-self-evaluating"),
        new IsSelfEvaluating()
    ));
    return operations;
}

#include "instruction.h"
#include "machine.h"

/**
 * Inline here make_machine, the Facade
 */
Machine* eceval()
{
    Machine* eceval = new Machine();
    eceval->allocate_register("exp");
    eceval->allocate_register("env");
    eceval->allocate_register("val");
    eceval->allocate_register("proc");
    eceval->allocate_register("argl");
    eceval->allocate_register("continue");
    eceval->allocate_register("unev");
    eceval->install_operations(machine_operations());
    eceval->install_instruction_sequence(eceval->assemble(explicit_control_evaluator()));
    return eceval;
}



void Machine::start()
{
    this->pc = 0;
    this->execute();
}

void Machine::execute()
{
    while (this->pc < this->the_instruction_sequence.size()) {
        Instruction* i = this->the_instruction_sequence.at(this->pc);
        // TODO: return effects like the increment of pc
        // instead of always applying them (will be needed to implement jumps)
        i->execute();
        this->pc++;
    }
    cout << "End of controller" << endl;
}

int main() {
    /*
    Cons* cell = new Cons(new SchemeInteger(42), new SchemeInteger(43));
    Value* i = cell->car();
    cout << i->toString() << endl;
    cout << cell->toString() << endl;
    cout << NIL->toString() << endl;
    cout << is_pair(NIL) << endl;
    cout << is_pair(cell) << endl;
    cout << is_eq(cell, cell) << endl;
    cout << is_eq(cell, NIL) << endl;
    Value* s = new Symbol("tag");
    cout << s->toString() << endl;
    Cons* taggedList = new Cons(new Symbol("integer"), new SchemeInteger(42));
    cout << is_tagged_list(taggedList, new Symbol("integer")) << endl;
    std::vector<Value*> elements = {new SchemeInteger(1), new SchemeInteger(2), new SchemeInteger(3)};
    Value* threeElementList = build_list({new SchemeInteger(1), new SchemeInteger(2), new SchemeInteger(3)});
    cout << threeElementList->toString() << endl;
    */
    Machine* machine = eceval();
    machine->start();
    return 0;
}
