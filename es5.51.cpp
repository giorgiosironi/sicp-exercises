#include <string>
#include <iostream>
using namespace std;

typedef char* Symbol;


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


#define NIL (new Nil())

int main() {
    Cons* cell = new Cons(new SchemeInteger(42), new SchemeInteger(43));
    Value* i = cell->car();
    cout << i->toString() << endl;
    cout << cell->toString() << endl;
    cout << NIL->toString() << endl;
    return 0;
}
