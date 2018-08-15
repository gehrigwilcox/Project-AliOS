/*
  memoryManager.c

  Gehrig Wilcox

  8/5/18
*/


#include "memoryManager.h"

/************* Involves Freeing Blocks *************/
void freeMemoryBlock(void* address){
  //Check to make sure this is a valid address
  if(address > memoryTableSize) return;

  //Update memory table to say this address is free
  memoryHeaderEntry_t* topMemoryHeader = memoryTableOffset + address * HEADER_SIZE;
  topMemoryHeader->isFree = 1;

  //Increment memoryBlockEntries by 1
  memoryBlockEntries++;


  //Combine nextBlockHeader and topMemoryHeader blocks
  memoryHeaderEntry_t* nextBlockHeader = topMemoryHeader + topMemoryHeader->chunkSize * HEADER_SIZE;
  combineBlocks(topMemoryHeader, nextBlockHeader);


  //Combine previousBlockHeader and topMemoryHeader blocks
  memoryHeaderEntry_t* previousBlockHeader = (topMemoryHeader - HEADER_SIZE)->firstHeader;
  if(combineBlocks(previousBlockHeader, topMemoryHeader)){
    //Set the topMemoryHeader to previousBlockHeader
    topMemoryHeader = previousBlockHeader;
  }

  //Figure out where in list this block needs to be
  //Binary search based on size

  memoryTableBinarySearch(topMemoryHeader);
}

//Given two memory table entries, it will combine both blocks into one singular block
uint8_t combineBlocks(memoryHeaderEntry_t* topHeader, memoryHeaderEntry_t* bottomHeader){

  if(isMemoryHeader(topHeader) && isMemoryHeader(bottomHeader) &&
    topHeader->isFree && bottomHeader->isFree){

      removeFromArray(topHeader);
      removeFromArray(bottomHeader);

    //Add bottomHeaders size to topHeaders size
    topHeader->chunkSize += bottomHeader->chunkSize;
    //Set last header to point to first header
    (topHeader + topHeader->chunkSize)->firstHeader = topHeader;
    //Clear bottomHeader
    memoryHeader->chunkSize = NULL;
    memoryHeader->isFree = NULL;
    memoryHeader->nextHeader = NULL;

    memoryBlockEntries--;

    //Successfully combined
    return 1;
  }
  //Unsuccessfully combined
  return 0;
}


/************* Involves Reserving Blocks *************/

//TODO: void* allocateMemoryBlock(int size)
//TODO: memoryHeaderEntry_t* findBlock(int size)
//TODO: void splitBlock(memoryHeaderEntry_t* block, int size)

/************* Involves Re-Locating Blocks *************/

//Finds location in table to insert given memoryHeader
void memoryTableBinarySearch(memoryHeaderEntry_t* memoryHeader){

  int lookingAt; //Use this to index array, essentally memorySizes[lookingAt];

  int topAddress = 0;
  int size = memoryBlockEntries;

  //While I can divide by 2
  while(size/2 > 0){
    size /= 2;
    lookingAt = topAddress + size;


    //If topAddress is the same as lookingAt, break as topAddress is where it will end
    if(lookingAt == topAddress) break;


    /*
    If memoryHeader size is smaller
    or the size is the same but memoryHeaders address is smaller than lookingAts address,
    then I need to be stored somewhere to the right
    */
    memoryHeaderEntry_t* indexed = indexArray(lookingAt);
    if((indexed->chunkSize > memoryHeader->chunkSize ||
        (indexed->chunkSize == memoryHeader->chunkSize && indexed < memoryHeader)){
          //Search right half
        topAddress = lookingAt;
      }
  }

  /*
  set memoryHeader to point to lookingAt, and have the header located at index lookingAt-1
  point to memoryHeader
  */

  memoryHeader->nextMemoryEntry = indexArray(lookingAt);
  indexArray(lookingAt-1)->nextMemoryEntry = memoryHeader;


}

void removeFromArray(memoryHeaderEntry_t* memoryHeader){
  for(int i=0; i < memoryBlockEntries; i++){
    memoryHeaderEntry_t* indexed = indexArray(i);
    if((indexed + indexed->chunkSize)->nextMemoryEntry == memoryHeader){
      (indexed + indexed->chunkSize)->nextMemoryEntry = memoryHeader->nextMemoryEntry;
    }
  }
}


/************* Helper Functions *************/
int isMemoryHeader(memoryHeaderEntry_t* memoryHeader){
  return memoryHeader >= memoryTableOffset &&
  memoryHeader + memoryHeader->chunkSize * HEADER_SIZE <= memoryTableOffset + memoryTableSize;
}

//Returns the memoryHeaderEntry for a given index
memoryHeaderEntry_t* indexArray(uint idx){

  memoryHeaderEntry_t* ret = memoryTableOffset;

  for(; idx > 0; idx--){
    ret = ret->nextMemoryEntry;
  }

  return ret;
}
