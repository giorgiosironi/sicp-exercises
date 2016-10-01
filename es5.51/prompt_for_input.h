#ifndef PROMPT_FOR_INPUT_H
#define PROMPT_FOR_INPUT_H
#include <string>
#include <vector>
#include "value.h"
#include "operation.h"
#include <iostream>

class PromptForInput: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

#endif
