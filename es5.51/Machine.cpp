#include <iostream>
#include "machine.h"
#include "instruction.h"
#include "initialize_stack.h"
using namespace std;

Machine::Machine()
{
    this->pc = 0;
    this->flag = new Register();
    this->stack = new Stack();
    this->the_instruction_sequence = std::vector<Instruction*>({});
    this->operations = std::map<Symbol,Operation*>();
    this->operations.insert(std::make_pair(
        Symbol("initialize-stack"),
        new InitializeStack()
    ));
}

