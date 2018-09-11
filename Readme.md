# MicroVM
Virtual machine written in C
Assmebler writtin in python


4 Registers
```
    R1
    R2
    R3
    R4
```

# Instructions
```
    NOP - No Operation

    SET - Sets a register to an immediate value

    PSH - Pushes a register ontop of the stack

    POP - Pops a value off the stack into a register

    ADD - Adds an immediate value to a register

    SUB - Subtracts an immediate value to a register

    MOV - Moves the value of one register into another

    SYS - Calls a VM Syscall

    CMP - Compares a register against an immediate value
            Sets an equal flag if equal
    
    JMP - Unconditonal jump to a specified location

    HLT - Completly stops execution of the VM

    JNE - Jump to the specified location if not equal

    JE  - Jumps to the specified location if equal

    CALL - jumps to the specified location and stores
            the old location on the stack

    RET  - Returns to the address ontop of the stack

    PEEK - Pushes the value in memory at the specified address
            onto the stack

    POKE - Writes the value ontop of the stack at the specified address

``` 

# Assembling the firmware and applications
```
    $ python micro-compile.py
    File to assemble >src\main.asm
    ...
    ...
    File to write>main.bin

    $ python micro-compile.py
    File to assemble >src\main.asm
    ...
    ...
    File to write>main.bin
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
```
