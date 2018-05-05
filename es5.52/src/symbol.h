#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include "value.h"

class Symbol: public Value {
    private:
        std::string _name;
    public:
        Symbol(const std::string name);
        virtual std::string to_string() const;
        std::string name() const;
        bool operator <(const Symbol& right) const
        {
            return this->_name < right._name;
        }
        virtual bool equals(const Value& other) const;

};

ostream& operator<<(ostream& os, const ::Symbol& symbol);

#endif
