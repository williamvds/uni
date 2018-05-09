# Insertion Sort
```
InsertionSort(A) 
	<precondition: A is an array of length n > 0 integers>
  for(j = 2 to A.length)  
		<invariant: subarray A[1..j-1] is sorted>
		key = A[j] 
		i = j – 1  
		while(i > 0 and A[i] > key)          
			<invariant: all elements A[i+1..j] are >= key>
			A[i + 1] = A[i];         
			i--
		A[i + 1] = key
	<postcondition: elements in A are sorted>
```
- Keeps the front of the list sorted
- As the end is processed, those elements are reinserted into the correct place
in front
- Insertions shift right the elements from removed point to insertion point to
make space for insertion

## Correctness

### While invariant
- If `A[i] <= key` the while loop is skipped
- Extending subarray `A[1..j-1]` to `A[1..j]` between iterations leaves `A[j]`
in same place
- `key = A[j]; i = j-1`
- Thus `A[i+1] = key` == `A[j] = key`
- Value `key` stays where it is

### For invariant
- __Initialisation__: when `j=2` subarray `A[1..j-1]` is of length 1, so
trivially sorted

# Divide and Conquer
- Divide-and-conquer is a general algorithm design paradigm
  1. __Divide__: create two disjoints subsets datasets from input data
  2. __Recur__: solve subproblems of both subsets
  3. __Conquer__: combine solutions for both subsets into solution for input data

## Merge-sort
- Eg, sorting an input sequence `S` with `n` elements
1. __Divide__: Partition input into two sequences `S₁` and `S₂` both of size
approx. n/2
2. __Recur__: Recursively sort `S₁` and `S₂`
3. __Conquer__: Merge `S₁` and `S₂` into a sorted sequence

- Can create binary tree representing subarrays at each stage of
splitting/merging
- 𝑂(nlog(n))
  - Height `h` of tree is 𝑂(log(n))
  - Work done at each depth is 𝑂(n)
- __Pros__
  - Fast sorting for arrays
  - Sequential data access = good for sorting data in slow external memory
- __Con__: Not good with lists due to reliance on constant time access to
middle of sequence

## Quick-sort
- __Motivation__: simplify the _merge_ portion of merge-sort
- This is done by making the _divide_ more complicated - the _merge_ becomes
concatenate
- Create adjacent disjoint ordered ranges that can be simply concatenated, or
if already consecutive subarrays, simply forget the boundaries between them
- __Pro__: Can be done in-place = less memory usage

### Algorithm
1. __Divide__: Pick a random element `x` (aka pivot) and partition `S` into
  - `L` elements less than `x`
  - `E` elements equal to `x`
  - `G` elements greater than `x`
2. __Recur__: Sort `L` and `G`
3. __Conquer__: Concatenate `L`, `E`, and `G`, in that order

- Can combine `E` and `G`, merging into a single subarray `EG` - 2-way split
instead of 3-way

### Extra workspace
- Elements are extracted from `S` and placed in one of `L`, `E`, `G`
- Each insertion/removal is at the beginning or end of `S`, so 𝑂(1)
- Thus, partitioning is 𝑂(n)
- Doubles memory usage

### In-place
- Avoid using extra memory, so space complexity is 𝑂(n)
- Scan from both ends of the array to pivot, swapping elements that belong
on the other side of the pivot
- __Binary tree visualisation__
  - Can depict execution of quick-sort using a binary tree
  - Each node shows a transition of the array
  - Child nodes show the result of quick-sorting the remaining numbers either
  side of the pivot

### Time complexity
- Worst-case is 𝑂(n²) - when the pivot is the minimum or maximum element
  - One of `L` and `G` has size `n-1`, the other `0`
  - Running time proportional to sum of `n+(n-1)+...+2+1`
- Best case is 𝑂(nlog(n)) - when the pivot is the median element
  - `L` and `G` are the same size - splitting `S` into halves, like merge sort
- Average case is 𝑂(nlog(n)) - half hte times the pivot is close to the median

## Comparison sorting
> Comparison sorting: A sorting algorithm that compares between elements in the
> sequence to determine in which order to place them

- Eg: Bubble, selection, insertion, heap, merge, quick
- Not comparison: Bucket sort
  - 𝑂(n), but relies on knowing the range of values in sequence
- Such algorithms can be modeled as a binary decision tree
  - At each node two elements are compared - resulting in more information about
the correct order of elements in the sequence
  - The final result is the full information about the correct order of elements
in the sequence

### Complexity
- A binary tree with `n!` leaves has minimum number of levels `(log₂(n!))+1`
- This shows 𝑂(nlog(n)) sorting algorithms are essentially optimal
- Thus, the limitation of comparison-based sorting is 𝑂(nlog(n))

## Recurrence Relations
- A sort of recursively defined function
  - Generally applied to functions that measure resources
  - Might also want the big-Oh properties of solution
- Divide and conquer algorithms can have their recurrence relations extracted

### Merge sort
- `T(n) = 2T(n/2) + b + a*n`
  - `2T(n/2)`: Sorting two subarrays each of size `n/2`
  - `b`: Cost of doing split
  - `a*n`: Cost of doing merge, including copying to/from workspace

### Bubble sort
- `T(n) = T(n-1) + d*n`
  - `d*n`: A pass of the outer loop
  - `T(n-1)`: The remaining passes - done `n-1` times

### Solving
1. Start from base case
  - Use recurrence to work out many cases for `T(n)`
2. Inspect result, find pattern, form hypothesis
3. Attempt to prove hypothesis by induction

## Master Theorem
- Given a relation of the form `T(n) = aT(n/b) + f(n)`
- `f(n) ∈ 𝑂(nᶜ)`

### Case 1: f(n) grows slower
- I.e. `log_b(a) > c`
- Means that `f(n)` can be ignored
- `T(n) ∈ Θ(log_b(a))`

### Case 2: f(n) grows as quickly as aT(n/b)
- I.e. `log_b(a) = c`
- Given `f(n) ∈ Θ(nᶜlog(n)ᵏ)`
- Means that `f(n)` can be ignored
- `T(n) ∈ Θ(nᶜlog(n)ᵏ⁺¹)`

### Case 3: f(n) grows quicker
- I.e. `log_b(a) < c`
- `T(n) ∈ Θ(f(n))`

# Abstract Data Types: Stacks & Queues

## Abstract Data Types (ADTs)
- An abstraction of a data structure
- __Contents__
	- Data stored (attributes)
	- Operations on the data (methods)
		- May specify efficiency requirements in big-Oh notation
	- Error conditions associated with operations
- Does __not__ specify implementation - hence _abstract_
- __Narrow__: small set of specified methods
	- Eg Stack ADT
	- Less flexible to use
	- More flexible to implement - may be more efficient
- __Wide__: large set of methods
	- Eg Java Stack
	- More flexible to use
	- Possibly more difficult to implement efficiently

## Concrete Data Types (CDTs)
- An implementation of an ADT
- Implemented ADT interface hides actual implementation
	- Concept of data hiding and encapsulation in Object Oriented programming
- CDT choice affects running time and memory usage
	
### Eg: reversible array
- Suppose the _Array_ ADT specified an operation _reverse()_ that reverses
the contents
- __Poor implementation__: Reverse elements of internal data structure
	- 𝑂(n)
- __Efficient implementation__: Recalculate index if Array is currently reversed
		- 𝑂(1)
		```
		array x[N];
		boolean flipped = false;
		reverse() {flipped = !flipped;}
		get(i) {return x[flipped? N-i : i];}
		```

## Stacks
- Last-in First-out (LIFO) insertions/removal

### Methods
- `push(object)`: insert element at top
- `object pop()`: remove and return element at top
	- Throw `EmptyStackException` if no element available
- `object top()`: return element at top without removal
	- Throw `EmptyStackException` if no element available
- `int size()`: return number of elements stored
- `boolean isEmpty()`: true iff no elements stored

### Applications
- __Direct__
	- Tab history in a web browser
	- Undo sequence in a text editor
	- Chain of method calls in the Java Virtual Machine
- __Indirect__
	- Auxiliary data structure for algorithms
	- Components of other data structures

### Array implementation
- Add elements left to right
- Use a variable to track index of top element
- If full a `push()` would raise a `FullStackException`
- Space complexity 𝑂(n) - one array index for each element in stack
- Time complexity 𝑂(1) for all operations
- __Limitations__
	- Max size of stack must be defined in advance
	- Size cannot be changed dynamically
	- Attempted `push()`es to a full stack would cause an implementation-specific
exception

### Linked List implementation
- Top element stored at first node
- Insert/remove from head of list
- Store size as attribute, update upon insertion/removal
- Space complexity 𝑂(n) - one list entry for each element
- Time complexity 𝑂(1) operations

## Queues
- First-in First-out (FIFO) insertion/removal
- Stores arbitrary objects
- Insert at end of queue, remove from start

### Methods
- `enqueue(object)`: insert an element to the end of the queue
- `object dequeue()`: remove and return element at the front of queue
	- If empty throw `EmptyQueueException`
- `object front()`: return element at front of queue
	- If empty throw `EmptyQueueException`
- `int size()`: return number of elements in the queue
- `boolean isEmpty()`: true iff no elements in queue

### Applications
- __Direct__
	- Waiting lists
	- Access to shared resource (eg printer)
	- Event queues in GUIs and simulations
- __Indirect applications__
	- Auxiliary data structure for algorithms
	- Components of other data structures

### Array implementation
- Use an array of size `N` circularly
- Two variables `f` and `r` track front and rear respectively
- Empty at index `r`
- Wrap around the array using the modulo operator
- Throw `FullQueueException` if full on `enqueue()`

### Linked List implementation
- New arrivals placed at head
- Remove from head, insert at tail
- First element in queue stored at head of list
- Store size as attribute, update upon insertion/removal
- Space complexity 𝑂(n) - one list entry for each element
- Time complexity 𝑂(1) operations

## Array vs Linked List CDTs

### Array
- __Con__: Fixed size - possibly unused, or possibly too small
- __Pro__: Contiguous memory usage
	- Localised memory access = more effective CPU caching & pre-fetching

### Linked list
- __Pro__: Size can grow and shrink
- __Cons__
	- Can be scattered around memory = poor cache usage
	- Has to store _next_ reference = more memory usage


# Trees
- An abstract model of a hierarchical structure
- Composed of __nodes__ with at most one parent, and an unlimited number of
children

## Terminology
- __Root__: node without parent
- __Internal node__: node with at least one child
- __External node/leaf__: node without children
- __Ancestors__: chain of parents of a node
- __Depth__: Number of ancestors
- __Height__: greatest depth of all nodes in the tree
- __Descendant__: nodes that are part of the subtree of which a particular
node is the root of

## ADT
- `int size()`
- `bool isEmpty()`
- `Iterator iterator()`
- `Iterator positions()`
- `object replace(p, o)`
- __Accessors__
	- `position root()`
	- `position parent(p)`
	- `Iterator children(p)`
- __Queries__
	- `bool isInternal(p)`
	- `bool isExternal(p)`
	- `bool isRoot(p)`

## Traversals
- Goal is to visit each element precisely once in a systematic and meaningful
order

### Preorder traversal
- Visit a node before its descendants
- Eg when printing a structured document

### Postorder traversal
- Visit a node after its descendants
- Eg computing disk space used by a directory

## Linked List implementation
- __Element contents__
	- Pointer to parent
	- Value
	- List of child nodes

## Binary trees
- Each node has at most two children
- Children are an ordered pair - though only one child may be present
- Children are named _left_ and _right_
- Height is 𝑂(n) and Ω(log(n))

### Binary Tree ADT
- Extends `Tree`
- `position left(p)`
- `position right(p)`
- `bool hasLeft(p)`
- `bool hasRight(p)`

### Linked List implementation
- __Element contents__
	- Pointer to parent
	- Pointer to left child
	- Pointer to right child
	- Value

### Array implementation
- `rank(root) = 1`
- `rank(leftChild) = 2*rank(parent(leftChild))`
- `rank(rightChild) = 2*rank(parent(rightChild)) +1`
- Effectively stores in inorder traversal, leaving gaps for missing child
nodes, and skipping index 0

### In-order traversal
1. Explore left child
2. Visit node
3. Explore right child 

### Proper binary tree
- Is a binary tree
- Nodes must either have two or no children
- A tree consisting of only a root node is a proper binary tree

### Perfect binary tries
- All leaves are at the same depth - hence all levels are full
- `n` is the number of nodes in the tree
- `d` is the depth of the tree
- __Nodes at depth__ `d`: `2^d`
	- Level 0 contains 1 node (root) - `2^0 = 1`
	- Level `k-1` contains `2^(k-1)`
	- Since each node at level `k-1` has 2 children, level `k` contains
`2*2^(k-1) = 2^k` nodes
- __Nodes at depth__ `d+1`: `2^(d+1) -1`
- __Height__: `log₂(n+1)-1`
	- Θ(log(n))
- __Total nodes with height__ `h`: `2^(h-1) -1`
	- `h = 0`: `2^1 -1 = 1` node (root)
	- Assuming tree of height `h-1` has `2^h -1` nodes, a tree with another level
(total `n`) has another `2^h` nodes
	- Total: `2*2^h -1 = 2^(h+1) -1`

## Applications
- Organisation charts
- File systems
- Programming environments
- __Binary trees__: Searching
- __Proper binary trees__
	- Arithmetic expression trees: Nodes are operators, leaves are arguments
	- Decision trees: Nodes are yes/no questions, edges represent answers

# Vector ADT & CDT and amortised analysis

## Vector ADT
- Generalises the Array CDT
- Index of an entry is equivalent to number of elements preceding it
- Index aka rank
- Stores a sequence of arbitrary objects
- Exceptions are thrown if an invalid rank is specified (eg negative)

### Operations
- `object elemAtRank(int r)`: return element at rank `r`
- `object replaceAtRank(int r, object o)`: replace element at rank with `o`,
return old rank
- `insertAtRank(int r, object o)`: insert `o` at rank `r`
- `object removeAtRank(int r)`: remove and return element at `r`
- `size()` and `isEmpty()`

### Applications
- Stored collection of object (elementary database)
- Auxiliary data structure for algorithms
- Components of other data structures

## Vector using Array CDT
- Array `V` of size `N` used
- Variable `n` tracks size of vector - elements actually stored

### Operations
- `elemAtRank(r)`: 𝑂(1) - return `V[r]`
- `insertAtRank(r, o)`: 𝑂(n)
  - Need to make room by shifting forward `n - r` elements
  - Worst case, `r = 0`, requires shifting `n` elements
  - Inserting when array is full could simply resize the array instead of
throwing exception
- `removeAtRank(r)`: 𝑂(n)
  - Need to fill hole left by removing element
  - Shift backward `n - r - 1` elements
  - Worst case, `r = 0`, requires shifting `n - 1` elements
- `size`, `isEmpty`, `replaceAtRank`: 𝑂(1)
- Insert and remove can run in 𝑂(1) if using array circularly (as queue)

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
- `T_s` is `𝑜(sT)` even in worst case
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
- Constant fraction of pushes have cost 𝑂(n) meaning average is 𝑂(n)
- Total time `T(n)` of `n` push operations is proportional to:
  - `n + c + 2c + 3c + ... + kc`
  - `= n + c(1 + 3 + 3 + ... + k)`
  - `= n + ck(k + 1)/2`
  - `c` is constant, so `T(n)` is 𝑂(n + k²), so 𝑂(n²)
  - Amortised time is 𝑂(n)

### Incremental example
- Array starts with size 3
- Example sequence of _push_ operations: `1, 1, 1, 3+1, 1, 1, 1, 6+1, 1, 1, 1,
1, 1, 1, 12+1, ...`
- Fraction of pushes with cost 𝑂(n) reduces with n
  - Every push of cost (n) allows another 𝑂(n) pushes of cost 𝑂(1)
- Cost of resizing is amortised over n other 𝑂(1) operations
- Average becomes 𝑂(1) per operation
- Array is replaced log₂(n) times
- Total time `T(n)` of `n` push operations is proportional to:
  - `n + 1 + 2 + 4 + 8 + ... + 2^(k-1)`
  - `= n + 2^k -1`
  - `= 2n -1`
  - So T(n) is 𝑂(n)
  - Amortised time is 𝑂(1) - no worse than pre-assigning memory
