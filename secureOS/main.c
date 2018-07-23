/*

  main.c

  Author: Gehrig Wilcox

  6/14/18

*/

/*


  Memory Management:

    https://www.tutorialspoint.com/operating_system/os_memory_management.htm


  Register addresses:

    https://github.com/CTCaer/hekate/blob/36bd3bbed123628b75a3837f2e2d7a75f4ed764d/ipl/t210.h


  Init:

    https://github.com/CTCaer/hekate/blob/36bd3bbed123628b75a3837f2e2d7a75f4ed764d/ipl/main.c


*/




void config_se_brom(){

  //Security engine stuffs

  // Fuse private key 0-3
  //Secure boot key?
  u32 sbk[4] = {FUSE(0x1A4),FUSE(0x1A8),FUSE(0x1AC),FUSE(0x1B0))};

  //I have no idea why 14 or 0x10
  se_aes_key_set(14,sbk,0x10);

  /*

    Other stuffs I didn't care to type out right now, need to figure out why
    they are needed

  */

}



void initMMU(){

    

}



void main(void){

  /*

    Current State:

      We are in TrustZone
      We need to set up processor
      We need to set up SecureOS
      We need to set up un-secure space
      We need to load AliOS in un-secure space
      We need to branch to AliOS


      I should probably disable EL2 (Hypervisor) because I do not see why I need
      more than 1 OS running at a time

  */


  /*

    Goal to get basic OS up and running:

    Set up SecureOS in TrustZone

    Configure MMU

    Make sure Interrupt Vector is configured properly
    for both AliOS and SecureOS

    Load AliOS in

    Change processor state to AliOS

    AliOS takes over

    AliOS needs to have ability to:

      Make a new Process
      Destroy a Process
      Make a new Page
      Destroy a Page
      Allocate equal processing time to processes
      Have basic I/O
        Drawing to screen
        Recieving keyboard input

  */

  initMMU();

}
