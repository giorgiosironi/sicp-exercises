#ifndef STRING_H
#define STRING_H
#include <string>
#include "value.h"

class String: public Value {
    private:
        std::string contents;
    public:
        String(std::string contents);
        virtual std::string toString();
        bool operator <(const String& right) const
        {
            return this->contents < right.contents;
        }
        virtual bool equals(const Value& other) const;
};

#endif
