## Problem

Exercise 5.52. As a counterpoint to exercise 5.51, modify the compiler so that it compiles Scheme procedures into
sequences of C instructions. Compile the metacircular evaluator of section 4.1 to produce a Scheme interpreter
written in C.

## Approach

The compiler doesn't really need to be ported, because it should produce assembly instructions for the virtual machine.

If we write a translation layer for the output of the compiler, we can use that to transform the compiler output into the C-data-structure-based assembly.

Do we also have to link it up into the existing explicit-control evaluator in some way (`compile-and-go`)?

Actually in the end, we should compile the meta-circular evaluator, so we won't need to use the explicit-control evaluator; only the underlying virtual machine.

## Testing

What should be the first acceptance test?

+ fork the es5.51 code
+ write a `compile` that only works for self-evaluating (even if it's fake)
++ stub InstructionSequence data structure
++ returns just a fixed instruction sequence
++ write a unit test for `compile`
++ complete InstructionSequence data structure so that you can assert on it
++ implement compile just enough for the compileTest first test to pass
- try to write `compile-and-go`, which should (re)use `assemble`
++ `assemble` may need to be extracted from the previous code
+ use it to compile `(list 42)` which should only evaluate 42 and stop
++ start from a `main()` that compiles a fixed input `(list 42)` to a sequence of assembly instructions, and just prints it
++ then you can put it into the `Machine` instead and try to execute it
+ (compile-variable exp target linkage)
++ implement InstructionSequence::to_string()
++ implement InstructionSequence << overload to use it
++ now do you have a good error message?
++ implement the compile-variable port
++ generalize to_string in dump.h
+ (compile-quoted exp target linkage)
++ fix Cons-as-pair to_string
++ make test pass
+ add linkage! as the 3rd parameter to compile, at least one sample case
++ can we do Linkage as an enum? No, `return`, `next` or arbitrary `label`
+++ some kind of polimorphism? start with a Value Object
+++ linkage.h with base class and subclass
+++ add `InstructionSequence::empty()` or similar to create an empty one
++ implement `compile_linkage(Linkage)`
+-- as a virtual method of Linkage
++++ LinkageNext
++++ LinkageReturn
++++ LinkageLabel
++ implement `InstructionSequence::append(InstructionSequence* another)`
+++ define as best as you can expectation
+++ hardcode a result
+++ compute `needs`
++++ `registers-needed` is just `this->needs` through a getter
++++ `registers-modified` is just `this->modifies` through a getter
++++ `list-union` is http://www.cplusplus.com/reference/algorithm/set_union/
++++ `list-difference` is http://www.cplusplus.com/reference/algorithm/set_difference/
+++ compute `modifies`
+++ compute `statements`
++++ implement `Cons::append_(Cons*)`
++++ rename `Cons::append_(Cons*)`
++++ implement `Nil::append_list*(Cons*)`
++++ pull up the common signature
++++ concatenate the two Cons to make `new_statements`
++ implement `InstructionSequence::preserving(vector<Symbol*> registers, InstructionSequence*, InstructionSequence*)`
+++ case with 0 registers
+++ case with some registers
++++ implement `needs(Symbol*)`
++++ implement `modifies(Symbol*)`
++++ case of untouched register
++++ case of modified register
+++++ build wrapped
+++++ build new call to preserve
+++++ avoid repetition in needs, modifies
++++++ change Value::to_string() to `const`
++++++ implement `<` for `Value`
++++++ introduce `set<Symbol>` for `this->_needs`
++++++ use `set<Symbol>` in all methods using `this->_needs`
++++++ introduce `set<Symbol>` for `this->_modifies`?
++++++ use `set<Symbol>` in all methods using `this->_modifies`?
+++++ add save calls
+++++ add restore calls
++ implement `end_with_linkage(Linkage, InstructionSequence*)`
+++ in the form of `Linkage::use_to_end_with(InstructionSequence)`
- (compile-application exp target linkage)
++ end2end test for calling a primitive procedure
++ make sure it produces an error saying this is not implemented
-- implement compile part
+++ also unit test should produce comprehensible errors
-- ADD LINKAGE (if needed for this)
++ compile operator
++ compile operands
-- (construct-arglist operand-codes)
+++ reverse
+++ code-to-get-rest-args
+++ implement zero argument case
+++ implement one argument case
+++ complete 2 missing cdr on operandCodes
++++ could pass an iterator around rather than a copy of the vector? https://stackoverflow.com/questions/421573/best-way-to-extract-a-subvector-from-a-vector
++++ tried, but after comparing `reverse_iterators` the code became unreadable and couldn't get it to work
++++ implement vector copy first, then refactor
+++ implement two arguments case
-- (compile-procedure-call target linkage)))))
+++ make-label
+++ parallel-instruction-sequences
--- compile-proc-appl
---- case 1: target val, linkage not return
----- not sure what to put as the `,linkage` value, should be a label we are able to jump to
----- clear enough that I can put a Symbol (label) into `continue` for a `LinkageLabel`
+++++ not clear for LinkageNext: is the Symbol `next` being put into `continue`?
++++++ no, would just cause a runtime error
+++++ it should be an error if we get into the situation of having to jump to `next`?
    (let ((compiled-linkage
            (if (eq? linkage 'next) after-call linkage)))
++++++ means LinkageNext can't be used here, only LinkageLabel and LinkageReturn
+++++++ therefore we need a LinkageJump(Linkage)
++++++++ LinkageLabel and LinkageReturn extend it
++++++++ LinkageNext does not extend it
+++++++ then `compile-proc-appl` actually moves on LinkageJump
++++ case 2: not target val, linkage not return
+++++ implement teardown for LinkageTest
+++++ move code up into LinkageLabel
+++++ update compileTest that broke
++++ case 3: target val, linkage return
---- case 4: not target val, linkage return: exception
--- actual code of compile-procedure-call
++++ case with LinkageNext is the base
---- case with a LinkageJump, just to test the difference without writing down the whole assembly code all over again
++++ is-primitive-procedure needs to be implemented as an operation
+++++ implemented with IsTaggedList(new Symbol("primitive"))
++++ needs minimal end-with-linkage
+++++ implemented on Linkage
++++ then two labels and be prepended/appended
++ end2end test should show somewhere the sum, even if it doesn't print it on stdout due to the lack of a REPL
+++ implement missing operations
++++ list
++++ cons
++++ compiled-procedure-entry
+++ add PrimitiveDisplay and configure it
+++ try to run '(display (+ 2 3))'
+++ debug why it explodes
+++ add assertions
--- the intention is to in the end compile the meta-circular evaluator which has the REPL, so we don't need a REPL now
++ start passing a Linkage (default one, `next`) to `compile_*()`
++ start passing a Linkage to `compile()` but perhaps overload allowing a default of `next`
-- actually use Linkage in `compile[_*]()`
--- with `use_to_end_with()`
-- add end2end test: an assignment (will fail)
+ (compile-assignment exp target linkage)
+ (compile-definition exp target linkage)
++ to end2end test it, Register `env` must be initialized
++ done this with `compile-and-execute`
--- what we need to do is to replicate `compile-and-go`
--- `assemble` must include eceval (for some reason, but also because it initializes stack and environment).
---- in general, it gives you a REPL where to use what you just compiled?
---- when Machine is created it must be initialized with the explicit control evaluator
---- needs to be ported over from es5.51
--- this will be substituted later when we compile the meta-circular evaluator (some configuration to be done)
- (compile-if exp target linkage)
- (compile-lambda exp target linkage)
- (compile-sequence (begin-actions exp) target linkage))
- (compile (cond->if exp) target linkage)
- `compile_and_go` should be extended to include `eceval` alongside the compiled expressions, see chapter5.5.scm
- think about where to deallocate memory, `delete` not just `new`

## You know you'll have to do this but you can postpone this until the first acceptance test works
- `compile` should implement `end-with-linkage` to wrap the `InstructionSequence`
++ create `Linkage` enum (or similar data structure with limited choices
+++ perhaps subclasses
++ pass linkage to `compile`
-- implement `preserve`
- `Value::to_string()` should become `const`, if this means what I think it means. It could then be used when you have a `const Value` without `discards qualifiers` interrupting the compilation
- `final` classes?

## References

- `es5.51/` provides the virtual machine (this will be forked)
- `chapter5.5.scm` (and dependencies) has the compiler

## Dependencies

- `cmake`
- `libboost-regex-dev`
- `libgtest-dev` and [googletest](https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/)
