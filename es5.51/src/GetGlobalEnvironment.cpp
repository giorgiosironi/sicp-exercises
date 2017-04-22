#include "get_global_environment.h"
#include "symbol.h"
#include "environment.h"
#include <iostream>
using namespace std;

GetGlobalEnvironment::GetGlobalEnvironment(Environment* environment)
{
    this->global_environment = environment;
}

Value* GetGlobalEnvironment::execute(std::vector<Value*> elements)
{
    return this->global_environment;
}

std::string GetGlobalEnvironment::to_string()
{
    return std::string("Operation-GetGlobalEnvironment");
}

