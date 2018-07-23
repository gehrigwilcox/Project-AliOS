/*

  memoryAccess.c

  Gehrig Wilcox

  7/9/18

*/


#include "memoryAccess.h"
#include <stdlib.h>

/*

  Useful Documentation:
  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/BABIHJFE.html
  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/BABIHJFE.html
  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/CDDEIJCH.html
  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/ch12s04.html
  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/CHDIHCJE.html

*/

/*

  I'd like to pass in a uint16_t as it is a smaller value,
  but if I am the kernel, how do I declare that I want to
  access kernel memory?

*/
uint8_t getByte(uint32_t addr){

  //Get Execution Level

  uint8_t EL;

  //64-bit address
  uint virtualAddress;

  /*
  Sets all of the first 16 bits to 1 or 0 as per
  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/ch12s03.html
      "Virtual Address to the corresponding Physical Address.
      For a Virtual Address the top 16 bits [63:47] must be all 0s or 1s,
      otherwise the address triggers a fault."


      if first 16 bits are 0, then use TTBR0
      if first 16 bits are 1, then use TTBR1
  */


  /*
    First, if EL0, then first 16 bits are 0
    Otherwise, first 16 bits are 0 or 1

    This is so the kernel memory is accessed in its own table
    (I don't know why this would be adventagous, but I think isolating
      the kernel as much as possible is a good idea)

    Then, go to process pointer table and find the processes address

    Finally, last 29 bits are set to the address requested
  */
  virtualAddress = (((EL == 0 ? 0x0000 : 0xFF00) & addr) << 47);

  //Process ID
  virtualAddress |= /* TEMP: currentProcess */ << 29;

  //Last 29 bits of addr (Process page and Physical Address)
  virtualAddress |= addr & 0x1FFFFFFF;

  /*Send virtualAddress to MMU to get real address*/

  /*Return byte at address*/
}

void writeByte(uint32_t addr, uint8_t value){



}


void* malloc(size_t size){
  /*
    find a location in memory I can fill, if I have to allocate a new page,
    record it to the processes reserved memory table
  */
}

void free(void *ptr){

}
