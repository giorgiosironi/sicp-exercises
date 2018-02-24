#ifndef PROMPT_FOR_INPUT_H
#define PROMPT_FOR_INPUT_H
#include <string>
#include <vector>
#include "value.h"
#include "operation.h"

class PromptForInput: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
