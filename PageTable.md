Page table layout


The MMU supports 3 granule sizes

4KB
16KB
64KB


Pros/Cons:

  Bigger sizes means a smaller Translation Table and faster translation
    but more memory wasted if it isn't all used

  Smaller sizes means a bigger Translation Table and slower translation
    but less memory wasted if it isn't all used


Solution:
  When allocating memory, I should allocate the largest block that would be
    fully used, this way I won't waste space with too big of a memory block
    and I won't waste time with too small a memory block
    I should also try to fill out the already reserved memory for a process
    before reserving more memory




Questions:

  How do I determine how large of a block to allocate? How do I determine
  where to place the memory?


  Possible Solutions:

    I could just allocate the needed amount, but then I might waste cycles on
      allocating. I could allocate more than needed, which would save on cycles
      but I might waste memory. I could try to logically figure out how much
      memory to allocate, but that would take cycles, and what would be used to
      determine how much memory to allocate?

      Because I have to validate that a given process is allowed to write to a
        memory location, I'd ideally like to have a system that allows a quick
        permissions lookup. The easiest way I came up with would be that part of
        the memory address is the processes ID.

        Pros: Fast, efficient, intuitive, secure memory management
        Cons: Limited memory, limited processes

          Possible fixes for cons:
            If memory or process IDs become scarce, processes gain a memory table
            defining what specific memory locations they own. This way, multiple
            processes can share the same memory location process ID without
            interfering with each other.






  Should I also have a generalized dynamic memory area? Like dynamically
  allocated integers, floats, doubles etc. are all stored in an OS owned
  memory block?
  Pros: Pages are always in memory, so you don't have to wait for the page to
  load in
  Cons: Pages are always in memory, so it is constantly taking up space
  Also, the OS has to check to see if the given process is allowed to write
  somewhere, this would be more difficult than if they just had their own heap

  I decided no generalized dynamic memory area (for now), because I currently
    do not know of an efficient way of checking memory permissions if I use
    this memory model
