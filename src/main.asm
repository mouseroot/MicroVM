.org 100
;Author: Mouseroot
;Date: 9/9/2018
;Main code
;
;Small battle simulation

*hp equ 30
*mp equ 31

;   Reset Function
;   
reset:
    set r2,100  ;Set R2 to 100
    psh r2      ;Push 100 onto the stack
    set r1,*hp  ;Set R1 to *hp
    poke r1     ;Set memory of R1 to top of stack

    set r2,100  ;Set R2 to 100
    psh r2      ;Push 100 onto the stack
    set r1,*mp  ;Set R1 to *mp
    poke r1     ;Set memory of R1 to top of stack


;   Main function
;
main:
    call take_hit   ;Simulate a hit
    call check_dead ;Call to check if *hp == 0
    jne main
    hlt


;   Removes 1 from *hp
;
take_hit:
    set r1,*hp  ;Set R1 to *hp
    peek r1     ;Get the value
    pop r1      ;Pop it into R1
    sub r1,1    ;Subtract 1
    psh r1      ;Push the value back onto the stack
    set r2,*hp  ;Set R2 to *hp
    poke r2     ;Set memory of R2 to top of stack
    ret

;   Check if *hp is 0
;
check_dead:
    set r1,*hp  ;Set R1 to *hp
    peek r1     ;Get the value
    pop r1      ;Pop it into R1
    cmp r1,0    ;Compare R1 to 0
    ret
