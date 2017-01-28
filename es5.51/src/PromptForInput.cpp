#include "prompt_for_input.h"
#include "symbol.h"
#include <iostream>
using namespace std;

Value* PromptForInput::execute(std::vector<Value*> elements)
{
    for (std::vector<Value*>::iterator it = elements.begin() ; it != elements.end(); ++it) {
        cout << (*it)->toString();
    }
    cout << endl;
    cout << ">>> ";
    cout << endl;
    
    return new Symbol("ok");
}

std::string PromptForInput::toString()
{
    return std::string("Operation-PromptForInput");
}

