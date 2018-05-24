# Introduction

## Formal systems
- Considering the follow Java code
```java
class Foo {
  int n;
  void printNSqrd() {
    System.out.println(n * n);
  }
}
```
- It is fundamentally a string of characters
- Has defined __structure__:
  - keywords
  - identifiers
  - operators
  - nesting - methods must be inside class
- Need to consider how to describe the set of strings that are valid Java
  - Determine whether a string is valid Java or not
  - Recover the structure of a Java program from a _flat_ string
- __Regular expressions__ and __grammars__ are precise descriptions of languages
- __Automata__ decide if a a string belongs to a language or not

### The Chomsky Hierarchy
- Noam Chomsky (1928-)
  - American linguist who introduced __context free grammars__ to describe natural
languages formally
- Introduced the __Chomsky Hierarchy__
  - Classifies grammars & languages and their descriptive power
- __All langauges__
  - __Recursively enumerable (type 0)__
    - __Decidable languages__: Turing Machines
      - __Context sensitive languages (type 1)__
        - __Context free languages (type 2)__: pushdown automata
          - __Regular langauges (type 3)__: finite automata

## The Halting Problem
```c
while (n > 1) {
  if even(n) {
    n = n / 2;
  } else {
    n = n * 3 + 1;
  }
}
```
- Does the above program terminate for all `n ≥ 1`?
- eg, `n = 7`:
  - `7, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1`
- Sequence involved is known as the __hailstone sequence__
- The __Collatz conjecture__ says that the number `1` will always be reached
- For all numbers up to `2⁶⁰` the program has terminated
- No proof so far that it it does terminate for all `n ≥ 1`

> The Halting problem: tt is impossible to write a program that decides if
> another, arbitrary, program terminates (halts) or not.

- Proven by __Alan Turing__ (1912-1954)
- Introduced an abstract model of computation, Turing Machines, in 1936
  - A universal model of computation
  - Gives a precise definition of _effectively calculable_ problems
    - Ie ones that can be solved mechanically
- Instrumental in British deciphering efforts during WWII
- PhD student of Alonzo Church

## λ-Calculus
- Theory of pure functions
```
(λx.x)(λy.y)
```
- Functional programming languages (eg Haskell) implement the λ-calculus
- Introduced by __Alonzo Church__ (1903-1995) in 1936
  - A universal model of computation
  - Gives a precise definition of what problems are _effectively calculable_
- __Church-Turing thesis__: What is effectively calculable is exactly what can be
computed by a Turing Machine

## P vs NP
> Can every problem whose solution can be checked quickly by a computer also be
> solved quickly by a computer?

- Likely most famous open problem in computer science
- Dates back to 1950s
- 'Quickly' meaning in time proportional to a polynomial in size of problem
- Many important problems in which solution can be checked quickly, but best 
_known_ algorithm for finding a solution is exponential with size

> Subset sum problem: Does some non-empty subset of given set of integers sum
> to zero?
- eg for `{3, -2, 8, -5, 4, 9}` subset `{-5, -2, 3, 4}` sums to 0
- Checking solution is simple: sum numbers in subset and compare to 0
- Finding a solution requires (as far as we know) testing each possible
subset
- Number of possible subsets is `2^n`

# Languages
> Language: a (possibly infinite) set of words

> Word/string: a finite sequence (string) of symbols

> Symbol: anything contained in an alphabet Σ. A finite set

- Most common (and important) instance is `Σ = {0, 1}`
- __ϵ__: the empty word - sequence of zero symbols
  - Never a symbol of an alphabet
- __Σ^*__: the set of words over Σ, given
  - The empty word `ϵ ∈  Σ^*`
  - A symbol `𝓍 ∈  Σ^*` and `𝑤 ∈  Σ^*` implies `𝓍𝑤 ∈  Σ^*`
  - This is an inductive definition
  - Words have a finite length, but Σ^* is infinitely large (when Σ =/= ∅)
  - Since Σ^* contains the empty word, it always contains at least one element

## Examples
- __Alphabet__: `Σ = {a, b}`
- __Words__: `ϵ, a, b, aa, ab, ba, bb, aaa, ...`
- __Languages__: `∅, {ϵ}, {a}, {b}, {a, aa}, {ϵ, a, aa, aaa}...`
- Can use set builder notation to define a language
- The set of palindromes is a language for any alphabet
- The set of correct Java programs is a language over the set of Unicode
characters

## Language membership
- Can we determinate if, for a language `L` and word `𝑤`, `𝑤 ∈ L`?
- If `L` is finite, enumerate it and check
- If `L` is infinite, enumeration may never terminate
- Require:
  - A __finite__ and preferably concise formal description of `L`
  - An algorithmic method to decide if `𝑤 ∈ L` given a suitable description
- There are various approaches for this

# Finite Automata
- A method for determining whether a word belongs to a language
- Correspond to a computer with a fixed finite amount of memeory (states)
- An automaton accepts or rejects words
  - Accepted words of automaton A is the _language_ of A (`L(A)`) 

## Deterministic Finite Automata (DFA)
- Defined by tuple (𝑄, Σ, ẟ, q₀, 𝐹)

### Composition
- 𝑄: Finite set of states
- ẟ ∈ 𝑄 ⨯ Σ → 𝑄: Transition function
  - Maps a state and symbol pair onto a new state to move to
- q₀∈ 𝑄: Initial state
- 𝐹 ⊆ 𝑄: Accepting (final) states

### Extended Transition function
- Defined on a state and a __word__ instead of a single symbol
- ẟ 𝑄 ⨯ Σ^* → 𝑄
- No transition on ϵ
- Transition of `𝓍𝑤` where `𝓍` is a symbol and `𝑤` a word is: ẟ(ẟ(q, 𝓍), 𝑤)

### Language of DFA A L(A)
- Are words accepted by a DFA
- Ie ones that end on an accepting state, starting from q₀ and applying the
transition function for each symbol

## Nondeterministic Finite Automata (NFA)
- Defined by tuple (𝑄, Σ, ẟ, 𝑆, 𝐹)
- ẟ ∈ 𝑄 ⨯ Σ → 𝒫(𝑄): Transition function
  - Maps a state and symbol pair onto a __zero or more__ states to move to
  - There is a choice involved - hence __nondeterministic__
- 𝑆: is a set of possible starting states
  - Instead of a single starting state q₀
- All possible states are considered simultaneously as a word passes through
the machine
- A word is accepted if any of those possible terminating states is accepting
- A word is rejected if there is no available transition for an input symbol
- Accepts same class of languages as DFAs

### Subset Construction
- Converts a NFA to a DFA
  - Since DFAs can be viewed as a special case of NFAs, they can be converted
between

| δ_D(C) | 0 | 1 |
|:-:|:-:|:-:|
| ∅ | ∅ | ∅ |
| → {q₀} | {q₀} | {q₀,q₁} | 
| {q₁} | {q₂} | {q₂} | 
| * {q₂} | {q₀,q₂} | {q₀,q₁,q₂} | 
| {q₀,q₁} | {q₀} | {q₀} | 
| * {q₀,q₂} | {q₀} | {q₀,q₁} | 
| * {q₁,q₂} | {q₂} | {q₂} | 
| * {q₀,q₁,q₂} | {q₀,q₂} | {q₀,q₁,q₂} | 

- `→` indicates a starting state
- `*` indicates this is an accepting state - it contains one of the original
final states
- Each set becomes its own _state_ in the DFA - though one might not be used
  - Only need to show the ones that can be reached from the starting state(s)

# Regular Expressions
- A concise and more direct way to describe languages
- Concept implemented in programming languages and applications

## Definition
1. ∅ is a regex
    - Empty set - no accepted words
-  ϵ is a regex
    - Only accept the empty string
-  __x__ is a regex ∀ __x__ ∈ Σ
    - Accept single symbols from the alphabet
-  E+F is a regex if E and F are regexes
    - __Alternation__
    - Accept either E or F
-  EF is a regex if E and F are regexes
    - __Juxtaposition/concatenation__
-  E^*  is a regex if E is a regex
    - __Kleene star__
    - Accept all possible combinations of the full strings of set E
-  (E) is a regex if E is a regex
    - Allows stronger binding

- Operator binding is stronger further down the definition
  - (E) > E^* > EF > E+F

## Converting to NFA
- Since regular expressions are equivalent to Finite Automata, there is a
simple method to convert to a NFAs
- Can convert through induction on the syntax of regular expressions

### N(∅)
- __A single initial state__
- Will reject everything, since there are no initial states

### N(ϵ)
- __A single initial and accepting state__
- Will accept the empty word but reject everything else
  - There is no transition available for any symbol

### N(x)
- An initial state connected to an accepting state
- Initial state has a transition to the accepting state on symbol x

### N(E+F)
- The diagrams for N(E) and N(F) are merged into one - draw a box around both

### N(EF)
1. Identify penultimate states in N(E) (ie. ones leading to an accepting state)
2. Connect each of these to each of the initial states of N(F)
3. If there is an initial state in N(E) that is also accepting, keep the initial
states in N(F), otherwise remove them

### N(E^*)
1. Identify penultimate states in N(E) (ie. ones leading to an accepting state)
2. Connect each of these to each of the initial states of N(E)
3. Add an initial and accepting state

# 𝒫  vs 𝒩𝒫
- __Motivations__
  - __Efficient__ exact algorithms have runtimes of low-order power laws
  - __Inefficient__ complete/exact algorithms have runtimes have exponential
runtime, though incomplete or approximate methods are often fast

## 𝒫
- The set of problem classes that can be solved using a deterministic
Turing Machine in polynomial time p(n)
  - Deterministic TM: There is at most one action or 5-tuple for any current
state qₖ and any symbol that can occur when the machine is in that state
  - At most one choice for the next move

## 𝒩𝒫
- The set of problem classes that can be solved using a
__nondeterministic__ Turing Machine in polynomial time
- A subset of __𝒫__
- __Turing Machine definition__
  - A language L is in the class 𝒩𝒫 if there is a deterministic Turing Machine
M and a polynomial function f such that...
    - Running M on a tape with two inputs w and v (separated by a blank), it
  always terminates in steps less than f(|w|)
    - If w ∈ L then there exists some v such that M gives a positive answer when
  run on w and v
    - If w ∉ L, for every v M always gives a negative answer when run on w and v
  - If M gives a positive answer when run on w and v, v is a _certificate/proof_
w is in L
    - If L is a problem, and w an instance, v is a solution for w
- Many common decision problems are 'obviously' __𝒩𝒫__
- eg SUBSET-SUM: Find a subset of a set of values that sum to a particular value
  - Verification is 𝑂(n) - sum the subset, compare to value
  - Brute force algorithm 𝑂(2ⁿ) - check sum of each subset of S
  - Nondeterministic algorithm - for each element of the set of values, either
place it in the subset or don't, then compare its sum to the desired value

### Nondeterminism
- In a nondeterministic Turing Machine, there is more than one possible path
through it 
  - Each point where there is a choice results in a _decision_
- Only one action may be selected, but it is always the _best one_
- The shortest path is used every time
  - This is not physically possible
- If there is any sequence of decisions that results in success, the algorithm
has succeeded
  - Regardless of however many paths fail

### Reductions
- Can relate the hardness of two different problem classes
  - Even if the true hardness is not known
- This is done by showing that a (part of a) problem class is equivalent
to another
- Need to be able to convert (in polynomial time) from instance x of problem
class X to instance y(x) of problem class Y
- __Restricted conversions__
  - If it is allowed to reduce anything to a trivial problem, the conversion
itself can solve the problem
  - It is desirable to reason about what can or cannot be done in polynomial
time
  - So conversions are restricted to those that can be done in polynomial time

### 𝒩𝒫-hardness
- A problem class to which _any_ 𝒩𝒫 problem can be reduced to
- Such a problem class is 'as bad as it gets'
  - If such a problem class turns out to be in 𝒫 then 𝒫=𝒩𝒫 
- Usually done by showing polynomial-time reduction from some known 𝒩𝒫-complete
problem
- Eg Boolean satisfiability

### 𝒩𝒫-completeness
- Problem class X is 𝒩𝒫-complete if:
  - X is in 𝒩𝒫
    - All instances of X can be solved in nondeterministic polynomial time
    - Membership of N is usually demonstrated directly (and fairly easily)
  - X is 𝒩𝒫-hard
