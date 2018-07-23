/*

  processManager.c

  Gehrig Wilcox

  7/9/18

*/

#include "processManager.h"


process_t createProcess(size_t executableSize, *uint executableLocation){

  //Find a location in memory with enough space to fit executableSize

  //Reserve memory location

  //Create a new process ID

  //Store memory location in process ID pointer

  //Copy executable from storage into memory

  //return process

}

/*
  Switch currently running process
*/
void switchProcess(struct process_t process){

  //Save processor state, restore other processor state

}

void destroyProcess(struct process_t destroy){

}
