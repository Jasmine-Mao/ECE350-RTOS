#include "common.h"
#include "k_mem.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "kernel.h"


int k_mem_init(){
    // if the kernel has already been initialized
    if(initialized == 0 || k_mem_initialized == 1){
        return RTX_ERR;
        // if the kernel is not intialized or if the k mem init has already run once
    }
    else{
        k_mem_initialized = 1;


        return RTX_OK;
    }
}

void *k_mem_alloc(size_t size){

}

int k_mem_dealloc(void *ptr){

}

int k_mem_count_extfrag(size_t size){
    
}