# Lab 2 Grading Report

## Table of Contents
[[_TOC_]]

## test0
Compilation & compatibility with evaluation framework ~ calls osKernelInit, k_mem_init, and printf.

### expected output
```
---- test0 ----
PASS: build successful
<serial timeout>
<end of test>
```
### your output
```
---- test0 ----
PASS: build successful
<serial timeout>
<end of test>

```
### your score: 1.00/1.00

## test1
Allocate function is able to find free space if it exists.

### expected output
```
---- test1 ----
k_mem_alloc 933 bytes, ptr=0x2000a7e8
k_mem_alloc 743 bytes, ptr=0x2000abe8
k_mem_alloc 262 bytes, ptr=0x2000afe8
k_mem_alloc 529 bytes, ptr=0x2000b3e8
k_mem_alloc 700 bytes, ptr=0x2000b7e8
Validating buffer contents... 
PASS: no corrupted buffers 
PASS: all k_mem_alloc calls successful 
<serial timeout>
<end of test>
```
### your output
```
---- test1 ----
k_mem_alloc 933 bytes, ptr=0x2000a844
k_mem_alloc 743 bytes, ptr=0x2000ac44
k_mem_alloc 262 bytes, ptr=0x2000b044
k_mem_alloc 529 bytes, ptr=0x2000b444
k_mem_alloc 700 bytes, ptr=0x2000b844
Validating buffer contents... 
PASS: no corrupted buffers 
PASS: all k_mem_alloc calls successful 
<serial timeout>
<end of test>

```
### your score: 1.00/1.00

## test2
Deallocation function makes a block available for allocation again.

### expected output
```
---- test2 ----
allocating 4 bytes...
allocating large block...
deallocating the first block...
PASS: k_mem_dealloc returned OK
allocating 4 bytes again... should fit into the first spot
PASS: freed memory was used again

<serial timeout>
<end of test>
```
### your output
```
---- test2 ----
allocating 4 bytes...
allocating large block...
deallocating the first block...
PASS: k_mem_dealloc returned OK
allocating 4 bytes again... should fit into the first spot
PASS: freed memory was used again

<serial timeout>
<end of test>

```
### your score: 1.00/1.00

## test3
Deallocated blocks are coalesced together correctly, according to the buddy scheme.

### expected output
```
---- test3 ----
1 byte block allocated, ptr=0x2000b3d8
33 byte block allocated, ptr=0x2000b418
deallocating 0x2000b3d8
testing if 33 bytes can fit at 0x2000b3d8 
PASS: k_mem_dealloc coalesced with its buddy
257 byte block allocated, ptr=0x2000b5d8
deallocating 0x2000b418
testing if 257 bytes can fit at 0x2000b3d8 
PASS: k_mem_dealloc coalesced three iterations
<serial timeout>
<end of test>
```
### your output
```
---- test3 ----
1 byte block allocated, ptr=0x2000b434
33 byte block allocated, ptr=0x2000b474
deallocating 0x2000b434
testing if 33 bytes can fit at 0x2000b434 
PASS: k_mem_dealloc coalesced with its buddy
257 byte block allocated, ptr=0x2000b634
deallocating 0x2000b474
testing if 257 bytes can fit at 0x2000b434 
PASS: k_mem_dealloc coalesced three iterations
<serial timeout>
<end of test>

```
### your score: 1.00/1.00

## test4
Managed memory blocks are always powers of two in size, smallest block is 32B, which can fit a 4-byte allocation.

### expected output
```
---- test4 ----
1 byte block allocated, ptr=0x2000b478
4 byte block allocated, ptr=0x2000b498
PASS: smallest block is 32B
4 byte block allocated, ptr=0x2000b4b8
PASS: 4 bytes could fit into 32B block
k_mem_alloc 533 bytes, ptr=0x2000b878
k_mem_alloc 243 bytes, ptr=0x2000b678
k_mem_alloc 362 bytes, ptr=0x2000bc78
k_mem_alloc 329 bytes, ptr=0x2000be78
k_mem_alloc 300 bytes, ptr=0x2000c078
k_mem_alloc 708 bytes, ptr=0x2000c478
k_mem_alloc 52 bytes, ptr=0x2000b4f8
k_mem_alloc 156 bytes, ptr=0x2000b578
k_mem_alloc 656 bytes, ptr=0x2000c878
k_mem_alloc 19 bytes, ptr=0x2000c278
k_mem_alloc 711 bytes, ptr=0x2000cc78
k_mem_alloc 851 bytes, ptr=0x2000d078
k_mem_alloc 543 bytes, ptr=0x2000d478
k_mem_alloc 605 bytes, ptr=0x2000d878
k_mem_alloc 708 bytes, ptr=0x2000dc78
k_mem_alloc 293 bytes, ptr=0x2000e078
k_mem_alloc 30 bytes, ptr=0x2000c2b8
k_mem_alloc 66 bytes, ptr=0x2000c2f8
k_mem_alloc 569 bytes, ptr=0x2000e478
k_mem_alloc 332 bytes, ptr=0x2000e278
Validating block sizes...
PASS: all blocks could be power of 2
<serial timeout>
<end of test>

```
### your output
```
---- test4 ----
1 byte block allocated, ptr=0x2000b4d4
4 byte block allocated, ptr=0x2000b4f4
PASS: smallest block is 32B
4 byte block allocated, ptr=0x2000b514
PASS: 4 bytes could fit into 32B block
k_mem_alloc 533 bytes, ptr=0x2000b8d4
k_mem_alloc 243 bytes, ptr=0x2000b6d4
k_mem_alloc 362 bytes, ptr=0x2000bcd4
k_mem_alloc 329 bytes, ptr=0x2000bed4
k_mem_alloc 300 bytes, ptr=0x2000c0d4
k_mem_alloc 708 bytes, ptr=0x2000c4d4
k_mem_alloc 52 bytes, ptr=0x2000b554
k_mem_alloc 156 bytes, ptr=0x2000b5d4
k_mem_alloc 656 bytes, ptr=0x2000c8d4
k_mem_alloc 19 bytes, ptr=0x2000c2d4
k_mem_alloc 711 bytes, ptr=0x2000ccd4
k_mem_alloc 851 bytes, ptr=0x2000d0d4
k_mem_alloc 543 bytes, ptr=0x2000d4d4
k_mem_alloc 605 bytes, ptr=0x2000d8d4
k_mem_alloc 708 bytes, ptr=0x2000dcd4
k_mem_alloc 293 bytes, ptr=0x2000e0d4
k_mem_alloc 30 bytes, ptr=0x2000c314
k_mem_alloc 66 bytes, ptr=0x2000c354
k_mem_alloc 569 bytes, ptr=0x2000e4d4
k_mem_alloc 332 bytes, ptr=0x2000e2d4
Validating block sizes...
PASS: all blocks could be power of 2
<serial timeout>
<end of test>

```
### your score: 1.00/1.00

## test5
32KB of heap memory are managed; bonus awarded if full heap size is managed

### expected output
```
---- test5 ----

allocating large block that fills up the heap...
PASS: largest block is 32744 bytes

checking if bonus was attempted...
found additional capacity of 0B
test completed
<serial timeout>
<end of test>
```
### your output
```
---- test5 ----

allocating large block that fills up the heap...
PASS: largest block is 32748 bytes

checking if bonus was attempted...
found additional capacity of 0B
test completed
<serial timeout>
<end of test>

```
### your score: 1.00/1.00

## test6
Deallocating a random pointer will return an error.

### expected output
```
---- test6 ----
allocating one block, then try to deallocate a pointer outside of this block...
PASS: k_mem_dealloc returned error (expected)
allocating large block...
deallocating a pointer part way in the large block
PASS: k_mem_dealloc returned error (expected)
try to deallocate a valid pointer twice...
PASS: k_mem_dealloc returned error on second call (expected)
<serial timeout>
<end of test>
```
### your output
```
---- test6 ----
allocating one block, then try to deallocate a pointer outside of this block...
PASS: k_mem_dealloc returned error (expected)
allocating large block...
deallocating a pointer part way in the large block
PASS: k_mem_dealloc returned error (expected)
try to deallocate a valid pointer twice...
PASS: k_mem_dealloc returned error on second call (expected)
<serial timeout>
<end of test>

```
### your score: 1.00/1.00

## test7
Only the owner can free a block of memory (this will require using the kernel to run 2 tasks and calling allocate & deallocate from those tasks).

### expected output
```
allocating from first task
deallocating from first task
PASS: k_mem_dealloc successful
allocating again from first task
deallocating from second task
PASS: k_mem_dealloc returned error (expected)
<serial timeout>
<end of test>
```
### your output
```
allocating from first task
deallocating from first task
PASS: k_mem_dealloc successful
allocating again from first task
deallocating from second task
PASS: k_mem_dealloc returned error (expected)
<serial timeout>
<end of test>

```
### your score: 1.00/1.00

## test8
The entire heap space should be back in one piece after deallocating everything (bonus version should be back to starting state, shown below)

### expected output
```
---- test8 ----
Maximum allocation accepted at the start = 32756 bytes
Found additional capacity of 2624B
Deallocating everything...

Commence random usage

itr=0, alloc 933 bytes, ptr=0x200135c4
itr=1, alloc 743 bytes, ptr=0x200139c4
itr=2, alloc 262 bytes, ptr=0x20013dc4
also dealloc mem from itr 1, ptr=0x200139c4, ~743 bytes
itr=3, alloc 700 bytes, ptr=0x200139c4
itr=4, alloc 508 bytes, ptr=0x2000b5c4
also dealloc mem from itr 0, ptr=0x200135c4, ~933 bytes
itr=5, alloc 256 bytes, ptr=0x2000b9c4
itr=6, alloc 256 bytes, ptr=0x2000bbc4
[...]
itr=47, alloc 352 bytes, ptr=0x2000f1c4
itr=48, alloc 665 bytes, ptr=0x2000cdc4
also dealloc mem from itr 47, ptr=0x2000f1c4, ~352 bytes
itr=49, alloc 738 bytes, ptr=0x200139c4
now deallocate everything...
dealloc mem from itr 7, ptr=0x2000bdc4, ~351 bytes
dealloc mem from itr 8, ptr=0x2000c1c4, ~843 bytes
[...]
dealloc mem from itr 46, ptr=0x20013fc4, ~7 bytes
dealloc mem from itr 48, ptr=0x2000cdc4, ~665 bytes
dealloc mem from itr 49, ptr=0x200139c4, ~738 bytes
retest capacity...

Maximum allocation accepted at the end = 32756 bytes
Found additional capacity of 2624B
PASS: heap space is same capacity as the start
<serial timeout>
<end of test>
```
### your output
```
---- test8 ----
Maximum allocation accepted at the start = 32748 bytes
Found additional capacity of 0B
Deallocating everything...

Commence random usage

itr=0, alloc 933 bytes, ptr=0x2000b5bc
itr=1, alloc 743 bytes, ptr=0x2000b9bc
itr=2, alloc 262 bytes, ptr=0x2000bdbc
also dealloc mem from itr 1, ptr=0x2000b9bc, ~743 bytes
itr=3, alloc 700 bytes, ptr=0x2000b9bc
itr=4, alloc 508 bytes, ptr=0x2000c1bc
also dealloc mem from itr 0, ptr=0x2000b5bc, ~933 bytes
itr=5, alloc 256 bytes, ptr=0x2000bfbc
itr=6, alloc 256 bytes, ptr=0x2000b5bc
also dealloc mem from itr 3, ptr=0x2000b9bc, ~700 bytes
itr=7, alloc 351 bytes, ptr=0x2000b7bc
itr=8, alloc 843 bytes, ptr=0x2000b9bc
also dealloc mem from itr 4, ptr=0x2000c1bc, ~508 bytes
itr=9, alloc 393 bytes, ptr=0x2000c1bc
itr=10, alloc 330 bytes, ptr=0x2000c3bc
also dealloc mem from itr 6, ptr=0x2000b5bc, ~256 bytes
itr=11, alloc 169 bytes, ptr=0x2000b5bc
itr=12, alloc 932 bytes, ptr=0x2000c5bc
also dealloc mem from itr 11, ptr=0x2000b5bc, ~169 bytes
itr=13, alloc 972 bytes, ptr=0x2000c9bc
itr=14, alloc 868 bytes, ptr=0x2000cdbc
also dealloc mem from itr 5, ptr=0x2000bfbc, ~256 bytes
itr=15, alloc 549 bytes, ptr=0x2000d1bc
itr=16, alloc 592 bytes, ptr=0x2000d5bc
also dealloc mem from itr 9, ptr=0x2000c1bc, ~393 bytes
itr=17, alloc 551 bytes, ptr=0x2000d9bc
itr=18, alloc 427 bytes, ptr=0x2000b5bc
also dealloc mem from itr 16, ptr=0x2000d5bc, ~592 bytes
itr=19, alloc 624 bytes, ptr=0x2000d5bc
itr=20, alloc 635 bytes, ptr=0x2000ddbc
also dealloc mem from itr 10, ptr=0x2000c3bc, ~330 bytes
itr=21, alloc 862 bytes, ptr=0x2000c1bc
itr=22, alloc 484 bytes, ptr=0x2000bfbc
also dealloc mem from itr 13, ptr=0x2000c9bc, ~972 bytes
itr=23, alloc 301 bytes, ptr=0x2000c9bc
itr=24, alloc 710 bytes, ptr=0x2000e1bc
also dealloc mem from itr 12, ptr=0x2000c5bc, ~932 bytes
itr=25, alloc 876 bytes, ptr=0x2000c5bc
itr=26, alloc 431 bytes, ptr=0x2000cbbc
also dealloc mem from itr 19, ptr=0x2000d5bc, ~624 bytes
itr=27, alloc 397 bytes, ptr=0x2000d5bc
itr=28, alloc 675 bytes, ptr=0x2000e5bc
also dealloc mem from itr 2, ptr=0x2000bdbc, ~262 bytes
itr=29, alloc 344 bytes, ptr=0x2000bdbc
itr=30, alloc 134 bytes, ptr=0x2000d7bc
also dealloc mem from itr 25, ptr=0x2000c5bc, ~876 bytes
itr=31, alloc 629 bytes, ptr=0x2000c5bc
itr=32, alloc 30 bytes, ptr=0x2000d8bc
also dealloc mem from itr 23, ptr=0x2000c9bc, ~301 bytes
itr=33, alloc 126 bytes, ptr=0x2000c9bc
itr=34, alloc 743 bytes, ptr=0x2000e9bc
also dealloc mem from itr 32, ptr=0x2000d8bc, ~30 bytes
itr=35, alloc 256 bytes, ptr=0x2000edbc
itr=36, alloc 932 bytes, ptr=0x2000f1bc
also dealloc mem from itr 34, ptr=0x2000e9bc, ~743 bytes
itr=37, alloc 509 bytes, ptr=0x2000e9bc
itr=38, alloc 119 bytes, ptr=0x2000d8bc
also dealloc mem from itr 31, ptr=0x2000c5bc, ~629 bytes
itr=39, alloc 327 bytes, ptr=0x2000efbc
itr=40, alloc 719 bytes, ptr=0x2000c5bc
also dealloc mem from itr 17, ptr=0x2000d9bc, ~551 bytes
itr=41, alloc 824 bytes, ptr=0x2000d9bc
itr=42, alloc 596 bytes, ptr=0x2000f5bc
also dealloc mem from itr 27, ptr=0x2000d5bc, ~397 bytes
itr=43, alloc 356 bytes, ptr=0x2000d5bc
itr=44, alloc 184 bytes, ptr=0x2000cabc
also dealloc mem from itr 41, ptr=0x2000d9bc, ~824 bytes
itr=45, alloc 245 bytes, ptr=0x2000d9bc
itr=46, alloc 7 bytes, ptr=0x2000dbbc
also dealloc mem from itr 40, ptr=0x2000c5bc, ~719 bytes
itr=47, alloc 352 bytes, ptr=0x2000c5bc
itr=48, alloc 665 bytes, ptr=0x2000f9bc
also dealloc mem from itr 47, ptr=0x2000c5bc, ~352 bytes
itr=49, alloc 738 bytes, ptr=0x2000c5bc
now deallocate everything...
dealloc mem from itr 7, ptr=0x2000b7bc, ~351 bytes
dealloc mem from itr 8, ptr=0x2000b9bc, ~843 bytes
dealloc mem from itr 14, ptr=0x2000cdbc, ~868 bytes
dealloc mem from itr 15, ptr=0x2000d1bc, ~549 bytes
dealloc mem from itr 18, ptr=0x2000b5bc, ~427 bytes
dealloc mem from itr 20, ptr=0x2000ddbc, ~635 bytes
dealloc mem from itr 21, ptr=0x2000c1bc, ~862 bytes
dealloc mem from itr 22, ptr=0x2000bfbc, ~484 bytes
dealloc mem from itr 24, ptr=0x2000e1bc, ~710 bytes
dealloc mem from itr 26, ptr=0x2000cbbc, ~431 bytes
dealloc mem from itr 28, ptr=0x2000e5bc, ~675 bytes
dealloc mem from itr 29, ptr=0x2000bdbc, ~344 bytes
dealloc mem from itr 30, ptr=0x2000d7bc, ~134 bytes
dealloc mem from itr 33, ptr=0x2000c9bc, ~126 bytes
dealloc mem from itr 35, ptr=0x2000edbc, ~256 bytes
dealloc mem from itr 36, ptr=0x2000f1bc, ~932 bytes
dealloc mem from itr 37, ptr=0x2000e9bc, ~509 bytes
dealloc mem from itr 38, ptr=0x2000d8bc, ~119 bytes
dealloc mem from itr 39, ptr=0x2000efbc, ~327 bytes
dealloc mem from itr 42, ptr=0x2000f5bc, ~596 bytes
dealloc mem from itr 43, ptr=0x2000d5bc, ~356 bytes
dealloc mem from itr 44, ptr=0x2000cabc, ~184 bytes
dealloc mem from itr 45, ptr=0x2000d9bc, ~245 bytes
dealloc mem from itr 46, ptr=0x2000dbbc, ~7 bytes
dealloc mem from itr 48, ptr=0x2000f9bc, ~665 bytes
dealloc mem from itr 49, ptr=0x2000c5bc, ~738 bytes
retest capacity...

Maximum allocation accepted at the end = 8172 bytes
Found additional capacity of 24576B
FAIL: heap space capacity has changed
<serial timeout>
<end of test>

```
### your score: 0.00/1.00

## test9
Execution time over a series of allocations; excution time over a series of deallocations. (Thresholds are calculated as the midpoint between the compiler's implementation and linear search through all blocks.)

### expected output
```
---- test9 ----
Using DWT for timing

k_mem_alloc runtime=80901 [this is the threshold]
Time per iteration:
... 

k_mem_dealloc runtime=65369 [this is the threshold]
Time per iteration:
... 

<serial timeout>
<end of test>

```
### your output
```
---- test9 ----
Using DWT for timing

k_mem_alloc runtime=32237
Time per iteration:
1629, 171, 315, 171, 459, 171, 315, 171, 603, 171, 315, 171, 459, 171, 315, 171, 747, 171, 315, 171, 459, 171, 315, 171, 603, 171, 315, 171, 459, 171, 315, 171, 891, 171, 315, 171, 459, 171, 315, 171, 603, 171, 315, 171, 459, 171, 315, 171, 747, 171, 315, 171, 459, 171, 315, 171, 603, 171, 315, 171, 459, 171, 315, 171, 1035, 171, 315, 171, 459, 171, 315, 171, 603, 171, 315, 171, 459, 171, 315, 171, 747, 171, 315, 171, 459, 171, 315, 171, 603, 171, 315, 171, 459, 171, 315, 171, 891, 171, 315, 170, 

k_mem_dealloc runtime=36828
Time per iteration:
227, 361, 210, 973, 210, 357, 210, 511, 210, 357, 210, 665, 210, 357, 210, 511, 210, 357, 210, 819, 210, 357, 210, 511, 210, 357, 210, 665, 210, 357, 210, 511, 210, 357, 210, 1127, 210, 357, 210, 511, 210, 357, 210, 665, 210, 357, 210, 511, 210, 357, 210, 819, 210, 357, 210, 511, 210, 357, 210, 665, 210, 357, 210, 511, 210, 357, 210, 973, 210, 357, 210, 511, 210, 357, 210, 665, 210, 357, 210, 511, 210, 357, 210, 819, 210, 357, 210, 511, 210, 357, 210, 665, 210, 357, 210, 511, 210, 357, 210, 1730, 

<serial timeout>
<end of test>

```
### your score: 1.00/1.00

## test10
Execution time performance over random usage: allocations with random sizes interspersed with deallocations with random (valid) addresses; bonus awarded if top 10% in class.

### expected output
```
---- test10 ----
Using DWT for timing

Total runtime=69459.5 [this is the threshold]
Time per iteration (^ denotes deallocations):
...

<serial timeout>
<end of test>
```
### your output
```
---- test10 ----
Using DWT for timing

Total runtime=48523
Time per iteration (^ denotes deallocations):
1534, 1632^, 1532, 351, 267, 361, 384^, 417, 247, 267, 545, 262^, 273, 515, 247, 401, 431^, 417, 267, 823, 257, 269^, 273, 411, 247, 257, 269^, 233, 207, 267, 545, 262^, 273, 267, 535, 237, 262^, 521, 247, 267, 957, 1031^, 849, 267, 535, 257, 269^, 273, 247, 555, 381, 246^, 417, 247, 227, 257, 269^, 253, 391, 495, 813, 246^, 213, 267, 351, 401, 262^, 253, 371, 267, 257, 253^, 561, 247, 227, 381, 237^, 417, 247, 207, 381, 269^, 273, 351, 371, 977, 230^, 397, 247, 227, 217, 368^, 417, 267, 679, 237, 262^, 273, 351, 267, 401, 368^, 273, 351, 699, 257, 269^, 273, 535, 267, 237, 214^, 685, 267, 247, 649, 230^, 253, 391, 247, 833, 262^, 273, 267, 534, 

<serial timeout>
<end of test>

```
### your score: 1.00/1.00

## Test 5 with build workaround
If your test 5 above did not build and this test builds, then this is your test 5 score. 
(It is normal if only one of test 5 or 11 manages to build). 

### expected output
```
---- test5 ----

allocating large block that fills up the heap...
PASS: largest block is 32744 bytes

checking if bonus was attempted...
found additional capacity of 0B
test completed
<serial timeout>
<end of test>
```
### your output
```
<build failed>

```
### your score: 0.00/1.00



