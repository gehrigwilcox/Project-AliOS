/*
  PageTableHandler.h

  Gehrig Wilcox

  7/2/18
*/


/*

  This manages and enforces the allocation of Pages in the Page Table

*/



typedef struct {
  
} pageTable_t;




void setPageTranslation(int virtualAddress, void* physicalAddress);



void* allocateBlock(uint8_t size);
