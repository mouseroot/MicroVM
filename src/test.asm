.org 100

jmp main

message:
.data "ABCD"

main:
    set r1,message  ;Address of message
    set r2,4       ;Size of message
    sys 0
    hlt

