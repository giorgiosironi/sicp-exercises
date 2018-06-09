#include "list_operation.h"
#include "cons.h"
using namespace std;

Value* ListOperation::execute(std::vector<Value*> elements)
{
    return Cons::from_vector(elements);
}

std::string ListOperation::to_string() const
{
    return std::string("Operation-List");
}

