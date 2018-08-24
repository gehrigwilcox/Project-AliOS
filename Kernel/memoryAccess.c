/*

  memoryAccess.c

  Gehrig Wilcox

  7/9/18

*/


#include <stdlib.h>

/*

  Useful Documentation:
  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/BABIHJFE.html
  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/BABIHJFE.html
  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/CDDEIJCH.html
  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/ch12s04.html
  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/CHDIHCJE.html
  https://developer.arm.com/products/architecture/cpu-architecture/a-profile/docs/100940/latest/translation-tables-in-armv8-a
*/


void* malloc(size_t size){
  /*
    Search for a memory space I can fill

    If I can't find one in a block I own, request a new block
  */
}

void free(void *ptr){
  /*
    Free the memory.

    If this results in the whole block being empty, remove the block from the
      Page table, and free the block

  */
}
