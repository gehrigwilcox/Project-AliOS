/*
  memoryManager.h

  Gehrig Wilcox

  8/8/18

*/

/************* VARIABLES *************/

/************* Definitions *************/
//TODO: Define memoryTableOffset
//TODO: Define memoryTableSize
#define HEADER_SIZE sizeof(memoryHeaderEntry_t)

/************* Generic Variables *************/
int memoryBlockEntries; //keeps count of how many memoryBlocks there are in the memory table

/************* Structs *************/
typedef struct {
  uint8_t isFree:1; //packed boolean
  memoryHeaderEntry_t* nextMemoryEntry; //Should point to a lower address and same size or a lower size

  union LocationSpecific {
    uint chunkSize; //Belongs to Top header, How many headers are in this chunk (minimum of 1)
    memoryHeaderEntry_t* firstHeader; //Belongs to Bottom Header
  } chunkSize, firstHeader;

} memoryHeaderEntry_t;


/************* FUNCTIONS *************/

/************* Involves Freeing Blocks *************/
void freeMemoryBlock(void* address);
uint8_t combineBlocks(memoryHeaderEntry_t* topHeader, memoryHeaderEntry_t* bottomHeader);

/************* Involves Reserving Blocks *************/


/************* Involves Re-Locating Blocks *************/
void memoryTableBinarySearch(memoryHeaderEntry_t* memoryHeader);
void removeFromArray(memoryHeaderEntry_t* memoryHeader);

/************* Helper Functions *************/
int isMemoryHeader(memoryHeaderEntry_t* memoryHeader);
memoryHeaderEntry_t* indexArray(uint idx);
