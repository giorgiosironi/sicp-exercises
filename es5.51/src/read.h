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
        virtual std::string to_string();
    private:
        void append_to_last_element(std::vector<Value*> &sexp, std::string word);
        void append_to_last_element(std::vector<Value*> &sexp, Value* word);
};

#endif
