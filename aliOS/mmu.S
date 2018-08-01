//********* This sets up the MMU *********


//Set BADDR (Table Base Address), located in register TTBR0_EL1
//http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0488c/CIHEBIGD.html

//TABLE_BASE_ADDRESS is wherever TranslationTable0.S is
MSR TTBR0_EL1, TABLE_BASE_ADDRESS<<9


//****************************** Enable MMU ******************************


/*

QUESTION

ASID is used to seperate Process 1's address 0 and Process 2's address 0 right?
How do I set up the Page Table?
What is the process the MMU takes to translate the Virtual Address to the
  Physical address? (including how it takes into account the ASID)


*/


//Set bit[0] to 1
//https://developer.arm.com/docs/ddi0488/latest/system-control/aarch64-register-descriptions/system-control-register-el1
MSR SCTLR_EL1, 1

//Jump
jmp //TODO: Jump somewhere





//****************************** FUNCTIONS ******************************

  //Change ASID (Process ID)
  //  void setASID(int ASID);
  setASID:
    // "The TCR_EL1.A1 field selects either the TTBR0.ASID or the TTBR1.ASID"
    //  -Cortex-A57 4.3.44 Translation Table Base Register 0, EL1

    //Set first 16 bits to the ASID
    MSR TTBR0_EL1, ((0xFFFF&&C_FUNCTION_ARGUMENT0)<<48)

    //Return (Jump back)
    jmp RET_ADDR


  //Change Translation Table 1
  //  void setTTBR0_EL1(int TTBR0);
  setTTBR0_EL1:
                    //Select First 48 bits and shift them 10 bits to the left
                    //https://developer.arm.com/docs/ddi0488/latest/system-control/aarch64-register-descriptions/translation-table-base-register-0-el1
    MSR TTBR0_EL1, ((0x7FFFFFFFFF&&C_FUNCTION_ARGUMENT0)<<10)

    //Return (Jump back)
    jmp RET_ADDR


  //Setup Kernel Translation Table (TTBR1 EL1)
  // void setupKernelTranslationTable();
  setupKernelTranslationTable:

    MSR TTBR1_EL1, ((0x7FFFFFFFFF&&KERNEL_TRANSLATION_TABLE_BASE_ADDRESS)<<10)

    jmp RET_ADDR
