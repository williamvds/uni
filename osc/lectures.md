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
- __New__: just created (has PCB), waiting to be admitted to ready queue, may not yet be in memory
- __Ready__: waiting for CPU to become available
- __Running__: controls the CPU (or a core)
- __Blocked__: process cannot continue, eg is waiting for I/O
- __Terminated__: no longer executable, though data structures including PCB may be temporarily 
preserved
- __Suspended__: process is swapped out

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

- - Creates overhead in execution: time is spent saving, reading, re-loading register states

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
  - When to admit to the system (new ➡ ready)
  - Select next process to run (ready ➡ run)
  - Decide when and which process to interrupt (running ➡ ready)

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
1. First Come First Served (FCFS) / First In First Out (FIFO)
  - Non-preemptive
  - Strict queueing mechanism - schedules in same order processes were added to the queue
  - Pros
      - Positional fairness
      - Easy to implement
  - Cons
      - Favours long processes over short ones
      - Could compromise resource utilisation - CPU vs I/O devices
- Shortest Job First
  - Non-preemptive
  - Starts processes in order of ascending processing time using a provided/known estimate of processing
  - Pros
      - Always optimal turnaround time
  - Cons
      - Starvation of long processes
      - Fairness and predictability compromised
      - Processing times have to be known beforehand
- Round Robin
  - Preemptive version of FCFS - forces context switches at periodic intervals or time slices
  - Run in order that they were added to queue
  - Processes are forcefully interrupted by the timer
  - Pros
      - Improved response time
      - Effective for general purpose time sharing systems
  - Cons
      - Increased context switching = overhead
      - Favours CPU bound processes (usually longer) over I/O processes (usually shorter)
        - Possibly prevented by working with multiple queues
      - Can reduce to FCFS
  - Length of time slice must be carefully considered
    - Short = good (low) response time = low throughput
    - Long = high throughput = bad (long) response time
  - If time slice is used partially, the next process start immediately
- Priority Queues
  - Preemptive
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
1. First Come First Served (FCFS) / First In First Out (FIFO)
  - Non-preemptive
  - Strict queueing mechanism - schedules in same order processes were added to the queue
  - Pros
      - Positional fairness
      - Easy to implement
  - Cons
      - Favours long processes over short ones
      - Could compromise resource utilisation - CPU vs I/O devices
- Shortest Job First
  - Non-preemptive
  - Starts processes in order of ascending processing time using a provided/known estimate of processing
  - Pros
      - Always optimal turnaround time
  - Cons
      - Starvation of long processes
      - Fairness and predictability compromised
      - Processing times have to be known beforehand
- Round Robin
  - Preemptive version of FCFS - forces context switches at periodic intervals or time slices
  - Run in order that they were added to queue
  - Processes are forcefully interrupted by the timer
  - Pros
      - Improved response time
      - Effective for general purpose time sharing systems
  - Cons
      - Increased context switching = overhead
      - Favours CPU bound processes (usually longer) over I/O processes (usually shorter)
        - Possibly prevented by working with multiple queues
      - Can reduce to FCFS
  - Length of time slice must be carefully considered
    - Short = good (low) response time = low throughput
    - Long = high throughput = bad (long) response time
  - If time slice is used partially, the next process start immediately
- Priority Queues
  - Preemptive
  - Schedules processes by priority (saved in process control block)
  - Can prioritise I/O bound jobs
  - Priorities are fixed
  - Low priority processes may be starved (if process priorities do not change)
  - Schedules processes by priority (saved in process control block)
  - Jobs of same priority run in Round Robin fashion
  - Pros 
      - Can prioritise I/O bound jobs
  - Cons
      - Low priority processes may be starved (if process priorities do not change)

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

# Something TODO

## Another thing

### Implementation
23/11 - #21

- The layout of the file system and the fire allocation methods used by the OS heavily influences the seek movements
  - Contiguous files will result in many short head movements

- Disk scheduling could be implemented in the controller, but OS could prioritise requests

Sequential vs random access:
- Files will be composed of a number of blocks
- Sequential access - blocks before a desired one must be processed before the desired one
- Random access - the desired block can be accessed without processing any before it

#### Contiguous allocation
Similar to dynamic partitioning in memory allocation:
  - Each file stored in a single group of adjacent blocks on the hard disk
  - Eg 1KB blocks, storing a 100KB file, would use 100 contiguous blocks

- Allocation of free space can be done using first fit, best fit, next fit, etc

Pros:
  - Simple to implement: need store only location of first block and length of file (in directory entry)
  - Optimal read/write performance - related blocks clustered in nearby/adjacent sectors = minimised seek time

Cons:
  - Exact size of file is not always known beforehand - need to consider if file size overflows initially allocated disk space
  - Allocation algorithms needed to decide which free blocks to allocate t oa given file
  - Deleting a file = external fragmentation: need to defrag
  - !!

#### Linked lists
- Avoid external fragmentation by storing files in separate blocks (similar to paging) that are linked to one another
- Only address of first block needed to locate file
- Each block contains a data pointer to the next block (taking up space)

Pros:
  - Easy to maintain - only first block (address) has to be maintained in the directory entry
  - File sizes can grow dynamically - new blocks/sectors can be added to the end of the file as necessary
  - Eliminates external fragmentation - all blocks/sectors can be used
  - Sequential access is straightforward - though more seek ops/disk access may be required

Cons:
  - Random access very slow - need to walk list to find desired block
  - Internal fragmentation - on average the last half of the block is left unused
    - Internal fragmentation will be reduced with smaller block sizes
  - May result in random disk access - !!
  - !!

#### File Allocation Tables (FAT)
- Stores linked-list pointers in a separate index table - called a File Allocation Table (FAT)
- Information stored in memory

Pros:
  - Block size remains power of 2 - no space lost due to the pointer
  - Index table can be kept in memory - fast non-sequential/random access

Cons:
  - Also need to store FAT on disk
  - Size of FAT grows with number of blocks (ie with size of disk)
    - For a 200GB disk with 1KB block size 200 million entries are required
    - Given 4B per entry, the FAT will use 800MB of main memory

#### I-nodes
- Each file has a small data structure (on disk) called an I-node (index-node)
  - Contains its attributes and block pointers
  - They are only loaded when the file is open (stored in system-wide open file table)
  - If !!

- !!
