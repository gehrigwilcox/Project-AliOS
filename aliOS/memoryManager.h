/*
  memoryManager.h

  Gehrig Wilcox

  8/8/18

*/


//TODO: Define memoryTableOffset
//TODO: Define memoryTableSize
#define HEADER_SIZE sizeof(memoryHeaderEntry_t)

int memoryBlockEntries; //keeps count of how many memoryBlocks there are in the memory table

typedef struct {
  uint8_t isFree:1; //packed boolean
  memoryHeaderEntry_t* nextMemoryEntry; //Should point to a lower address and same size or a lower size

  union LocationSpecific {
    uint chunkSize; //Belongs to Top header, How many headers are in this chunk (minimum of 1)
    memoryHeaderEntry_t* firstHeader; //Belongs to Bottom Header
  } chunkSize, firstHeader;

} memoryHeaderEntry_t;



void freeMemoryBlock(void* address);

int isMemoryHeader(memoryHeaderEntry_t* memoryHeader);

void memoryTableBinarySearch(memoryHeaderEntry_t* memoryHeader);

void removeFromArray(memoryHeaderEntry_t* memoryHeader);

memoryHeaderEntry_t* indexArray(uint idx);
