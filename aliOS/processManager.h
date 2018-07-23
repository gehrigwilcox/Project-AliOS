/*
  processManager.h

  Gehrig Wilcox

  7/2/18
*/

/*

  This manages the creation, management, and destruction of processes

*/



#define MAX_PID 9999

/*
This is the offset that is added to the PID to retrieve the pointer
to the processes virtual memory address

So, to get a virtual address, first get the PID_POINTER_OFFSET, add it to the
  PID, the data at that location is the virtual address for that process
TODO: Find an actual location for the PID pointer table
*/
#define PID_POINTER_OFFSET 0xDEADBEEF


/*

  How do I remember what PIDs are reserved?
  What also needs to be stored?

*/
typedef struct {

  uint32_t PID; //32 bit process id, might even change it to 16 bit process id


} process_t;


process_t createProcess(size_t executableSize, *uint executableLocation);

void switchProcess(struct process_t);

void destroyProcess(struct process_t);
