#include <iostream>
#include "machine.h"
#include "instruction.h"
#include "initialize_stack.h"
#include "label_noop.h"
#include "perform.h"
#include "is.h"
#include "length.h"
using namespace std;

Machine::Machine()
{
    this->pc = 0;
    this->flag = new Register();
    this->stack = new Stack();
    this->registers = std::map<std::string,Register*>();
    this->the_instruction_sequence = std::vector<Instruction*>({});
    this->operations = std::map<Symbol,Operation*>();
    this->operations.insert(std::make_pair(
        Symbol("initialize-stack"),
        new InitializeStack()
    ));
}

void Machine::allocate_register(std::string name)
{
    this->registers.insert(std::make_pair(
        name,
        new Register()
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
        return this->make_perform(cons);
    }
    cout << "Error compiling: " << instruction->toString() << endl;
    exit(1);
}

Instruction* Machine::make_perform(Cons* instruction)
{
    Symbol* operation = (Symbol*) instruction->cadadr();
    cout << "make_perform: " << operation->toString() << endl;
    // TODO: check this->operations[*operation] is not null
    return new Perform(
        this->operations[*operation]
    );
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
