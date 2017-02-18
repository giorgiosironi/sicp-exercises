#ifndef BOOL_H
#define BOOL_H
#include <string>
#include "value.h"

class Bool: public Value {
    private:
        bool value;
    public:
        Bool(bool value);
        virtual std::string toString();
        bool isTrue();
        bool isFalse();
        virtual bool equals(const Value& other) const;
};


#endif
