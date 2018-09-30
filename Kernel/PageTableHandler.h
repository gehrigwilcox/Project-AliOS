/*
  PageTableHandler.h

  Gehrig Wilcox

  7/2/18
*/


/*

  This manages and enforces the allocation of Pages in the Page Table

*/

#include "memoryManager.h"

#define TTBR0 //TODO: some address I cant find right now

#define numberOfPageTableEntries 512


typedef struct {

  pageTableEntry_t entries[numberOfPageTableEntries];

} pageTable_t;

typedef struct {

  //Based on https://static.docs.arm.com/100940/0100/armv8_a_address%20translation_100940_0100_en.pdf
  //http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.den0024a/ch12s08.html
  //and https://static.docs.arm.com/100940/0100/armv8_a_address%20translation_100940_0100_en.pdf

  //  bits [63:59] are Res0
  //  bits [58:55] are Reserved for software use
  //  bit 54 is Unprivileged execute never
  //  bit 53 is Privileged execute never

  void* address; //could be a pageTable or a block

  //  bit 10 is Access Flag
  //  bits [9:8] are Shareable Flag
  //  bits [7:6] are Access Permission
  //  bit 5 is Security bit (only at EL3 and Secure EL1)
  //  bits [4:2] are Index into the MAIR_ELn
  //  bits [1:0] determine the type of entry [11] is a table descriptor or a table entry, [01] is a block entry, and [x0] is an invalid entry
} pageTableEntry_t;


pageTable_t* createPageTable();

void destroyPageTable(pageTable_t* pageTable);

void setPageTranslation(process_t* process, int tableLevel, void* virtualAddress, freeMemoryHeader_t* physicalAddress);

void removePageTranslation(process_t* process, void* virtualAddress, int levelNumber);

void findDeadPageTable(process_t* process, void* virtualAddress, int levelNumber);

void destroyPageTableEntry(int type, void* address);

pageTableEntry_t createPageTableEntryBlock(freeMemoryHeader_t* physicalAddress);

pageTableEntry_t createPageTableEntryTable();

pageTableEntry_t createPageTableEntryInvalid();

pageTableEntry_t* getPageTableEntry(pageTable_t pageTable, int offset);
