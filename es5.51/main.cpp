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
#include "src/is_self_evaluating.h"
#include "src/is_variable.h"
#include "src/lookup_variable_value.h"
#include "src/set_variable_value.h"
#include "src/is_tagged_list.h"
#include "src/text_of_quotation.h"
#include "src/cons_method_operation.h"
#include "src/announce_output.h"
#include "src/initialize_stack.h"
#include "src/user_print.h"


Value* build_list(std::vector<Value*> elements) {
    Value *head = NIL;
    for (int i = elements.size() - 1; i >= 0; i--) {
        head = new Cons(elements.at(i), head);
    }
    return head;
}

Value* explicit_control_evaluator()
{
    return build_list({
        //start-of-machine
        new Symbol("start-of-machine"),
        //read-eval-print-loop
        new Symbol("read-eval-print-loop"),
        //(perform (op initialize-stack))
        build_list({
            new Symbol("perform"),
            build_list({
                new Symbol("op"),
                new Symbol("initialize-stack"),
            })
        }),
        //(perform (op prompt-for-input) (const ";;; EC-Eval input:"))
        build_list({
            new Symbol("perform"),
            build_list({
                new Symbol("op"),
                new Symbol("prompt-for-input"),
            }),
            build_list({
                new Symbol("const"),
                new String(";;; EC-Eval input:")
            })
        }),
        //(assign exp (op read))
        build_list({
            new Symbol("assign"),
            new Symbol("exp"),
            build_list({
                new Symbol("op"),
                new Symbol("read"),
            })
        }),
        //(assign env (op get-global-environment))
        build_list({
            new Symbol("assign"),
            new Symbol("env"),
            build_list({
                new Symbol("op"),
                new Symbol("get-global-environment")
            })
        }),
        //(assign continue (label print-result))
        build_list({
            new Symbol("assign"),
            new Symbol("continue"),
            build_list({
                new Symbol("label"),
                new Symbol("print-result")
            })
        }),
        //(goto (label eval-dispatch))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("eval-dispatch")
            })
        }),
        //; eval starts with a case analysis on the type of the expression
        //eval-dispatch
        new Symbol("eval-dispatch"),
        //(test (op self-evaluating?) (reg exp))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-self-evaluating")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            }),
        }),
        //(branch (label ev-self-eval))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-self-eval")
            }),
        }),
        //(test (op variable?) (reg exp))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-variable")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            }),
        }),
        //(branch (label ev-variable))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-variable")
            }),
        }),
        //(test (op quoted?) (reg exp))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-quoted")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            }),
        }),
        //(branch (label ev-quoted))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-quoted")
            }),
        }),
        //(test (op assignment?) (reg exp))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-assignment")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            }),
        }),
        //(branch (label ev-assignment))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-assignment")
            }),
        }),
        //(test (op definition?) (reg exp))
        //(branch (label ev-definition))
        //(test (op if?) (reg exp))
        //(branch (label ev-if))
        //(test (op lambda?) (reg exp))
        //(branch (label ev-lambda))
        //(test (op begin?) (reg exp))
        //(branch (label ev-begin))
        //; label to target for patching in derived expressions
        //extensions
        //(test (op application?) (reg exp))
        //(branch (label ev-application))
        //(goto (label unknown-expression-type))
        //; evaluating simple expressions
        //ev-self-eval
        new Symbol("ev-self-eval"),
        //(assign val (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("val"),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(goto (reg continue))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("reg"),
                new Symbol("continue")
            })
        }),
        //ev-variable
        new Symbol("ev-variable"),
        //(assign val (op lookup-variable-value) (reg exp) (reg env))
        build_list({
            new Symbol("assign"),
            new Symbol("val"),
            build_list({
                new Symbol("op"),
                new Symbol("lookup-variable-value")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("env")
            })
        }),
        //(goto (reg continue))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("reg"),
                new Symbol("continue")
            })
        }),
        //ev-quoted
        new Symbol("ev-quoted"),
        //(assign val (op text-of-quotation) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("val"),
            build_list({
                new Symbol("op"),
                new Symbol("text-of-quotation")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(goto (reg continue))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("reg"),
                new Symbol("continue")
            })
        }),
        //ev-lambda
        //(assign unev (op lambda-parameters) (reg exp))
        //(assign exp (op lambda-body) (reg exp))
        //(assign val (op make-procedure) (reg unev) (reg exp) (reg env))
        //(goto (reg continue))
        //; evaluating procedure applications
        //;; evaluating operator
        //ev-application
        //(save continue)
        //(save env)
        //(assign unev (op operands) (reg exp))
        //(save unev)
        //(assign exp (op operator) (reg exp))
        //(assign continue (label ev-appl-did-operator))
        //(goto (label eval-dispatch))
        //;; evaluating operands
        //ev-appl-did-operator
        //(restore unev) ; the operands
        //(restore env)
        //(assign argl (op empty-arglist))
        //(assign proc (reg val)) ; the operator
        //(test (op no-operands?) (reg unev))
        //(branch (label apply-dispatch))
        //(save proc)
        //; cycle of the argument-evaluation loop
        //ev-appl-operand-loop
        //(save argl)
        //(assign exp (op first-operand) (reg unev))
        //(test (op last-operand?) (reg unev))
        //(branch (label ev-appl-last-arg))
        //(save env)
        //(save unev)
        //(assign continue (label ev-appl-accumulate-arg))
        //(goto (label eval-dispatch))
        //; when an operand has been evaluated, we put in in argl
        //; and continue to evaluate the others from unev
        //ev-appl-accumulate-arg
        //(restore unev)
        //(restore env)
        //(restore argl)
        //(assign argl (op adjoin-arg) (reg val) (reg argl))
        //(assign unev (op rest-operands) (reg unev))
        //(goto (label ev-appl-operand-loop))
        //; the last argument evaluation is different:
        //; we need to dispatch on proc
        //ev-appl-last-arg
        //(assign continue (label ev-appl-accum-last-arg))
        //(goto (label eval-dispatch))
        //ev-appl-accum-last-arg
        //(restore argl)
        //(assign argl (op adjoin-arg) (reg val) (reg argl))
        //(restore proc)
        //(goto (label apply-dispatch))
        //; apply procedure of the metacircular evaluator:
        //; choose between primitive or user-defined procedure
        //apply-dispatch
        //(test (op primitive-procedure?) (reg proc))
        //(branch (label primitive-apply))
        //(test (op compound-procedure?) (reg proc))
        //(branch (label compound-apply))
        //(goto (label unknown-procedure-type))
        //; let's apply a primitive operator such as +
        //primitive-apply
        //(assign val (op apply-primitive-procedure) (reg proc) (reg argl))
        //(restore continue)
        //(goto (reg continue))
        //; let's apply a compound procedure like a user-defined one
        //compound-apply
        //(assign unev (op procedure-parameters) (reg proc))
        //(assign env (op procedure-environment) (reg proc))
        //(assign env (op extend-environment) (reg unev) (reg argl) (reg env))
        //(assign unev (op procedure-body) (reg proc))
        //(goto (label ev-sequence))
        //; evaluates a sequence of expressions
        //ev-begin
        //(assign unev (op begin-actions) (reg exp)) ; list of unevaluated expressions
        //(save continue)
        //(goto (label ev-sequence))
        //;; let's go evaluate each element of the sequence
        //ev-sequence
        //(assign exp (op first-exp) (reg unev))
        //(test (op last-exp?) (reg unev))
        //(branch (label ev-sequence-last-exp))
        //(save unev)
        //(save env)
        //(assign continue (label ev-sequence-continue))
        //(goto (label eval-dispatch))
        //;; we return after having evaluated the element
        //;; there is no return value
        //ev-sequence-continue
        //(restore env)
        //(restore unev)
        //(assign unev (op rest-exps) (reg unev))
        //(goto (label ev-sequence))
        //;; the last element of the sequence is handled differently
        //;; basically it substitutes the previous expression without
        //;; saving values on the stack: it's tail-recursive
        //ev-sequence-last-exp
        //(restore continue)
        //(goto (label eval-dispatch))
        //; evaluating conditionals
        //ev-if
        //(save exp) ; save expression for later
        //(save env)
        //(save continue)
        //(assign continue (label ev-if-decide))
        //(assign exp (op if-predicate) (reg exp))
        //(goto (label eval-dispatch)) ; evaluate the predicate
        //ev-if-decide
        //(restore continue)
        //(restore env)
        //(restore exp)
        //(test (op true?) (reg val))
        //(branch (label ev-if-consequent))
        //ev-if-alternative ; else
        //(assign exp (op if-alternative) (reg exp))
        //(goto (label eval-dispatch))
        //ev-if-consequent ; then
        //(assign exp (op if-consequent) (reg exp))
        //(goto (label eval-dispatch))
        //ev-assignment
        new Symbol("ev-assignment"),
        //(assign unev (op assignment-variable) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("unev"),
            build_list({
                new Symbol("op"),
                new Symbol("assignment-variable")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(save unev) ; save variable for later
        build_list({
            new Symbol("save"),
            new Symbol("unev"),
        }),
        //(assign exp (op assignment-value) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("exp"),
            build_list({
                new Symbol("op"),
                new Symbol("assignment-value")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(save env)
        build_list({
            new Symbol("save"),
            new Symbol("env"),
        }),
        //(save continue)
        build_list({
            new Symbol("save"),
            new Symbol("continue"),
        }),
        //(assign continue (label ev-assignment-1))
        build_list({
            new Symbol("assign"),
            new Symbol("continue"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-assignment-1"),
            }),
        }),
        //(goto (label eval-dispatch)) ; evaluate the assignment value
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("eval-dispatch"),
            }),
        }),
        //ev-assignment-1
        new Symbol("ev-assignment-1"),
        //(restore continue)
        build_list({
            new Symbol("restore"),
            new Symbol("continue"),
        }),
        //(restore env)
        build_list({
            new Symbol("restore"),
            new Symbol("env"),
        }),
        //(restore unev)
        build_list({
            new Symbol("restore"),
            new Symbol("unev"),
        }),
        //(perform (op set-variable-value!) (reg unev) (reg val) (reg env))
        build_list({
            new Symbol("perform"),
            build_list({
                new Symbol("op"),
                new Symbol("set-variable-value!"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("unev"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("val"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("env"),
            }),
        }),
        //(assign val (const ok))
        build_list({
            new Symbol("assign"),
            new Symbol("val"),
            build_list({
                new Symbol("const"),
                new Symbol("ok"),
            }),
        }),
        //(goto (reg continue))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("reg"),
                new Symbol("continue")
            })
        }),
        //; definitions are very similarly put into the current environment
        //ev-definition
        //(assign unev (op definition-variable) (reg exp))
        //(save unev) ; save variable for later
        //(assign exp (op definition-value) (reg exp))
        //(save env)
        //(save continue)
        //(assign continue (label ev-definition-1))
        //(goto (label eval-dispatch)) ; evaluate the definition value
        //ev-definition-1
        //(restore continue)
        //(restore env)
        //(restore unev)
        //(perform (op define-variable!) (reg unev) (reg val) (reg env))
        //(assign val (const ok))
        //(goto (reg continue))
        //print-result
        new Symbol("print-result"),
        //(perform (op announce-output) (const ";;; EC-Eval value:"))
        build_list({
            new Symbol("perform"),
            build_list({
                new Symbol("op"),
                new Symbol("announce-output"),
            }),
            build_list({
                new Symbol("const"),
                new String(";;; EC-Eval value:"),
            })
        }),
        //(perform (op user-print) (reg val))
        build_list({
            new Symbol("perform"),
            build_list({
                new Symbol("op"),
                new Symbol("user-print"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("val"),
            })
        }),
        //(goto (label read-eval-print-loop))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("read-eval-print-loop"),
            }),
        }),
        //unknown-expression-type
        //(assign val (const unknown-expression-type-error))
        //(goto (label signal-error))
        //unknown-procedure-type
        //(restore continue) ; clean up stack (from apply-dispatch)
        //(assign val (const unknown-procedure-type-error))
        //(goto (label signal-error))
        //signal-error
        //(perform (op user-print) (reg val))
        //(goto (label read-eval-print-loop))
        //end-of-machine
    });
}

/**
 * Try to define Operation : Value
 * http://stackoverflow.com/questions/20835534/function-pointer-without-arguments-types
 * that stores a pointer to a function that takes any parameters and then
 * returns a *Value
 * Should have a method apply(std::vector<Value*>)
 * and when we implement apply we can pass the arguments in
 * It should probably have a case on the number of arguments (from 0 to 3-4)
 * so that it can then cast the general pointer to the correct one and call
 * it.
 * This should become a map from String representing the name to the Operation then.
 */
std::map<Symbol,Operation*> machine_operations()
{
    auto operations = std::map<Symbol,Operation*>();
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
        Symbol("announce-output"),
        new AnnounceOutput()
    ));
    operations.insert(std::make_pair(
        Symbol("user-print"),
        new UserPrint()
    ));
    return operations;
}

/**
 * Inline here make_machine, the Facade
 */
Machine* eceval()
{
    Machine* eceval = new Machine();
    eceval->allocate_register("exp");
    eceval->allocate_register("env");
    eceval->allocate_register("val");
    eceval->allocate_register("proc");
    eceval->allocate_register("argl");
    eceval->allocate_register("continue");
    eceval->allocate_register("unev");
    eceval->install_operations(machine_operations());
    eceval->install_instruction_sequence(eceval->assemble(explicit_control_evaluator()));
    return eceval;
}



int main() {
    /*
    Cons* cell = new Cons(new Integer(42), new Integer(43));
    Value* i = cell->car();
    cout << i->toString() << endl;
    cout << cell->toString() << endl;
    cout << NIL->toString() << endl;
    cout << is_pair(NIL) << endl;
    cout << is_pair(cell) << endl;
    cout << is_eq(cell, cell) << endl;
    cout << is_eq(cell, NIL) << endl;
    Value* s = new Symbol("tag");
    cout << s->toString() << endl;
    Cons* taggedList = new Cons(new Symbol("integer"), new Integer(42));
    cout << is_tagged_list(taggedList, new Symbol("integer")) << endl;
    std::vector<Value*> elements = {new Integer(1), new Integer(2), new Integer(3)};
    Value* threeElementList = build_list({new Integer(1), new Integer(2), new Integer(3)});
    cout << threeElementList->toString() << endl;
    */
    Machine* machine = eceval();
    machine->start();
    return 0;
}
