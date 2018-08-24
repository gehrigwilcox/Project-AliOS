/*

  PageTableHandler.c

  Gehrig Wilcox

  7/7/18

*/

#include "PageTableHandler.h"


/*
  This function takes in a virtual address and configures the current
    TTBR0 to map the virtual address to the physical address

    SHOULD ONLY BE CALLED BY KERNEL
*/
void setPageTranslation(int virtualAddress, void* physicalAddress){

  //Make sure that this is called by kernel (EL1)

}





/*
  Allocates a new memory block

  size: 2 bits

    if granule size is 4KB:
      00: Error
      01: 4KB Block
      10: 2MB Block
      11: 1GB Block

    if granule size is 64KB:
      00: Error
      01: 64KB Block
      10: 512MB Block
      11: Error

  Returns a pointer to the memory block


  SHOULD ONLY BE CALLED BY KERNEL
*/
void* allocateBlock(uint8_t size){

  //Make sure that this is called by kernel (EL1)

}
