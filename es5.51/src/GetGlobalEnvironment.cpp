#include "get_global_environment.h"
#include "symbol.h"
#include "environment.h"
#include <iostream>
using namespace std;

GetGlobalEnvironment::GetGlobalEnvironment()
{
    this->global_environment = new Environment();
}

Value* GetGlobalEnvironment::execute(std::vector<Value*> elements)
{
    return this->global_environment;
}

std::string GetGlobalEnvironment::toString()
{
    return std::string("Operation-GetGlobalEnvironment");
}

