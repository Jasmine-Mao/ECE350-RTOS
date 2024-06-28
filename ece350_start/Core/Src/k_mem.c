#include "common.h"
#include "k_mem.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "kernel.h"

extern U32 _img_end; //the start of the heap will be from here, could add 0x200 bytes offset
extern U32 _estack;
extern U32 _Min_Stack_Size;

header_block *header_array[MAX_ORDER] = {NULL};  // array of 11 pointers for the 11 levels; initially set to NULL

int k_mem_init(){
    // if the kernel has already been initialized
    if(initialized == 0 || k_mem_initialized == 1){
        return RTX_ERR;
        // if the kernel is not intialized or if the k mem init has already run once
    }
    else{
        k_mem_initialized = 1;
        heap_start = &_img_end; //set the start of the heap to the end of the image
        heap_end = &_estack - &_Min_Stack_Size; //set the end of the heap to _estack - _Min_Stack_Size

        header_block *root_block;       // create the very first free block encompassing all the free memory
        root_block->next = NULL;
        root_block->size = (1 << (MAX_ORDER + MIN_BLOCK_ORDER));
        root_block->status = 0;
        root_block->address = heap_start;

        header_array[MAX_ORDER - 1] = root_block;       // place the root memory block at the last index of the pointer array
        //initialize the heap
        
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
        size += sizeof(header_block);   // add the header to the size
        int block_level = -1;
        for(int i = MIN_BLOCK_ORDER; i <= MIN_BLOCK_ORDER + MAX_ORDER; i++){       // find what memory block size is needed to accomodate
            if(size < (1 << i)){
                block_level = i - MIN_BLOCK_ORDER;      // block order is now the index value needed to find blocks of the size we need
                break;
            }
        }
        if(block_level == -1){
            // we didn't find an appropriate size :(
            printf("couldn't fund sufficient block size. exiting...\n");
            return NULL;
        }
        // check the header array at index block_level. this will be the list of free blocks or the desired size

        // if no node is found, the pointer in the array will be NULL. thus, we need to check the pointer value
        int tracker = block_level;
        while(header_array[tracker] == NULL){
            if(tracker == MIN_BLOCK_ORDER + MAX_ORDER){  // if we have reached the root and the pointer is NULL, there is simply no space for our current block
                return NULL;
            }
            tracker++;      // increment tracker to look at the level above
        }
        // reach here once we find a list that has a free node we can split

        // now we need to split the free block until we reach our desired block size, block_level
        while(tracker != block_level){  // stay here until we have reached the block size we want
            // create 2 nodes in the level below
            header_block *buddy1;
            header_block *buddy2;

            buddy1->size = (1 << (tracker + MIN_BLOCK_ORDER - 1));      //****
            buddy2->size = buddy1->size;

            buddy1->address = header_array[tracker]->address;
            buddy2->address = buddy1->address + buddy1->size;       // this is pointer arithmetic? need this checked

            buddy1->status = 0;
            buddy2->status = 0;

            buddy1->next = buddy2;
            buddy2->next = NULL;

            // remove the now-used node from the free list
            header_array[tracker]->status = 1;      // set the status to 1 now that it is partially occupied
            header_array[tracker] = header_array[tracker]->next;    // the pointer of the array now points to the next item in the free list.

            // decrement tracker
            tracker--;
            // set the next free list
            header_array[tracker]->next = buddy1;
        }

        // now we have a free block we can manipulate

        header_array[block_level]->status = 1;
        void *pointer = header_array[block_level]->address;
        header_array[block_level] = header_array[block_level]->next;

        return pointer;
    }
}


int k_mem_dealloc(void *ptr){
    if(k_mem_initialized == 0){
        return RTX_ERR;
    }
}

int k_mem_count_extfrag(size_t size){
    
}