# Vector ADT & CDT and amortised analysis

## Vector ADT
- Generalises the Array CDT
- Index of an entry is equivalent to number of elements preceding it
- Index aka rank
- Stores a sequence of arbitrary objects
- Exceptions are thrown if an invalid rank is specified (eg negative)

### Operations
- `object elemAtRank(int r)`: return element at rank r
- `object replaceAtRank(int r, object o)`: replace element at rank with o,
return old rank
- `insertAtRank(int r, object o)`: insert o at rank r
- `object removeAtRank(int r)`: remove and return element at r
- `size()` and `isEmpty()`

### Applications
- Stored collection of object (elementary database)
- Auxiliary data structure for algorithms
- Components of other data structures

## Vector using Array CDT
- Array `V` of size `N` used
- Variable `n` tracks size of vector - elements actually stored

### Operations
- `elemAtRank(r)`: O(1) - return V[r]
- `insertAtRank(r, o)`: O(n)
  - Need to make room by shifting forward `n - r` elements
  - Worst case, `r = 0`, requires shifting `n` elements
  - Inserting when array is full could simply resize the array instead of
throwing exception
- `removeAtRank(r)`: O(n)
  - Need to fill hole left by removing element
  - Shift backward `n - r - 1` elements
  - Worst case, `r = 0`, requires shifting `n - 1` elements
- `size`, `isEmpty`, `replaceAtRank`: O(1)
- Insert and remove can run in O(1) if using array circularly (as queue)

### Growable array
- Insertions need to consider if the array is full
- If it is, the array can be replaced with a larger one
- Copy elements into the new array
- __Incremental__: increase size by a constant `c`
- __Doubling__: double the size of the array
- Can compare performance of strategies using __amortised time__
  - Analyse total time `T(n)` needed to perform `n` operations
  - The average time of an operation over the series of operations - `T(n)/n`

> Amortise: paying off debts over a period of time

### Comparing growth strategies
- Given an individual operation takes time `T` in worst case
- Suppose a sequence of `s` operations are done, taking `T_s`
- `sT` is the upper bound for `T_s`
  - Upper bound might never occur
- `T_s` is `o(sT)` even in worst case
  - average time `T_s/s` is sometimes most relevant

### Amortised vs average case analysis
- __Amortised__: (long) real sequence of dependent operations
- __Average case__: set of possibly independent operations
- Big-Oh family still used in amortised analysis
  - It describes functions
  - In amortised analysis: "worst case of a sequence"

### Incremental example
- Array starts with size 3, `c = 3`
- Example sequence of _push_ operations: `1, 1, 1, 3+1, 1, 1, 1, 6+1, 1, 1, 1,
9+1, ...`
- Constant fraction of pushes have cost O(n) meaning average is O(n)
- Total time `T(n)` of `n` push operations is proportional to:
  - `n + c + 2c + 3c + ... + kc`
  - `= n + c(1 + 3 + 3 + ... + k)`
  - `= n + ck(k + 1)/2`
  - `c` is constant, so `T(n)` is O(n + k²), so O(n²)
  - Amortised time is O(n)

### Incremental example
- Array starts with size 3
- Example sequence of _push_ operations: `1, 1, 1, 3+1, 1, 1, 1, 6+1, 1, 1, 1,
1, 1, 1, 12+1, ...`
- Fraction of pushes with cost O(n) reduces with n
  - Every push of cost (n) allows another O(n) pushes of cost O(1)
- Cost of resizing is amortised over n other O(1) operations
- Average becomes O(1) per operation
- Array is replaced log2(n) times
- Total time `T(n)` of `n` push operations is proportional to:
  - `n + 1 + 2 + 4 + 8 + ... + 2^(k-1)`
  - `= n + 2^k -1`
  - `= 2n -1`
  - So T(n) is O(n)
  - Amortised time is O(1) - no worse than pre-assigning memory
