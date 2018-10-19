/*
  memoryManager.c

  Gehrig Wilcox

  8/5/18
*/


#include "memoryManager.h"


void* freeMemoryLinkedList; //TODO: Point to first memory block id:5
void* lastMemoryInList; //TODO: Point to last memory block id:0


//TODO: Init by setting up linked list, each memory block needs to have the first byte point to the next memory block id:3
//TODO: Create a function to create virtual memory id:8

void freeMemoryBlock(void* address){


  //TODO: Check to see if address is virtual memory, if it is, check to see if I need to exist or if I can be freed id:10

  //Add the memory to the linked list
  *lastMemoryInList = address;
  //Point lastMemoryInList to address
  lastMemoryInList = address;
  //Have address point to lastMemoryInList
  *address = lastMemoryInList;

}


/*

  Allocates memory block and adds memory block to page table

  int size is how many memory blocks to allocate

*/
void allocateMemoryBlock(int size){

  /*
  Should memory blocks be able to be shared to prevent fragmentation?
  If so, how should the kernel prevent each process from accessing data they shouldnt?
    Should it just keep record of what portion it owns and only allow access to those areas?
  */

  //Create an array of blocks
  void blocks[size];

  //Set first element to first index in linked list
  blocks[0] = *freeMemoryLinkedList;

  //Fill out array
  for(int i=1; i < size; i++){
    blocks[i] = *blocks[i-1];
  }

  //Set the head of the linked list to the new head
  freeMemoryLinkedList = blocks[size];

  //TODO: Fill out page table id:6
}
