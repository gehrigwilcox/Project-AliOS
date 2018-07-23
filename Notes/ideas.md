Memory Management:

   Each process gets its own:
      Executable memory space
      IPC memory space
      Stack memory space
      Heap memory space

   If the process needs more heap, it will request more from the kernel,
    and the kernel will try to allocate more memory


IPC:

  Each process will have its own region in memory for IPC. Each process is
    responsible for checking its IPC area and reacting accordingly

Page Table


Permissions




Microkernel
Each process can create its own pages (with restrictions)
  The page table handler will have to be able to optimize pages in some way
