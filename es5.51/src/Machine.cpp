#include <iostream>
#include <stdexcept>
#include "machine.h"
#include "instruction.h"
#include "initialize_stack.h"
#include "prompt_for_input.h"
#include "read.h"
#include "label_noop.h"
#include "perform.h"
#include "assign.h"
#include "goto.h"
#include "branch.h"
#include "test.h"
#include "save.h"
#include "restore.h"
#include "is.h"
#include "length.h"
#include "conversion.h"
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

Instruction* Machine::compile(Value* instruction, std::map<Symbol,int> labels)
{
    if (Symbol *symbol = dynamic_cast<Symbol *>(instruction)) {
        return this->make_label_noop(symbol);
    }
    Cons* cons = dynamic_cast<Cons *>(instruction);
    if (is_tagged_list(cons, new Symbol("perform"))) {
        return this->make_perform(cons);
    }
    if (is_tagged_list(cons, new Symbol("assign"))) {
        return this->make_assign(cons, labels);
    }
    if (is_tagged_list(cons, new Symbol("goto"))) {
        return this->make_goto(cons, labels);
    }
    if (is_tagged_list(cons, new Symbol("branch"))) {
        return this->make_branch(cons, labels);
    }
    if (is_tagged_list(cons, new Symbol("test"))) {
        return this->make_test(cons);
    }
    if (is_tagged_list(cons, new Symbol("save"))) {
        return this->make_save(cons);
    }
    if (is_tagged_list(cons, new Symbol("restore"))) {
        return this->make_restore(cons);
    }
    throw std::logic_error("Error compiling, unknown instruction: " + instruction->to_string());
}

Instruction* Machine::make_label_noop(Symbol* symbol)
{
    return new LabelNoop(
        symbol->name(),
        this
    );
}

// (perform (op prompt-for-input) (const "Input:"))
Instruction* Machine::make_perform(Cons* instruction)
{
    auto operation = this->operation(instruction->cadr());
    cerr << "make_perform: " << operation->to_string() << endl;
    Value* maybe_operands = instruction->cddr();
    std::vector<Value*> operands_vector = this->operands_vector(maybe_operands);
    return new Perform(
        operation,
        operands_vector,
        this
    );
}

Operation* Machine::lookup_operation(Symbol* name)
{
    if (this->operations[*name] == NULL) {
        throw std::invalid_argument("Error looking up operation: " + name->to_string());
    }
    return this->operations[*name];
}

// (op prompt-for-input)
Operation* Machine::operation(Value* instruction_argument)
{
    Symbol* operation = (Symbol*) (((Cons*) instruction_argument)->cadr());
    cerr << "operation: " << operation->to_string() << endl;
    return this->lookup_operation(operation);
}

/**
 * tail_of_instruction after instruction name and (op ...) have been removed
 */
std::vector<Value*> Machine::operands_vector(Value* tail_of_instruction)
{
    std::vector<Value*> operands_vector;
    if (tail_of_instruction->to_string() != NIL->to_string()) {
        Cons* operands = (Cons*) tail_of_instruction;
        cerr << "operands: " << operands->to_string() << endl;
        operands_vector = operands->to_vector();
        cerr << "vector: " << operands_vector.size() << endl;
    } else {
        operands_vector = std::vector<Value*>();
    }
    return operands_vector;
}

// (assign exp (op read))
// (assign continue (label something))
// (assign val (op read) (reg exp))
// (assign val (const 42))
Instruction* Machine::make_assign(Cons* instruction, std::map<Symbol,int> labels)
{
    Symbol* register_ = convert_to<Symbol>(instruction->cadr());
    Symbol* assignmentType = (Symbol*) instruction->caaddr();
    if (assignmentType->name() == "op") {
        Symbol* operation = (Symbol*) instruction->cadaddr();
        cerr << "make_assign: " << operation->to_string() << endl;
        Value* maybe_operands = instruction->cdddr();
        std::vector<Value*> operands_vector = this->operands_vector(maybe_operands);
        return new Assign(
            this->get_register(register_->name()),
            this->lookup_operation(operation),
            operands_vector,
            this
        );
    } else if (assignmentType->name() == "label") {
        Symbol* label = (Symbol*) instruction->cadaddr();

        if (!labels.count(label->name())) {
            throw std::logic_error("Unknown label used by assign: " + label->to_string());
        }
        int labelIndex = labels[label->name()];
        return new Assign(
            this->get_register(register_->name()),
            new Integer(labelIndex),
            this
        );
    } else if (assignmentType->name() == "reg") {
        Symbol* source = (Symbol*) instruction->cadaddr();
        return new Assign(
            this->get_register(register_->name()),
            this->get_register(source->name()),
            this
        );
    } else if (assignmentType->name() == "const") {
        Value* constant = instruction->cadaddr();
        return new Assign(
            this->get_register(register_->name()),
            constant,
            this
        );
    } else {
        throw std::logic_error("Unsupported assignment: " + assignmentType->name());
    }
}

// (goto (label eval-dispatch))
// (goto (reg continue))
Instruction* Machine::make_goto(Cons* instruction, std::map<Symbol,int> labels)
{
    Symbol* assignmentType = (Symbol*) instruction->caadr();
    if (assignmentType->name() == "label") {
        Symbol* labelName = (Symbol*) instruction->cadadr();
        cerr << "labelName: " << labelName->to_string() << endl;
        if (!labels.count(*labelName)) {
            throw std::logic_error("Unknown label pointed by goto: " + labelName->to_string());
        }
        int labelIndex = labels[*labelName];
        cerr << "labelIndex: " << labelIndex << endl;
        return new Goto(
            this,
            labelIndex
        );
    } else if (assignmentType->name() == "reg") {
        Symbol* register_ = (Symbol*) instruction->cadadr();
        return new Goto(
            this,
            this->get_register(register_->name())
        );
    } else {
        throw std::logic_error("Unknown assignment type in goto: " + assignmentType->to_string());
    }
}

// (branch (label eval-dispatch))
Instruction* Machine::make_branch(Cons* instruction, std::map<Symbol,int> labels)
{
    Symbol* labelName = (Symbol*) instruction->cadadr();
    cerr << "labelName: " << labelName->to_string() << endl;
    if (!labels.count(*labelName)) {
        throw std::logic_error("Unknown label pointed by branch: " + labelName->to_string());
    }
    int labelIndex = labels[*labelName];
    cerr << "labelIndex: " << labelIndex << endl;
    return new Branch(
        this->flag,
        this,
        labelIndex
    );
}

// (test (op self-evaluating?) (reg exp))
Instruction* Machine::make_test(Cons* instruction)
{
    auto operation = this->operation(instruction->cadr());
    cerr << "make_test: " << operation->to_string() << endl;
    Value* maybe_operands = instruction->cddr();
    std::vector<Value*> operands_vector = this->operands_vector(maybe_operands);
    return new Test(this->flag, operation, operands_vector, this);
}

// (save unev)
Instruction* Machine::make_save(Cons* instruction)
{
    Symbol* register_ = dynamic_cast<Symbol*>(instruction->cadr());
    if (register_ == NULL) {
        throw std::logic_error("(save ...) needs a symbol");
    }
    cerr << "make_save: register " << register_->to_string() << endl;
    Register* r = this->get_register(register_->name());
    return new Save(this->stack, r, this);
}

// (restore continue)
Instruction* Machine::make_restore(Cons* instruction)
{
    Symbol* register_ = dynamic_cast<Symbol*>(instruction->cadr());
    if (register_ == NULL) {
        throw std::logic_error("(restore ...) needs a symbol");
    }
    cerr << "make_restore: register " << register_->to_string() << endl;
    Register* r = this->get_register(register_->name());
    return new Restore(this->stack, r, this);
}

std::vector<Instruction*> Machine::assemble(Value* controller_text)
{
    int instruction_length = length(controller_text); 
    auto instructions = std::vector<Instruction*>({});
    Value *head = controller_text;
    auto labels = this->extract_labels(controller_text);
    for (int i = 0; i < instruction_length; i++) {
        Cons *head_as_cons = (Cons*) head;
        cerr << head_as_cons->car()->to_string() << endl;

        instructions.push_back(this->compile(head_as_cons->car(), labels));
        head = head_as_cons->cdr();
    }
    return instructions;
}

std::map<Symbol,int> Machine::extract_labels(Value* controller_text)
{
    auto labels = std::map<Symbol,int>();
    int instruction_length = length(controller_text); 
    Value *head = controller_text;
    for (int index = 0; index < instruction_length; index++) {
        Cons *head_as_cons = (Cons*) head;

        if (Symbol *symbol = dynamic_cast<Symbol *>(head_as_cons->car())) {
            labels.insert(std::make_pair(
                *symbol,
                index
            ));
        }
        head = head_as_cons->cdr();
    }
    return labels;
}

Register* Machine::get_register(std::string name)
{
    Register* r = this->registers[name];
    if (r == NULL) {
        throw std::logic_error("Unknown register: ");
    }
    return r;
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
    cerr << "End of controller" << endl;
}


