# Introduction to the Operating System
> Operating system: A layer of indirection on top of the hardware

## Properties of an OS
- Has access to the full capabilities of the hardware
- Provides...
  - abstractions for application programs (eg file systems)
  - cleaner and easier interface to the hardware - hiding 'bare metal'
  - common routines
- Most programs rely on them
- Hardware (below) Operating system (below) Applications
- Good to know how the OS' services/abstractions are implemented

## Example scenarios where the OS is used
__Reading a file in Java__
- __File systems__: abstract where a file is physically writing on the disk, and how it is retrieved
- __Platform abstraction__: the instructions look the same regardless of the device running it
- __Concurrency__: managing when multiple programs access the same file simultaneously
- __Security__: denying access when necessary

__Loading a large array of data__
- Deciding where to store it in memory and protecting that memory from unauthorised access
- Managing situations when more memory than physically available is required
- Managing when only a part of the array is in use
- Managing when other processes start running

## The OS as a resource manager
- Many modern OSs use multi-programming 
  - Can run multiple programs simultaneously
  - Improves user experience and maximise resource utilisation
  - Disks are slow - just waiting for I/O wastes many potential instructions

- Multi-programming affects operating system design
  - Need to allocate and share resources - including CPU, I/O 
  - Share resources fairly and safely between competing processes

- Execution of multiple processes needs to be interleaved with one another
  - Context switches and process scheduling requires... 
  - mutual exclusion
  - deadlock avoidance
  - protection...

# Process management
- Address spaces, interrupts
- OS structures/implementation

## CPU design
- Basic cycle is fetch-decode-execute (but usually includes pipelines or superscalar systems)
- Each model has their own instruction set
- Have a set of registers
  - Very fast memory close to the 'core'
  - Used to store data and for specific functions, including...
  - the program counter
  - program status word
- Compiler/programmer decides what to keep in the registers
- Context switching must save and restore CPU's internal state, including registers

## The Memory Management Unit (MMU)
- Running the same program multiple times, printing the memory address of a variable, will yield 
the exact same address - even simultaneously (in most operating systems)
- Variables are simply mnemonic names for memory addresses
- The compiler...
  - assigns a memory address to variables at compile time
  - does not know where in physical memory the process will run (multiple processes run on modern 
machines) 
  - assumes it will start at `0` (in logical address space)
- Rarely, a process may run at physical address `0`
- Otherwise, `physical address = logical address + offset`
- Modern computers use logical and physical memory addresses
  - Logical address space: `0` to `MAX64` (where `MAX64` is theoretically up to 16 exbibytes on 64 
bit machines)
  - Physical address space: `0` to `MAX`, (where `MAX` is determined by amount of physical memory)
- Address translation takes place in the MMU - logical addresses are converted to physical
- Context switches between processes... 
  - invalidates the MMU
  - invalidates registers, cache
  - requires the internal state of the current process to be saved, and the new one's restored

## Interrupts
- Temporarily pause a process' normal operation
- Interrupts only performed at the end of the fetch-decode-execute cycle - after the instruction 
has been executed
- Types include...
  - Timer interrupts (by CPU clock)
  - I/O interrupts (for I/O completion or error codes)
  - Software generated (eg errors and exceptions)

### Timer interrupts
1. Timer generates an interrupt
-  CPU finishes current instruction and tests for interrupts
-  Transfer to interrupt service routing: 
  1. save current process state - status word, program counter
  -  set program counter to interrupt service routine
  -  save registers and other state information
-  Carry out interrupt service routine (aka the scheduler)
-  Restore next process to run

- Can be used to trigger context switches after a set time (known as the _time slice_)

## Computer architecture
### Multi-core and hyperthreaded processors
- Modern CPUs contain multiple cores and are often hyper-threaded
- Evolution in hardware affects operating system design
- Need to provide process scheduling accounting for load balancing and CPU affinity
- Cache coherency becomes important

### Memory
- Hierarchies are used to balance cost and performance
  - Fast and expensive memory used for caching
  - Slow and inexpensive memory used for long term storage
  - Includes registers, L1/L2 cache, main/core memory, disk etc
- L2 cache can be shared or dedicated to individual cores
- Cache management mainly done by hardware
- CPU can only access main memory directly - files have to loaded into it

## OS structures and implementation
- OSs contain a lot of functionality, including...
  - Processes - management, scheduling, context switching, etc
  - Memory - management, virtual memory, etc
  - File systems
  - I/O management

- OS can be structured in _micro_ and _monolithic_ kernels

### Micro kernels
- Provide minimal kernel functionality
- Non-essential functionality is extracted from the kernel
  - Communication, memory management, and CPU scheduling likely to be included
  - File system, GUI, device drivers are likely to be user processes
- Pros
  - Easier to extend
  - More portable
  - Usually more reliable
- Cons
  - More frequent system calls and kernel traps = more overhead from mode switches

- For example
  - Some Unix versions
  - Mac OS X
  - Minix
  - Early versions of Windows (NT4.0) (partially)

### Monolithic kernels
- All procedures linked into one single executable, runs in kernel mode
- Cons
  - Difficult to maintain due to size

- Examples
  - Current versions of...
  - Windows
  - Linux

# Processes
> Process: a running instance of a program

- Programs are passive - they are stored on a disk
- Process has associated control structures, may be active, may have resources (I/O devices, 
memory, processor)
- Control structures... 
  - register a process with OS
  - are process control blocks (PCBs), stored as entries in the OS's process table 
- PCBs contain info to administer process, necessary for context switching

## Memory layout
- __Code__: aka Text, can be shared between processes running the same code
- __Data__
- __Stack__: Last in First Out structure - local variables removed once a function exits
- __Heap__: dynamic memory for data

| STACK |
|:-----:|
| ...   |
| HEAP  |
| DATA  |
| TEXT  |

- The top of the table is MAX (logical address) and the bottom 0
- Stack and heap are placed at opposite ends to allow them to grow
- Some OSs use address space layout randomisation TODO

## Process states and transitions
### States
  - __New__: just created (has PCB), waiting to be admitted to ready queue, may not yet be in memory
  - __Ready__: waiting for CPU to become available
  - __Running__: controls the CPU (or a core)
  - __Blocked__: process cannot continue, eg is waiting for I/O
  - __Terminated__: no longer executable, though data structures including PCB may be temporarily 
  preserved
  - __Suspended__: process is swapped out

### Transitions
- __New__     to __Ready__:  process admitted and OS commits to execution
- __Ready__   to __Running__: process selected by process scheduler
- __Running__ to __Blocked__: process needs to wait for interrupt or carried out a system call
- __Blocked__ to __Ready__: event waited for happens, eg I/O operation finished
- __Running__ to __Ready__: process is preempted, eg by timer interrupt or pause
- __Running__ to __Terminated__: process has finished, eg ended or encountered exception

- Interrupts, traps, and system calls lie on the basis of transitions

## Multi-processing
- Modern computers run multiple processes 'simultaneously'
- In a single processor system, instructions of individual processes are executed sequentially
- Processor alternates processes using context switches
- True parallelism requires multiple processors

### Process Control Blocks
- __Identification__: ID, user, parent ID
- __Control information__: process state, scheduling information, etc
- __State information__
  - user registers
  - program counter
  - stack pointer
  - program status word
  - memory management information
  - files
  - etc

- Are kernel data structures - protected and only accessible in kernel mode
- Allowing user applications to access them directly could compromise their integrity 
(eg could monopolise the CPU)
- OS manages them on the user's behalf through system calls (eg to set priority)

### Process tables
- __Process__: holds control blocks for each process
- __Memory__: info about memory allocation, protection, virtual memory
- __I/O:__ availability, status, transfer information
- __File:__ location, status

- Maintained by kernel and usually cross referenced

### Context switching
> Context switch: Save state of old process and loads the state of the new process

1. __Save process state__: program counter, registers, etc
-  __Update PCB__: change status from running to ready/blocked
-  Move PCB to appropriate queue (ready/blocked)
-  __Run scheduler__: select new process
-  __Update PCB__: change status to running
-  Update memory management unit
-  Restore process

- Con: Creates overhead in execution - time is spent saving, reading, re-loading register states

### Time slicing
> Time slice: the maximum duration a process can keep executing before being preempted

- Short time slices provide...
 - Good response times - less time before a process starts executing
 - Low effective utilisation - more time spent context switching

- Long time slices provide...
  - Low response times
  - High effective utilisation

## Creating and terminating processes
- Use system calls - usually wrapped around OS libraries (eg libc) following a well-defined API 
(eg POSIX, WIN32)

- Unix: `fork()` - generates exact copy of parent
- Windows: `NTCreateProcess()`
- Linux: `Clone()`

- `fork()`:
  - Returns process ID to the parent
  - Returns 0 to the child process

- System calls are necessary to notify the OS the process has terminated:
  - Resources de-allocated
  - Output flushed
  - Process administration may have to performed
  - Unix/Linux: `fork()` or `kill()`
  - Windows: `TerminateProcess()`

# Process scheduling
- The OS is responsible for managing and scheduling processes:
  - When to admit to the system ( __New__ to __Ready__ )
  - Select next process to run ( __Ready__ to __Running__ )
  - Decide when and which process to interrupt ( __Running__ to __Ready__ )

- Scheduler (aka dispatcher) decides which process to run
- Scheduler uses a scheduling algorithm to do so
- Type of algorithm used is influenced by the type of OS (eg real time, batch)

## Evaluation
- User-oriented criteria
  - __Response time__: time between creating the job and it beginning execution
  - __Turnaround time__: time between creating the job and finishing it
  - __Predictability__: the variance in processing times

- System-oriented criteria
  - __Throughput__: number of jobs processed per hour
  - __Fairness__: equal distribution of processing and waiting time and avoiding keeping some processes
waiting excessively long (starvation)

- Criteria can conflict - eg improving response time may require more context switches, worsening 
throughput and increasing turnaround time

- Performance measures:
  - __Average response time__: average time of process start
  - __Average turnaround time__: average time taken for each processes to finish

## Scheduler types
### By time horizon
- __Long term__ 
  - Applies to new processes
  - Controls the degree of multiprogramming by deciding which process to admit and when
  - Good mix of CPU and I/O bound processes keeps all resources as busy as possible
  - Usually absent in modern popular OSs

- __Medium term__: controls swapping and the degree of multiprocessing

- __Short-term__: decide which process to run next
  - Manages the ready queue
  - Invoked very frequently, so must be fast
  - Usually called in response to clock interrupts, I/O interrupts, or blocking system calls

### By approach
- __Non-preemptive__
  - Processes are only interrupted voluntarily - eg I/O or a 'nice' system call like `yield()`
  - eg Windows 3.1 and DOS

- __Preemptive__
  - Processes can be interrupted forcefully or voluntarily
  - Requires context switches = overhead, so too many should be avoided
  - Prevents processes from monopolising the CPU
  - Most popular modern operating systems take this approach

## Scheduling algorithms
### First Come First Served (FCFS)
- aka First In First Out (FIFO)
- Non-preemptive
- Strict queueing mechanism - schedules in same order processes were added to the queue

- Pros
  - Positional fairness
  - Easy to implement

- Cons
  - Favours long processes over short ones
  - Could compromise resource utilisation - CPU vs I/O devices

### Shortest Job First
- Non-preemptive
- Starts processes in order of ascending processing time using a provided/known estimate of processing

- Pro: Always optimal turnaround time

- Cons
  - Starvation of long processes
  - Fairness and predictability compromised
  - Processing times have to be known beforehand

### Round Robin
- Preemptive version of FCFS - forces context switches at periodic intervals or time slices
- Run in order that they were added to queue
- Processes are forcefully interrupted by the timer
- If time slice is used partially, the next process start immediately

- Pros
  - Improved response time
  - Effective for general purpose time sharing systems

- Cons
  - Increased context switching = overhead
  - Can reduce to FCFS
  - Favours CPU bound processes (usually longer) over I/O processes (usually shorter)
    - Possibly prevented by working with multiple queues

- Length of time slice must be carefully considered
  - Short = good (low) response time = low throughput
  - Long = high throughput = bad (long) response time

### Priority Queues
  - Preemptive
  - Schedules processes by priority (saved in process control block)
  - Jobs of same priority run in Round Robin fashion
  - Pro: Can prioritise I/O bound jobs
  - Con: Low priority processes may be starved (if process priorities do not change)

## Multi-level feedback queues
- Multiple queues, for each priority level
- Different scheduling algorithm(s) can be used for individual queues
- Jobs can move between queues - migration policy between queues:
  - Lower priority queue if too much CPU time is used - prioritise I/O and interactive processes
  - Higher priority queue to prevent starvation and avoid inversion of control 

> Inversion of control/priority inversion: Where a high priority process is overwhelmed by lower 
> priority ones because they are using the same resources)

- Are highly configurable and offer significant flexibility

### Characteristics
- Number of queues
- Scheduling algorithms used for individual queues
- Migration policy between queues
- Initial access to queues

### Case study: Windows 7
- Interactive system
- Preemptive scheduler
- Dynamic priority levels
  - Two priority classes with 16 priority levels
  - __Real time__: fixed priority level
  - __Variable__: can have their priority temporarily boosted
- Use round robin within the queues

- Priorities based on _process base priority_ (0-15) and _thread base priority_ (±2 relative to process priority)
- Priority dynamically changes between _base priority_ and _maximum priority_
  - Interactive I/O bound processes receive larger boost
  - Boosting priorities prevents priority inversion

## Linux - the Completely Fair Scheduler
- Scheduling has evolved over different versions of Linux to account for...
  - multiple processors/cores
  - processor affinity
  - load balancing between cores

- Scheduling types
  - Real time tasks (for POSIX compliance)
    - Real time FIFO tasks
    - Real time Round Robin tasks
  - Time sharing tasks using a preemptive approach (similar to variable in Windows)

- Linux's scheduling algorithm for time sharing tasks is the Completely Fair Scheduler (CFS)

- Real time FIFO tasks...
  - have the highest priority 
  - are scheduled using the FCFS approach
  - are preempted if a higher priority shows up
- Real time round robin tasks are preemptable by clock interrupts and have an associated time slice
- Both approaches cannot guarantee hard deadlines

### Time sharing tasks - equal priority
- CFS divides the CPU time between all processes
- They will be allocated a time slice of `1/N * (available CPU time)`
  - eg, if `N = 5` each processes will receive 20% of the processor's time

> Targeted latency: Interval of time during which every process should run at least once
> Length of time slice and available CPU time are based on this

- Larger N means the context switch time becomes dominant, so a lower bound on the 'time slice' 
is imposed by the minimum granularity
  - A process' time slice can be no less than the minimum granularity, else response time will 
deteriorate

### Time sharing tasks - different priority
- Weighting scheme used to take different priorities into account
- Each process allocated a weight `w(i)` that reflects its priority
- The time slice allocated to the process is proportional to the percentage of allocated CPU time 
it has not yet used
- The tasks with the lowest proportional amount of used CPU time are selected first

## Multiprocessor scheduling
- On a single processor machine, scheduler only has to consider which process (/thread) to run next
- Scheduling on a multiprocessor/core machine requires deciding...
  - __Where__: which CPU to run a process on
  - __When__: what time to run a process

### Shared queues
- Single or multi-level queue shared between all CPUS
- Pros
  - Automatic load balancing
- Cons
  - Contention for the queues - locking required
  - Does not account for processor affinity - moving to a different CPU invalidates cache, and 
look aside buffers in MMU
- Windows allocates the highest priority threads to the individual CPU/cores

### Private queues
- Each CPU has a private (set of) queue(s)
- Pros
  - CPU affinity automatically satisfied
  - Contention for a shared queue is minimised
- Cons
  - Less load balancing
- Migrating between CPU queues is possible

### Related threads
- Some threads (of the same process) are cooperating - sending messages to one another
  - eg search algorithms
- Ideally these threads run simultaneously on multiple CPUs
  - Otherwise threads will have to wait until their next time slice to handle responses

#### Space scheduling
- N threads are allocated to N dedicated CPUs
- N threads are kept waiting until N CPUs are available
- Non-preemptive - blocking calls result in idle CPUs = less context switching overhead but results
in CPU idle time
- N can be dynamically adjusted to match processor capacity

#### Gang scheduling
- Time slices synchronised and scheduler groups threads together to run simultaneously
(as much as possible)
- Preemptive
- Blocking threads result in idle CPUs

# Threads
> Threads: Execution traces with which a process can share its resources, 
> running in the same resource environment

- Process contain...
  - resources - related ones grouped together
    - logical address space containing process image (program, data, heap, stack)
    - Files, I/O devices, I/O channels
  - execution trace - an entity that is executed

- Threads...
  - have their execution states - program counter, stack, and register states
  - have states and transitions (new, running, blocked, ready, terminated)
  - have a thread control block
  - share code
  - share data - global variables and memory
  - share files - one thread opens the file, all other threads can access it

- Some CPUs (hyperthreaded) have direct hardware support for multithreading
  - Can offer up to 8 hardware threads per core

- Pros
  - Less overhead to create/terminate/switch - address space is the same for threads of the same 
process
	- Inter-thread communication is easier/faster than interprocess - threads share memory by default
	- Share the same resources used by multiple activities
	- Carry out blocking tasks in parallel/concurrently - I/O and memory access 
	- No protection boundaries are required in the address space:
		- Threads are cooperating
		- Belong the same user 
		- Share a common goal

- Cons
	- Synchronisation has to be considered carefully

## Shared resources
- Shared between threads
  - Address space
  - Global variables
  - Open files
  - Child processes
  - Pending alarms
  - Signals and signal handlers
  - Accounting information

- Private to threads
  - Program counter
  - Registers
  - Stack
  - State
  - Local variables

## Implementation

### User threads
- Many to one - kernel only sees owning process
- Thread management performed in user space using user library
	- Creating, destroying, scheduling, thread control block manipulation
- Process maintains thread table managed by the runtime system without kernel's knowledge
	- Similar to process table
	- Used for thread switching
	- Tracks thread related information

- Pros
	- In user space - no mode switches required
	- Full control over the thread scheduler
	- OS independent - can use threads on OS' that don't support them
- Cons
	- Blocking system calls suspend the entire process - the threads are mapped onto a single process managed by the kernel
	- No true parallelism - process is scheduled on single CPU
	- Clock interrupts are non-existent - no preemptive interrupts
	- Page faults result in blocking the process

### Kernel threads
- One to one - kernel sees each individual thread
- Kernel manages threads, user application accesses threading facilities through API and system calls
	- Thread table is in kernel, containing thread control blocks - subset of process control blocks
	- If a thread blocks, the kernel chooses another thread from the same or different process
- Used by Windows and Linux

- Pros
	- True parallelism can be performed
- Cons
	- Frequent mode switches = lower performance
	- Greater overhead when dealing with null forks and signal waits compared to user threads

### Hybrid
- Many to many
- User threads multiplexed onto kernel threads
- Kernel sees and schedules a limited number of kernel threads
- User application sees user threads and creates/schedules these - unrestricted number

## Management
- Thread libraries:
  - Provide an API/interface for managing threads 
    - creating, running, destroying, synchronising, etc
  - Implementation:
    - User space = user threads
    - System calls - rely on kernel for thread implementations
  - Eg POSIX's PThreads, Windows Threads, Java Threads

- PThreads:
  - A specification that anyone can implement - defines a set of API function calls, including:
  - Can be implemented as user or kernel threads
  - `pthread_create`: create new thread
  - `pthread_exit`: Exit existing thread
  - `pthread_join`: Wait for existing thread with ID
  - `pthread_yield`: Release CPU
  - `pthread_attr_init`: Thread attributes (eg priority)
  - `pthread_attr_destroy`: Release attributes

# Concurrency
- Threads and processes that execute concurrently or in parallel can share resources
  - eg devices, memory - variables and data structures
  - Multiprocessing improves system utilisation
- A process/thread can be interrupted at any point in time - eg by timer, I/O
  - The process state (including registers) is saved in the process control block
- The outcome of programs may become unpredictable:
  - Sharing data can lead to inconsistencies - when interrupted whilst manipulating data
  - Outcome of a process may depend on order of execution
  - eg incrementing a counter - need to read, add, and store new value
  - If interrupted during concurrent processing each thread will have a different state

## Critical sections
> Race condition: When multiple threads/processes access shared data and the result is dependent on
> the order in which the instructions are interleaved

- A set of instructions in which shared resources between processes/threads (eg variables) are 
changed
- Mutual exclusion must be enforced for critical sections

> Mutual exclusion: Ensuring only one process at a time can be in the critical section

- Processes have to get 'permission' before entering their critical section
  - Request lock, hold lock, release lock

### Within the OS 
- Multiple processes/threads are running in the kernel
- Kernel processes can be interrupted
- Need to ensure that kernel data structures are not corrupted by concurrency issues due to race 
conditions
- Processes share resources, including memory, files, processor time, printers, I/O devices, etc
- Needs to provide locking mechanisms to implement/support mutual exclusion 
(and prevent starvation and deadlocks)
- Need to allocate and deallocate these resource safely - avoid interference, deadlocks, starvation

### Requirements for solving the critical section problem
- __Mutual exclusion__: only one process can be in its critical section at any point in time
- __Progress__: any process must be able to enter its critical section at some point in time
  - Processes/threads in the 'remaining code' do not influence access to critical sections
- __Fairness / bounded waiting__: processes cannot be made to wait indefinitely

- These must be satisfied, independent of the order in which sequences are executed

### Enforcing mutual exclusion
- __Software__: using Peterson's solution
- __Hardware__: using `test_and_set()`, `swap_and_compare()`
  - CPU instructions that check and modify values in one go = no risk of interruption

- Based on 
  - Mutexes
  - Semaphores
  - Monitors (software construct within the programming languages)

### Deadlocks
> Deadlock: Where each process/thread in the set is waiting for an event that only the other 
> process/thread in the set can cause

- Given two mutually exclusive resources X and Y, which can only be held by one process/thread at 
a time
- Threads A and B need to acquire both resources ( _locks_ ), and request them in opposite orders
- Such a sequence of events could occur in a multiprocess system:
  - A requests and acquires X
  - B requests and acquires Y
  - A requests Y
  - B requests X
  - Neither thread can continue
- Each deadlocked process/thread is waiting for a resource held by another deadlocked 
process/thread, which cannot run and hence cannot release the resources
- Can occur between any number of processes/threads and for any number of resources

- Conditions for a deadlock
  - __Mutual exclusion__: A resource can be assigned to at most one process at a time
  - __Hold and wait condition__: A resource can be held whilst requesting new resources
  - __No preemption__: Resources cannot be forcefully taken away from a process
  - __Circular wait__: There is a circular chain of two or more processes, waiting for a resource held
by the other processes

## Peterson's solution
- Software solution
- Worked well on older machines

- Two shared variables:
  - `turn`: indicates which process is next to enter its critical section
  - `boolean flag[2]`: indicates that a process is ready to enter its critical section
- Two processes (i and j) execute in strict alternation, can be generalised to multiple processes

- Pros
  - Satisfies all critical section requirements - mutual exclusion, progress, fairness
- Cons
  - Busy waiting is used - process loops endlessly while waiting for the lock to clear


- Eg, for thread 0:
    ```c
    flag[0] = true;
    turn = 1;
    while (flag[1] == true && turn == 1) {
      // busy wait
    }
    // critical section
    ...
    // end of critical section
    flag[0] = false;
    ```
- Thread 1 would use the same structure, but replacing `1` with `0` and vice versa

### Satisfying mutual exclusion
- Both `flag[i]` and `flag[j]` are true when they want to enter their critical section
- `turn` is a singular variable that can only store one value
- Hence, either `while(flag[i] && turn == i)` or `while(flag[j] && turn == j)` is true and at most 
one process can enter its critical section

### Satisfying progress and bounded waiting
- If process j does not want to enter its critical section
  - `flag[j] == false`
  - `while(flag[j] && turn == j)` will terminate for the process i
  - i enters critical section

- If both want to enter their critical section
  - Both flags are true
  - `turn` is either i or j - eg for `turn == j`
  - `while(flag[j] && turn == j)` terminates and i enters section
  - i finishes critical section - `flag[i] == false`
  - `while(flag[i] && turn == i)` terminates and j enters section

## Hardware solution
- Disable interrupts whilst executing a critical section and prevent interruption 
(eg form timers, I/O devices)
- _May_ be appropriate on a single CPU machine

- Atomic instructions:
  - `test_and_set()`
  - `swap_and_compare()`
  - Uninterruptible - done in one contiguous set of instructions
  - Used in combination with global lock variables, assumed to be `true` if the lock is in use

- Cons
  - Are hardware instructions and (usually) not directly accessible to the user - OS is meant to 
abstract this
  - Busy waiting
  - Deadlock is possible - if two threads request resources in opposite order
  - Insufficient on modern multi-core/processor machines

- OS uses hardware instructions to implement higher level mechanisms/instructions for mutual 
exclusion - ie mutexes and semaphores

## Mutexes
> Mutex: An approach for mutual exclusion provided by the OS

- Contains a boolean lock variable to indicate availability
- If `true` the lock is available - the process can enter critical section

- Manipulation functions:
  - `acquire()`: before entering a critical section - boolean set to `false`
  - `release()`: called after exiting the critical section - boolean set to `true` again
  - Both must be atomic - no interrupts should occur between reading and setting the lock
  - Process that acquires the lock must release the lock (in contrast to semaphores)

- Pros
  - Context switches avoided - good for short critical sections
  - Efficient on multi-core/processor systems when locks are held for a short time only

- Cons
  - `acquire()` calls result in busy waiting (appears to be OS dependent)
    - ie mutex is a 'spinlock'
    - Detrimental for performance on single CPU systems

## Semaphores
> Semaphore: An approach for mutual exclusion and process synchronisation provided by the OS

- Can be binary
- Or integer - 0 to N (counting semaphore)

- Manipulation functions:
  - `wait()`: Called when resource is acquired - the counter is decremented
  - `signal()`/`post()`: Called when resource is released - the counter is incremented
  - Both must be atomic - no interrupts should occur between reading and setting the counter

- Calling `post()` removes a process from the blocked queue if the counter is non-negative
  - State changed from blocked to ready
- Different queueing strategies can be employed to remove processes (eg FIFO)
- The negative value of a semaphore is the number of processes waiting for the resource
- `block()` and `wakeup()` are system calls provided by the OS

- Atomicity of `post()` and `wait()` can be achieved through...
  - use of mutexes
  - disabling interrupts in single CPU systems
  - hardware instructions
- Atomicity of those functions means busy waiting is moved from the critical section to `wait()` 
and `post()` - which are short

- Semaphores within the same process can be declared as global variables of the type `sem_t`
  - `sem_init()`: Initialises value of the semaphore
  - `sem_wait()`: Decrements value of semaphore
  - `sem_post()`: Increments the value of the semaphore

- Pros
  - No busy waiting - calling `wait()` will block the process when the internal counter is negative
    - Process joins blocked queue
    - Process state changed from running to blocked
    - Control transferred to the process scheduler

- Cons
  - __Context switch overhead__: If critical section is short context switch dominates
  - __Performance penalty__: From synchronising code
    - Synchronize only when necessary
    - Synchronize as few instructions as possible - otherwise you're delaying others from entering
their critical section
  - __Starvation__: Poorly designed queueing approaches (eg LIFO) may result in fairness violations
  - __Deadlocks__
  - __Priority inversion__: High priority process has to wait for the lower priority one to release a 
resource it requires
    - Can happen in chains
    - Can be prevented by implementing priority inheritance to boost the lower's priority

## Producer/consumer problem
- Producer(s) and consumer(s) share `n` buffers (eg array) that are capable of holding one item 
each (eg a printer queue)
- Can be bounded (size `n`) or unbounded size
- Producers adds items - goes to sleep if buffer is full
- Consumers remove items - goes to sleep if buffer is empty
- Manipulation of counter will need to be synced
- Counter (index) variable keeps track of the number of items in the buffer
- Simplest version of problem has one producer, one consumer, unbounded size

- Two binary semaphores/mutexes:
  - `sync` synchronizes access to the buffer (counter), initialised to 1
  - `delay_consumer` ensures that the consumer goes to sleep when there are no items available, 
  initialised to 0
  - Cons
      - Race condition - When consumer has exhausted the buffer, the produce can still increment 
count before consumer checks it

### Synchronisation problems
- Bounded buffer
  - eg with `n` consumers, `m` producers, fixed buffer size `N`
  - `sync`: boolean mutex/semaphore - enforce mutual exclusion when manipulating the buffer
  - `empty`: tracks number of empty spaces in buffer, initialised to `N`
  - `full`: tracks number of full spaces in buffer, initialised to `0`
  - `empty` and `full` are counting semaphores, updated as elements are removed/added respectively

### Dining philosophers problem
- 5 philosophers sitting on a round table
- Each needs 2 forks to be able to eat
- When hungry (in between thinking), the philosopher tries the acquire the forks on their left and 
right
- Reflects general problem of sharing a limited set of resources (forks) between a number of 
processes (philosophers)

#### Naïve solutions
- Pick up a fork and wait for a second one to become available
  - Have one semaphore per fork
  - If all start at the same time, they will all take the fork on the left = deadlock as each is 
  waiting for the fork on their right
  - Cons
      - Can avoid deadlock by putting forks down and waiting a random time
(similar to Ethernet networks)

- Put one spare fork in the center of the table
  - Each philosopher has a fork for themselves
  - Each philosopher waits for the spare to be free when hungry
  - Cons
      - Results in poor usage of resources

#### Ideal solution
- Store state of philosophers:
- `state[N]`: State of each philosopher - thinking, hungry, eating
- `phil[N]`: One semaphore per philosopher (each initialised to 0)
- `sync`: enforce mutual exclusion of the critical section
- Philosopher sleeps if one of their neighbours are eating
- Neighbours wake up the philosopher if they have finished eating

# Memory management
- Computers typically have memory hierarchies:
  - Registers, L1/2/3 cache
  - Main memory
  - Disks
- _Higher memory_ is faster, more expensive, and volatile
- _Lower memory_ is slower, cheaper, non volatile
- OS provides a memory abstraction
- Memory can be seen as one linear array of bytes/words

- OS is responsible for...
  - allocating/deallocating memory when requested by processes
  - keeping track of used/unused memory
  - distributing memory between processes and simulating an 'infinitely large' memory space
  - controlling access in multiprogramming
  - transparently moving data from memory to disk and vice versa

- Memory management has evolved - amount of memory available and used has greatly increased
  - Many of the early ideas underpin more modern memory management approaches (eg relocation)
  - Modern consumer electronics often require less complex memory management processes

- Partitioning: A process' memory can either be stored...
  - __Contiguously__: As a single block in physical (main) memory, without holes or gaps
  - __Non-contiguously__: Data divided into multiple blocks (or segments), spread around physical 
memory, not necessarily adjacent

> Contiguous: Connecting, without a break

## Mono-programming
> Mono-programming: Having a single partition for user processes

- One single user process in memory/executed at any point
- A fixed region of memory is allocated to the OS/kernel - remaining used by the single process
- eg used in MS-DOS
- Process has direct access to physical memory = no address translation
- Process always located in the same address space
- No protection between different user processes required
- Overlays enable the programmer to use more memory than available - load program incrementally

> Overlaying: Transferring a block of data/code into memory, replacing what is already there

- Common in embedded systems and modern consumer electronics - eg washing machines, microwaves, etc

- Cons
  - If a process has direct memory access it might be able to access OS memory
  - OS can be seen as a process - there's already multiple processes
  - Low utilisation of hardware resources (CPU, I/O, etc)
  - Mono-programming unacceptable as multiprogramming is expected on modern machines

- Can simulate multiprogramming through swapping
  - Swap process out to disk and load a new one (though context switches would become time 
consuming)

## Modelling multi-programming
- Given `n` processes in memory
- A process spends `p` percent of its time waiting for I/O
- CPU utilisation is `1 - (time all processes are waiting for I/O)`
- CPU utilisation is given by `1 - p^n`
- eg, given `p = .2`, we can achieve 100% CPU utilisation using 4 processes `(1 - .2^4)`
- CPU util increases with `n` and decreases with `p`
- More memory means space for more processes, which enables achieving higher util

- __Multi-programming improves CPU utilisation, and so memory management should support it__

- Caveats
  - Assumes all processes are independent (not always true)
  - Could build more complex models using the _queueing theory_, but could use this model for 
approximate predictions


## Partitioning

### Fixed partitions, equal size
- Divide memory into static, contiguous, and equally sized partitions, with fixed size and location
- Any process can take any (large enough) partition
- OS keeps track of which parts are being used, and which are free

- Pros
  - Allocation of fixed equal sized partitions to process is trivial
  - Very little overhead, simple implementation
  - Allows multiprocessing = better CPU util

- Cons
  - Low memory utilisation and internal fragmentation - parts may be unnecessarily large
  - Overlays needed if a program does not fit into partition (burden on programmer)

> Internal fragmentation: When part of a partition is not being used

### Fixed partitions, non-equal size
- Divide memory into static, non-equally sized partitions, with fixed size and location

- Pros
  - Reduces internal fragmentation
  - Allows multiprocessing = better CPU util

- Cons
  - Low memory utilisation and internal fragmentation - parts may be unnecessarily large
  - Allocating processes to partitions must be carefully considered
  - Overlays needed if a program does not fit into partition (burden on programmer)

#### Allocation methods
- Private queue per partition
  - Assigns each process to smallest partition in which it would fit
  - Pro: Reduces internal fragmentation
  - Con: Can reduce memory util - lots of small jobs results in unused large parts = starvation

- Single shared queue
  - Applies to all partitions
  - Can allocate small processes to large partitions
  - Con: Results in increased internal fragmentation

## Relocation and protection
- When run, a program does not know in advance which partition/address it will occupy
  - Cannot generate static addresses that are absolute (referring to physical memory)
  - Addresses should be relative to where the program has been loaded
  - OS must resolve relocation, allowing processes to run at different memory locations

- Protection - once you can have two programs in memory at the same time, need to consider and 
enforce protection 
  - One process must not be able to access another's memory

> Logical address: A memory address seen by a process

- Logical addresses are...
  - independent of the current physical memory assignment
  - Eg relative to the start of the program

> Physical address: Refers to an actual location in main memory

- Logical address space needs to map onto physical address space

### Approaches
- Static 'relocation' at compile time - a process has to be located at the same point in memory 
every time

- Dynamic relocation at load time
  - Offset added to every logical address - accounts for its physical location in memory
  - Cons
    - Slows down loading of a process
    - Does not account for swapping

- Dynamic relocation at runtime
  - Two special purpose registers maintained in the CPU (in MMU)
    - __Base register__: Stores the start address of the partition
    - __Limit register__: Holds the size of the partition
  - At runtime:
    - Base register added to logical (relative) address to generate physical address
    - Result is compared against the limit register
  - Con: Requires hardware support - was not always present

## Dynamic partitioning
> Dynamic partitioning: Variable number of partitions of which the size and starting address can
> change over time

- Fixed partitioning = internal fragmentation
  - There may not exist a partition that is exactly the size the process needs
  - The partition may not be used entirely
- Dynamic partitioning allocates the precise amount of contiguous memory a process requires
  - Prevents internal fragmentation

### Swapping
> Swapping: Holding some processes on the drive and moving them between drive and main memory as 
> necessary

- Reasoning
  - Some processes only run occasionally
  - There are more processes than partitions (assuming fixed partitions)
  - A process' memory requirements have changed, eg increasing
  - The total amount of memory that is required for the process exceeds the available memory

- Issues
  - Exact memory requirements may not be known in advance 
    - The heap and stack grow dynamically
    - Could include extra space on top of current requirements

  - __External fragmentation__
    - Swapping a process out of memory will create an unused gap ('hole') in physical memory
    - A new process may not use the entire hole, leaving a small unused block
    - A new process may be too large for a given "hole"
    - Overhead of memory compaction to recover holes can be prohibitive and requires dynamic 
relocation

  - __Memory management__
    - Becomes more complicated
    - Need to keep track of available memory, using...
        - bitmaps
        - linked lists
    - Consider how to quickly allocate processes to available memory
> External fragmentation: Blocks of memory that go unused because they are to small to be allocated
> to a process

### Allocation structures
#### Bitmaps
- Simple data structure - like an array
- Each entry is 1 or 0 boolean, indicating whether the block at that index is allocated
- Size of bitmap depends on amount of memory and size of blocks
- Eg, with 4K blocks and 32M of memory
  - 8192 entries in bitmap
  - = 1KB of storage used

- Finding gaps of sufficient size requires finding a certain number of adjacent bits in bitmap
  - Quite a long operation

- Issues
  - Small block sizes means a large bitmap = slower searching
  - While larger blocks result in internal fragmentation

- The issues mean that bitmaps are rarely used for this purpose

#### Linked lists
- Entry contains...
  - start of memory block
  - size
  - allocated/unallocated boolean

- Allocation is non-trivial

# File systems

## Disk construction
- Multiple aluminium/glass platters covered in __magnetisable material__
  - Stacked on top of each other, held in place by a spindle
  - __Read/write heads__ fly above the surface (distance 0.2 to 0.007 mm)
    - Connected to a single disk arm, controlled by a single actuator
  - Data stored on both sides of disks
  - Common diameters range from 1.8 to 3.5 inches
  - Disks rotated at a constant speed - the speed on the inside is less than on the outside
- Disk controller between CPU and the drive
- Hard disks are currently about 4 orders of magnitude slower than main memory - need to reduce the
impact

### Low-level format and organisation
- __Tracks__: Concentric circle on a single platter side
  - Multiple on each side, become larger as they move outwards
- __Sectors__: Segments of a track (usually 512B or 4KB)
  - Usually have an equal number of bytes in them
  - Number increases from inner side to outside of disk
  - Consists of preamble, data, and error correcting code
  - __Additional data stored results in reduced disk capacity__
- __Cylinders__: collection of tracks in the same relative position to the spindle

- Usually have a __cylinder skew__ - offset is added to sector 0 in adjacent tracks
  - Compensates for seek time - moving from one track to the next

### Access times
- __Access time__ = seek time + rotational delay + transfer time
  - __Seek time__: Time needed to move the arm to the cylinder - is dominant
  - __Rotational latency__: Time before desired sector appears under the head
    - On average half the rotation time
  - __Transfer time__: Time to transfer the data

- Multiple requests can occur concurrently
  - Access time may be increased by a __queueing time__
  - Dominance of seek time leaves room for optimisation - consider the order of read operations

- Estimated seek time (moving arm from one track to another): `Ts = n * m + s`
  - `Ts`: Seek time
  - `n`: Number of tracks to be crossed
  - `s`: Any additional startup delay

- Rotational latency can be estimated from disk RPM (rotations per minute)
  - `time for one rotation = (60*100)/rpm` (in ms)
  - `average rotational latency = time for one rotation /2`
  - `average rotation latency = 30000/rpm`

- Transfer time `Tt`:
  - For the number of bytes in a track `N`, it takes one revolution to read them all
  - `b` contiguous bytes takes `b/N` revolutions
  - `Tt = b/N * (ms per minute)/rpm`

## Disk scheduling
- OS must use hardware efficiently
  - File system can position/organise files strategically
  - Having multiple disk requests queued can minimise arm movement
- Every I/O operation is handled by a system call, allowing the OS to intercept and reorder requests
- If the drive or controller is free, the request can be handled immediately, otherwise it is queued

- In a dynamic situation, several I/O requests will be made over time
  - Requests are stored in a table of requested sectors, per cylinder
- __Disk scheduling algorithms__ determine the order in which requests are processed

### First come first served (FCFS)
- Requests processed in order that they arrive

### Shortest Seek Time First
- Request closest to current head position is processed next
- Aims to reduce head movement
- __Pro__: Performance improvement upon FCFS
- __Con__: Can result in starvation
  - Arm stays in the middle of the disk when under heavy load
  - Edge cylinders are poorly served - unfair
  - Continuously receiving requests for the same location could __starve__ other regions

### SCAN / Lift algorithm
- Head moves in the same direction until end is reached (starting from outside)
  - Handles all pending requests as it passes over cylinders
  - Reverses direction when it gets to the last cylinder in current direction

- __Pro__: Upper limit on waiting time is `2 * number of cylinders` - no starvation
- __Con__: Middle cylinders are favoured if disk is heavily used 
  - Max wait time is `N` tracks at center, `2N` tracks at edges

### C-SCAN (Circular SCAN)
- Once the edge of the disk is reached, requests at the other end have been waiting the longest
- When reversing, C-SCAN does not handle requests, returning to where it began
- Only handles requests in one direction
- __Pros__: fairer, equalises response times across disk

### Look-SCAN
- Moves head to the last cylinder __of the first/last__ request instead of simply to the edges
- __Con__: Seeks are cylinder by cylinder - each containing multiple tracks
  - The arm may _stick_ to a cylinder

### N-step-SCAN
- Only services a limited number of requests every sweep

### Observations and notes
- Look-SCAN and variations are reasonable choices for algorithms
- Performance of each algorithm is dependent on the load of the disk
  - If only one request is received at a time, FCFS will perform as well as any other
- __Optimal__ algorithms are difficult to achieve if requests arrive over time

- Controlling disk scheduling in Unix/Linux
  - Can read/write `/sys/block/<device name, eg sda>/queue/scheduler`
  - Three options:
    - `noop`: FCFS
    - `deadline`: N-step-SCAN
    - `cfq`: Complete Fairness Queueing

    ```
    $ cat /sys/block/sda/queue/scheduler
    noop [deadline] cfq
    ```
  - Option surrounded by square brackets is the currently active scheduler

- Driver caching
  - In most modern drives, the time required to seek to a new cylinder > the rotational time
  - Makes sense to read more sectors than actually required
    - Read sectors during the rotation delay (that are passed by)
    - Modern controllers read multiple sectors when asked for data from a single on - 
track-at-a-time caching

- Solid State Drives (SSDs) have no moving parts - they store data in electrical circuits
  - No seek or rotation delays
  - FCFS is useful in general purpose system
  - Other algorithms may reduce performance

## User view
> User view: defines a file system in terms of the abstractions that the operating system provides

- How the file system looks like to regular users (and programmers)
- Relates to abstractions

- Provides:
  - __File abstraction__: Hides away implementation of files from user
  - __File naming policies__: Abstracts storage details
  - __User file attributes__: Ability to read/manage size, protection, owner, protection, modification 
times
  - __System attributes__: Non-human readable file descriptors, archive & temporary flags
  - __System calls__: Enable interaction with file system
  - __Directory structures__ and organisation

### File types
- Many OSs support several types of file
- Windows and Unix have regular files and directories
  - __Regular files__: Contain user data in ASCII or (a well-defined) binary format
  - __Directories__: Group files together - are files in the implementation level
- Unix has character and block special files
  - __Character special files__: Used to model serial I/O devices - eg keyboards, printers
  - __Block special files__: Model block storage devices like hard drive

### File control block (FCB)
| permissions |
|:-:|
| dates (create, access, write) |
| owner, group, Access Control List (ACL) |
| size |
| (pointers to) data blocks |

- Are kernel data structures - protected and only accessible in kernel mode
- Allowing user applications to access them could compromise their integrity
  - System calls provided for user applications

### Directories
> Directories: Special files that group together other files.
> Their structure is defined by the file system
- Eg, a bit is set that indicates the file is a directory

- Multiple directory structures have been used in the past
  - __Single level__: All files in the same directory (still used in consumer electronics)
  - __Two/multiple level (hierarchical) directories__: Tree structures
    - __Absolute path name__: Path from root of the file system
    - __Relative path name__: The current working directory is used as a starting point
  - __Directed acyclic graph (DAG)__: Allows files to be shared (with links to files or sub-directories)
    - Cycles are forbidden
  - __Generic graph structure__: Links and cycles can be used

- Using DAG and generic graph structures complicates implementation
  - When searching the file system...
    - cycles can result in infinite loops
    - sub-trees can be traversed multiple times
  - Files can have multiple absolute names
  - Deleting files becomes complicated
    - Links may no longer point to a file
    - Inaccessible cycles may exist
  - Garbage collection may be required to remove files that are no longer accessible from the tree
    - Files may become part of a cycle only

### System calls
> System calls: Allow the OS to perform (kernel mode) actions on a user application's behalf
- Categorised into __file manipulation__ and __directory manipulation__
- __File manipulation__: `open()`, `close()`, `read()`, `write()`, etc
- __Directory manipulation__:
  - `create()`/`delete()`: Create/delete directory
  - `opendir()`/`closedir()`: Add/free directory to/from internal tables
  - `readdir()`: Return next entry in the directory file
  - `rename()`, `link()`, `unlink()`, `list()`, `update()`

## Implementation view
> Implementation view: defines the file system in terms of its low-level implementation
- All file systems have to address several considerations:
  - Disk partitions, partition tables, boot sectors, etc
  - Free space management
  - System wide and per process file tables
- Low level formatting writes sectors to disk
- High level formatting imposes a file system on top - blocks can cover multiple sectors

### Partitions
- Disks are usually divided into multiple partitions
  - On each an independent file system may exist
- The Master Boot Record (MBR) is located at the start of the entire drive
  - Used to boot the computer - it is read and executed by the BIOS
  - Contains a partition table that the end, indicating the active partition

#### Unix partition contents
| Boot block |
|:-:|
| Super block |
| Free space management |
| I-nodes |
| Root directory |
| Data |

- __Boot block__: Exists on every partition, will contain code to boot the OS
- __Super block__: Contains partition details, eg size, umber of blocks, I-node table size
- __Free space management__: A bitmap or linked list, indicating the free blocks
- I-nodes: An array of data structures, each storing information about a single file
- __Root directory__: The top of the file system tree
- __Data__: Files and directories

### Free space management
- Need to keep track of free disk space
  - Store a list of free blocks

#### Using bitmaps
- An array on the disk
- A single bit for each block indicates whether that block is free or not
- __Pro__: Take up comparatively less space than linked lists
- __Con__: Size of the bitmap grows with the size of the disk
  - Fixed size for each disk
  - Can only keep bitmap in memory for small disks

#### Using linked lists
- Aka _grouping_
- Free blocks are used to hold the indexes of free blocks
  - eg with 1KB blocks and 32b disk block number, each block holds 255 blocks
  - One pointer points to the next block
- Size of list grows with disk size, shrinks with block size
- Can instead keep track of number of consecutive blocks
  - Known as _counting_
- __Pros__
  - Less wasted space
    - Size of free list shrinks as disk fills
  - Only need to keep in memory one block of pointers
    - Load a new block when needed

### File tables
- Need to store multiple data structures in memory
  - __Mount table__
  - __Directory cache__: Recently accessed directory information
  - __System-wide open file table__: Contains a copy of the FCB for every open file
    - Location on disk
    - File size
    - Open count - number of processes using the file
  - __Per-process open file table__: Contains a pointer to the system open file table

- Opening a file requires...
  1. checking the directory structure (in memory, or on disk)
  2. loading the FCB from disk into memory

- Reading a file requires...
  1. checking the file index in the per-process open-file table for a pointer
  2. following that pointer to the system-wide open-file table
  3. loading the FCB from disk into memory
  4. reading the data blocks on disk

### Directories
- Contain a list of human readable file names that are mapped onto unique identifiers and disk
locations
  - Map logical file onto the physical location
- Can store all related file attributes
  - Name
  - Disk address (on Windows)
  - Pointer to I-node (Unix)
- Finding a file involves searching a directory file
  - Random order of directory entries could be slow - would mean O(n) search time
  - Indexes or hash tables can be used

## Implementations
- The layout of the file system and the file allocation methods used by the OS influences the 
seeking of a mechianical hard drive
  - Contiguous files will result in many short head movements

- Disk scheduling could be implemented in the controller, but OS can prioritise requests

Sequential vs random access:
  - Larger files are composed of a number of blocks
  - __Sequential access__: - blocks before a desired one must be processed before the desired one
  - __Random access__: - the desired block can be accessed without processing any before it

### Contiguous allocation
Similar to dynamic partitioning in memory allocation:
  - Each file stored in a single group of adjacent blocks on the hard disk
  - Eg 1KB blocks, storing a 100KB file, would use 100 contiguous blocks

- Allocation of free space can be done using first fit, best fit, next fit, etc
- In use by CD-ROMs and DVDs

- __Pros__
  - __Simple to implement__: Need store only location of first block and length of file
(in directory entry)
  - __Optimal read/write performance__: Related blocks clustered in nearby/adjacent sectors 
= minimised seek time

- __Cons__:
  - __Need to know exact file size__: Not always known beforehand
    - If file size grows it could overflow the initially allocated disk space
  - __Allocation algorithms__ are needed to decide which free blocks to allocate to a given file
  - __Deleting a file = external fragmentation__: Need to defrag disk

### Linked lists
- Avoid external fragmentation by storing files in separate blocks (similar to paging) that are 
linked to one another
- Only address of first block needed to locate file
- Each block contains a data pointer to the next block (taking up space)

- __Pros__
  - __Easy to maintain__: Only first block (address) has to be maintained in the directory entry
  - __File sizes can grow dynamically__: New blocks/sectors can be added to the end of the file as necessary
  - __Eliminates external fragmentation__: all blocks/sectors can be used
  - Sequential access is straightforward - though more seek ops/disk access may be required

- __Cons__
  - __Random access is very slow__: Need to walk the list to find desired block
  - __Internal fragmentation__: On average the last half of the last block is left unused
    - Smaller block sizes = less internal fragmentation
  - __Possibility of random disk access__
    - Blocks stored around the disk
    - Need to seek to the next block for each link in the list
    - This would be very slow
    - Larger blocks (containing multiple sectors) will be faster
  - __Pointer takes up space__
  - __Reliability worsened__: If a block in the list is corrupted, the rest of the file is lost

### File Allocation Tables (FAT)
- Stores linked-list pointers in a separate index table - called a File Allocation Table (FAT)
- Information stored in memory

- __Pros__
  - __Block size remains power of 2__: No space is lost due to the pointer
  - __Index table can be kept in memory__: Fast non-sequential/random access

- __Cons__
  - __Also need to store FAT on disk__
  - __Size of FAT grows with number of blocks (ie with size of disk)__
    - For a 200GB disk with 1KB block size, 200 million entries are required
    - Given 4B per entry, the FAT will use 800MB of main memory

### I-nodes
- Each file has a small data structure (on disk) called an I-node (index-node)
  - Contains its attributes and block pointers
  - Each only loaded when the file is open (stored in system-wide open file table)
  - Amount of memory required is `n * k`:
    - `n`: Size of an I-node
    - `k`: Max number of files that can be open simultaneously


- Composed of a combination of:
  - Direct block pointers (usually 10)
  - Indirect block pointers

- With only direct block pointers, maximum file size is `block size * no. direct blocks`
- A single indirect block can store up to `(block size) / (size of disk address)` block pointers
- A double indirect block would square the number of blocks pointable by a single indirect block
- Larger files will require a greater level of indirect blocks

### Directories using I-nodes
- In UNIX, all information about the file is stored in its I-node
- Allows directory tables to be simple data structures composed of a file name and I-node pointer
- Directories are a special file, that have their own I-node

### I-node file lookups
1. Locate the root directory of the file system
  - Its I-node is in a fixed location in the disk
  - The directory itself could be anywhere on disk
2. Locate the directory entries specified in the path
  - Find I-node number of first directory
  - Use I-node number to index the I-node table and retreive the directory file
  - Repeat above cycle until the lowest-level directory file is reached
3. Search the file's directory file for the I-node, cache it in memory

### Hard and soft links
- Allow directories to share files
- One directory is the 'real' owner

#### Hard link
- Each folder holds a reference to the same I-node
- An _I-node link reference counter_ tracks number of directories referring to each I-node
- Created using `ln file.txt linkName`

- __Pro__: Faster - doesn't require reading another I-node
- __Cons__: Deleting a file becomes difficult
  - If owner deletes the file, the other directories will hold a reference to an invalid/undesired I-node
  - I-node is kept intact if > 1 reference
  - File is deleted from owner's directory table but technically is responsible for the space the 
file takes up

#### Symbolic/soft link
- A file stores the location of the shared file
- Only the owner maintains the I-node reference
- New file has its own I-node
- Created using `ln -s file.txt linkName`

- __Pros__: 
  - No issues with deleting the original file - link is simply broken
  - Can cross boundaries of filesystems - linked file could be stored on a different machine

- __Cons__
  - Result in another file lookup
  - Require an extra I-node for the link file

### File system examples
- Unix V7
  - Tree structured with links
  - Directories contain file names and I-node numbers
  - I-nodes contain user and system attributes
  - One single, double, and triple indirect block can be used

- More sophisticated systems like ext3 were developed later
- Windows (up to XP) used FAT16/32
- Windows (since XP) moved to 64b NTFS because of file size limitations
  - Uses a similar idea to I-nodes called Master File Tables
  - Have bigger I-nodes that can also contain small files and directories

## Paradigms

### Log structured
- Many operations, eg creating a file, may involve using several blocks
  - Blocks do not need to be adjacent
  - Seeking to blocks in a hard drive causes delays, slowing down performance
- Log structured filesystems try to __improve speed__ by __minimising head movements and rotation delays__
- They use the disk as a log - only writes at the end
- Read and write operations are buffered in memory, to write larger volumes in one go
- Once the buffer is full, it is _flushed_ to the disk, written as one contiguous segment
  - I-nodes and data written to the same segment
  - Finding I-nodes becomes more difficult
- I-node map is maintained in memory to quickly find disk address of I-nodes
- __Cleaner thread__: A process that runs in the background, scanning the log circularly to compact it
  - Deleted files are removed
  - Files in use are marked as free segments - they will later be written to the end
- The hard drive is treated as a circular buffer

- __Pros__
  - __Performance greatly increased__: On writes, file creation and deletion
  - __Writes are more robust__: Done in a single operation
- __Cons__
  - Highly incompatible with existing file systems
  - Cleaner thread uses CPU time

### Journaling
- Deleting a file requires
  1. Removing the respective entry in the directory entry
  2. Adding the file's I-node to the list of free I-nodes
  3. Adding the file's blocks to the free list
- Failure points:
  - __Crash after removing directory entry__: I-nodes and disk blocks inaccessible
  - __Crash after freeing I-nodes__: Disk blocks inaccessible
- Changing order of the events does not resolve these issues

- Journaling aims to increase resilience against crashes
  - Filesystem updates are recorded as a transaction
  1. Write operations to log file
  2. Carry out operations
  3. Remove/commit the log entries

- If a crash occurs in the middle of an operation, the log entries will still be there
  - Log can be examined after crash
  - __Pro__: Can restore consistency of the file system

- eg NTFS, ext3/4

### Virtual (VFS)
- Multiple filesystems usually exist on a computer
- They can be seamlessly integrated by the OS (eg in Unix/Linux)
- VFS relies on the standard object oriented principles of polymorphism
  - A generic interface is specified by the POSIX standards
  - Commonly contains the POSIX system calls: `open()`, `close()`, `read()`, `write()`
  - Each filesystem implements the interface
  - Done in the implementation layer of the file system
- Allows Unix/Linux to unify different file systems
  - Files are shown as a single hierarchy
  - Implementation details are hidden from the user
  - Files can be stored on different machines (eg [sshfs](https://github.com/libfuse/sshfs))

- All file systems, including the root, are registered with the VFS
  - A list/table to the VFS function calls is kept - function pointers
  - Every VFS function call corresponds to the specific entry in the VFS function table for the given file system
  - VFS maps the POSIX call onto the file system's operation
