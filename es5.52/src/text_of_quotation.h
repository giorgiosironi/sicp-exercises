#ifndef TEXT_OF_QUOTATION_H
#define TEXT_OF_QUOTATION_H
#include "operation.h"

class TextOfQuotation: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string();
};

#endif
