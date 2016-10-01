#include "prompt_for_input.h"
#include "symbol.h"
#include <iostream>
using namespace std;

Value* PromptForInput::execute(std::vector<Value*> elements)
{
    cout << ">>> ";
    return new Symbol("ok");
}

std::string PromptForInput::toString()
{
    return std::string("Operation-PromptForInput");
}

