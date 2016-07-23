#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Value
{
    public:
        virtual std::string toString() = 0;
};

class SchemeInteger : public Value
{
    private:
        int contents;
    public:
        SchemeInteger(int contents);
        virtual std::string toString();
};

SchemeInteger::SchemeInteger(int contents)
{
    this->contents = contents;
}

std::string SchemeInteger::toString()
{
    return std::to_string(this->contents);
}

bool is_number(Value *exp)
{
    if (SchemeInteger *schemeInteger = dynamic_cast<SchemeInteger *>(exp)) {
        return true;
    }
    return false;
}


class Cons : public Value
{
    private:
        Value *car_ptr;
        Value *cdr_ptr;

    public:
        Cons(Value *car_ptr, Value *cdr_ptr);
        Value* car();
        Value* cdr();
        virtual std::string toString();
};

Cons::Cons(Value *car_ptr, Value *cdr_ptr)
{
    this->car_ptr = car_ptr;
    this->cdr_ptr = cdr_ptr;
}

Value* Cons::car()
{
    return this->car_ptr;
}

Value* Cons::cdr()
{
    return this->cdr_ptr;
}

std::string Cons::toString()
{
    return std::string("(")
        + this->car_ptr->toString()
        + std::string(" . ")
        + this->cdr_ptr->toString() 
        + std::string(")");
}

class Nil : public Value 
{
    public:
        virtual std::string toString();
};

std::string Nil::toString()
{
    return std::string("NIL");
}

bool is_pair(Value *exp)
{
    if (Cons *cons = dynamic_cast<Cons *>(exp)) {
        return true;
    }
    return false;
}

#define NIL (new Nil())

class Symbol: public Value {
    private:
        std::string name;
    public:
        Symbol(std::string name);
        virtual std::string toString();
};

Symbol::Symbol(std::string name)
{
    this->name = name;
}

std::string Symbol::toString()
{
    return std::string("'") + this->name;
}

class String: public Value {
    private:
        std::string name;
    public:
        String(std::string name);
        virtual std::string toString();
        bool operator <(const String& right) const
        {
            return this->name < right.name;
        }
};

String::String(std::string name)
{
    this->name = name;
}

std::string String::toString()
{
    return this->name;
}


bool is_string(Value *exp)
{
    if (String *string = dynamic_cast<String *>(exp)) {
        return true;
    }
    return false;
}

class Bool: public Value {
    private:
        bool value;
    public:
        Bool(bool value);
        virtual std::string toString();
};

Bool::Bool(bool value)
{
    this->value = value;
}

std::string Bool::toString()
{
    return std::string(this->value ? "#t" : "#f");
}

class Operation: public Value {
    public:
        virtual Value* execute(std::vector<Value*> elements) = 0;
};

class IsSelfEvaluating: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

Value* IsSelfEvaluating::execute(std::vector<Value*> elements)
{
    return new Bool(is_number(elements.at(0)) || is_string(elements.at(0)));
}

std::string IsSelfEvaluating::toString()
{
    return std::string("Operation-IsSelfEvaluating");
}


/**
 * Trick: compare the string representations, since we are talking about
 * simple data structures here. If we get a recurring pointer, this will explode
 */
bool is_eq(Value *former, Value *latter)
{
    return former->toString() == latter->toString();
}

bool is_tagged_list(Value *exp)
{
    if (is_pair(exp)) {
        return true;
    }
    return false;
}

bool is_tagged_list(Value *exp, Symbol* tag)
{
    if (is_pair(exp)) {
        Cons *expAsPair = (Cons *) exp;
        return is_eq(expAsPair->car(), tag);
    }
    return false;
}

bool is_begin(Value* exp)
{
    return is_tagged_list(exp, new Symbol("begin"));
}

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
        new Symbol("read-eval-print-loop")/*,
        build_list({
            new Symbol("perform"),
            build_list({
                new Symbol("op"),
                new Symbol("initialize-stack"),
            })
        }),
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
std::map<String,Operation*> machine_operations()
{

    auto operations = std::map<String,Operation*>();
    operations.insert(std::make_pair(
        String("is_self_evaluating"),
        new IsSelfEvaluating()
    ));
    return operations;
}

class Instruction
{
    public:
        virtual void execute() = 0;
};

class LabelNoop : public Instruction
{
    private:
        std::string name;
    public:
        LabelNoop(std::string name);
        virtual void execute();
};

LabelNoop::LabelNoop(std::string name)
{
    this->name = name;
}

void LabelNoop::execute()
{
    cout << "Label: " << this->name << endl;
}

class Machine {
    private:
        int pc;
        std::vector<Instruction*> the_instruction_sequence;
        std::vector<Instruction*> assemble(Value* controller_text);
        void execute();
    public:
        Machine(std::vector<Value*> register_names, std::map<String,Operation*> operations, Value* controller_text);
        void start();
};

Machine::Machine(std::vector<Value*> register_names, std::map<String,Operation*> operations, Value* controller_text)
{
    this->pc = 0;
    this->the_instruction_sequence = this->assemble(controller_text);
}

std::vector<Instruction*> Machine::assemble(Value* controller_text)
{
    
}

void Machine::start()
{
    this->pc = 0;
    this->execute();
}

void Machine::execute()
{
    if (this->pc >= this->the_instruction_sequence.size()) {
        cout << "End of controller" << endl;
        return;
    }
    Instruction* i = this->the_instruction_sequence.at(this->pc);
    // TODO: return effects like the increment of pc
    i->execute();
}

Machine* eceval()
{
    return new Machine(
        {
            new Symbol("exp"),
            new Symbol("env"),
            new Symbol("val"),
            new Symbol("proc"),
            new Symbol("argl"),
            new Symbol("continue"),
            new Symbol("unev")
        },
        machine_operations(),
        explicit_control_evaluator()
    );
}

int main() {
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
    Machine* machine = eceval();
    machine->start();
    return 0;
}
