;  This is the entry-point for the BootLoader
;  this is responsible for setting up the system and launching the OS


.section .text ._start
.arm ; 32-bit instruction set


  ; C memset()

  .extern memset
  .type memset, %function





  .globl _start
  .type _start, %function






  _start:


;      We want to get into a higher-level language as soon as possible, so
;      lets set up a stack so we can start using C instead of Assembly
;      We are currently in TrustZone (This is how ARM boots) so we will use
;      TZRAM for stack
;      Let's give 1K to stack (Arbitrary choice, should optimize later)
;      Might also want to make sure this (and C program) is loaded where I want


      ; Set up stack


      ;TODO: Fix to be Start of TZRAM + 1K
       LDR SP, =0x7c01fc17    ; 1K from end of TZRAM


       ; Now lets clear out _bss

       LDR R0, =__bss_start   ; Set Register 0 to __bss_start
       EOR R1, R1, R1         ; Set Register 1 to 0
       LDR R2, =__bss_end     ; Set Register 2 to __bss_end
       SUB R2, R2, R0         ; Set Register 2 to size of ._bss
       BL memset              ; Call memset(bss_start, 0, bssLength)


       ; Now lets go to main()!

       BL main                ; Call main(void)


       ; Infinite loop!

       B .    ; Should never reach this









;     Called from C to reposition stack
  .globl position_stack
  .type position_stack, %function
  position_stack:

    ; Set stack pointer to passed argument
    MOV SP, R0

    ; Branch back to return address
    BX LR
