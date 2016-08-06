#ifndef STRING_H
#define STRING_H
#include <string>
#include "value.h"

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

#endif
