#include "common.h"
#include "k_mem.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "kernel.h"

extern U32 _img_end; //the start of the heap will be from here, could add 0x200 bytes offset
extern U32 _estack;


int k_mem_init(){
    // if the kernel has already been initialized
    if(initialized == 0 || k_mem_initialized == 1){
        return RTX_ERR;
        // if the kernel is not intialized or if the k mem init has already run once
    }
    else{
        k_mem_initialized = 1;
        //initialize the heap
        U32 *heap_start = &_img_end; //set the start of the heap to the end of the image
        U32 *heap_end = &_estack - 0x4000; //set the end of the heap to _estack - _Min_Stack_Size

        return RTX_OK;
    }
}

void *k_mem_alloc(size_t size){

}

int k_mem_dealloc(void *ptr){

}

int k_mem_count_extfrag(size_t size){
    
}