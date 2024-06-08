 .syntax unified
 .cpu cortex-m4
 .fpu softvfp
 .thumb

 .global Case2

 .thumb_func

 Case2:

	MRS R0, PSP
	LDMIA R0!, {R4, R11}
	MSR PSP, R0
	BX LR
