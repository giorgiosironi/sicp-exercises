#include <stdexcept>
#include <algorithm>
#include "compile.h"
#include "cons.h"
#include "is.h"
#include "symbol.h"
#include "conversion.h"
#include "make_label.h"

// temporary
#include "nil.h"

MakeLabel make_label;

InstructionSequence* compile(Value* exp, Symbol* target, Linkage* linkage)
{
    if (is_self_evaluating(exp)) {
        return compile_self_evaluating(exp, target, linkage);
    }
    if (is_variable(exp)) {
        return compile_variable(exp, target, linkage);
    }
    if (is_quoted(exp)) {
        return compile_quoted(exp, target, linkage);
    }
    if (is_definition(exp)) {
        return compile_definition(exp, target, linkage);
    }
    if (is_application(exp)) {
        return compile_application(exp, target, linkage);
    }
    throw std::runtime_error("Cannot compile expression: " + exp->to_string());
}

bool is_self_evaluating(Value* exp)
{
    return is_number(exp) || is_string(exp);
}

InstructionSequence* compile_self_evaluating(Value* exp, Symbol* target, Linkage* linkage)
{
    return new InstructionSequence(
        vector<Symbol*>(),
        vector<Symbol*>({ target }),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("assign"),
                target,
                Cons::from_vector({
                    new Symbol("const"),
                    exp
                })
            })
        })
    );
}

bool is_variable(Value* exp)
{
    if (Symbol *symbol = dynamic_cast<Symbol *>(exp)) {
        return true;
    }
    return false;
}

InstructionSequence* compile_variable(Value* exp, Symbol* target, Linkage* linkage)
{
    return new InstructionSequence(
        vector<Symbol*>({ new Symbol("env") }),
        vector<Symbol*>({ target }),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("assign"),
                target,
                Cons::from_vector({
                    new Symbol("op"),
                    new Symbol("lookup-variable-value"),
                }),
                Cons::from_vector({
                    new Symbol("const"),
                    exp
                }),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("env"),
                })
            })
        })
    );
}

bool is_quoted(Value *exp) {
    return is_tagged_list(exp, new Symbol("quote"));
}

InstructionSequence* compile_quoted(Value* exp, Symbol* target, Linkage* linkage)
{
    return new InstructionSequence(
        vector<Symbol*>({ }),
        vector<Symbol*>({ target }),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("assign"),
                target,
                Cons::from_vector({
                    new Symbol("const"),
                    convert_to<Cons>(exp)->cadr()
                }),
            })
        })
    );
}

bool is_definition(Value *exp) {
    return is_tagged_list(exp, new Symbol("define"));
}

InstructionSequence* compile_definition(Value* exp, Symbol* target, Linkage* linkage)
{
    // TODO: only implements variables, not functions
    Value* definition_variable = convert_to<Cons>(exp)->cadr();
    Value* definition_value = convert_to<Cons>(exp)->caddr();
    InstructionSequence* value_code = compile(definition_value, new Symbol("val"), new LinkageNext());

    InstructionSequence* intermediate = new InstructionSequence(
        vector<Symbol*>({ new Symbol("env"), new Symbol("val") }),
        vector<Symbol*>({ target }),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("perform"),
                Cons::from_vector({
                    new Symbol("op"),
                    new Symbol("define-variable!"),
                }),
                Cons::from_vector({
                    new Symbol("const"),
                    definition_variable,
                }),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("val"),
                }),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("env"),
                }),
            }),
            Cons::from_vector({
                new Symbol("assign"),
                target,
                Cons::from_vector({
                    new Symbol("const"),
                    new Symbol("ok"),
                }),
            }),
        })
    );

    // TODO: (end-with-linkage linkage
    //                  (preserving '(env)
    //                              get-value-code
    //                              intermediate
    return value_code->preserving(
        { new Symbol("env") },
        intermediate
    );
}

bool is_application(Value *exp) {
    return is_pair(exp);
}

InstructionSequence* compile_application(Value* exp, Symbol* target, Linkage* linkage)
{
    List* application = convert_to<List>(exp);
    Value* operator_ = application->car();
    InstructionSequence* procedureCode = compile(operator_, new Symbol("proc"), new LinkageNext());
    vector<Value*> operands = convert_to<List>(application->cdr())->to_vector();
    vector<InstructionSequence*> operandCodes = vector<InstructionSequence*>();
    for (vector<Value*>::iterator it = operands.begin(); it != operands.end(); ++it) {
        operandCodes.push_back(compile(*it, new Symbol("val"), new LinkageNext()));
    }
    //(let ((proc-code (compile (operator exp) 'proc 'next))
    //      (operand-codes
    //        (map (lambda (operand)
    //               (compile operand 'val 'next))
    //             (operands exp))))
    //  (preserving '(env continue)
    //              proc-code
    //              (preserving '(proc continue)
    //                          (construct-arglist operand-codes)
    //                          (compile-procedure-call target linkage)))))
    return procedureCode;
}

// building the argument list from last to first, with cons
InstructionSequence* construct_arg_list(vector<InstructionSequence*> operandCodes)
{
    std::reverse(operandCodes.begin(), operandCodes.end());
    if (operandCodes.size() == 0) {
        return new InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>({ new Symbol("argl") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("argl"),
                    Cons::from_vector({
                        new Symbol("const"),
                        NIL
                    })
                })
            })
        );
    }
    InstructionSequence* code_to_get_last_arg = operandCodes.at(0)->append(
        new InstructionSequence(
            vector<Symbol*>({ new Symbol("val") }),
            vector<Symbol*>({ new Symbol("argl") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("argl"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("list"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    }),
                })
            })
        )
    );
    if (operandCodes.size() == 1) {
        return code_to_get_last_arg;
    } else {
        vector<InstructionSequence*>::const_iterator first = operandCodes.begin() + 1;
        vector<InstructionSequence*>::const_iterator last = operandCodes.end();
        vector<InstructionSequence*> rest(first, last);
        return code_to_get_last_arg->preserving(
            vector<Symbol*>({ new Symbol("env") }),
            code_to_get_rest_args(rest)
        );
    }
}

// building all the arguments different from the last
InstructionSequence* code_to_get_rest_args(vector<InstructionSequence*> operandCodes)
{
    InstructionSequence* codeForNextArg = operandCodes.at(0)->preserving(
        vector<Symbol*>({ new Symbol("argl") }),
        new InstructionSequence(
            vector<Symbol*>({ new Symbol("val"), new Symbol("argl") }),
            vector<Symbol*>({ new Symbol("argl") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("argl"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("cons"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("argl"),
                    }),
                })
            })
        )
    );
    if (operandCodes.size() == 1) {
        return codeForNextArg;
    } else {
        vector<InstructionSequence*>::const_iterator first = operandCodes.begin() + 1;
        vector<InstructionSequence*>::const_iterator last = operandCodes.end();
        vector<InstructionSequence*> rest(first, last);
        return codeForNextArg->preserving(
            vector<Symbol*>({ new Symbol("env") }),
            code_to_get_rest_args(rest)
        );
    }
}

//; compiling the procedure call, either to a primitive or compiled procedure
//; the primitive branch is directly specified here
//(define (compile-procedure-call target linkage)
//  (let ((primitive-branch (make-label 'primitive-branch))
//        (compiled-branch (make-label 'compiled-branch))
//        (after-call (make-label 'after-call)))
//    (let ((compiled-linkage
//            (if (eq? linkage 'next) after-call linkage)))
//      (append-instruction-sequences
//        (make-instruction-sequence '(proc) '()`((test (op primitive-procedure?) (reg proc))
//                                                (branch (label ,primitive-branch))))
//        ; parallel becaue they won't be executed sequentially
//        (parallel-instruction-sequences
//          (append-instruction-sequences
//            compiled-branch
//            (compile-proc-appl target compiled-linkage))
//          (append-instruction-sequences
//            primitive-branch
//            (end-with-linkage linkage
//                              (make-instruction-sequence '(proc argl)
//                                                         (list target)
//                                                         `((assign ,target
//                                                                   (op apply-primitive-procedure)
//                                                                   (reg proc)
//                                                                   (reg argl)))))))
//        after-call))))
