## Problem

Exercise 5.51. Develop a rudimentary implementation of Scheme in C (or some other low-level language of your
choice) by translating the explicit-control evaluator of section 5.4 into C. In order to run this code you will need to
also provide appropriate storage-allocation routines and other run-time support.

## Approach

The explicit-control evaluator provided by the book is composed by a virtual machine (with registers, operations, a stack, etc.) and a Lisp interpreter written in its assembly language running over it.

It would be possible to translate the explicit-control evaluator directly to a sequence of C instructions, perhaps with some `goto` statements here and there. You would still have to provide the implementation of the primitive operations and everything related to the virtual machine.

This layer of manual translation looks to me as a recipe for bugs however, so I preferred not to do a translation and input the explicit-control evaluator as a data structure made up of atoms and cons cells. This fictional assembly language is essentially the bytecode for the virtual machine.

This means that by converting the format of assembly code into the C data structure we can execute it directly, and the explicit-control evaluator needs no modifications to run.

The end result is still what was required by the exercise: a rudimentary implementation of [a] Scheme [interpreter], written in C. But thanks to the two layers the implementation is simpler to debug. In the real world, it would be easier to port bug fixes to the explicit control evaluator into this version.

## Architecture

`Machine` is a virtual machine composed of `Register` instances, a `Stack` and primitive `Operation` instances. It takes a controller as an input in `install_instruction_sequence()` and `execute()`s it.

`main.cpp` passes an explicit-control evaluator (an implementation of Scheme written for this virtual machine) as the instruction sequence. The result is a Scheme interpreter that is loaded into the virtual machine at startup and provides a REPL.

### Instructions implemented

- `Assign`
- `Branch`
- `Goto`
- `LabelNoop `
- `Perform`
- `Restore`
- `Save`
- `Test`

### Operations implemented

- `AdjoinArg`
- `AnnounceOutput`
- `ApplyPrimitiveProcedure`
- `ConsMethodOperation`
- `Constant`
- `DefineVariable`
- `DefinitionValue`
- `DefinitionVariable`
- `ExtendEnvironment`
- `GetGlobalEnvironment`
- `InitializeStack`
- `IsEqualTo`
- `IsInstanceOf`
- `IsLastExp`
- `IsLastOperand`
- `IsNotEqualTo`
- `IsSelfEvaluating`
- `IsTaggedList`
- `IsVariable`
- `LookupVariableValue`
- `MakeProcedure`
- `Operation`
- `PromptForInput`
- `Read`
- `SetVariableValue`
- `TextOfQuotation`
- `UserPrint`

## Commands

```
./build.sh
./test.sh
```

## Testing

`tests/*.cpp` files provide some unit tests written in C++ for the various classes being used.

`tests/test_end2end.py` executes examples of inputs for the REPL, testing their output. Every test uses a new `main` process.

## References 

- `chapter4.1.scm`: application?
- `chapter5.2.scm`: make-machine, make-new-machine
- `chapter5.4.scm`: explicit-control-evaluator, operations
- `chapter5.scm`: assignment-variable and many basic operations
- `es4.13.scm`: environments, frames, variables
