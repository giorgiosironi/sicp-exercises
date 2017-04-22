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

