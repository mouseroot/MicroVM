# MicroVM
Virtual machine written in _C_

Assmebler writtin in _python_


4 Registers
```
    R1 General
    R2 Purpose
    R3 Registers
    R4 ...
```

SP - Stack Pointer
IP - Instruction Pointer

# Instructions

_a list of instructions that the machine understands_

NOP
---

No Operation

_This is like a skip, it simply increments the instruction pointer_

    NOP
    nop

SET
---

Sets a register to an immediate value

_This sets a register to an fixed value_

    SET <register>,<immediate>
    set r1,15
    set r4,56



PSH
---

Pushes a register ontop of the stack

_Pushes a value ontop of the stack and increments the stack pointer_

    PSH <register>
    psh r1
    psh r4

POP
---

Pops a value off the stack into a register

_Copies a value from the stack and decrements the stack pointer_

    POP <register>
    pop r3
    pop r1

ADD
---

Adds an immediate value to a register

_Takes the value of the register and adds it to the register_

```Register += (Register + Value);```

    ADD <register>,<immediate>
    add r2,1
    add r4,23

SUB
---

Subtracts an immediate value to a register

_Takes the balue of the register and subtracts it to the register_

```Register -= (Register - Value);```

    SUB <register>,<immediate>
    sub r1,34
    sub r4,1

MOV
---

Moves the value of one register into another

_Copies the value from one register to another_

    MOV <register>,<register>
    mov r1,r4
    mov r3,r4
    mov r2,r4

SYS
---

Calls a VM Syscall

_Calls a internal function from the VM, this is like a syscall_

    SYS <immediate>
    sys 3
    sys 1

CMP
---

Compares a register against an immediate value,
        Sets an equal flag if equal

_Compares the register against an value_

```if(Register == Value)```

    CMP <register>,<immediate>
    cmp r4,1
    cmp r2,0

JMP
---

Unconditonal jump to a specified location

_Simply sets the IP to the address_

    JMP <immediate>
    jmp 100
    jmp 106

HLT
---

Completly stops execution of the VM

_This sets the vm.running bool to FALSE or 0_

    HLT
    hlt

JNE
---

Jump to the specified location if not equal

_If vm.flags.equal is 0 then IP is set to the address_

    JNE <immediate>
    jne 103
    jne 2

JE
---

Jumps to the specified location if equal

_If vm.flags.equal is 1 then IP is set to the address_

    JE <immediate>
    je 4
    je 104

CALL
----

jumps to the specified location and stores
        the old location on the stack

_This is like a subroutine, the concept being that you push the paramaters onto the stack and CALL the subroutine then exit_

    CALL <immediate>
    call 45
    call 102

RET
---

Returns to the address ontop of the stack

_Returns from a called subroutine_

    RET
    ret


PEEK
----

Pushes the value in memory at the specified address
        onto the stack

_The Memory Reading Opcode_

_Allows you to read a value from memory and store it onto the stack_

    PEEK <register>
    peek r4
    peek r1

POKE
---

Writes the value ontop of the stack at the specified address

_The Memory Writing Opcode_

_Allows you to write a value from the top of the stack into the specified address_

    POKE <register>
    poke r1
    poke r3



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