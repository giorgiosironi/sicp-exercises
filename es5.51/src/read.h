#ifndef READ_H
#define READ_H
#include <string>
#include <vector>
#include "value.h"
#include "operation.h"

class Read: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual Value* parse(std::string input);
        virtual std::string toString();
    private:
        void appendToLastElement(std::vector<Value*> &sexp, std::string word);
        void appendToLastElement(std::vector<Value*> &sexp, Value* word);
};

#endif
