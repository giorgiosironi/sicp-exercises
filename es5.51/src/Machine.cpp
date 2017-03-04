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
#include "branch.h"
#include "test.h"
#include "save.h"
#include "restore.h"
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
    cout << "Error compiling, unknown instruction: " << instruction->toString() << endl;
    exit(1);
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
    cout << "make_perform: " << operation->toString() << endl;
    Value* maybe_operands = instruction->cddr();
    std::vector<Value*> operands_vector = this->operands_vector(maybe_operands);
    return new Perform(
        operation,
        operands_vector,
        this
    );
}

// (op prompt-for-input)
Operation* Machine::operation(Value* instruction_argument)
{
    Symbol* operation = (Symbol*) (((Cons*) instruction_argument)->cadr());
    cout << "operation: " << operation->toString() << endl;
    if (this->operations[*operation] == NULL) {
        cout << "Error looking up operation: " << operation->toString() << endl;
        exit(1);
    }
    return this->operations[*operation];
}

/**
 * tail_of_instruction after instruction name and (op ...) have been removed
 */
std::vector<Value*> Machine::operands_vector(Value* tail_of_instruction)
{
    std::vector<Value*> operands_vector;
    if (tail_of_instruction->toString() != NIL->toString()) {
        Cons* operands = (Cons*) tail_of_instruction;
        cout << "operands: " << operands->toString() << endl;
        operands_vector = operands->toVector();
        cout << "vector: " << operands_vector.size() << endl;
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
    Symbol* register_ = dynamic_cast<Symbol*>(instruction->cadr());
    if (register_ == NULL) {
        cout << "First argument to assign is not a register name" << endl;
        exit(1);
    }
    Symbol* assignmentType = (Symbol*) instruction->caaddr();
    if (assignmentType->name() == "op") {
        Symbol* operation = (Symbol*) instruction->cadaddr();
        // TODO: this->_lookup_operation()
        if (this->operations[*operation] == NULL) {
            cout << "Error looking up operation: " << operation->toString() << endl;
            exit(1);
        }
        cout << "make_assign: " << operation->toString() << endl;
        Value* maybe_operands = instruction->cdddr();
        std::vector<Value*> operands_vector = this->operands_vector(maybe_operands);
        return new Assign(
            this->get_register(register_->name()),
            this->operations[*operation],
            operands_vector,
            this
        );
    } else if (assignmentType->name() == "label") {
        Symbol* label = (Symbol*) instruction->cadaddr();

        if (!labels.count(label->name())) {
            cout << "Unknown label used by assign: " << label->toString() << endl;
            exit(1);
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
        cout << "Unsupported assignment: " << assignmentType->name();
        exit(1);
    }
}

// (goto (label eval-dispatch))
// (goto (reg continue))
Instruction* Machine::make_goto(Cons* instruction, std::map<Symbol,int> labels)
{
    Symbol* assignmentType = (Symbol*) instruction->caadr();
    if (assignmentType->name() == "label") {
        Symbol* labelName = (Symbol*) instruction->cadadr();
        cout << "labelName: " << labelName->toString() << endl;
        if (!labels.count(*labelName)) {
            cout << "Unknown label pointed by goto: " << labelName->toString() << endl;
            exit(1);
        }
        int labelIndex = labels[*labelName];
        cout << "labelIndex: " << labelIndex << endl;
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
        cout << "Unknown assignment type in goto: " << assignmentType->toString() << endl;
    }
}

// (branch (label eval-dispatch))
Instruction* Machine::make_branch(Cons* instruction, std::map<Symbol,int> labels)
{
    Symbol* labelName = (Symbol*) instruction->cadadr();
    cout << "labelName: " << labelName->toString() << endl;
    if (!labels.count(*labelName)) {
        cout << "Unknown label pointed by branch: " << labelName->toString() << endl;
        exit(1);
    }
    int labelIndex = labels[*labelName];
    cout << "labelIndex: " << labelIndex << endl;
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
    cout << "make_test: " << operation->toString() << endl;
    Value* maybe_operands = instruction->cddr();
    std::vector<Value*> operands_vector = this->operands_vector(maybe_operands);
    return new Test(this->flag, operation, operands_vector, this);
}

// (save unev)
Instruction* Machine::make_save(Cons* instruction)
{
    Symbol* register_ = dynamic_cast<Symbol*>(instruction->cadr());
    if (register_ == NULL) {
        cout << "(save ...) needs a symbol" << endl;
        exit(1);
    }
    cout << "make_save: register " << register_->toString() << endl;
    Register* r = this->get_register(register_->name());
    return new Save(this->stack, r, this);
}

// (restore continue)
Instruction* Machine::make_restore(Cons* instruction)
{
    Symbol* register_ = dynamic_cast<Symbol*>(instruction->cadr());
    if (register_ == NULL) {
        cout << "(restore ...) needs a symbol" << endl;
        exit(1);
    }
    cout << "make_restore: register " << register_->toString() << endl;
    Register* r = this->get_register(register_->name());
    return new Restore(this->stack, r, this);
}

std::vector<Instruction*> Machine::assemble(Value* controller_text)
{
    int instruction_length = length(controller_text); 
    auto instructions = std::vector<Instruction*>({});
    Value *head = controller_text;
    auto labels = this->extract_labels(controller_text);
    // trying to dump labels
    //for (auto i = labels.begin(); i != labels.end(); i++) {
    //    cout << (i->first).toString() << endl;// " " << i->second << endl;
    //}
    for (int i = 0; i < instruction_length; i++) {
        Cons *head_as_cons = (Cons*) head;
        cout << head_as_cons->car()->toString() << endl;

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
        cout << "Unknown register: " << name << endl;
        exit(1);
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
    cout << "End of controller" << endl;
}


