/*
  memoryManager.c

  Gehrig Wilcox

  8/5/18
*/


#include "memoryManager.h"


freeMemoryHeader_t* freeMemoryLinkedList; //TODO: Point to first memory block


//TODO: Init by setting up linked list, each memory block needs to have the first byte point to the next memory block
void initMemory(){

}



/*

  NOTE: NEEDS TO BE RUN WITH MMU DISABLED!!!!!!!
  (Dont forget to re-enable afterwards)

  address is a physical address


  address should be passed in with
  size filled out

*/
void freeMemoryBlock(void* address, int size){

  //TODO: Check to see if address is virtual memory, if it is free it


  /******* Turn address into freeMemoryHeader_t ********/
  makeHeader(address, size);



  /******* Get block above ******/

  //Memory block immediately above address
  freeMemoryHeader_t* aboveMemoryBlockBottom = address - MEMORY_BLOCK_SIZE;
  //The top-most free adjacent memory block
  freeMemoryHeader_t* aboveMemoryBlockTop = aboveMemoryBlockBottom-(aboveMemoryBlockBottom->size-1)*MEMORY_BLOCK_SIZE;



  /******** Combine with blocks above and below ********/

  //SAFTEY CHECK
  if(isValidMemoryBlock(aboveMemoryBlockTop) && unsafeRemoveFromFreeMemoryLinkedList(aboveMemoryBlockTop)){
    address=aboveMemoryBlockTop;
    unsafeCombineWithBlockBelow(aboveMemoryBlockTop);
  }
  //Ignore the name, this is really belowMemoryBlockTop
  aboveMemoryBlockTop=address+(address->size+1)*MEMORY_BLOCK_SIZE;

  //SAFTEY CHECK
  if(isValidMemoryBlock(aboveMemoryBlockTop) && unsafeRemoveFromFreeMemoryLinkedList(aboveMemoryBlockTop)){
    unsafeCombineWithBlockBelow(address);
  }



  /******* Place in Linked List ******/

  unsafePlaceBlockInFreeLinkedList(address);
}


/*

  Allocates memory block and adds memory block to page table

  int size is how many 4K memory blocks to allocate

*/
void allocateMemoryBlocks(int amount){

  freeMemoryHeader_t* lookingAt = freeMemoryLinkedList;

  freeMemoryHeader_t* allocateBlockLinkedList;

  for(int sizeToAllocate = 250000; sizeToAllocate > 0; sizeToAllocate/=500){
    //Allocate 1GB, 2MB and 4KB blocks
    findBlockSize(sizeToAllocate, lookingAt);
    while(amount/sizeToAllocate>0){
      if(lookingAt->previous->size >= sizeToAllocate){
        allocateBlockLinkedList->next = unsafeSplitMemoryBlock(lookingAt->previous, sizeToAllocate);
        allocateBlockLinkedList->next->previous=allocateBlockLinkedList;
        allocateBlockLinkedList=allocateBlockLinkedList->next;
        amount-=sizeToAllocate;

        //This triggers when we allocated the last block in freeMemoryLinkedList
        if(allocateBlockLinkedList->next==allocateBlockLinkedList) break;
      }else{
        break; //Break out of while loop, continue for loop
      }
    }
  }


  if(size > 0){
    //ERROR, NOT ENOUGH MEMORY
    /*
    TODO: TRY TO MAKE VIRTUAL MEMORY, if not possible, then return a null pointer and
    free all memory I reserved
    */
  }
}

/*

  Returns the top-most valid freeMemoryHeader
  if the given block is not a valid freeMemoryHeader, it returns NULL

  NOTE: Make sure the block passed in is a valid memory header,
    the block below is a valid memory header, and make sure both the passed in
    block and the block underneath are out of the freeMemoryLinkedList before
    running

*/
freeMemoryHeader_t* unsafeCombineWithBlockBelow(freeMemoryHeader_t* block){

  //Pointers to next memoryBlock headers
  freeMemoryHeader_t* bottomHeader=block+block->size*MEMORY_BLOCK_SIZE;
  freeMemoryHeader_t* belowMemoryBlockTop=bottomHeader+MEMORY_BLOCK_SIZE;
  freeMemoryHeader_t* belowMemoryBlockBottom=belowMemoryBlockTop+belowMemoryBlockTop->size*MEMORY_BLOCK_SIZE;

  //Clear the old headers
  unsafeClearHeader(belowMemoryBlockTop);
  unsafeClearHeader(bottomHeader);

  //Combine the blocks
  block->size+=belowMemoryBlockBottom->size+1;//+1 because adjacent free memory is non-inclusive
  belowMemoryBlockBottom->size=address->size;

  return block;

}

/*

  BE CAREFUL!
  If you do not record the pointer to memory somewhere else, all reference to it
    will be lost

    NOTE: Make sure the block passed in has a valid header
          Make sure the block passed in is in linked list

*/
void unsaveRemoveFromFreeMemoryLinkedList(freeMemoryHeader_t* block){

  //Should I set memory->next and memory->previous to NULL?

  block->next->previous=block->previous;
  block->previous->next=block->next;

  return 1;

}

/*

  Finds a location in the freeMemoryLinkedList to insert the given block
  based on size

  NOTE: Make sure the block is not currently in freeMemoryLinkedList before calling

*/
void unsafePlaceBlockInFreeLinkedList(freeMemoryHeader_t* block){


  while(block->size<block->next->size){
    block->next=block->next->next;
  }

  block->previous=block->next->previous;
  block->previous->next=block;
  block->next->previous=block;

}


uint8_t isValidMemoryBlock(freeMemoryHeader_t* block){
  freeMemoryHeader_t* bottomHeader = block + block->size*MEMORY_BLOCK_SIZE;

  return
  block%MEMORY_BLOCK_SIZE==0 //Make sure header is block aligned
  && block->magicNumber==FREE_MEMORY_HEADER_MAGIC_NUMBER
  && bottomHeader->magicNumber==FREE_MEMORY_HEADER_MAGIC_NUMBER
  && block->size==bottomHeader->size;
}


uint8_t isInLinkedList(freeMemoryHeader_t* block){

  /*
  NOTE: If both conditions are true, it isnt in linked list,
    but something weird has to happen for one to be true and the other to be false
    what do I do in that instance?
  */
  if(block->previous->next!=block || block->next->previous!=block){
    return 0;
  }
  return 1;
}

/*

  NOTE: Make sure passed in header is a header before running

*/
void unsafeClearHeader(freeMemoryHeader_t* header){
  header->magicNumber=NULL;
  header->size=0;
  header->next=NULL;
  header->previous=NULL;
}


/*

  Makes top header and bottom header

  header is the memory location for the memory block
  size is how much memory this block has
    (if the block is 8k, size is 2 because that is 2 4k blocks)

*/
void makeHeader(void* header, int size){
  if(header%MEMORY_BLOCK_SIZE==0){
    //Top header
    header->magicNumber=FREE_MEMORY_HEADER_MAGIC_NUMBER;
    header->size=size;
    header->next=freeMemoryLinkedList;
    header->previous=freeMemoryLinkedList;

    //Bottom Header
    void* bottomHeader = header+size*MEMORY_BLOCK_SIZE
    bottomHeader->magicNumber=FREE_MEMORY_HEADER_MAGIC_NUMBER;
    bottomHeader->size=size;
  }
}


/*

TODO: This

*/
void* createVirtualMemory(){

}


/*

  Splits a memory block in two.
  Breaks top half into desired size, frees bottom half

  NOTE: Make sure header is a header before running

*/
void unsafeSplitMemoryBlock(freeMemoryHeader_t* header, int amount){
  if(header->size<=amount) return;
  unsafeRemoveFromFreeMemoryLinkedList(header);

  int remaningMemory = header->size - amount;
  freeMemoryHeader_t* splitMemory = header+(amount+1)*MEMORY_BLOCK_SIZE;

  makeHeader(header, amount);
  makeHeader(splitMemory, remaningMemory);

  unsafePlaceBlockInFreeLinkedList(splitMemory);

}


/*

  Points pointer to a memory block in freeMemoryLinkedList whos previous pointer points
  to a block of the given size or greater


  The returned pointer will always pass the following test:

    pointer->previous->size>=size && pointer->size < size;

*/
void findBlockSize(int size, freeMemoryHeader_t* pointer){

  //If size is smaller or equal to the smallest size in the linked list
  if(size==1 || freeMemoryLinkedList->previous->size >= size){
    pointer = freeMemoryLinkedList;
    return;
  }


  //If the pointer is to the left of where it needs to be, move right
  while(pointer->size>=size){
    pointer=pointer->next;
  }

}
