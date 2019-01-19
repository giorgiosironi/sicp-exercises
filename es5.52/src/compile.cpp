#include <stdexcept>
#include <algorithm>
#include "compile.h"
#include "cons.h"
#include "is.h"
#include "symbol.h"
#include "bool.h"
#include "conversion.h"
#include "make_label.h"

// temporary
#include "nil.h"


InstructionSequence* compile(Value* exp, Symbol* target, Linkage* linkage)
{
    if (is_self_evaluating(exp)) {
        return compile_self_evaluating(exp, target, linkage);
    }
    if (is_variable(exp)) {
        return compile_variable(exp, target, linkage);
    }
    if (is_assignment(exp)) {
        return compile_assignment(exp, target, linkage);
    }
    if (is_quoted(exp)) {
        return compile_quoted(exp, target, linkage);
    }
    if (is_definition(exp)) {
        return compile_definition(exp, target, linkage);
    }
    if (is_if(exp)) {
        return compile_if(exp, target, linkage);
    }
    if (is_lambda(exp)) {
        return compile_lambda(exp, target, linkage);
    }
    if (is_begin(exp)) {
        List* beginActions = convert_to<Cons>(convert_to<Cons>(exp)->cdr());
        return compile_sequence(beginActions, target, linkage);
    }
    if (is_cond(exp)) {
        return compile(cond_to_if(exp), target, linkage);
    }
    if (is_let(exp)) {
        return compile(let_to_combination(exp), target, linkage);
    }
    if (is_application(exp)) {
        return compile_application(exp, target, linkage);
    }
    throw std::runtime_error("Cannot compile expression: " + exp->to_string());
}

bool is_self_evaluating(Value* exp)
{
    return is_number(exp) || is_string(exp) || is_bool(exp);
}

InstructionSequence* compile_self_evaluating(Value* exp, Symbol* target, Linkage* linkage)
{
    return linkage->use_to_end_with(new InstructionSequence(
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
    ));
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
    return linkage->use_to_end_with(new InstructionSequence(
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
    ));
}

bool is_assignment(Value *exp) {
    return is_tagged_list(exp, new Symbol("set!"));
}

InstructionSequence* compile_assignment(Value* exp, Symbol* target, Linkage* linkage)
{
    //(define (assignment-variable exp) (cadr exp))
    //(define (assignment-value exp) (caddr exp))
      //(let ((var (assignment-variable exp))
      //      (get-value-code
      //        (compile (assignment-value exp) 'val 'next)))
    List* assignmentStatement = convert_to<List>(exp);
    Value* var = assignmentStatement->cadr();
    InstructionSequence* getValueCode = compile(assignmentStatement->caddr(), new Symbol("val"), new LinkageNext());

    InstructionSequence* performSequence = new InstructionSequence(
        vector<Symbol*>({ new Symbol("env"), new Symbol("val"), }),
        vector<Symbol*>({ target }),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("perform"),
                Cons::from_vector({
                    new Symbol("op"),
                    new Symbol("set-variable-value!"),
                }),
                Cons::from_vector({
                    new Symbol("const"),
					var,
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
      //  (end-with-linkage linkage
      //                    (preserving '(env)
      //                                get-value-code
      //                                (make-instruction-sequence '(env val) (list target)
      //                                                           `((perform (op set-variable-value!)
      //                                                                      (const ,var)
      //                                                                      (reg val)
      //                                                                      (reg env))
      //                                                             (assign ,target (const ok))))))))
    return linkage->use_to_end_with(
		getValueCode->preserving({ new Symbol("env") }, performSequence)	
    );
}

bool is_quoted(Value *exp) {
    return is_tagged_list(exp, new Symbol("quote"));
}

InstructionSequence* compile_quoted(Value* exp, Symbol* target, Linkage* linkage)
{
    return linkage->use_to_end_with(new InstructionSequence(
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
    ));
}

bool is_definition(Value *exp) {
    return is_tagged_list(exp, new Symbol("define"));
}

InstructionSequence* compile_definition(Value* exp, Symbol* target, Linkage* linkage)
{
    List* definition_list = convert_to<List>(exp);
    Value* definition_variable;
    if (is<Symbol>(definition_list->cadr())) {
        definition_variable = definition_list->cadr();
    } else {
        definition_variable = definition_list->caadr();
    }
    Value* definition_value;
    if (is<Symbol>(definition_list->cadr())) {
        definition_value = convert_to<Cons>(exp)->caddr();
    } else {
        definition_value = new Cons(
            new Symbol("lambda"),
            new Cons(
                definition_list->cdadr(),
                definition_list->cddr()
            )
        );
    }
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

    return linkage->use_to_end_with(value_code->preserving(
        { new Symbol("env") },
        intermediate
    ));
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

    return procedureCode->preserving(
        { new Symbol("env"), new Symbol("continue") },
        construct_arg_list(operandCodes)
            ->preserving(
                { new Symbol("proc"), new Symbol("continue") },
                compile_procedure_call(target, linkage)
            )
    );
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


InstructionSequence* compile_procedure_call(Symbol* target, Linkage* linkage) {
    Symbol* primitive_branch = make_label.next("primitive-branch");
    Symbol* compiled_branch = make_label.next("compiled-branch");
    Symbol* after_call = make_label.next("after-call");

    LinkageJump* compiled_linkage;
    // checking for a LinkageNext class 
    LinkageNext* result = dynamic_cast<LinkageNext*>(linkage);
    if (result != NULL) {
        compiled_linkage = new LinkageLabel(after_call);
    } else {
        compiled_linkage = dynamic_cast<LinkageJump*>(linkage);
        if (compiled_linkage == NULL) {
            throw std::runtime_error("Cannot convert Linkage to LinkageJump");
        }
    }
//      (append-instruction-sequences
    InstructionSequence* primitive_decision = new InstructionSequence(
        vector<Symbol*>({ new Symbol("proc") }),
        vector<Symbol*>(),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("test"),
                Cons::from_vector({
                    new Symbol("op"),
                    new Symbol("is-primitive-procedure"),
                }),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("proc"),
                }),
            }),
            Cons::from_vector({
                new Symbol("branch"),
                Cons::from_vector({
                    new Symbol("label"),
                    primitive_branch
                }),
            }),
        })
    );
    

//        ; parallel because they won't be executed sequentially
//        (parallel-instruction-sequences
    InstructionSequence* compiled_parallel_branch = InstructionSequence::label(compiled_branch)
        ->append(compiled_linkage->compile_proc_appl(target));

    InstructionSequence* primitive_parallel_branch = InstructionSequence::label(primitive_branch)
        ->append(
            linkage->use_to_end_with(new InstructionSequence(
                vector<Symbol*>({ new Symbol("proc"), new Symbol("argl") }),
                vector<Symbol*>({ target }),
                Cons::from_vector({
                    Cons::from_vector({
                        new Symbol("assign"),
                        target,
                        Cons::from_vector({
                            new Symbol("op"),
                            new Symbol("apply-primitive-procedure"),
                        }),
                        Cons::from_vector({
                            new Symbol("reg"),
                            new Symbol("proc"),
                        }),
                        Cons::from_vector({
                            new Symbol("reg"),
                            new Symbol("argl"),
                        }),
                    }),
                })
            ))
        )->append(
            InstructionSequence::label(after_call)
        );

    InstructionSequence* parallel_branches = compiled_parallel_branch->parallel(primitive_parallel_branch);
    return primitive_decision->append(parallel_branches);
}

bool is_if(Value *exp) {
    return is_tagged_list(exp, new Symbol("if"));
}

InstructionSequence* compile_if(Value* exp, Symbol* target, Linkage* linkage)
{
    Symbol* t_branch = make_label.next("true-branch");
    Symbol* f_branch = make_label.next("false-branch");
    Symbol* after_if = make_label.next("after-if");
    Linkage* consequent_linkage;
    // TODO: extract to Linkage.consequent(after_if)
    // and rename consequent to something meaningful
    if (LinkageNext *next = dynamic_cast<LinkageNext *>(linkage)) {
        // we are here
        consequent_linkage = new LinkageLabel(after_if);
    } else {
        consequent_linkage = linkage;
    }
    InstructionSequence* p_code = compile(convert_to<Cons>(exp)->cadr(), new Symbol("val"), new LinkageNext());
    InstructionSequence* c_code = compile(convert_to<Cons>(exp)->caddr(), target, consequent_linkage);
    InstructionSequence* a_code = compile(convert_to<Cons>(exp)->cadddr(), target, linkage);
    InstructionSequence* test = new InstructionSequence(
        vector<Symbol*>({ new Symbol("val") }),
        vector<Symbol*>(),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("test"),
                Cons::from_vector({
                    new Symbol("op"),
                    new Symbol("is-false"),
                }),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("val"),
                })
            }),
            Cons::from_vector({
                new Symbol("branch"),
                Cons::from_vector({
                    new Symbol("label"),
                    f_branch
                }),
            }),
        })
    );
    // TODO: move to InstructionSequence::forLabel(Symbol*)
    // it appears t_branch_sequence doesn't jump to after_if_sequence after
    // executing
    InstructionSequence* t_branch_sequence = new InstructionSequence(
        {},
        {},
        Cons::from_vector({
            t_branch
        })
    );
    InstructionSequence* f_branch_sequence = new InstructionSequence(
        {},
        {},
        Cons::from_vector({
            f_branch
        })
    );
    InstructionSequence* after_if_sequence = new InstructionSequence(
        {},
        {},
        Cons::from_vector({
            after_if
        })
    );
    InstructionSequence* parallel = t_branch_sequence->append(c_code)->parallel(f_branch_sequence->append(a_code));
    return p_code->preserving(
        { new Symbol("env"), new Symbol("continue") },
        // TODO: danger, we need to append 3 instruction sequences, 2 at a time
        test->append(parallel)->append(after_if_sequence)
    );
}

bool is_cond(Value *exp) {
    return is_tagged_list(exp, new Symbol("cond"));
}

Value* cond_to_if(Value *exp) {
    List* clauses = convert_to<List>(convert_to<List>(exp)->cdr());
    return expand_clauses(clauses);
}

Value* expand_clauses(List* clauses)
{
    if (*clauses == *NIL) {
        //    'false                          ; no else clause
        return new Bool(false);
    }
    List* first = convert_to<List>(clauses->car());
    List* rest = convert_to<List>(clauses->cdr());
    Value* cond_predicate_clause = first->car();
    if (Symbol("else") == *cond_predicate_clause) {
        if (*rest == *NIL) {
            return sequence_to_exp(convert_to<List>(first->cdr()));
        } else {
            //              (error "ELSE clause isn't last - COND->IF"
            //                     clauses))
        }
    } else {
        // (make-if (cond-predicate first)
        //          (sequence->exp (cond-actions first))
        //          (expand-clauses rest))))))
        return Cons::from_vector({
            new Symbol("if"),
            first->car(),
            sequence_to_exp(convert_to<List>(first->cdr())),
            expand_clauses(rest)
        });
    }
}

Value* sequence_to_exp(List *seq) {
    //(cond ((null? seq) seq)
    //      ((last-exp? seq) (first-exp seq))
    //      (else (make-begin seq))))
    if (*seq == *NIL) {
        return seq;
    }
    if (*seq->cdr() == *NIL) {
        return seq->car();
    }
    return Cons::from_vector({
        new Symbol("begin"),
    })->append_list(seq);
}

bool is_let(Value *exp) {
    return is_tagged_list(exp, new Symbol("let"));
}

Value* let_to_combination(Value *exp) {
    //(define (let->combination exp)
    //  (define (make-lambda parameters body)
    //    (cons 'lambda (cons parameters body)))
    //  ; exercise
    //  (define (make-application proc parameters)
    //    (cons proc parameters))
    //  (define (let-vars exp)
    //    (map (lambda (binding) (car binding))
    //         (cadr exp)))
    //  (define (let-exps exp)
    //    (map (lambda (binding) (cadr binding))
    //         (cadr exp)))
    //  (define (let-body exp)
    //    (cddr exp))
    //  (make-application (make-lambda (let-vars exp)
    //                                 (let-body exp))
    //                    (let-exps exp)))
    List* let = convert_to<List>(exp);
    vector<Value*> vars_and_exps = convert_to<List>(let->cadr())->to_vector();
    vector<Value*> vars;
    vector<Value*> exps;
    for (vector<Value*>::iterator it = vars_and_exps.begin(); it != vars_and_exps.end(); ++it) {
        List* var_and_exp = convert_to<List>(*it);
        vars.push_back(var_and_exp->car());
        exps.push_back(var_and_exp->cadr());
    }
    Value* let_vars = Cons::from_vector(vars);
    Value* let_exps = Cons::from_vector(exps);
    Value* let_body = let->cddr();
    auto lambda = new Cons(
        new Symbol("lambda"),
        new Cons(
            let_vars,
            let_body
        )
    );
    return new Cons(
        lambda,
        let_exps
    );
}

bool is_lambda(Value *exp) {
    return is_tagged_list(exp, new Symbol("lambda"));
}

InstructionSequence* compile_lambda(Value* exp, Symbol* target, Linkage* linkage)
{
    Symbol* proc_entry = make_label.next("entry");
    Symbol* after_lambda = make_label.next("after-lambda");
    Linkage* lambda_linkage = linkage->lambda_linkage(after_lambda);
    return lambda_linkage
        ->use_to_end_with(
            new InstructionSequence(
                { new Symbol("env") },
                { target },
                Cons::from_vector({
                    Cons::from_vector({
                        new Symbol("assign"),
                        target,
                        Cons::from_vector({
                            new Symbol("op"),
                            new Symbol("make-compiled-procedure"),
                        }),
                        Cons::from_vector({
                            new Symbol("label"),
                            proc_entry,
                        }),
                        Cons::from_vector({
                            new Symbol("reg"),
                            new Symbol("env"),
                        }),
                    })
                })
            )
        )
        ->append(
            compile_lambda_body(exp, proc_entry)
                ->tack_on(Cons::from_vector({
                    after_lambda
                }))
        );
}

InstructionSequence* compile_lambda_body(Value* exp, Symbol* proc_entry)
{
    Value* formals = convert_to<List>(exp)->cadr();
    InstructionSequence* environment_extension = new InstructionSequence(
        { new Symbol("env"), new Symbol("proc"), new Symbol("argl"), },
        { new Symbol("env") },
        Cons::from_vector({
            proc_entry,
            Cons::from_vector({
                new Symbol("assign"),
                new Symbol("env"),
                Cons::from_vector({
                    new Symbol("op"),
                    new Symbol("compiled-procedure-env"),
                }),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("proc"),
                }),
            }),
            Cons::from_vector({
                new Symbol("assign"),
                new Symbol("env"),
                Cons::from_vector({
                    new Symbol("op"),
                    new Symbol("extend-environment"),
                }),
                Cons::from_vector({
                    new Symbol("const"),
                    formals,
                }),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("argl"),
                }),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("env"),
                }),
            }),
        })
    );
    List* lambda_body = convert_to<List>(convert_to<List>(exp)->cddr());
    return environment_extension->append(
        compile_sequence(lambda_body, new Symbol("val"), new LinkageReturn())
    );
}

bool is_begin(Value *exp) {
    return is_tagged_list(exp, new Symbol("begin"));
}

InstructionSequence* compile_sequence(List* seq, Symbol* target, Linkage* linkage)
{
    if (*NIL == *seq->cdr()) {
        return compile(seq->car(), target, linkage);
    } else {
        // (preserving '(env continue)
        //             (compile (first-exp seq) target 'next)
        //             (compile-sequence (rest-exps seq) target linkage))))
        InstructionSequence* firstStepOfSequence = compile(seq->car(), target, new LinkageNext());
        InstructionSequence* restOfSequence = compile_sequence(convert_to<List>(seq->cdr()), target, linkage);
        return firstStepOfSequence->preserving(
            { new Symbol("env"), new Symbol("continue") },
            restOfSequence
        );
    }
}
