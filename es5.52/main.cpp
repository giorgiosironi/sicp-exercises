#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "src/data_structures.h"
#include "src/is.h"
#include "src/conversion.h"

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
#include "src/is_equal_to.h"
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
#include "src/list_operation.h"
#include "src/cons_operation.h"
#include "src/make_compiled_procedure.h"

// primitive procedures
#include "src/primitive_plus.h"
#include "src/primitive_minus.h"
#include "src/primitive_equal.h"
#include "src/primitive_times.h"
#include "src/primitive_division.h"
#include "src/primitive_less_than.h"
#include "src/primitive_greater_than.h"
#include "src/primitive_is_null.h"
#include "src/primitive_cons.h"
#include "src/primitive_car.h"
#include "src/primitive_cdr.h"
#include "src/primitive_list.h"
#include "src/primitive_display.h"
#include "src/primitive_apply_in_underlying_scheme.h"

// proper 5.52 components
#include "src/compile.h"
#include "src/input.h"
#include "src/input_end_exception.h"


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
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-definition"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp"),
            }),
        }),
        //(branch (label ev-definition))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-definition"),
            }),
        }),
        //(test (op if?) (reg exp))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-if")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            }),
        }),
        //(branch (label ev-if))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-if")
            }),
        }),
        //(test (op lambda?) (reg exp))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-lambda")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            }),
        }),
        //(branch (label ev-lambda))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-lambda")
            })
        }),
        //(test (op begin?) (reg exp))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-begin")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            }),
        }),
        //(branch (label ev-begin))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-begin")
            })
        }),
        //; label to target for patching in derived expressions
        //extensions
        new Symbol("extensions"),
        //(test (op application?) (reg exp))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-application")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(branch (label ev-application))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-application")
            })
        }),
        //(goto (label unknown-expression-type))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("unknown-expression-type")
            })
        }),
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
        new Symbol("ev-lambda"),
        //(assign unev (op lambda-parameters) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("unev"),
            build_list({
                new Symbol("op"),
                new Symbol("lambda-parameters")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(assign exp (op lambda-body) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("exp"),
            build_list({
                new Symbol("op"),
                new Symbol("lambda-body")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(assign val (op make-procedure) (reg unev) (reg exp) (reg env))
        build_list({
            new Symbol("assign"),
            new Symbol("val"),
            build_list({
                new Symbol("op"),
                new Symbol("make-procedure")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("unev")
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
        //; evaluating procedure applications
        //;; evaluating operator
        //ev-application
        new Symbol("ev-application"),
        //(save continue)
        build_list({
            new Symbol("save"),
            new Symbol("continue")
        }),
        //(save env)
        build_list({
            new Symbol("save"),
            new Symbol("env")
        }),
        //(assign unev (op operands) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("unev"),
            build_list({
                new Symbol("op"),
                new Symbol("operands")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(save unev)
        build_list({
            new Symbol("save"),
            new Symbol("unev")
        }),
        //(assign exp (op operator) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("exp"),
            build_list({
                new Symbol("op"),
                new Symbol("operator")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(assign continue (label ev-appl-did-operator))
        build_list({
            new Symbol("assign"),
            new Symbol("continue"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-appl-did-operator")
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
        //;; evaluating operands
        //ev-appl-did-operator
        new Symbol("ev-appl-did-operator"),
        //(restore unev) ; the operands
        build_list({
            new Symbol("restore"),
            new Symbol("unev")
        }),
        //(restore env)
        build_list({
            new Symbol("restore"),
            new Symbol("env")
        }),
        //(assign argl (op empty-arglist))
        build_list({
            new Symbol("assign"),
            new Symbol("argl"),
            build_list({
                new Symbol("op"),
                new Symbol("empty-arglist"),
            }),
        }),
        //(assign proc (reg val)) ; the operator
        build_list({
            new Symbol("assign"),
            new Symbol("proc"),
            build_list({
                new Symbol("reg"),
                new Symbol("val"),
            }),
        }),
        //(test (op no-operands?) (reg unev))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-no-operands"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("unev"),
            }),
        }),
        //(branch (label apply-dispatch))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("apply-dispatch"),
            }),
        }),
        //(save proc)
        build_list({
            new Symbol("save"),
            new Symbol("proc"),
        }),
        //; cycle of the argument-evaluation loop
        //ev-appl-operand-loop
        new Symbol("ev-appl-operand-loop"),
        //(save argl)
        build_list({
            new Symbol("save"),
            new Symbol("argl"),
        }),
        //(assign exp (op first-operand) (reg unev))
        build_list({
            new Symbol("assign"),
            new Symbol("exp"),
            build_list({
                new Symbol("op"),
                new Symbol("first-operand"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("unev"),
            })
        }),
        //(test (op last-operand?) (reg unev))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-last-operand"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("unev"),
            })
        }),
        //(branch (label ev-appl-last-arg))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-appl-last-arg"),
            }),
        }),
        //(save env)
        build_list({
            new Symbol("save"),
            new Symbol("env"),
        }),
        //(save unev)
        build_list({
            new Symbol("save"),
            new Symbol("unev"),
        }),
        //(assign continue (label ev-appl-accumulate-arg))
        build_list({
            new Symbol("assign"),
            new Symbol("continue"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-appl-accumulate-arg"),
            }),
        }),
        //(goto (label eval-dispatch))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("eval-dispatch"),
            }),
        }),
        //; when an operand has been evaluated, we put in in argl
        //; and continue to evaluate the others from unev
        //ev-appl-accumulate-arg
        new Symbol("ev-appl-accumulate-arg"),
        //(restore unev)
        build_list({
            new Symbol("restore"),
            new Symbol("unev"),
        }),
        //(restore env)
        build_list({
            new Symbol("restore"),
            new Symbol("env"),
        }),
        //(restore argl)
        build_list({
            new Symbol("restore"),
            new Symbol("argl"),
        }),
        //(assign argl (op adjoin-arg) (reg val) (reg argl))
        build_list({
            new Symbol("assign"),
            new Symbol("argl"),
            build_list({
                new Symbol("op"),
                new Symbol("adjoin-arg"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("val"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("argl"),
            }),
        }),
        //(assign unev (op rest-operands) (reg unev))
        build_list({
            new Symbol("assign"),
            new Symbol("unev"),
            build_list({
                new Symbol("op"),
                new Symbol("rest-operands"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("unev"),
            }),
        }),
        //(goto (label ev-appl-operand-loop))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-appl-operand-loop"),
            }),
        }),
        //; the last argument evaluation is different:
        //; we need to dispatch on proc
        //ev-appl-last-arg
        new Symbol("ev-appl-last-arg"),
        //(assign continue (label ev-appl-accum-last-arg))
        build_list({
            new Symbol("assign"),
            new Symbol("continue"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-appl-accum-last-arg"),
            }),
        }),
        //(goto (label eval-dispatch))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("eval-dispatch"),
            }),
        }),
        //ev-appl-accum-last-arg
        new Symbol("ev-appl-accum-last-arg"),
        //(restore argl)
        build_list({
            new Symbol("restore"),
            new Symbol("argl"),
        }),
        //(assign argl (op adjoin-arg) (reg val) (reg argl))
        build_list({
            new Symbol("assign"),
            new Symbol("argl"),
            build_list({
                new Symbol("op"),
                new Symbol("adjoin-arg"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("val"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("argl"),
            }),
        }),
        //(restore proc)
        build_list({
            new Symbol("restore"),
            new Symbol("proc"),
        }),
        //(goto (label apply-dispatch))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("apply-dispatch"),
            }),
        }),
        //; apply procedure of the metacircular evaluator:
        //; choose between primitive or user-defined procedure
        //apply-dispatch
        new Symbol("apply-dispatch"),
        //(test (op primitive-procedure?) (reg proc))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-primitive-procedure"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("proc"),
            }),
        }),
        //(branch (label primitive-apply))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("primitive-apply"),
            }),
        }),
        // translate this check and implement the compound-apply branch
        //(test (op compound-procedure?) (reg proc))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-compound-procedure"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("proc"),
            }),
        }),
        //(branch (label compound-apply))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("compound-apply"),
            }),
        }),
        //(goto (label unknown-procedure-type))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("unknown-procedure-type"),
            }),
        }),
        //; let's apply a primitive operator such as +
        //primitive-apply
        new Symbol("primitive-apply"),
        //(assign val (op apply-primitive-procedure) (reg proc) (reg argl))
        build_list({
            new Symbol("assign"),
            new Symbol("val"),
            build_list({
                new Symbol("op"),
                new Symbol("apply-primitive-procedure"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("proc"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("argl"),
            }),
        }),
        //(restore continue)
        build_list({
            new Symbol("restore"),
            new Symbol("continue"),
        }),
        //(goto (reg continue))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("reg"),
                new Symbol("continue"),
            }),
        }),
        //; let's apply a compound procedure like a user-defined one
        //compound-apply
        new Symbol("compound-apply"),
        //(assign unev (op procedure-parameters) (reg proc))
        build_list({
            new Symbol("assign"),
            new Symbol("unev"),
            build_list({
                new Symbol("op"),
                new Symbol("procedure-parameters"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("proc"),
            }),
        }),
        //(assign env (op procedure-environment) (reg proc))
        build_list({
            new Symbol("assign"),
            new Symbol("env"),
            build_list({
                new Symbol("op"),
                new Symbol("procedure-environment"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("proc"),
            }),
        }),
        //(assign env (op extend-environment) (reg unev) (reg argl) (reg env))
        build_list({
            new Symbol("assign"),
            new Symbol("env"),
            build_list({
                new Symbol("op"),
                new Symbol("extend-environment"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("unev"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("argl"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("env"),
            }),
        }),
        //(assign unev (op procedure-body) (reg proc))
        build_list({
            new Symbol("assign"),
            new Symbol("unev"),
            build_list({
                new Symbol("op"),
                new Symbol("procedure-body"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("proc"),
            }),
        }),
        //(goto (label ev-sequence))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-sequence"),
            }),
        }),
        //; evaluates a sequence of expressions
        //ev-begin
        new Symbol("ev-begin"),
        //(assign unev (op begin-actions) (reg exp)) ; list of unevaluated expressions
        build_list({
            new Symbol("assign"),
            new Symbol("unev"),
            build_list({
                new Symbol("op"),
                new Symbol("begin-actions")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(save continue)
        build_list({
            new Symbol("save"),
            new Symbol("continue")
        }),
        //(goto (label ev-sequence))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-sequence")
            })
        }),
        //;; let's go evaluate each element of the sequence
        //ev-sequence
        new Symbol("ev-sequence"),
        //(assign exp (op first-exp) (reg unev))
        build_list({
            new Symbol("assign"),
            new Symbol("exp"),
            build_list({
                new Symbol("op"),
                new Symbol("first-exp")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("unev")
            })
        }),
        //(test (op last-exp?) (reg unev))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-last-exp")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("unev")
            })
        }),
        //(branch (label ev-sequence-last-exp))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-sequence-last-exp")
            })
        }),
        //(save unev)
        build_list({
            new Symbol("save"),
            new Symbol("unev")
        }),
        //(save env)
        build_list({
            new Symbol("save"),
            new Symbol("env")
        }),
        //(assign continue (label ev-sequence-continue))
        build_list({
            new Symbol("assign"),
            new Symbol("continue"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-sequence-continue")
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
        //;; we return after having evaluated the element
        //;; there is no return value
        //ev-sequence-continue
        new Symbol("ev-sequence-continue"),
        //(restore env)
        build_list({
            new Symbol("restore"),
            new Symbol("env")
        }),
        //(restore unev)
        build_list({
            new Symbol("restore"),
            new Symbol("unev")
        }),
        //(assign unev (op rest-exps) (reg unev))
        build_list({
            new Symbol("assign"),
            new Symbol("unev"),
            build_list({
                new Symbol("op"),
                new Symbol("rest-exps"),
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("unev"),
            })
        }),
        //(goto (label ev-sequence))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-sequence"),
            })
        }),
        //;; the last element of the sequence is handled differently
        //;; basically it substitutes the previous expression without
        //;; saving values on the stack: it's tail-recursive
        //ev-sequence-last-exp
        new Symbol("ev-sequence-last-exp"),
        //(restore continue)
        build_list({
            new Symbol("restore"),
            new Symbol("continue")
        }),
        //(goto (label eval-dispatch))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("eval-dispatch")
            })
        }),
        //; evaluating conditionals
        //ev-if
        new Symbol("ev-if"),
        //(save exp) ; save expression for later
        build_list({
            new Symbol("save"),
            new Symbol("exp"),
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
        //(assign continue (label ev-if-decide))
        build_list({
            new Symbol("assign"),
            new Symbol("continue"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-if-decide")
            })
        }),
        //(assign exp (op if-predicate) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("exp"),
            build_list({
                new Symbol("op"),
                new Symbol("if-predicate")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(goto (label eval-dispatch)) ; evaluate the predicate
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("eval-dispatch")
            })
        }),
        //ev-if-decide
        new Symbol("ev-if-decide"),
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
        //(restore exp)
        build_list({
            new Symbol("restore"),
            new Symbol("exp"),
        }),
        //(test (op true?) (reg val))
        build_list({
            new Symbol("test"),
            build_list({
                new Symbol("op"),
                new Symbol("is-true")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("val")
            })
        }),
        //(branch (label ev-if-consequent))
        build_list({
            new Symbol("branch"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-if-consequent")
            })
        }),
        //ev-if-alternative ; else
        new Symbol("ev-if-alternative"),
        //(assign exp (op if-alternative) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("exp"),
            build_list({
                new Symbol("op"),
                new Symbol("if-alternative")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
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
        //ev-if-consequent ; then
        new Symbol("ev-if-consequent"),
        //(assign exp (op if-consequent) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("exp"),
            build_list({
                new Symbol("op"),
                new Symbol("if-consequent")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(goto (label eval-dispatch))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("eval-dispatch")
            }),
        }),
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
        new Symbol("ev-definition"),
        //(assign unev (op definition-variable) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("unev"),
            build_list({
                new Symbol("op"),
                new Symbol("definition-variable")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(save unev) ; save variable for later
        build_list({
            new Symbol("save"),
            new Symbol("unev")
        }),
        //(assign exp (op definition-value) (reg exp))
        build_list({
            new Symbol("assign"),
            new Symbol("exp"),
            build_list({
                new Symbol("op"),
                new Symbol("definition-value")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("exp")
            })
        }),
        //(save env)
        build_list({
            new Symbol("save"),
            new Symbol("env")
        }),
        //(save continue)
        build_list({
            new Symbol("save"),
            new Symbol("continue")
        }),
        //(assign continue (label ev-definition-1))
        build_list({
            new Symbol("assign"),
            new Symbol("continue"),
            build_list({
                new Symbol("label"),
                new Symbol("ev-definition-1")
            }),
        }),
        //(goto (label eval-dispatch)) ; evaluate the definition value
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("eval-dispatch")
            }),
        }),
        //ev-definition-1
        new Symbol("ev-definition-1"),
        //(restore continue)
        build_list({
            new Symbol("restore"),
            new Symbol("continue")
        }),
        //(restore env)
        build_list({
            new Symbol("restore"),
            new Symbol("env")
        }),
        //(restore unev)
        build_list({
            new Symbol("restore"),
            new Symbol("unev")
        }),
        //(perform (op define-variable!) (reg unev) (reg val) (reg env))
        build_list({
            new Symbol("perform"),
            build_list({
                new Symbol("op"),
                new Symbol("define-variable!")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("unev")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("val")
            }),
            build_list({
                new Symbol("reg"),
                new Symbol("env")
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
                new Symbol("continue"),
            }),
        }),
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
        new Symbol("unknown-expression-type"),
        //(assign val (const unknown-expression-type-error))
        build_list({
            new Symbol("assign"),
            new Symbol("val"),
            build_list({
                new Symbol("const"),
                new Symbol("unknown-expression-type-error"),
            }),
        }),
        //(goto (label signal-error))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("signal-error"),
            }),
        }),
        //unknown-procedure-type
        new Symbol("unknown-procedure-type"),
        //(restore continue) ; clean up stack (from apply-dispatch)
        build_list({
            new Symbol("restore"),
            new Symbol("continue"),
        }),
        //(assign val (const unknown-procedure-type-error))
        build_list({
            new Symbol("assign"),
            new Symbol("val"),
            build_list({
                new Symbol("const"),
                new Symbol("unknown-procedure-type-error"),
            }),
        }),
        //(goto (label signal-error))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("signal-error"),
            }),
        }),
        //signal-error
        new Symbol("signal-error"),
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
            }),
        }),
        //(goto (label read-eval-print-loop))
        build_list({
            new Symbol("goto"),
            build_list({
                new Symbol("label"),
                new Symbol("read-eval-print-loop"),
            }),
        }),
        //end-of-machine
        new Symbol("end-of-machine"),
    });
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
        Symbol("is-false"),
        new IsEqualTo(new Bool(false))
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
    operations.insert(std::make_pair(
        Symbol("list"),
        new ListOperation()
    ));
    operations.insert(std::make_pair(
        Symbol("cons"),
        new ConsOperation()
    ));
    operations.insert(std::make_pair(
        Symbol("make-compiled-procedure"),
        new MakeCompiledProcedure()
    ));
    operations.insert(std::make_pair(
        Symbol("compiled-procedure-entry"),
        ConsMethodOperation::cadr()
    ));
    operations.insert(std::make_pair(
        Symbol("compiled-procedure-env"),
        ConsMethodOperation::caddr()
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
            new Symbol("/"),
            new Symbol("<"),
            new Symbol(">"),
            new Symbol("null?"),
            new Symbol("cons"),
            new Symbol("car"),
            new Symbol("cdr"),
            new Symbol("list"),
            new Symbol("display"),
            new Symbol("apply-in-underlying-scheme"),
        },
        {
            Cons::from_vector({ new Symbol("primitive"), new PrimitivePlus() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveMinus() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveEqual() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveTimes() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveDivision() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveLessThan() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveGreaterThan() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveIsNull() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveCons() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveCar() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveCdr() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveList() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveDisplay() }),
            Cons::from_vector({ new Symbol("primitive"), new PrimitiveApplyInUnderlyingScheme() }),
        }
    ));
}

/**
 * Inline here make_machine, the Facade
 * TODO: possibly we should install the instruction sequence along with the eceval machine, to be able to continue executing stuff
 * after we have compiled it.
 * This is a limited version which just executed what has been compiled rather than giving you a prompt
 * see chapter5.5.scm
 * TODO: incomplete
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
    Environment* globalEnvironment = add_primitive_procedures(new Environment());
    mymachine->install_operations(machine_operations(globalEnvironment));
    mymachine->install_instruction_sequence(mymachine->assemble(explicit_control_evaluator()));

    //mymachine->install_instruction_sequence(
    //    mymachine->assemble(
    //        compile(
    //            input,
    //            new Symbol("val"),
    //            new LinkageNext()
    //        )->statements()
    //    )
    //);
    return mymachine;
}

Machine* compile_and_execute(std::vector<Value*> expressions)
{
    std::vector<List*> compiledPrograms;
    for (int i = 0; i < expressions.size(); i++) {
        List* compiledProgram = compile(expressions.at(i), new Symbol("val"), new LinkageNext())->statements();
        compiledPrograms.push_back(compiledProgram);
    }
    List* linkedProgram = Cons::from_vector({
        Cons::from_vector({
            new Symbol("perform"),
            Cons::from_vector({
                new Symbol("op"),
                new Symbol("initialize-stack"),
            }),
        }),
        Cons::from_vector({
            new Symbol("assign"),
            new Symbol("env"),
            Cons::from_vector({
                new Symbol("op"),
                new Symbol("get-global-environment"),
            }),
        }),
    });
    for (int i = 0; i < compiledPrograms.size(); i++) {
        linkedProgram = linkedProgram->append_list(compiledPrograms[i]);
    }

    Machine* mymachine = new Machine();
    mymachine->allocate_register("exp");
    mymachine->allocate_register("env");
    mymachine->allocate_register("val");
    mymachine->allocate_register("proc");
    mymachine->allocate_register("argl");
    mymachine->allocate_register("continue");
    mymachine->allocate_register("unev");
    Environment* globalEnvironment = add_primitive_procedures(new Environment());
    mymachine->install_operations(machine_operations(globalEnvironment));
    //vector<Value*> linkedProgramVector = linkedProgram->to_vector();
    //vector<Instruction*> castedLinkedProgramVector = vector<Instruction*>();
    //for (vector<Value*>::iterator it = linkedProgramVector.begin(); it != linkedProgramVector.end(); ++it) {
    //    castedLinkedProgramVector.push_back(convert_to<Instruction>(*it));
    //}
    mymachine->install_instruction_sequence(mymachine->assemble(linkedProgram));
//    (display "Compiled a ")
//    (display (length compiled-program))
//    (display "-instruction program. Now starting it...")
//    (newline)
    return mymachine;
}


int main() {
    // TODO: we should use compile_and_go() when ready
    try {
        Machine* machine = compile_and_execute(input());
        machine->start();
    } catch (std::runtime_error e) {
        cerr << e.what() << endl;
        return 3;
    } catch (InputEndException e) {
        cerr << "CTRL+D pressed" << endl;
        return 0;
    //} catch (char const* e) {
    //    cerr << e << endl;
    //    return 2;
    }
    return 0;
}
