.org 100
;Author: Mouseroot
;Date: 9/9/2018
;Main code
;

main:
    set r1,15   ;Set r1 to 15
    psh r1      ;Push r1 to stack

    set r2,141  ;set r2 to 141
    poke r2     ;set @141 to R1 (15)

next:
    set r4,20   ;Set r4 to 20
    psh r4      ;Push r4 to stack

    set r4,142  ;Set r4 to 142
    poke r4     ;set @142 to R4 (20)


    hlt         ;Stop Execution