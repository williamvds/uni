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

- Aims to find the __best__ possible decision/solution in any given set of
circumstances
- In most cases, the __best__ is unattainable

> Global optimum: The best possible solution

> Local optimum: The best solution in a certain neighbourhood

> Neighbourhood: A subsection of the entire search space.
> The neighbourhoods of one solution is the set of solutions that can be
> reached from x by applying a move operator
>>>>>>> a515fb6... aim notes: move acceptance, parameters

> Global optimum: Better than all other solutions (ie the best)

- Optimisation aims to maximise or minimise the objective function value of
the returned solution

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

### Pros
- Very easy to implement
- Only needs
  - Representation
  - Evaluation function
  - A measure that defines neighbourhoods

### Cons
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
  1. Generate a list of neighbouring solutions
  - Find the best of neighbours
  - Check if _accessible_
  - If accessible, accept it and replace current solution, otherwise
continue with next best neighbour

### Eg MAX-SAT design
- __Initialisation__: Random
- __Move operator__: A hill climbing / local search algorithm
- __Neighbourhood definition__: Eg, attainable by single bit flip
- __Memory__: Associate tabu status (boolean) with each variable of in problem
  - tabu = changed in last `T` steps, where `T` is tabu tenure
  - For each variable `xᵢ` store number of the search step when it was last
changed (`tᵢ`).
  - tabu = `c - tᵢ < T`, where `c` is current search step number

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

# Move acceptance
- In heuristic search, there decisions need to be made on whether to accept a
move to a new solution
- __Approaches__
  - __Static__
    - Fixed value and/or no dependency on time/iteration or history
    - Constant acceptance threshold
  - __Dynamic__
    - Changes over time/iterations
    - Same acceptance threshold for same candidate solution at the same
  time/iteration
  - __Adaptive__
    - Changes depending on time/iteration and/or history
    - Possibly different acceptance threshold for same candidate solution at the
same time/iteration

## Stochastic
- Randomness is involved
- eg, accept with random probability

### Simulated Annealing
- Analogous to the cooling of a molten metal
  - Slower cooling creates a more organised molecular crystal alignment
- Initially accept many worsening moves
- Gradually decrease rate at which worsening moves are accepted
1. Generate an initial _temperature_
2. Perturb current solution
3. Accept if better or with Boltzman probability - _e_^(delta/temp)
  - Lower temperature means fewer worsening accepted
4. _Cool_ temperature according to _cooling schedule_

- __Geometric Cooling__
  - α: Cooling rate - fixed value less than 1
  - temp = α*temp
- __Lundy & Mees__
  - Parameter β
  - temp = temp/(1+ β*temp)
- Could reheat with a certain rate after a number of non-improving iterations

## Non-stochastic
- No randomness involved

### Basic
- Compare objective function values of solutions
- __Static__: accept...
  - all moves
  - only improving moves (OI)
  - improving and equal moves (IE)
- __No dynamic examples__
- __Adaptive__
  - __Late acceptance__: compare current solution quality with that of the solution
a certain number iterations ago

### Threshold
- Compare objective function values to a _threshold value_
- __Static__: accept worsening solution if no worse than threshold
- __Dynamic__
  - Great Deluge
    - Parameters: _rain up speed_, _water level_
    - Tighten threshold upon each accepted solution
  - Flex Deluge
- __Adaptive__
  - Record to Record Travel (RRT)
    - Fixed _deviation_
    - Accept solutions with value `best ± deviation` (depending on min/maximisation)
  - Extended Great Deluge
    - Extra parameters: _initial boundary level B₀_, _decay rate •B_
    - Use B as threshold
    - Decrease boundary B by •B each iteration
    - On many iterations without improvement:
      - Reset B to value of current solution
      - Set new •B based on secondary cooling parameter
  - Modified Great Deluge

## Parameter setting

### Tuning
> Parameter control: Modifying parameters during the search

> Parameter tuning: Values are fixed throughout run, good values found
> experimentally
- Traditional approaches
  - Arbitrary setting
  - Trial & error using intuition
  - Use theoretical studies
  - A mixture of the above
- Sequential tuning: fix parameter values successively
- Meta-optimisation: use a metaheuristic to find 'optimal' settings
- Design of Experiments
  - Systematically finding relationship between controllable and uncontrollable
factors
  - Find how settings affect performance
  - Sampling - need to choose what values to test
  - __Random__: pick random values in the continuous range of possible settings
  - __Latin hyper-cube__: Turn 2D settings range into grid, ensure at most one
sample is used from each _cell_
  - __Orthogonal sampling__: Divide Latin hyper-cube into subgrids, pick
precisely one sample from each subgrid

- __Taguchi Orthogonal Arrays__
  1. Select control parameters
  - Select number of level settings for each parameter
  - Select a suitable orthogonal array based on 1 and 2
  - Conduct experiments
  - Analyse results
  - Determine optimum levels for individual parameters
  - Confirmation experiment

# Scheduling
> Scheduling: The process of planning, controlling, and optimising work and
> workloads in a production/manufacturing process

- `i = [1, m]`: Number of machines
- `j = [1, n]`: Number of jobs
- `(i,j)`: A processing step (operation) of job `j` on machine `i`
- `pᵢⱼ`: Processing time of job `j` on machine `i`
- `dⱼ`: Due date - time job `j` must be completed by
- `wᵢⱼ`: Weight - importance of job `j` relative to other ones

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
- Release date `rⱼ`: earliest time at which job `j` can start being processed
- Sequence dependent startup times `sⱼₖ`: setup time between `j` and `k`
- Breakdowns `brkdwn`: machines are not continuously available
- Permutation `prmu`: eg order of queue processing (FIFO)

### γ examples
- Completion time `Cᵢⱼ`: of job `j` on machine `i`
- Time when job exits system `Cⱼ`
- Lateness of `j` `Lⱼ = Cⱼ - dⱼ`
- Tardiness `Tⱼ = max(Cⱼ - dⱼ, 0)`
- Unit penalty `Uⱼ = 1 if Cⱼ > dⱼ otherwise 0`

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

- __Chromosome__: A candidate solution (aka individual)
- __Population__: A set of _individuals_ currently 'alive' - being considered
- __Evolution__: Each population is are evolved from one generation ( _iteration_ )
to another depending on their _fitness_ 
  - Fitness is how close it is to the optimal solution, depends on objective
function value
- Ideally the last generation will contain the best solution(s)

## History
- __Genetic algorithms__: Evolving bit strings
- __Evolutionary programming__: Evolves parameters of a program with fixed structure
- __Evolution strategies__: Evolves vectors of real numbers
- __Genetic programming__: Evolves computer programs in tree form
  - __Gene expression programming__: Computer programs of different sizes
are encoded in linear chromosomes of fixed length)
  - __Grammatical evolution__: Evolves solutions with respect to a specified
grammar

## Weaknesses
- Limited theoretical and mathematical analyses - but is a growing field of
study
- Considered slow for real-time applications and even for large offline problems
  - Newer faster hardware and parallel processing has improved performance

## Features
- Population based search algorithm
  - Search performed using multiple initial candidate solutions
  - Conducted in parallel over search space
- Avoid converging to local optima
- Combine exploration and exploitation of promising areas
- May be used together with other approaches (hybrids)

## Genetic algorithms
1. Generate an initial population
  - Size is a parameter
  - Individuals are generated randomly
2. Calculate _fitness_ values for each individual
3. Reproduce: Select parents - pairs of candidate solutions from population
4. Recombine: Crossover between parents
  - With probability p_c
5. Mutate: Alter offspring/children
  - With probability pₘ
6. Replace population
  - By filtering from children
7. Calculate _fitness_ values for each individual
8. If termination criteria not met, go to 2

### Representation
- _Haploid structure_: Each individual contains one chromosome
- _Fitness value_: Find from calculating objective function value
- _Chromosome length_: fixed number of genes
- Binary encoding for each gene - allele value ∈ {0,1}
- _Generation_: an iteration

### Initialisation
- Random allele values

### Reproduction
- aka Mate/parent selection
1. Select individuals 
  - Use selection pressure to avoid randomness
  - Focus on creating high quality children
  - eg roulette wheel selection, tournament selection
2. Copy selecting individuals into a mating pool (can duplicate individuals)
3. Pairing individuals from population

- __Roulette wheel selection__
  - Probability of selection of each individual is its fitness over the total
of all fitness scores
  - Fitter individuals have a higher chance of selection
  - Randomly select number in [0,total fitness]
  - Add up fitnesses of individuals incrementally, return individual
in which the random number lies in its range
- __Tournament selection__
  - Choose a certain number of individuals strictly less than the size of the
population
  - Return one of the most fit individuals

### Recombination/crossover
- __One Point Crossover (1PTX)__
  - Generate random number in [0,1)
  - If it not less that _crossover probability_ `p_c`, just return the parents
  - Select a random crossover point in [1,chromosome length]
  - Swap the segments between pairs to form two new individuals
- __PMX__: TODO
- __OX__: TODO
- __CX__: TODO

### Mutation
- Provides diversity - allowing exploration of different regions of search
space and escaping from local minima
- Loop through alleles of all individuals, choose ones randomly for mutation
- Mutation rate is usually very small (&gt 0.001)
- With probability as `1/chromosome length` the expectation is that one
gene per allele will be mutated

### Replacement
- Need to choose which individuals to keep to maintain fixed population size
- __Generation gap (G)__: controls fraction of population to be replaced each
generation [1/N,1]

## Memetic algorithms
- An extension of genetic algorithms
- Includes local search at some point in the iteration (eg, after mutation)
- __Pros__: Can perform better than normal GEs
  - Depends on aptitude of local search algorithm, dependent parameters

### Multimeme memetic algorithms
- Implement _self adaptation_ in memetic algorithms
  - Operators and settings are changed during the evolutionary search process,
upon receiving feedback
- Idea is to __co-evolve__ genetic and _memetic_ material
- __Probability__: Save probability of applying each operator
  - Done by Davis
  - Performance of algorithm over last few generations is used to calculate it
- __Memeplex__: An additional representation for memetic material
  - Stored alongside allele in individuals
  - Can store many details, including search operator, when to apply it,
where, and other parameters
  - Crossover/mutate memetic material alongside genetic material
  - __Innovation Rate (IR)__: Probability of mutating a meme
    - 0 = no innovation - memes do not change over iterations
    - 1 = all memes available are used equally
  - __Concentration of a meme cᵢ(t)__: The total number of individuals carrying
meme at the given generation
  - __Evolutionary activity of a meme cᵢ(t)__: The accumulation of meme
concentration until a given generation
- __Pros__: 
  - Effective memes are automatically identified and used more often
  - More quickly find good solutions
  - Experiments show optimal solution is quickly found
- __Con__: A simple MA using the best meme is superior
  - The MA takes some iterations to learn the best ones
  - Some iterations are spent using useless operators
  - These iterations are wasted

## Genetic programming
- __Goal__: Get a computer to perform a task without telling how
- Automatically creates working computer program from a high level problem
statement
  - Known as program synthesis/induction
- Iteratively transforms a population of programs
- __Pros__:
  - Uses a more natural representation for solutions (a program)
  - Fixed length character strings are overly restrictive for solution
representations

### Parse trees
- __Internal nodes__: functions (+, -, if, etc.)
- __Leaves__: arguments

### Generating programs
- __Function set__: Set of functions that can be used
  - eg. {+, -, *, /}
- __Terminal set__: Set of values that can be used in leaves
  - eg. integers, named variables
1. Randomly select either a function or terminal
2. If function generated, randomly generate programs as arguments

### Mutation
1. Pick a random node
2. Delete it and its children, replace with a new sub-program

### Crossover
1. Pick a random node
2. Swap them

# Selection Hyperheuristics
> Hyperheuristic: A search method or learning mechanism for selecting or
> generating heuristics to solve computationally difficult problem

- A class of methodologies for cross-domain search
- Aim to provide a _one-fits-all_ algorithm for search problems, which can
be applied to any problem domain
- Performs a search on low level heuristic algorithms (operators)
  - Operators perform actual search on potential solutions
  - Operators are more specific, designed to solve specific problems
(eg MAX-SAT, Travelling Salesman)
- Hyperheuristics are also metaheuristics
- __Algorithm selection learning__
  - Use machine learning to find best method for solving a particular problem
instance
  - Use a classifier on the history of the performance of different operators
- __Hyperheuristic framework__
  - __Problem domain barrier__: an interface between the hyperheuristic and problem
domain
  - Can assume everything in the problem domain has been implemented
  - Hyperheuristic able to apply available operators, gauge their
performance

## Characteristics
- Operate on search space of heuristics rather than directly on a search
space of solutions
- Aim to take advantage of strengths and avoid weaknesses of each heuristic
- No problem specific knowledge is required
- Easy to implement, practical to deploy (easy, cheap, fast)
- Can use existing heuristics and computer generated ones

## Classification
- __Selection__
  - Have a predefined (mostly human designed) list of operators
  - Operators could be constructive/perturbative
- __Generation__
  - Create new (constructive/perturbative) heuristics
- __Online learning__
  - Adapt to each problem instance while solving it
  - eg reinforcement learning
- __Offline learning__
  - Use a sample training set
  - Feedback is gathered from training instances
  - Applies learnt feedback to unknown instances
  - eg classifiers

## Heuristic selection methods
- __Greedy__: Apply all available heuristics to the solution, pick the solution
with the best improvement
- __Reinforcement Learning__: Keep a score for each heuristic, pick the one
with highest score
  - A machine learning technique
  - Inspired by reward and punishment psychological theory
  - Improving moves increments score, otherwise score is decremented
- __Choice Function__
  - Record performance metrics:
    1. Individual performance
    - Performance when combined with other heuristics
    - Elapsed time since being applied
  - Fₜ(hⱼ) = αₜf₁(hⱼ) + βₜf₂(h_k, hⱼ) + γₜf₃(hⱼ)
  - fₙ is the respective performance metric
  - Parameters alpha , β, and γ control importance of each metric [0,1]

## Misconceptions (opinionated)
- Hyperheuristics...
  - do not require parameter tuning
  - are all tested
  - can be applied to new domains easily
  - should not deal with domain-specific information (i.e. only objective value)

# Cross-domain heuristic search

## Iterated multi-stage selected heuristic
- Single point based search - crossover operators ignored
- Discrete values for intensity of mutation (IoM) and depth of search (DoS) are
are randomly chosen in [0,1]
  - Random value from these discrete values
- Parameters are kept after improvements, otherwise randomised
- Uses _Stage 1_ and _Stage 2_ hyperheuristics
  - With a specific probability, randomly apply stage 2 after stage 1 in each
iteration

### Stage 1
- Maintain score for each low-level heuristic (scoreᵢ)
- Ends if a duration s₁ is exceeded without improvement
1. Select a low level heuristic i with probability of ratio of
scoreᵢ/(Σ scoreₖ ∀k)
- Apply chosen heuristic
- Accept/reject based on adaptive threshold acceptance method

### Acceptance
- __Good design__
  - Balance exploration and exploitation
    - Use multiple operators, some that use learning, others that done
  - Accept worsening moves to escape local minima
    - Increasingly relax acceptance criteria when iterations keep resulting in
no improvement
  - Pair up heuristics to create 'new' heuristics (relay hybridisation)
- __Threshold acceptance__
  - Accepted if better than current solution
  - Accept if better than (1+ϵ) * best objective function value
    - ϵ = (floor(log(f(best))) + cᵢ)/f(best)
    - ϵ is updated if no improvement for a duration d

### Stage 2
- Pair up heuristics to create new ones (_test_)

## Graph-based hyperheuristic
- General framework (GHH) employ a set of low level constructive graph colouring
heuristics

### Exam timetabling problem
- __Nodes__ = exams
- __Edges__ = clashing - they share pupils
- __Colors__: assigned time periods
- __Objective__: assign different colors to adjacent nodes, minimising colors
used

### Heuristics
- __Tabu search hyperheuristic__: High level Tabu search
  - __Neighbourhood operator__: randomly change two heuristics in heuristic list
  - __Objective function__: quality of solutions built by heuristic list
  - __Tabu list__: Forbid the same heuristic list
- __Largest degree__: Give colors to nodes in descending order of degree
- __Largest enrolment__: Give colors to nodes in descending order of enrolment

# Generation Hyper-heuristics

## Index policies
- Giving a score to each possible choice, independent of other options
  - Option with the highest index value is taken
  - Need a rule to break ties (eg, take first available option)
- Are a special case, but in some situations can be optimal, or at least very
good

## Generation hyperheuristics

## Generating heuristics
- Space of functions in GP
  - is hard to understand
  - is potentially biased based on representation
- Alternative - matrix representation
  - Eg, in bin packing
  - All item sizes and residual capacities are integers, so `f(r, s)` is
a large matrix `M(r, s)` of _parameter values_
  - Just use lower diagonal where `r >= s`

# Advanced topics

## Single objective hyper²-heuristic
- Many real-world data are multidimensional
  - Very high-dimensional with a large amount of redundancy
- Multi-dimensional arrays representing such data describe a _tensor_
- Example applications include signal processing, psychometrics, social network
analysis

### Tensor factorisation
- Multiple decomposition methods
- Can use Canonical Polyadic (CP)
  - Projects 3D data onto 1D
  - Helps discover latent structures in data
  - Quantifies relationship between pairs of different components
- Can apply tensor analysis by applying each heuristic
- Apply CP
- Order heuristics by 

## Apprenticeship Learning
- aka Inverse reinforcement learning, learning via demonstration
- Policy is undefined - instead learn from expert to find it
- Theoretically possible to outperform the expert
- Can be applied to heuristic search
- Machine learning/analytics/data science helps improve hyperheuristic search
processes
  - Problem features vs solution/state features
  - Offline vs online learning
- Still a lack of benchmarks
- Automated design of search methodologies is extremely challenging
  - Still need mathematical and theoretical understanding

# Fuzzy Sets
> Fuzzy set: A set whose membership function is mu_A(x): X -> [0, 1]
> Elements are not simply a member nor not a member of the set, but have an
> assigned degree

- Introduced by Lotfi Zadeh
- Are extensions of conventional (crisp) sets that allow everyday notions to be
represented

## Compared to classical (aka crisp) sets
- Elements of the universal set `X` are defined to be or not to be members of
a set `A` by a characteristics function
- For a given set `A`, this function assigns value `μ_A(x)` to every `x` in `X`
- `μ_A(x): X -> {0,1}`, 0 iff `x` is in `A`, 1 otherwise
- Can create a diagram visualising which ranges map to 0, and those which map
to 1
- Eg, defining tall people - set an arbitrary lower limit of height, above which
people are considered tall
- Instead of a hard limit, a spectrum of height can be defined, measuring the
_degree_ of height

## Notation
- `A = μ₁/x₁ + μ₂/x₂ + ... + μₙ/xₙ`
- or `A =  Σ_(i=1,n) μᵢ/xᵢ`

## Meaning of fuzzy grades
- Fuzzy memberships are not probabilities - eg, not applicable to height
- Fuzzy membership function values can instead be interpreted as compatibilities
- Eg, given two bottles, A is _drinkable_ with probability 0.9, and B is
_drinkable_ with fuzzy membership 0.9
  - There is a 10% chance Bottle A is not drinkable
  - Bottle by is close to fully drinkable

## Linguistic Variables
> Linguistic Variable: a collection of fuzzy sets representing linguistic terms
> of a concept

## Components
- `X`: The name of the variable (eg height)
- `T`: The set of terms, each being a fuzzy variable (eg short, medium, tall)
- `U`: The universe of discourse of all terms, associated with base variable `u`
  - Effectively the range of values that can be used as boundaries for each term
- `G`: A syntactic rule (grammar) for generating composite terms (eg very short)
- `M`: A semantic rule for associating each term with its meaning (fuzzy set)

### Example: Age
- `X` = Age
- `U = [0, 100]`
- `T` = young + very young + not young + middle-aged + ...
- Some terms are atomic (young)
- Some terms are composite (not young)

## Hedges
- A qualifying word added to a term, indicating a minor modification to its
meaning
- Eg _very_, _slightly_, _somewhat_, _more or less_, etc
- __Concentration__: Squaring membership function concentrates the range -
_very_
- __Dilation__: Square-rooting membership function decreases concentration - 
_somewhat_

## Membership functions
- Meaning of terms such as M(young) are often defined by functions
  - Could be defined by enumeration (look-up table) instead
- When there is a function...
  - M can be thought of as a set of membership functions
  - Names of terms are related to the meaning of the terms
  - Usually written as young = ...

### Triangular
- __Parameters__: Left, center, right
- `low = trimf(x, c(0,0,5))`

### Trapezoidal
- __Parameters__: Left bottom, Left top, Right top, Right bottom
- `low = trapmf(x, c(0,0,1,4))`

### Gaussian
- __Parameters__: Center, standard deviation
- `low = gaussmf(x, c(1.5,0))`

### Sigmoid
- __Parameters__: Slope, half-point
