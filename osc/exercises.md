# File systems
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
