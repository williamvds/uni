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
- Lots of structure to valid Java code:
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
- Does the above program terminate for all `n >= 1`?
- eg, `n = 7`:
  - `7, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1`
- Sequence involved is known as the __hailstone sequence__
- The __Collatz conjecture__ says that the number `1` will always be reached
- For all numbers up to `2⁶⁰` the program has terminated
- No proof so far that it it does terminate for all `n >= 1`

> It is impossible to write a program that decides if another, arbitrary,
> program terminates (halts) or not.

- Proven by __Alan Turing__ (1912-1954)
- Introduced an abstract model of computation, Turing machines, in 1936
  - Gives a precise definition of 'effectively calculable' problems
  - ie can be solved mechanically
  - A universal model of computation
- Instrumental in British deciphering efforts during WWII
- PhD student of Alonzo Church

## λ-Calculus
- Theory of pure functions
```
(λx.x)(λy.y)
```
- Functional programming languages (eg Haskell) implement the λ-calculus
- Introduced by __Alonzo Church__ (1903-1995) in 1936
  - Gives a precise definition of what problems are effectively calculable
  - A universal model of computation
- Church-Turing thesis: What is effectively calculable is exactly what can be
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

## Languages
> Language: a (possibly infinite) set of words

> Word/string: a finite sequence (string) of symbols

> Symbol: anything contained in an alphabet Σ, a finite set

- Most common (and important) instance is `Σ = {0, 1}`
- __Є__: the empty word - sequence of zero symbols
- Є is never a symbol of an alphabet
- `Σ^*` is the set of words over Σ, given
  - The empty word `Є ∈  Σ^*`
  - A symbol `x ∈  Σ^*` and `w ∈  Σ^*` implies `xw ∈  Σ^*`
  - This is an inductive definition
  - Words have a finite length, but Σ^* is infinitely large (when Σ =/= ∅)
  - Since Σ^* contains the empty word, it always contains at least one element

### Examples
- __Alphabet__: `Σ = {a, b}`
- __Words__: `Є, a, b, aa, ab, ba, bb, aaa, ...`
- __Languages__: `∅, {Є}, {a}, {b}, {a, aa}, {Є, a, aa, aaa}...`
- Can use set builder notation to define a language
- The set of palindromes is a language for any alphabet
- The set of correct Java programs is a language over the set of Unicode
characters

### Language membership
- Can we determinate if, for a language `L` and word `w`, `w ∈ L`?
- If `L` is finite, enumerate it and check
- If `L` is infinite, enumeration will never terminate
- Require:
  - A __finite__ and preferably concise formal description of `L`
  - An algorithmic method to decide if `w ∈ L` given a suitable description
- Various approaches to check this
