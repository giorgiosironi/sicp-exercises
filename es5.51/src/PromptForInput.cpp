#include "prompt_for_input.h"
#include "symbol.h"
#include <iostream>
using namespace std;

Value* PromptForInput::execute(std::vector<Value*> elements)
{
    for (std::vector<Value*>::iterator it = elements.begin() ; it != elements.end(); ++it) {
        cout << (*it)->to_string();
    }
    cout << endl;
    cout << ">>> ";
    
    return new Symbol("ok");
}

std::string PromptForInput::to_string()
{
    return std::string("Operation-PromptForInput");
}

