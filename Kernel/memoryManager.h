/*
  memoryManager.h

  (WITH MMU)

  Gehrig Wilcox

  8/8/18

*/





#define MEMORY_BLOCK_SIZE 4000 //4K


/*

  Comments about using the magicNumber:

    The magic number isn't fool-proof. My anxiety makes me concious that it is
    possible for a memory block to have this number at the top
    (although unlikely, and even more unlikely that a memory block will see it)

    But, in the case that a memory block is falsely identified, the damage will
    be the following:

      (1) The freed memory will never be added to the free memory list,
            causing a memory leak

      (2) Bytes [9:17] of the falsely identified block - size * blockSize
            will be incremented by how many adjacent free memory blocks there are



      The ramifications of issue 1, although not ideal, aren't terrible. Worst
        case scenario, I get an out of memory error that can be fixed by a system reboot

      The ramifications of issue 2 are much more serious. This could possibly
        change a processor instruction.



    Although there are downsides to using the magic number, it is *WAY* faster
      to use a magic number than to search through the linked list


*/

//Set FREE_MEMORY_HEADER_MAGIC_NUMBER to random number (found at a TBD memory location)
//Remember to set the value at that memory location to another value later
#define FREE_MEMORY_HEADER_MAGIC_NUMBER 0xAC1D1CEAC1D1CE14

typedef struct {

  //The first 8 bytes should be something unique to identify the memory as a free block
  const int magicNumber = FREE_MEMORY_HEADER_MAGIC_NUMBER;

  int size;

  freeMemoryHeader_t* next; //To form the linked list

  freeMemoryHeader_t* previous; //To form the doubly linked list (make it easier to remove elements)

} freeMemoryHeader_t;



void initMemory();

void freeMemoryBlock(void* address, int size);

void allocateMemoryBlocks(int amount);

freeMemoryHeader_t* unsafeCombineWithBlockBelow(freeMemoryHeader_t* block);

void unsafeRemoveFromFreeMemoryLinkedList(freeMemoryHeader_t* block);

void unsafePlaceBlockInFreeLinkedList(freeMemoryHeader_t* block);

uint8_t isValidMemoryBlock(freeMemoryHeader_t* block);



void unsafeClearHeader(freeMemoryHeader_t* header);

void makeHeader(freeMemoryHeader_t* header);

void* createVirtualMemory();

void unsafeSplitMemoryBlock(freeMemoryHeader_t* header, int size);

void findBlockSize(int size, freeMemoryHeader_t* pointer);
