  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

  .global PendSV_Handler

  .thumb_func	// forces it all to be all 32 bit functions -> for alignment
  PendSV_Handler:

    MRS R0, PSP          	// store into R0 the program stack pointer
    STMDB R0!, {R4-R11}    // store r4 to r11 into the memory spaces above r0
    MSR PSP, R0             // move the value in R0 into the PSP
    BL scheduler            // branch to the scheduler function
    MRS R0, PSP             // move into R0 the PSP
    LDMIA R0!, {R4-R11}    // load r4 to r11 from the memory spaces above r0
    MSR PSP, R0             // move the value in R0 into the PSP
    MOV LR, 0xFFFFFFFD      // move the magic number into LR
    BX LR                   // branch to LR
