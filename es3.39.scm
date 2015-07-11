The increment is serialized with the multiplication, but not with the set of its result.
Given: inc, *, set*
we add the following possible execution:
- *, inc, set*
with the result 100 since the last write set* wins over 11 written by inc.
101 and 121 are still possible if the two procedures are perfectly isolated.
110 is not possible because * is isolated.
11 is not possible because inc* is isolated and can only act on 10 (but then be modified later) or 100
