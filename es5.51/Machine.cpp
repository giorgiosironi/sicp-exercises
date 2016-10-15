#include <iostream>
#include "machine.h"
#include "instruction.h"
#include "initialize_stack.h"
#include "prompt_for_input.h"
#include "read.h"
#include "get_global_environment.h"
#include "label_noop.h"
#include "perform.h"
#include "assign.h"
#include "goto.h"
#include "is.h"
#include "length.h"
using namespace std;

Machine::Machine()
{
    this->pc = 0;
    this->flag = new Register("flag");
    this->stack = new Stack();
    this->registers = std::map<std::string,Register*>();
    this->the_instruction_sequence = std::vector<Instruction*>({});
    this->operations = std::map<Symbol,Operation*>();
    this->operations.insert(std::make_pair(
        Symbol("initialize-stack"),
        new InitializeStack(this->stack)
    ));
    this->operations.insert(std::make_pair(
        Symbol("prompt-for-input"),
        new PromptForInput()
    ));
    this->operations.insert(std::make_pair(
        Symbol("read"),
        new Read()
    ));
    this->operations.insert(std::make_pair(
        Symbol("get-global-environment"),
        new GetGlobalEnvironment()
    ));
}

void Machine::allocate_register(std::string name)
{
    this->registers.insert(std::make_pair(
        name,
        new Register(name)
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
    if (is_tagged_list(cons, new Symbol("assign"))) {
        return this->make_assign(cons);
    }
    if (is_tagged_list(cons, new Symbol("goto"))) {
        return this->make_goto(cons);
    }
    cout << "Error compiling: " << instruction->toString() << endl;
    exit(1);
}

// (perform (op prompt-for-input) (const "Input:"))
Instruction* Machine::make_perform(Cons* instruction)
{
    Symbol* operation = (Symbol*) instruction->cadadr();
    if (this->operations[*operation] == NULL) {
        cout << "Error looking up operation: " << operation->toString() << endl;
        exit(1);
    }
    cout << "make_perform: " << operation->toString() << endl;
    // TODO: check this->operations[*operation] is not null
    Value* maybe_operands = instruction->cddr();
    std::vector<Value*> operands_vector;
    if (maybe_operands->toString() != NIL->toString()) {
        Cons* operands = (Cons*) maybe_operands;
        cout << "operands: " << operands->toString() << endl;
        operands_vector = operands->toVector();
    } else {
        operands_vector = std::vector<Value*>();
    }
    return new Perform(
        this->operations[*operation],
        operands_vector,
        this
    );
}

// (assign exp (op read))
// (assign continue (label something))
Instruction* Machine::make_assign(Cons* instruction)
{
    Symbol* register_ = (Symbol*) instruction->cadr();
    Symbol* assignmentType = (Symbol*) instruction->caaddr();
    if (assignmentType->name() == "op") {
        Symbol* operation = (Symbol*) instruction->cadaddr();
        // TODO: this->_lookup_operation()
        if (this->operations[*operation] == NULL) {
            cout << "Error looking up operation: " << operation->toString() << endl;
            exit(1);
        }
        cout << "make_assign: " << operation->toString() << endl;
        std::vector<Value*> operands_vector;
        // only 0-operands operations are supported for assignment for now
        operands_vector = std::vector<Value*>();
        return new Assign(
                // TODO: this should be read
            this->registers[register_->name()],
            this->operations[*operation],
            operands_vector,
            this
        );
    } else if (assignmentType->name() == "label") {
        Symbol* name = (Symbol*) instruction->cadaddr();
        return new Assign(
            this->registers[register_->name()],
            new Label(name),
            this
        );
    } else {
        cout << "Unsupported assignment: " << assignmentType->name();
        exit(1);
    }
}

// (goto (label eval-dispatch))
Instruction* Machine::make_goto(Cons* instruction)
{
    return new Goto(
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
    }
    cout << "End of controller" << endl;
}

void Machine::nextInstruction()
{
    this->pc++;
}

