#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include "value.h"

class Symbol: public Value {
    private:
        std::string _name;
    public:
        Symbol(std::string name);
        virtual std::string toString();
        std::string name();
        bool operator <(const Symbol& right) const
        {
            return this->_name < right._name;
        }
};

#endif
