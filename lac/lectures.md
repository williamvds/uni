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
    - __Decidable languages__: Turing machines
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
- Introduced an abstract model of computation, Turing machines, in 1936
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
computed by a Turing machine

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
