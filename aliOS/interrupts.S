/*
  This is the Exception Vector Table as described in
  https://developer.arm.com/products/architecture/a-profile/docs/100933/latest/aarch64-exception-vector-table
*/


// synchronous means that the code running called the interrupt



/*

  TODO: Have the interrupt handler figure out what interrupt was called
        and handle it accordingly

        Also, Figure out how the System timer works (Systick?)
*/

/****** EL1 (Kernel) ******/

.balign 0x800
Vector_table_el1:
curr_el_sp0_sync:        // The exception handler for a synchronous
                        // exception from the current EL using SP0.




.balign 0x80
curr_el_sp0_irq:         // The exception handler for an IRQ exception
                        // from the current EL using SP0.

  mrs ICC_AR0_EL1 r0      //Read from ICC_AR0_EL1 to r0
  //r0 &= (*ICC_CTLR_EL1.IDbits & 1) ? 0x00FFFFFF : 0x0000FFFF;
  ldr r1 . + 2 //Load next address into r1
  b el1_curr_el_sp0_irq_vector + r0
  b curr_el_sp0_irq //loop




.balign 0x80
curr_el_sp0_fiq:         // The exception handler for an FIQ exception
                        // from the current EL using SP0.
.balign 0x80
curr_el_sp0_serror:      // The exception handler for a System Error
                        // exception from the current EL using SP0.
.balign 0x80
curr_el_spx_sync:        // The exception handler for a synchrous
                        // exception from the current EL using the
                        // current SP.
.balign 0x80
curr_el_spx_irq:         // The exception handler for an IRQ exception from
                        // the current EL using the current SP.

.balign 0x80
curr_el_spx_fiq:         // The exception handler for an FIQ from
                        // the current EL using the current SP.

.balign 0x80
curr_el_spx_serror:      // The exception handler for a System Error
                        // exception from the current EL using the
                        // current SP.

.balign 0x80
lower_el_aarch64_sync:   // The exception handler for a synchronous
                        // exception from a lower EL (AArch64).

.balign 0x80
lower_el_aarch64_irq:    // The exception handler for an IRQ from a lower EL
                        // (AArch64).

.balign 0x80
lower_el_aarch64_fiq:    // The exception handler for an FIQ from a lower EL
                        // (AArch64).

.balign 0x80
lower_el_aarch64_serror: // The exception handler for a System Error
                        // exception from a lower EL(AArch64).

.balign 0x80
lower_el_aarch32_sync:   // The exception handler for a synchronous
                        // exception from a lower EL(AArch32).
.balign 0x80
lower_el_aarch32_irq:    // The exception handler for an IRQ exception
                        // from a lower EL (AArch32).
.balign 0x80
lower_el_aarch32_fiq:    // The exception handler for an FIQ exception from
                        // a lower EL (AArch32).
.balign 0x80
lower_el_aarch32_serror: // The exception handler for a System Error
                        // exception from a lower EL(AArch32).




/****** EL2 (Hypervisor) ******/

.balign 0x800
Vector_table_el2:
curr_el_sp0_sync:        // The exception handler for a synchronous
                         // exception from the current EL using SP0.
.balign 0x80
curr_el_sp0_irq:         // The exception handler for an IRQ exception
                         // from the current EL using SP0.
.balign 0x80
curr_el_sp0_fiq:         // The exception handler for an FIQ exception
                         // from the current EL using SP0.
.balign 0x80
curr_el_sp0_serror:      // The exception handler for a System Error
                         // exception from the current EL using SP0.
.balign 0x80
curr_el_spx_sync:        // The exception handler for a synchrous
                         // exception from the current EL using the
                         // current SP.
.balign 0x80
curr_el_spx_irq:         // The exception handler for an IRQ exception from
                         // the current EL using the current SP.

.balign 0x80
curr_el_spx_fiq:         // The exception handler for an FIQ from
                         // the current EL using the current SP.

.balign 0x80
curr_el_spx_serror:      // The exception handler for a System Error
                         // exception from the current EL using the
                         // current SP.

 .balign 0x80
lower_el_aarch64_sync:   // The exception handler for a synchronous
                         // exception from a lower EL (AArch64).

.balign 0x80
lower_el_aarch64_irq:    // The exception handler for an IRQ from a lower EL
                         // (AArch64).

.balign 0x80
lower_el_aarch64_fiq:    // The exception handler for an FIQ from a lower EL
                         // (AArch64).

.balign 0x80
lower_el_aarch64_serror: // The exception handler for a System Error
                         // exception from a lower EL(AArch64).

.balign 0x80
lower_el_aarch32_sync:   // The exception handler for a synchronous
                         // exception from a lower EL(AArch32).
.balign 0x80
lower_el_aarch32_irq:    // The exception handler for an IRQ exception
                         // from a lower EL (AArch32).
.balign 0x80
lower_el_aarch32_fiq:    // The exception handler for an FIQ exception from
                         // a lower EL (AArch32).
.balign 0x80
lower_el_aarch32_serror: // The exception handler for a System Error
                         // exception from a lower EL(AArch32).




/****** EL3 (Secure Monitor) ******/

.balign 0x800
Vector_table_el3:
curr_el_sp0_sync:        // The exception handler for a synchronous
                        // exception from the current EL using SP0.
.balign 0x80
curr_el_sp0_irq:         // The exception handler for an IRQ exception
                        // from the current EL using SP0.
.balign 0x80
curr_el_sp0_fiq:         // The exception handler for an FIQ exception
                        // from the current EL using SP0.
.balign 0x80
curr_el_sp0_serror:      // The exception handler for a System Error
                        // exception from the current EL using SP0.
.balign 0x80
curr_el_spx_sync:        // The exception handler for a synchrous
                        // exception from the current EL using the
                        // current SP.
.balign 0x80
curr_el_spx_irq:         // The exception handler for an IRQ exception from
                        // the current EL using the current SP.

.balign 0x80
curr_el_spx_fiq:         // The exception handler for an FIQ from
                        // the current EL using the current SP.

.balign 0x80
curr_el_spx_serror:      // The exception handler for a System Error
                        // exception from the current EL using the
                        // current SP.

.balign 0x80
lower_el_aarch64_sync:   // The exception handler for a synchronous
                        // exception from a lower EL (AArch64).

.balign 0x80
lower_el_aarch64_irq:    // The exception handler for an IRQ from a lower EL
                        // (AArch64).

.balign 0x80
lower_el_aarch64_fiq:    // The exception handler for an FIQ from a lower EL
                        // (AArch64).

.balign 0x80
lower_el_aarch64_serror: // The exception handler for a System Error
                        // exception from a lower EL(AArch64).

.balign 0x80
lower_el_aarch32_sync:   // The exception handler for a synchronous
                        // exception from a lower EL(AArch32).
.balign 0x80
lower_el_aarch32_irq:    // The exception handler for an IRQ exception
                        // from a lower EL (AArch32).
.balign 0x80
lower_el_aarch32_fiq:    // The exception handler for an FIQ exception from
                        // a lower EL (AArch32).
.balign 0x80
lower_el_aarch32_serror: // The exception handler for a System Error
                        // exception from a lower EL(AArch32).









//Do I need padding here?

//Interrupt Handling Vector Table
.balign 0x8
el1_curr_el_sp0_irq_vector:

.balign 0x18 //3 instructions
IRQ_1:
bl //branch to interrupt handler
msr r0 ICC_EOIR0_EL1 //Acknowledge that we have handled the interrupt
b r1 //Branch back to where I was called

.balign 0x18
IRQ_2:

//TODO: IRQ_1023: NO MORE INTERRUPTS
