# Lab 3 Grading Report

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
Cooperative multitasking still works — several tasks created using osCreateTask, which call osYield (after at least 1ms of execution time but before its deadline), will take turns running

### expected output
```
---- test1 ----
1
2
3
1
2
3
1
2
3
1
2
3
1
2
3
<serial timeout>
<end of test>
```
### your output
```
---- test1 ----
<serial timeout>
<end of test>

```
### your score: 0.00/1.00

## test2
If a task never yields, when its deadline is reached the kernel will pre-empt it (with the currently most urgent task). When the task is resumed later it will continue from where it was interrupted.

### expected output
```
---- test2 ----
A0 =0, B0 =0
A1 =[8000-40000], B1 =1
A2 =[16000-80000], B2 =2
A3 =[24000-120000], B3 =3
A4 =[32000-160000], B4 =4
<serial timeout>
<end of test>
```
### your output
```
---- test2 ----
<serial timeout>
<end of test>

```
### your score: 0.00/1.00

## test3
Task stacks are created dynamically using k_mem_alloc, and are freed on osTaskExit. (If the heap is exhausted the task will not be created and will return RTX_ERR.)

### expected output
```
---- test3 ----
creating tasks with 0x1000 stack size until stack space is exhausted...
created task with tid-1, stack_high=0x2000b440
created task with tid-2, stack_high=0x2000d440
created task with tid-3, stack_high=0x2000f440
PASS: osCreateTask failed (expected)

starting tasks...
task-1
task-2
stack_high of exiting task: 0x2000d440
task exiting...
task-3
creating new task
stack_high of newly created task: 0x2000d440
PASS: task stack freed & reused

task-4
<serial timeout>
<end of test>
```
### your output
```
---- test3 ----
creating tasks with 0x1000 stack size until stack space is exhausted...
<serial timeout>
<end of test>

```
### your score: 0.00/1.00

## test4
Several tasks created using osCreateDeadlineTask with different deadlines will be started according to the order of "earliest deadline first"

### expected output
```
---- test4 ----
first
second
third
fourth
<serial timeout>
<end of test>
```
### your output
```
---- test4 ----
<serial timeout>
<end of test>

```
### your score: 0.00/1.00

## test5
One task can run periodically via osPeriodYield

### expected output
```
---- test5 ----
Using DWT for timing

A started 
Resume1 delta time =[3000-5000] us
Resume2 delta time =[3000-5000] us
Resume3 delta time =[3000-5000] us
Resume4 delta time =[3000-5000] us
Resume5 delta time =[3000-5000] us
Resume6 delta time =[3000-5000] us
Resume7 delta time =[3000-5000] us
Resume8 delta time =[3000-5000] us
Resume9 delta time =[3000-5000] us
Resume10 delta time =[3000-5000] us
<serial timeout>
<end of test>
```
### your output
```
---- test5 ----
Using DWT for timing

<serial timeout>
<end of test>

```
### your score: 0.00/1.00

## test6
Multiple tasks can run periodically via osPeriodYield, taking turns correctly; e.g. simple_periodic_task_test.c

### expected output
```
---- test6 ----
0, 0, 1
1, 1, 3
2, 1, 5
3, 1, 7
4, 2, 9
5, 2, 11
6, 2, 13
7, 3, 15
8, 3, 17
9, 3, 19
10, 4, 21
11, 4, 23
12, 4, 25
13, 5, 27
14, 5, 29
15, 5, 31
16, 6, 33
17, 6, 35
18, 6, 37
19, 7, 39
<serial timeout>
<end of test>
```
### your output
```
---- test6 ----
<serial timeout>
<end of test>

```
### your score: 0.00/1.00

## test7
A simple task created with osCreateTask can use osSleep to run occasionally according to an arbitrary time schedule. 

### expected output
```
---- test7 ----
Using DWT for timing

Task started
osSleep 5 ms
Awake1 delta time =[4000-6000] us
osSleep 21 ms
Awake2 delta time =[20000-22000] us
osSleep 300 ms
Awake3 delta time =[299000-301000] us
osSleep 1 ms
Awake4 delta time =[100-2000] us

<serial timeout>
<end of test>
```
### your output
```
---- test7 ----
Using DWT for timing

<serial timeout>
<end of test>

```
### your score: 0.00/1.00

## test8
Using osSetDeadline to make another task more urgent than the RUNNING task will trigger a context switch. And that task's deadline is permanently changed in future iterations. 

### expected output
```
---- test8 ----
A
B
C
A
B
C
A
set C 2ms
C
B
C
A
B
C
C
A
B
C
C
<serial timeout>
<end of test>
```
### your output
```
---- test8 ----
<serial timeout>
<end of test>

```
### your score: 0.00/1.00

## test9
Robustness -- test #6 (or similar) runs continuously without glitches for at least 500 iterations

### expected output
```
---- test9 ----
0, 0
1, 1
2, 1
3, 1
4, 2
5, 2
6, 2
7, 3
8, 3
9, 3
10, 4
11, 4
12, 4
13, 5
14, 5
15, 5
...
493, 165
494, 165
495, 165
496, 166
497, 166
498, 166
499, 167
<serial timeout>
<end of test>
```
### your output
```
---- test9 ----
<serial timeout>
<end of test>

```
### your score: 0.00/1.00

## test10
Timing accuracy e.g. two periodic tasks execute on time within +-0.5ms accuracy

### expected output
```
---- test10 ----
Using DWT for timing

measured execution time of Task B: 7209 us

Timestamps of Task A (deadline 4ms, execution time ~0.01ms) 
A start1 =[0+-500] us
A start2 =[4000+-500] us
A start3 =[8000+-500] us
A start4 =[12000+-500] us
A start5 =[16000+-500] us
A start6 =[20000+-500] us
A start7 =[24000+-500] us
A start8 =[28000+-500] us
A start9 =[32000+-500] us
A start10 =[36000+-500] us

Timestamps of Task B (deadline 11ms, execution time ~7.2ms): 
B start1 =[10+-500] us, B end1 =[7220+-500] us
B start2 =[11000+-500] us, B end2 =[18220+-500] us
B start3 =[22000+-500] us, B end3 =[29220+-500] us

<serial timeout>
<end of test>
```
### your output
```
---- test10 ----
<serial timeout>
<end of test>

```
### your score: 0.00/1.00

## marking comments
{notes}



