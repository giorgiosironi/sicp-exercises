#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "src/data_structures.h"
#include "src/is.h"

#include "src/instruction.h"
#include "src/machine.h"

// operations
#include "src/operation.h"
#include "src/get_global_environment.h"
#include "src/is_self_evaluating.h"
#include "src/is_variable.h"
#include "src/lookup_variable_value.h"
#include "src/set_variable_value.h"
#include "src/define_variable.h"
#include "src/is_tagged_list.h"
#include "src/text_of_quotation.h"
#include "src/cons_method_operation.h"
#include "src/is_not_equal_to.h"
#include "src/make_procedure.h"
#include "src/is_last_exp.h"
#include "src/is_instance_of.h"
#include "src/constant.h"
#include "src/is_last_operand.h"
#include "src/adjoin_arg.h"
#include "src/apply_primitive_procedure.h"
#include "src/extend_environment.h"
#include "src/definition_variable.h"
#include "src/definition_value.h"
#include "src/announce_output.h"
#include "src/initialize_stack.h"
#include "src/user_print.h"

// primitive procedures
#include "src/primitive_plus.h"
#include "src/primitive_minus.h"
#include "src/primitive_equal.h"
#include "src/primitive_times.h"
#include "src/primitive_list.h"

// proper 5.52 components
#include "src/compile.h"
#include "src/input.h"


Value* build_list(std::vector<Value*> elements) {
    Value *head = NIL;
    for (int i = elements.size() - 1; i >= 0; i--) {
        head = new Cons(elements.at(i), head);
    }
    return head;
}

std::map<Symbol,Operation*> machine_operations(Environment* global_environment)
{
    auto operations = std::map<Symbol,Operation*>();
    operations.insert(std::make_pair(
        Symbol("get-global-environment"),
        new GetGlobalEnvironment(global_environment)
    ));
    operations.insert(std::make_pair(
        Symbol("is-self-evaluating"),
        new IsSelfEvaluating()
    ));
    operations.insert(std::make_pair(
        Symbol("is-variable"),
        new IsVariable()
    ));
    operations.insert(std::make_pair(
        Symbol("lookup-variable-value"),
        new LookupVariableValue()
    ));
    operations.insert(std::make_pair(
        Symbol("set-variable-value!"),
        new SetVariableValue()
    ));
    operations.insert(std::make_pair(
        Symbol("define-variable!"),
        new DefineVariable()
    ));
    operations.insert(std::make_pair(
        Symbol("is-quoted"),
        new IsTaggedList(new Symbol("quote"))
    ));
    operations.insert(std::make_pair(
        Symbol("text-of-quotation"),
        new TextOfQuotation()
    ));
    operations.insert(std::make_pair(
        Symbol("is-assignment"),
        new IsTaggedList(new Symbol("set!"))
    ));
    operations.insert(std::make_pair(
        Symbol("assignment-variable"),
        ConsMethodOperation::cadr()
    ));
    operations.insert(std::make_pair(
        Symbol("assignment-value"),
        ConsMethodOperation::caddr()
    ));
    operations.insert(std::make_pair(
        Symbol("is-if"),
        new IsTaggedList(new Symbol("if"))
    ));
    operations.insert(std::make_pair(
        Symbol("if-predicate"),
        ConsMethodOperation::cadr()
    ));
    operations.insert(std::make_pair(
        Symbol("is-true"),
        // whatever is not #f is true in an (if ... ... ...)
        new IsNotEqualTo(new Bool(false))
    ));
    operations.insert(std::make_pair(
        Symbol("if-consequent"),
        ConsMethodOperation::caddr()
    ));
    operations.insert(std::make_pair(
        Symbol("if-alternative"),
        ConsMethodOperation::cadddr()
    ));
    operations.insert(std::make_pair(
        Symbol("is-lambda"),
        new IsTaggedList(new Symbol("lambda"))
    ));
    operations.insert(std::make_pair(
        Symbol("lambda-parameters"),
        ConsMethodOperation::cadr()
    ));
    operations.insert(std::make_pair(
        Symbol("lambda-body"),
        ConsMethodOperation::cddr()
    ));
    operations.insert(std::make_pair(
        Symbol("make-procedure"),
        new MakeProcedure()
    ));
    operations.insert(std::make_pair(
        Symbol("is-begin"),
        new IsTaggedList(new Symbol("begin"))
    ));
    operations.insert(std::make_pair(
        Symbol("begin-actions"),
        ConsMethodOperation::cdr()
    ));
    operations.insert(std::make_pair(
        Symbol("is-last-exp"),
        new IsLastExp()
    ));
    operations.insert(std::make_pair(
        Symbol("first-exp"),
        ConsMethodOperation::car()
    ));
    operations.insert(std::make_pair(
        Symbol("rest-exps"),
        ConsMethodOperation::cdr()
    ));
    operations.insert(std::make_pair(
        Symbol("is-application"),
        new IsInstanceOf<Cons>()
    ));
    operations.insert(std::make_pair(
        Symbol("operands"),
        ConsMethodOperation::cdr()
    ));
    operations.insert(std::make_pair(
        Symbol("operator"),
        ConsMethodOperation::car()
    ));
    operations.insert(std::make_pair(
        Symbol("empty-arglist"),
        new Constant(NIL)
    ));
    operations.insert(std::make_pair(
        Symbol("is-no-operands"),
        new IsInstanceOf<Nil>()
    ));
    operations.insert(std::make_pair(
        Symbol("first-operand"),
        ConsMethodOperation::car()
    ));
    operations.insert(std::make_pair(
        Symbol("rest-operands"),
        ConsMethodOperation::cdr()
    ));
    operations.insert(std::make_pair(
        Symbol("is-last-operand"),
        new IsLastOperand()
    ));
    operations.insert(std::make_pair(
        Symbol("adjoin-arg"),
        new AdjoinArg()
    ));
    operations.insert(std::make_pair(
        Symbol("is-primitive-procedure"),
        new IsTaggedList(new Symbol("primitive"))
    ));
    operations.insert(std::make_pair(
        Symbol("apply-primitive-procedure"),
        new ApplyPrimitiveProcedure()
    ));
    operations.insert(std::make_pair(
        Symbol("is-compound-procedure"),
        new IsTaggedList(new Symbol("procedure"))
    ));
    operations.insert(std::make_pair(
        Symbol("procedure-parameters"),
        ConsMethodOperation::cadr()
    ));
    operations.insert(std::make_pair(
        Symbol("procedure-environment"),
        ConsMethodOperation::cadddr()
    ));
    operations.insert(std::make_pair(
        Symbol("extend-environment"),
        new ExtendEnvironment()
    ));
    operations.insert(std::make_pair(
        Symbol("procedure-body"),
        ConsMethodOperation::caddr()
    ));
    operations.insert(std::make_pair(
        Symbol("is-definition"),
        new IsTaggedList(new Symbol("define"))
    ));
    operations.insert(std::make_pair(
        Symbol("definition-variable"),
        new DefinitionVariable()
    ));
    operations.insert(std::make_pair(
        Symbol("definition-value"),
        new DefinitionValue()
    ));
    operations.insert(std::make_pair(
        Symbol("announce-output"),
        new AnnounceOutput()
    ));
    operations.insert(std::make_pair(
        Symbol("user-print"),
        new UserPrint()
    ));
    return operations;
}

Environment* add_primitive_procedures(Environment* initial_environment)
{
    return initial_environment->extend(new Frame(
        { 
            new Symbol("+"),
            new Symbol("-"),
            new Symbol("="),
            new Symbol("*"),
            new Symbol("list"),
        },
        {
            Cons::from_vector({ new Symbol("primitive"), new PrimitivePlus() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveMinus() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveEqual() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveTimes() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveList() }),
        }
    ));
}

/**
 * Inline here make_machine, the Facade
 */
Machine* compile_and_go(Value* input)
{
    Machine* mymachine = new Machine();
    mymachine->allocate_register("exp");
    mymachine->allocate_register("env");
    mymachine->allocate_register("val");
    mymachine->allocate_register("proc");
    mymachine->allocate_register("argl");
    mymachine->allocate_register("continue");
    mymachine->allocate_register("unev");
    Environment* global_environment = add_primitive_procedures(new Environment());
    mymachine->install_operations(machine_operations(global_environment));
    mymachine->install_instruction_sequence(
        mymachine->assemble(
            compile(input, new Symbol("val"))->statements()
        )
    );
    return mymachine;
}



int main() {
    Machine* machine = compile_and_go(input());
    try {
        machine->start();
    } catch (char const* e) {
        cerr << e << endl;
        if (std::string(e) == "CTRL+D pressed") {
            return 0;
        }
        return 2;
    }
    return 0;
}
