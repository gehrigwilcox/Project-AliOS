/*

  PageTableHandler.c

  Gehrig Wilcox

  7/7/18

*/

#include "PageTableHandler.h"




/*

  Make a new page table in kernel memory space and return the address

*/
pageTable_t* createPageTable(){

  pageTable_t* PT = malloc(sizeof(pageTable_t));

  //Fill out page table with invalid entries
  for(int i = 0; i < numberOfPageTableEntries; i++){
    PT->entries[i]->type = createPageTableEntryInvalid();
  }

  return PT;

}


/*
  This function takes in a virtual address and configures the current
    TTBR0 to map the virtual address to the physical address

    Size is how many 4KB blocks

    TODO: Finish this
*/
void setPageTranslation(process_t* process, void* virtualAddress, freeMemoryHeader_t* physicalAddress){

  pageTableEntry_t* PT = getPageTableEntry(process->pageTable, virtualAddress & (0x1FF<<39));

  /*
    This figures out how many tables are needed for the given block

    4KB = 500^0
    2MB = 500^1
    1GB = 500^2

    physicalAddress->size = 500^x
  */
  for(int tablesToIndex = 3-log(500,physicalAddress->size),i=0; (i < tablesToIndex); i++){
    //x = number of bits used to index table all set to 1
    //y = last bit location for second highest table index
    //z = number of bits used to index table
    //i = table we are indexing
                                                             //x       y   z
    PT = getPageTableEntry(PT->address, virtualAddress & (0x1FF<<(30-i*9)));

    if(PT->type == BLOCK) return;
  }

    if(!(PT->type & 1)) return; //REQUESTED VIRTUAL ADDRESS IS ALREADY ALLOCATED

    *PT = createPageTableEntryBlock(physicalAddress);

}

void removePageTranslation(process_t* process, void* virtualAddress, int levelNumber){

  findDeadPageTable(process, virtualAddress, levelNumber);

}

/*

  This function will properly clear and free the given page table entry and
   any page tables that will be left empty


   Terminology:
    parent page table: The page table that holds the entry that is to be destroyed
    root page table: the page table process points to
    dead page table: The only entry it contains is going to be destroyed

*/
void findDeadPageTable(process_t* process, void* virtualAddress, int levelNumber){

  if(levelNumber == 0){//If we are removing the root page table then just destroy it
    //Remove reference from process, and clear out pageTable

    void* entryAddress = process->pageTable;
    process->pageTable = NULL;

    destroyPageTableEntry(TABLE, entryAddress);

    return;
  }

  //Make sure the parent page table for this entry has other entries

  int entryIndex = virtualAddress & 0x1FF << 39 - (levelNumber-1) * tableIndexBitSize;

/****************   GET PARENT PAGE TABLE   ****************/
  pageTable_t* parent = process->pageTable; //Get root page table
  for(int i = 0; i < levelNumber-1; i++){ //Get parent page table
    //Get next page table
    parent = parent->entries[virtualAddress & 0x1FF << 39 - i * tableIndexBitSize]->address;
    //NOTE: 0x1FF needs to be changed to "tableIndexBitSize amount of bits set to 1"
  }


/****************  IS PARENT DEAD?  ****************/

  for(int i = 0; i < numberOfPageTableEntries; i++){
    if(i==pageTableEntryIndex) continue;
    if(table->entries[i]->type & 1){
      //The parent page table is not dead! Just remove the entry

      int entryType = table->entries[entryIndex]->type;
      int entryAddress = table->entries[entryIndex]->address;

      table->entries[entryIndex] = createPageTableEntryInvalid();

      destroyPageTableEntry(entryType, entryAddress);

      return;
    }
  }

  //The parent page table is dead, will its parent be dead too?
  findDeadPageTable(process, virtualAddress, tableNumber-1);

}


void destroyPageTableEntry(int type, void* address){
  if(type == INVALID) return;
  if(type == TABLE){
    for(int i = 0; i < numberOfPageTableEntries; i++){

      int entryType = address->entries[i]->type;
      void* entryAddress = address->entries[i]->address;

      address->entries[i] = createPageTableEntryInvalid();
      destroyPageTableEntry(entryType, entryAddress);
    }
  }
  freeMemoryBlock(address);
}

/*

  Creates a page table entry for a block of memory

*/
pageTableEntry_t createPageTableEntryBlock(freeMemoryHeader_t* physicalAddress){

}

/*

  Creates a page table entry for another table

*/
pageTableEntry_t createPageTableEntryTable(){
  pageTable_t* PT = createPageTable();


}

pageTableEntry_t createPageTableEntryInvalid(){

}

//Returns the pageTableEntry located offset away from pageTable
pageTableEntry_t* getPageTableEntry(pageTable_t* pageTable, int offset){

  pageTableEntry_t* entry = pageTable->entries[offset];

  if(entry->type == 0){
    //Create a page table entry
    *entry = createPageTableEntryTable();
  }
  return entry;
}
