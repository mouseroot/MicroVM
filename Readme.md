# MicroVM
Virtual machine written in _C_

[MicroVM Wiki](Http://github.com/mouseroot/MicroVM/wiki)

# Specifications


* R1-R4 General Registers
* SP - Stack Pointer
* IP - Instruction Pointer
* 255 Bytes of memory
* 100 Byte Stack
* 17+ Instructions
* Assembler writtin in pure _python_
* VM writtin in pure _C_


# Assembling the firmware and applications

```
$ python micro-compile.py
File to assemble >src\main.asm
...
...
File to write>main.bin

$ python micro-compile.py
File to assemble >src\micro_fw.asm
...
...
File to write>fw.bin
```

# Example Output
```
$./MicroVM
fw.bin is 3 bytes
Firmware loaded
main.bin is 21 bytes
JMP to 99
SET R1 15
PSH R1 (15)
SET R2 141
Pokeing 15 at @141
SET R4 20
PSH R4 (20)
SET R4 142
Pokeing 20 at @142
Machine HLT
R1: 0F  R2: 8D  R3: 00  R4: 8E
IP: 78  SP: 00
Zero: 0 Equal: 0
Hi Memory (Firmware)
#0      09 63 0A 00 00
#5      00 00 00 00 00
Low Memory
#100    01 01 0F 02 01
#105    01 02 8D 10 02
#110    01 04 14 02 04
#115    01 04 8E 10 04
#120    0A 00 00 00 00
#125    00 00 00 00 00
#130    00 00 00 00 00
#135    00 00 00 00 00
#140    00 0F 14 00 00
```

# Sample source (main.asm)
```
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
```
