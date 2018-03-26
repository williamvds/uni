# Introduction
- This module aims to provide...
  - an understanding of a selection of modern heuristic search techniques in AI
  - an understanding of the methods available for use in automated decision
making & optimisation
  - an acquaintance with a selection of applications and understanding of how
software tools are designed to solve them

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

# Heuristics

- Comparing algorithms
  - Multiple runs on single problem instance
  - Multiple problem instances
  - Same computational power, and time provided to each
  - P-value - if less than 0.05 (1 - confidence interval) then !!

> Metaheuristic: a high-level problem-independent algorithmic framework
> that provides a set of guidelines or strategies to develop heuristic
> optimisation algorithms

## Components

### Representation/encoding
- How candidate solutions should be represented
- __Binary encoding__ 
  - Most common
  - 0/1 Knapsack problem
    - 0/1 indicates whether an item should be taken or not
- __Integer encoding__
  - Assignment, personnel rostering, timetabling problems
  - Integers can indicate assigned time block or individual
- __Permutation encoding__
  - A sequence of symbols in a particular set
  - eg in the Travelling salesman problem
- __Value encoding__
  - Sequence of values - eg DNA
  - Useful in parameter/continuous optimisation

### Evaluation function
- AKA objective, cost, fitness, penalty
- Indicates quality of given solution
- Distinguishes between better and worse ones
- Provides feedback on search process
- Types: (non)separable, uni/multi-modal, single/multi-objective, ...
- Could be computationally expensive
- __Approximate methods__
  - eg polynomials, regression, SVMs, ...
  - Globally valid ones are not easy to make
  - Can combine approximate and evaluation function
- __Delta (incremental) evaluation__
  - Calculate difference between current and new solution
  - Evaluation functions often use independent parts of solution components
  - Crucial for efficient implementation of (meta/hyper)heuristics

### Initialisation
- How things are set up at the start
- eg initial candidate solution
- Could be random

### Neighbourhood relation
- Ie the move operator(s)
- Method of moving from the current candidate solution to a new one

### Other
- __Termination criteria__
    1. Fixed computational limit
        - Number of iterations, moves, objective function evaluations, or CPU
time
    2. When a target objective value is reached
- __Mechanism for escaping from local optima__
    1. Iterate with different solutions or restart
      - eg Iterated Local Search, GRASP
      - __Con__: Initialisation could be costly (using constructive algorithm)
    2. Change the search landscape
        1. Change objective function (eg Guided Local Search)
        2. Use/mix different neighbourhoods
            - eg Variable Neighbourhood Search, hyperheuristics
    3. Use memory (eg Tabu search)
        - Avoid re-searching the same solutions again
    4. Accept non-improving moves
        - Continue searching using candidate solutions with equal or worse
evaluation function value
      - __Con__: Could cause long walks on plateaus, potentially causing cycles
  - None are guaranteed to always escape effectively

## Effective searching
- Should provide a mechanism to balance exploration and exploitation

> Exploitation/intensification: Greedily increasing solution quality or
> probability. Eg by exploiting evaluation function

> Exploration/diversification: Aim to find a larger range of solutions, eg
> by applying mutation

## Hill Climbing
- Processes a candidate solution and generates one of equal or superior quality

### General algorithm
1. Pick an initial starting point (current state)
2. Repeat
    1. Consider neighbours of the current state
    2. Compare quality of points in the neighbourhood with the quality of the
current state, return the best among them
3. Until there is no improvement or a certain number of iterations is reached
4. Return the current solution (state)

### Best improvement
- AKA Steepest descent/ascent
  - Depending on whether it is a maximisation/minimisation problem
1. For each bit in the current solution...
    1. Flip the bit
    2. Evaluate the new solution
    3. Remember the flipped index that created the best quality, and whether it
was an improvement on the current one
    4. Undo the bit flip
2. If there was an improvement, flip the bit that produced the best quality
solution

### First improvement
- AKA next descent/ascent
- Like best improvement, but keeps the first bit flip that produces a higher
quality solution

### Davis' (Bit) Hill-climbing
1. Create a random solution permutation
2. For each bit `i` in the current solution...
    1. Flip the respective bit in `permutation[i]`
    2. If the quality has decreased (or is unchanged), undo the flip

### Random mutation
1. For a certain number of iterations...
    1. Flip a random bit
    2. If the quality has decreased (or is unchanged), undo the flip

### Strengths
- Very easy to implement
- Only needs
  - Representation
  - Evaluation function
  - A measure that defines neighbourhoods

### Weaknesses
- __Local optima__: Algorithm may halt at poor solution if neighbouring states
are worse (or equal)
- __Plateaus__: Would cause a random walk
- __Ridge/valley__: May oscillate from side to side without progressing
  - Could restart at a different point
- Hill climbing algorithms may not find the global optimum, becoming stuck
at local ones
- We don't know how much a local optima deviates from the global or other local
optima
- Usually no upper bound on computation time
- Success/failure depends on starting point
  - Where success is returning a global or local optimum

## Iterated local search
1. Create initial solution (randomly or construction heuristic)
2. Create random perturbation of current solution (exploration)
3. Re-perform hill-climbing search (exploitation)

- Perturbation strength is crucial
  - __Too small__: cycles may be generated
  - __Too big__: good properties of local optima are lost
- Acceptance criteria
  - __Extreme intensification__: accept only improving solution
  - __Extreme diversification__: accept any solution
  - Others including deterministic, probabilistic
- Memory: eg restart after a certain number of non-improving solutions are found

## Tabu Search
- Proposed by Fred W. Glover in 1986, formalised in 1989
- Stochastic local search
- Applies hill climbing / local search
- Uses _memory_

### Use of memory
- Enables __escape from local minima__
- Inspired by ideas from AI in late 1970s
- __Tabu-list__: contains recent past moves
  - Stored attributes are often defined by local search moves
  - Can store minimal amount of information by using attributes of previous
solutions
- __Tabu status__: Solutions containing attributes in the Tabu-list are
forbidden for a number of iterations
  - Assumes no point in accepting a new (poor) solution unless to avoid a path
already searched
- __Aspiration criterion__: An optional condition that allows tabu status to
be overridden (eg if there is an improvement)
- Simple strategies exploit only short term memory
- More complex ones exploit long term memory
- Cycles are avoided by avoiding revisiting previously seen solutions

### Strategies
- __Forbidding__: controlling what enters the tabu list
- __Freeing__: controlling what exists the tabu list and when
- __Short term__: managing interplay between forbidding and freeing to select
trial solutions

### Algorithm
- In each step
  - Generate a list of neighbouring solutions
  - Find the best of neighbours
  - Check if _accessible_
  - If accessible, accept it and replace current solution, otherwise
continue with next best neighbour

### Design (for MAX-SAT)
- __Initialisation__: Random
- __Move operator__: A hill climbing / local search algorithm
- __Neighbourhood definition__: Eg, attainable by single bit flip
- __Memory__: Associate tabu status (boolean) with each variable of in problem
  - tabu = changed in last `T` steps, where `T` is tabu tenure
  - For each variable `x_i` store number of the search step when it was last
changed (`t_i`).
  - tabu = `c - t_i < T`, where c is current search step number

### Considerations & improvements
- __Tabu tenure__ choice is critical for performance:
  - __too low__: risk of cycling
  - __too high__: may restrict search space too much
  - `T = 7` has been found to be sufficient to prevent cycling
- If a tabu move is smaller than the _aspiration level_ we accept it
- Can use intermediate and long-term memory for extra _intensification_ 
or _diversification_, eg:
  - Backtrack to elite candidate solutions, resetting tabu list
  - Freeze certain solution components for a number of steps
  - Occasionally force rarely used solution components
  - Extend evaluation function to capture frequency of use of candidate
solutions (as a ratio of no. of components)

# Scheduling
> Scheduling: The process of planning, controlling, and optimising work and
> workloads in a production/manufacturing process

- `i = [1, m]`: Number of machines
- `j = [1, n]`: Number of jobs
- `(i,j)`: A processing step (operation) of job `j` on machine `i`
- `p_ij`: Processing time of job `j` on machine `i`
- `d_j`: Due date - time job `j` must be completed by
- `w_j`: Weight - importance of job `j` relative to other ones

## Notation: α | β | γ
- α: Machine characteristics
- β: Job characteristics
- γ: Optimality criteria

### α examples
- Single machine: `α = 1`
- Identical machines in parallel: `α = Pm`
  - Speed of machines is the same
  - Job `j` requires a single operation and may be process on any of `m`
machines
- Different machines in parallel: `α = Qm`
  - Differences between speeds of the machines
- Unrelated machines in parallel: `α = Rm`
  - Machines have different speeds for different jobs

### β examples
- Release date `r_j`: earliest time at which job `j` can start being processed
- Sequence dependent startup times `s_jk`: setup time between `j` and `k`
- Breakdowns `brkdwn`: machines are not continuously available
- Permutation `prmu`: eg order of queue processing (FIFO)

### γ examples
- Completion time `C_ij`: of job `j` on machine `i`
- Time when job exits system `C_j`
- Lateness of `j` `L_j = C_j - d_j`
- Tardiness `T_j = max(C_j - d_j, 0)`
- Unit penalty `U_j = 1 if C_j > d_j otherwise 0`

# Evolutionary algorithms

> Evolution: Gradual change in the characteristics of a population of plants or
> animals over successive generations

- Evolution is problem solving in nature
- Often creates complexity from simplicity
- Application to solving computer problems

> Evolutionary algorithms: simulate natural evolution (Darwinian Evolution)
> of individual structures at the genetic level.
> Uses survival of the fittest via processes of selection, mutation, and
> reproduction (recombination)

- An individual (aka chromosome(s)) represents a candidate solution
- _Population_: A set of 'individuals' currently alive - current candidate solutions
- Individuals evolved from one generation ( _iteration_ ) to another depending on the _fitness_ (objective function value) of individuals
- Ideally he last generation will contain the final, best, solutions

## History
- __Genetic algorithms__: evolving bit strings
- __Evolutionary programming__: Evolves parameters of a program with fixed structure
- __Evolution strategies__: Evolves vectors of real numbers
- TODO

## Weaknesses
- Limited theoretical and mathematical analyses - but is a growing field of
study
- Considered slow for real-time applications and even for large offline problems
  - Newer faster hardware and parallel processing has improved performance

## Features
- Population based search algorithm
  - Search performed using multiple candidate solutions
  - Conducted in parallel over search space
- Avoid converging to local optima
- Use exploration and exploitation of promising areas
- May be used together with other approaches (known as a hybrid)

## Genetic algorithms
1. Generate an initial population
  - Size is a parameter
  - Individuals are generated randomly
2. Calculate _fitness_ values for each individual
3. Reproduce: Select parents - pairs of candidate solutions from population
4. Recombine: Crossover between parents
  - With probability p_c
5. Mutate: Alter offspring/children
  - With probability p_m
6. Replace population
  - By filtering from children
7. Calculate _fitness_ values for each individual
8. If termination criteria not met, go to 2

### Components

1. Encoding
TODO

#### Representation
- _Haploid structure_: Each individual contains one chromosome
- _Fitness value_: Find from calculating objective function value
- _Chromosome length_: fixed number of genes
- Binary encoding for each gene - allele value in {0, 1}
- _Generation_: an iteration

#### Initialisation
- Random allele values

#### Reproduction
- aka Mate/parent selection
1. Select individuals 
  - Use selection pressure to avoid randomness
  - Focus on creating high quality children
  - eg roulette wheel selection, tournament selection
2. Copy selecting individuals into a mating pool (can duplicate individuals)
3. Pairing individuals from population

# Selection Hyperheuristics
> Hyperheuristic: A search method or learning mechanism for selecting or
> generating heuristics to solve computationally difficult problem

- A class of methodologies for cross-domain search
- Is the control mechanism that performs a search on low level heuristic
algorithms (operators), which in turn search on potential solutions
- Hyperheuristics are also metaheuristics
- Are more general than lower level heuristics, which are designed to help solve
specific problems (eg MAX-SAT, Travelling Salesman)
- Aimed to be able to solve multiple problems
- Need an appropriate interface between hyperheuristics and operator
- Ultimate goal of creating a 'general solver' than can be applied to any
problem

- Algorithm selection learning
  - Use machine learning to find best method for solving a particular problem
instance
  - Use a classifier on the history of the performance of different operators

- Hyperheuristic framework
  - Problem domain barrier: an interface between the hyperheuristic and problem
domain
  - Can assume everything in the problem domain has been implemented
  - Hyperheuristic can track number of operators and their performance

- Characteristics
  - Operate on search space of heuristics rather than directly on a search
space of solutions
  - Aim to take advantage of strengths and avoid weaknesses of each heuristic
  - No problem specific knowledge is required during its search
  - Easy to implement, practical to deploy (easy, cheap, fast)

## Classification
- Selection
  - Have a predefined (mostly human designed) list of operators
  - Operators could be constructive/perturbative
- Generation
  - Create new (constructive/perturbative) heuristics

- Online learning
  - Adapt to each problem instance while solving it
  - eg reinforcement learning
- Offline learning
  - Use a sample training set
  - Feedback is gathered from training instances
  - Applies learnt feedback to unknown instances
  - eg classifiers

## Software tools
- [ECJ](https://cs.gmu.edu/~eclab/projects/ecj/)

## HyFlex
- Hyperheuristics flexible interface
- Hyperheuristic layer
  - Deciding which low-level heuristic to apply
  - Which solution to apply it to
  - At which location so store the new solution
    - Based on history of visited solutions and objective values
- Domain layer
  - Set of low-level heuristics
  - List of solutions
  - Evaluation/objective function
  - Problem instance

# Cross-domain heuristic search

## Iterated multi-stage selected heuristic
- Single point based search - crossover operators ignored
- Discrete values for IoM and DoS are made and are randomly chosen from
- Parameters are kept after improvements, randomised otherwise
- Uses _Stage 1_ and _Stage 2_ hyperheuristics
  - Randomly stop

### Stage 1
- Maintain score for each low-level heuristic (score_i)
1. Select a low level heuristic i with probability of ratio of score_i to
sum of score of other low-level heuristics
- Apply chosen heuristic
- Accept/reject based

### Acceptance
- Threshold acceptance - accept if better than a certain multiple of current
score
- Threshold range increases if improvements are not found after several
iterations

### Stage 2
- Pair up heuristics to create new ones (_test_)

## Graph-based hyperheuristic
- General framework (GHH) employ a set of low level contructive graph colouring
heuristics

### Exam timetabling problem
- __Nodes__ = exams
- __Edges__ = share pupils

### Graph colouring heursitics
- __Largest degree__: colour nodes in
  - descending order of degree
  - descending order of enrolement

### In hyperheuristics
- 
