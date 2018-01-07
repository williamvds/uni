# Memory management
## Paging and addressing
> 64b machine, uses paging
> Page/frame size: 4KB

1. What is the maximum number of frames?
  - Max logical addresses: `2^64 = 16384EB`
  - `2^64 / 2^12`
  - `= 2^54 frames`

2. 
  1. How many pages does a 17KB process have?
    - `ceil(17/4) = 5 pages`
  2. How much memory is wasted in the last partition?
    - Pages wasted:
      - `5 - 17/4 = 0.75`
    - `0.75 * 4KB = 3KB unused`

## Paging
> 4KB ppage/frame size
> 16b address space

1. Calculate...
  1. Number `M` of bits for offset within a page
    - `log2(4096) = 12`
  2. Number `N` of bits for representing pages, and number of pages
    - `16 - 12 = 4`
    - `2^4 = 16 pages`

| Pages | | Frames | |
|-|-|-|-|
| 0 | 0000 | 0010 | 2 |
| 1 | 0001 | 0001 | 1 |
| 2 | 0010 | 0110 | 6 |
| 3 | 0011 | 0000 | 0 |
| 4 | 0100 | 0100 | 4 |
| 5 | 0101 | 0011 | 3 |
| 6 | 0110 | x | x |
| 7 | 0111 | x | x |
| 8 | 1000 | x | x |
| 9 | 1001 | 0000 | 5 |
| 10 | 1010 | x | x |
| 11 | 1011 | 0000 | 7 |
| 12 | 1100 | x | x |

2. What is the physical address for...
  1. 0
    - Page: `0 /2^12 = 0`
    - Frame: `0010`
    - Offset: `0`
    - Address: `0010 0000 0000 0000`

  2. 8192
    - Page: `8192 / 2^12 = 2`
    - Frame: `0110`
    - Offset: `8192 - (2 * 2^12) = 0`
    - Address: `0110 0000 0000 0000`

  3. 20500
    - Page: `floor(20500 / 2^12) = 5`
    - Frame: `0011`
    - Offset: `20500 - (5 * 2^12) = 20`
    - Address: `0011 0000 0001 0100`

## Dynamic partitioning
> Main memory: 8GB
> Block size: 1MB
> Memory addresses: 32b
> Linked list: 32b memory address, 16b length, 16b next address
> Memory consists of an alternating sequence of allocated and free blocks

1. How much storage is used for a block bitmap?
  - `8GB / 1MB`
  - `= 8192 blocks`
  - `= 8192b = 1KB`

2. How much storage is used for a linked list?
  - Each node:
    - `32 + 16 + 16`
    - `= 64b = 8B`
  - Free blocks:
    - `8GB / 2 = 4GB`
    - `4GB / 1MB = 4096 blocks`
  - Storage used:
    - `4096 * 8B`
    - `= 32768B = 32KB`

# File systems

## Disk scheduling
> Disk requests cylinders: 10, 22, 20, 2, 40, 6, 38
> Arm at cylinder 20
> Initially moving upwards for SCAN

1. Calculate seek time needed in FCFS
  - `20 to 10 = 10`
  - `10 to 22 = 12`
  - `22 to 20 = 2`
  - `20 to 2  = 18`
  - `2  to 40 = 38`
  - `40 to 6  = 34`
  - `6  to 38 = 32`
  - Total cylinders passed: 146
  - Time: `146 * 6ms = 876ms`

2. Calculate seek time needed in SSTF
  - `20 to 20 = 0`
  - `20 to 22 = 2`
  - `22 to 10 = 12`
  - `10 to 6  = 4`
  - `6  to 2  = 4`
  - `2  to 38 = 36`
  - `38 to 40 = 2`
  - Total cylinders passed: 60
  - Time: `60 * 6ms = 360ms`

3. Calculate seek time needed in Look-SCAN
  - `20 to 20 = 0`
  - `20 to 22 = 2`
  - `22 to 38 = 16`
  - `38 to 40 = 2`
  - `40 to 10 = 30`
  - `10 to 6  = 4`
  - `6  to 2  = 4`
  - Total cylinders passed: 66
  - Time: `58 * 6ms = 348ms`

## Filesystem implementations
> 32b disk address space
> 1KB block size
> 500GB disk capacity

1. What would be the maximum theoretical file size for the FAT file system?
  - No max number of blocks that a single file can be allocated
  - Limited by number of blocks available: `total blocks - FAT blocks`
  - Total blocks: `500GB / 1KB = 524288000`
  - Each FAT entry: `32b = 4B`
  - FAT size: `524288000 * 4B = 2000MB`
  - Disk space available: `500GB - 2000MB ≈ 498GB (3sf)`

2. Why is FAT still in use in most flash drives, cameras, and MP3 players?
  - The limiting factor of using a FAT filesystem is the size of the FAT
  - In larger volumes, the FAT can become prohibitively large, wasting capacity
  - Devices such as these usually have smaller capacities (around 16GB)
  - FAT size is smaller, and as such less wasteful, on these capacities
  - These devices don't need to worry about file size limitations

3. When would you consider formatting your flash drive with NTFS or ext3?
  - When more safety against data corruption is desirable - both implement journaling
  - When the flash drive has a large capacity (>= 128GB)
  - When files larger than 4GB need to be stored on it

4. If you format your flash drive with (Windows') NTFS, will it work directly on Unix systems?
  - Windows' implementation does not implement POSIX APIs directly
  - Independent implementations like [NTFS-3G](https://www.tuxera.com/community/open-source-ntfs-3g/) would allow a Unix system to use an NTFS filesystem

## I-nodes
> ext2 filesystem (I-node 12 direct block addresses, 1 indirect, 1 double, 1 triple)
> Block size: 4KB
> 32b disk address space

1. Can a file of 18GB be stored?
  - Block references storable in a block: 
    - `4KB / 32b`
    - `= 4KB / 4B`
    - `= 1024`
  - Block references in indirect: `1024`
  - Block references in double indirect: `1024^2`
  - Block references in triple indirect: `1024^3`
  - Total block references in I-node: 
    - `12 + 1024 + 1024^2 + 1024^3`
    - `= 1074791436`
  - Maximum file size:
    - `1074791436 * 4KB`
    - `≈ 4.004 TB`

2. How many disk blocks are used for the I-node of a 16MB file?
  - Blocks used to store file:
    - `16MB / 4KB`
    - `= 4096`
  - Using the direct pointers, a single & double indirect:
    - `12 + 1024 + 1024^2`
    - `= 1048576`
  - Used blocks:
    - `1` for I-node, providing `12` blocks
    - `1` for single indirect, providing `1024` blocks
    - `ceil(3060/1024) + 1 = 4` for double indirect, providing `3060` blocks
    - Sum: 6 blocks

## File lookups
1. In Linux, how many lookups are needed to find (and load) the file `/opt/spark/bin/spark-shell`?
  - `/`:
    1. Find I-node
    2. Read directory file
  - `/opt/`:
    1. Read I-node
    2. Read directory file
  - `/opt/spark/`:
    1. Read I-node
    2. Read directory file
  - `/opt/spark/bin/`:
    1. Read I-node
    2. Read directory file
  - `/opt/spark/bin/spark-shell`:
    1. Read I-node
    2. Read file
  - Total: 10 lookups
