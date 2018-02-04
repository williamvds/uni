# Introduction
- Modern heuristic optimisation/search techniques can...
  - do automated timetabling
  - reduce operational cost of supply chains
  - increase energy production by optimising wind-farm layouts
  - improving packing and scheduling workflow for additive manufacturing
  - optimise multifunctional structures combining composite and porous layers

## Definitions
> Decision: The choice of one among a number of alternatives

> Decision making: The process of choosing among alternative course of action
> for the purpose of attaining a goal or goals - Turban and Aronson, 1998

### Decision support
- Covers multiple disciplines in contexts related to decision making, including
  - Artificial Intelligence
  - Operations Research
  - Decision Theory
  - Decision Analysis
  - Statistics
  - etc

### Systems
- Degree of independence
  - __Closed__: totally independent
  - __Open__: dependent on their environment

- Evaluations of systems
  - __Effectiveness__: degree to which goals are achieved, i.e. result or output
  - __Efficiency__: a measure of the use of inputs (resources) to achieve outputs
    - Eg speed

# Search & optimisation
## Solving problems by searching
1. Search for paths to goals
  - Efficiently finding a set of actions moving from initial state to a goal
  - Central to many AI problems - game playing, path finding
  - Typical algorithms:
    - Breadth first search
    - Uniform cost Search
    - Branch and bound
    - A*

2. Search for solutions ( _optimisation_ )
  - More general class than searching for paths to goals
  - Efficiently finding a solution to a problem in a large possible solution
space
  - Incorporates first type - path through a search tree can be encoded as a
candidate solution

### Global optimisation
> Global optimisation: finding the absolute best set of admissible conditions
> to achieve your objective, formulated in mathematical terms

- The fundamental problem of optimisation: arrive at the __best__ possible
decision/solution in any given set of circumstances
- Though in most cases, __best__ is unattainable

> Global optimum: Better than all other solutions (ie the best)

> Local optimum: Better than all solutions in a certain neighbourhood

- Optimisation process:
  - Choose a quantity to be maximised or minimized, which might be subject to
constraints
    - __Quantity__: Typically function of several variables, known as __objective
function__
    - When objective function is subject to constraints this is 
__constraint optimisation__ 

### Continuous vs Discrete space
- __Continuous spaces__: are infinite, varying between 0 and 1
  - eg the angle of the spoiler of a race car
- __Discrete spaces__: have a finite search space

## Combinatorial optimisation problems
- Need to find an optimal object from a finite set of objects
- Mostly NP-hard: checking for a correct solution is (much) faster than
finding one, eg...
  - determining the optimal way to deliver packages
    - Minimise travel distance
    - Constrained weight distribution in a truck
    - Choose truck to load, order to load
  - optimal scheduling of shifts/jobs with various constraints
  - optimal packing of items

## Optimisation/search methods
- Exact/exhaustive methods
  - Always provide the optimal solution since they explore entire search space
  - eg dynamic programming, branch & bound
  - __Con__: only work if the problem is structured and deterministic - often for
small problem instances
  - Often used to solve sub-problems
- Inexact/approximate methods
  - Includes heuristics, metaheuristics, hyperheuristics
  - We can use them to solve discrete combinatorial optimisation problems
effectively and efficiently, facilitating the use of data, models, and
structured decision processes for decision support

## Types
- Finding solutions
  - __Deterministic__: return same solution for same set
  - __Stochastic__: can return different solutions for same set - have a random
component
- Searching
  - __Systematic__: explores entire search space
  - __Local search__: employ sampling - explore a fraction of the search space
- Execution
  - __Sequential__: must run algorithm in a particular order
  - __Parallel__: can run algorithm in parallel
- Number of objectives
  - __Single objective__: single goal to achieve
  - __Multi-objective__: find trade-off solutions that consider multiple factor
(eg cost and performance)

## Search paradigms
- __Single-point (trajectory)_: use only current solution to perform search
- Multi-point (population)__: use multiple solutions to perform search
- __Constructive__: process partial candidate solutions
- __Perturbative__: can only deal with complete solutions

## Heuristic search methods
> Heuristic: a rule of thumb method derived from human intuition
- A problem dependent search method which seeks good (ie near-optimal) solutions
- Have a reasonable cost (eg speed)
- Good for solving ill-structured problems, or complex well-structured problems
  - Large-scale combinatorial problems have many potential solutions to explore

- __Cons__
  - Do not guarantee optimality
  - Usually can only be used for specific situations, for which they were
designed
  - If there are parameters, they could affect performance 
  - May give a poor solution

### Example: bin packing problem
- Heuristic: Largest item first fit
  1. Sort items by descending size
  2. Place each item into the first bin that it fits in
  3. If no bin fits the item, place it in a new bin
  - Binds are sorted in order they came into use
  - Deterministic local search/greedy constructive heuristic algorithm

### Graph colouring - classroom assignment problem
- Each room must have at most one assigned meeting or class at a time
- Each class or meeting must occupy only a single room at a time
- Objectives:
  - Schedule based on number of rooms available
  - Find a schedule that requires the fewest rooms
- Graph representation:
  - Vertices = meetings or classes
  - Edges = constraints - connected vertices must take place in separate rooms

#### Graph colouring
- Assigns labels called 'colours' to elements subject to constraints
- No two adjacent vertices may share the same colouring
- _k_-colouring problem: for a particular graph, can _k_ colours be used to solve
the graph colouring problem?
- _k_-colouring is NP-hard - need to colour vertices using optimal (minimum)
number of colours, so that no two adjacent vertices have the same colour

#### Saturation degree
- Degree of vertex: number of edges connected to that vertex
- Saturation degree of vertex: Number of differently coloured vertices already
connected to it
- Can use saturation degree in a heuristic to construct a solution

#### Algorithm
1. Arrange vertices in decreasing order of their degree
2. Colour a vertex with greatest degree with colour #1
3. Choose an uncoloured vertex with greatest saturation degree
    - If there is a tie, choose any in the subgraph
4. Colour the selected vertex using the colour with lost possible number (#)
5. If all vertices are coloured, STOP, else go to 3

- If high degree vertices are not assigned early on, they often end up requiring
new colours at the end of the process

### Stochastic local search - perturbative vs constructive algorithms
- In the context of the Travelling Salesman Problem (TSP)
- Given a list of cities and distances between them
- Need to find shortest possible route that visits all and returns to the
starting city
- NP-hard problem
- Underpins many real-world problems - planning, logistics, vehicle routing,
etc
- Search space for `N` cities is `N!` - combinatorial explosion
- Could take longer than the age of the universe to explore entire search space

#### Nearest neighbour (NN)
- __Constructive__, deterministic, systematic heuristic
1. Select a starting city
2. Explore the nearest unvisited city
3. Repeat 2 until starting city is chosen

- Constructive stochastic local search algorithm for TSP
1. Choose a random city
2. Apply NN to construct complete solution
3. Compare new solution to best found so far, update best solution if necessary
4. Go to 1, repeat for the specified max number of iterations
5. Return best found solution

#### Pairwise exchange (2-opt)
- aka Lin-Kernighan heuristics
- __Perturbative__, stochastic and local search
1. Start with a solution
2. Remove two edges and replace them with two different edges
    - Reconnects the fragments into a new and shorter tour

- Perturbative stochastic local search algorithm for TSP
1. Create a random current solution - shuffle a permutation array
2. Apply 2-opt: swap two randomly chosen cities
3. Compare new solution to current solution
  - If it has been improved upon, make the new solution the current one
  - Otherwise continue
4. Go to 2, repeat for the specified max number of iterations
5. Return the current solution

#### More on TSP
- Other Heuristics
  - Christofide's algorithm (1976)
  - Match Twice and Stitch `doi:10.1016/j.orl.2004.04.001`
  - Lin-Kenighan `doi:10.1016/S0377-2217(99)00284-2`
- Exact algorithm - [Concorde](http://www.math.uwaterloo.ca/tsp/concorde)
