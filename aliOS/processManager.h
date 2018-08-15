/*
  processManager.h

  Gehrig Wilcox

  7/2/18
*/

/*

  This manages the creation, management, and destruction of processes

*/



#define MAX_PID 0xFFFF


/*

  Should be stored in location that only kernel can access

*/
typedef struct {

  /*
    16 bit process id maximum, because that is the highest ASID will go
    Although, the ASID and the PID don't have to be the same

    This is so you can directly interface with each process
  */
  uint16_t PID;

  //Process state
  int* stackPointer;

  //Translation Table
  pageTable_t* pageTable;

  //Make processes an indexable array
  process_t* previousProcess;
  process_t* nextProcess;


} process_t;


extern void setASID(uint16_t asid);

process_t createProcess(size_t executableSize, *uint executableLocation);

void switchProcess(struct process_t);

void destroyProcess(struct process_t);
