# Introduction to the Operating System
> Operating system - A layer of indirection on top of the hardware


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

## Hardware considerations
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
