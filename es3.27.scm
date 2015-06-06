memo-fib only computes the n-th number once, as it is stored in the table for further evaluations. So the number of execution of the addition cannot be greater than n.

It is necessary to call memo-fib from inside the function itself, as just calling fib would result in no memoization of the majority of the calls (which come from recursion).
