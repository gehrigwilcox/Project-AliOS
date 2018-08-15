/*

  processManager.c

  Gehrig Wilcox

  7/9/18

*/

#include "processManager.h"

/*

  SHOULD ONLY BE CALLED BY KERNEL
*/
process_t createProcess(uint executableLocation){

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

  SHOULD ONLY BE CALLED BY KERNEL/interrupt
*/
void switchProcess(struct process_t process){

  //Make sure is called by kernel (EL1)

  /*
    Save processor state
      Push ELR_EL1 onto stack as Program Counter
      Push X0-X30 onto stack
      Save Stack Pointer
  */


  /*
    Restore other processor state
      Set stack pointer
      Pop X0-X30 from stack
      Pop ELR_EL1 from stack into Program Counter
  */

  setASID(process.PID); //Or some other unique ID
  setTTBR0_EL1(process.TTBR);

}


/*
  SHOULD ONLY BE CALLED BY KERNEL
*/
void destroyProcess(struct process_t destroy){

  //make sure is called by kernel (EL1)

  //Make next process's previous process point to my previous process
  //Make previous process's next process point to my next process
  //Reduce count of currently running processes

}
