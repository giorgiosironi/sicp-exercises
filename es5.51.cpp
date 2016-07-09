#include <string>
#include <iostream>
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
    return 0;
}
