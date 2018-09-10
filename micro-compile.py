import re
R1 = 1
R2 = 2
R3 = 3
R4 = 4

SP = 5
IP = 6


NOP = 0
SET = 1
PSH = 2
POP = 3
ADD = 4
SUB = 5
MOV = 6
SYS = 7
CMP = 8
JMP = 9
HLT = 10
JNZ = 11
CALL = 12
RET = 13

JE = 14

PEEK = 15
POKE = 16


def get_reg(reg):
    reg = reg.lower()
    if reg == "r1":
        return R1
    elif reg == "r2":
        return R2
    elif reg == "r3":
        return R3
    elif reg == "r4":
        return R4

def get_syscall(syscall):
    syscall = syscall.lower()
    if syscall == "write_char":
        return WRITE_CHAR
    elif syscall == "read_char":
        return READ_CHAR

def translate(name):
    org = name
    name = name.upper()

    if name == "SET":
        return SET
    elif name == "PSH":
        return PSH
    elif name == "POP":
        return POP
    elif name == "ADD":
        return ADD
    elif name == "SUB":
        return SUB
    elif name == "MOV":
        return MOV
    elif name == "SYS":
        return SYS
    elif name == "CMP":
        return CMP
    elif name == "JMP":
        return JMP
    elif name == "HLT":
        return HLT
    elif name == "JNE":
        return JNZ
    elif name == "CALL":
        return CALL
    elif name == "RET":
        return RET
    elif name == "NOP":
        return NOP
    elif name == "JE":
        return JE
    
    elif name == "PEEK":
        return PEEK
    elif name == "POKE":
        return POKE


    elif name == "R1":
        return R1
    elif name == "R2":
        return R2
    elif name == "R3":
        return R3
    elif name == "R4":
        return R4

    elif name == "SP":
        return SP
    elif name == "IP":
        return IP

    else:
        return org


def remove_comment(line):
    if line.find(";") > 0:
        index = line.find(";")
        return line[:index].rstrip()
    else:
        return line


print("MicroVM Assembler")
src_name = input("File to assemble >")
with open(src_name) as inf:
    code = []
    labels = {}
    _vars = {}
    org = 100
    lines = inf.readlines()
    for line in lines:
        if line == "\n":
            pass
        if line.startswith(";"):
            pass

        if line.isspace():
            pass
        else:
            try:
                line = line.lstrip()
                line = remove_comment(line)

                #Skip comments
                if line.startswith(";"):
                    pass

                #Constants
                elif "equ" in line:
                    if len(line.split("equ")) > 0:
                        name = line.split("equ")[0].strip(" ")
                        val = line.split("equ")[1].strip("\n").strip(" ")
                        _vars[name] = val
                        print(_vars)
                        pass

                #Set file origin
                elif line.startswith(".org"):
                    org = int(line.split(".org")[1].strip(" "))
                    print(f"Originating at @{org}")
                    pass
                #assembler code
                else:
                    length = line.replace("\n","").split(" ")
                    #if a single mneonic
                    if len(length) == 1:
                        op = line.replace("\n","")
                        code.append(op)
                    #if more then one
                    else:
                        op = line.replace("\n","").split(" ")[0]
                        code.append(op)
                        parts = line.replace("\n","").split(" ")[1].split(",")
                        code.append(parts[0])
                        #check for Chars
                        if parts[1].startswith("%"):
                            res = parts[1].replace("%","")
                            code.append(str(ord(res)))
                        else:
                            code.append(parts[1])
            except IndexError:
                pass



    #get labels
    for index,co in enumerate(code):
        if co.endswith(":"):
            name = co.replace(":","")
            labels[name] = index
            code.remove(co)

    #replace labels
    for it in code:
        if it in labels:
            ix = code.index(it)
            val = abs(int(labels[it]) + org - 1)
            code[ix] = it.replace(it,str(val))
    
    #replace vars
    for v in code:
        if v in _vars:
            index = code.index(v)
            val = _vars[v]
            code[index] = v.replace(v,val)

    print(f"{len(code)} Bytes")
    fname = input("File to write>")
    path = f"MicroVM\Debug\{fname}"

    with open(fname,"wb") as of:
        for i,op in enumerate(code):
            
            bit = translate(op)
            print(f"Writing {i} {bit} -> {op}")
            of.write(int(bit).to_bytes(1,byteorder="big"))


