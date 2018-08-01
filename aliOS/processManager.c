/*

  processManager.c

  Gehrig Wilcox

  7/9/18

*/

#include "processManager.h"

/*

  SHOULD ONLY BE CALLED BY KERNEL
*/
process_t createProcess(size_t executableSize, *uint executableLocation){

  //Make sure is being called by kernel (EL1)

  //Find a location in memory with enough space to fit executableSize

  //Reserve memory location

  //Create a new process ID

  //Store memory location in process ID pointer

  //Copy executable from storage into memory

  //return process

}

/*
  Switch currently running process

  SHOULD ONLY BE CALLED BY KERNEL
*/
void switchProcess(struct process_t process){

  //Make sure is called by kernel (EL1)

  //Save processor state, restore other processor state

  setASID(process.PID);
  setTTBR0_EL1(process.TTBR);

}


/*
  SHOULD ONLY BE CALLED BY KERNEL
*/
void destroyProcess(struct process_t destroy){

  //make sure is called by kernel (EL1)

}
