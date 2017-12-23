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
