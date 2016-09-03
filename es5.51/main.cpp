#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "data_structures.h"
#include "is.h"

int length(Value *exp)
{
    if (is_pair(exp)) {
        Cons *cons = (Cons*) exp;
        return 1 + length(cons->cdr());
    }
    if (is_nil(exp)) {
        return 0;
    }
    // TODO: error
}

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
#include "label_noop.h"

class Perform: public Instruction
{
    private:
        Operation* operation;
    public:
        Perform(Operation* operation);
        virtual void execute();
};

Perform::Perform(Operation* operation)
{
    this->operation = operation;
}

void Perform::execute()
{
    cout << "Perform: " << this->operation->toString() << endl;
}

#include "machine.h"

Machine* eceval()
{
    // TODO: make_machine() with same arguments, instead of object
    // delegates to make_new_machine
    Machine* eceval = new Machine();
    eceval->install_operations(machine_operations());
    eceval->install_instruction_sequence(eceval->assemble(explicit_control_evaluator()));
    return eceval;
        /*
        {
            new Symbol("exp"),
            new Symbol("env"),
            new Symbol("val"),
            new Symbol("proc"),
            new Symbol("argl"),
            new Symbol("continue"),
            new Symbol("unev")
        },
        */
}

Machine::Machine()
{
    this->pc = 0;
    this->flag = new Register();
    this->stack = new Stack();
    this->the_instruction_sequence = std::vector<Instruction*>({});
    this->operations = std::map<Symbol,Operation*>();
    this->operations.insert(std::make_pair(
        Symbol("initialize-stack"),
        new InitializeStack()
    ));
}

void Machine::install_operations(std::map<Symbol,Operation*> operations)
{
    // http://stackoverflow.com/questions/3639741/merge-two-stl-maps
    this->operations.insert(operations.begin(), operations.end());
}

void Machine::install_instruction_sequence(std::vector<Instruction*> instruction_sequence)
{
    this->the_instruction_sequence = instruction_sequence;
}

Instruction* Machine::compile(Value* instruction)
{
    if (Symbol *symbol = dynamic_cast<Symbol *>(instruction)) {
        return new LabelNoop(
            ((Symbol*) instruction)->name()
        );
    }
    Cons* cons = dynamic_cast<Cons *>(instruction);
    if (is_tagged_list(cons, new Symbol("perform"))) {
        Symbol* operation = (Symbol*) cons->cadadr();
        cout << operation->toString() << endl;
        return new Perform(
            this->operations[*operation]
        );
    }
    cout << "Error compiling: " << instruction->toString() << endl;
    exit(1);
}

std::vector<Instruction*> Machine::assemble(Value* controller_text)
{
    int instruction_length = length(controller_text); 
    auto instructions = std::vector<Instruction*>({});
    Value *head = controller_text;
    for (int i = 0; i < instruction_length; i++) {
        Cons *head_as_cons = (Cons*) head;
        cout << head_as_cons->car()->toString() << endl;

        instructions.push_back(this->compile(head_as_cons->car()));
        head = head_as_cons->cdr();
    }
    return instructions;
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
