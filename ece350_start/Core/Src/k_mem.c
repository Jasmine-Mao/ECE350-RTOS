#include "common.h"
#include "k_mem.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "kernel.h"

extern U32 _img_end; //the start of the heap will be from here, could add 0x200 bytes offset
extern U32 _estack;
extern U32 _Min_Stack_Size;

header_block header_array[16];


int k_mem_init(){
    // if the kernel has already been initialized
    if(initialized == 0 || k_mem_initialized == 1){
        return RTX_ERR;
        // if the kernel is not intialized or if the k mem init has already run once
    }
    else{
        k_mem_initialized = 1;

        header_block first_block;       // create the very first free block encompassing all the free memory
        first_block.next = NULL;
        first_block.ownership = -1;     // negative since there is no current ownership of the block
        first_block.size = (1 << MAX_ORDER);
        first_block.status = 0;

        header_array[0] = first_block;
        //initialize the heap
        heap_start = &_img_end; //set the start of the heap to the end of the image
        heap_end = &_estack - &_Min_Stack_Size; //set the end of the heap to _estack - _Min_Stack_Size

        return RTX_OK;
    }
}

void *k_mem_alloc(size_t size){
    //allocates size bytes of memory according to the Buddy System algorithm and returns a pointer to the start of the usable memory in the block

    if (k_mem_initialized == 0 || size == 0){
        return NULL;
    }
    else{
        // check what order the size fits within
        // add the header to the size
        int block_order;
        for(int i = 5; i <= 11; i++){
            if((1 << i) < size){
                block_order = i;
                break;
            }
        }
        // now we have the block order that we need to allocate
    }


}

int k_mem_dealloc(void *ptr){
    if(k_mem_initialized == 0){
        return RTX_ERR;
    }
}

int k_mem_count_extfrag(size_t size){
    
}