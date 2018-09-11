#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NOP		0
#define SET		1
#define PSH		2
#define POP		3
#define ADD		4
#define SUB		5
#define MOV		6
#define SYS		7
#define CMP		8
#define JMP		9
#define HLT		10
#define JNE		11
#define CALL	12
#define RET		13

#define JE		14

#define PEEK	15
#define POKE	16

#define R1		1
#define R2		2
#define R3		3
#define R4		4

#define Entrypoint 100

typedef struct {
	int zero;
	int equal;
} Flags;

typedef struct {
	int r1;
	int r2;
	int r3;
	int r4;
	int sp;
	int ip;
} GPR;

typedef struct {
	GPR registers;
	Flags flags;
	int memory[255];
	int stack[100];
	int running; 
} MicroVM;


char firmware[] = {
	JMP,Entrypoint,
	HLT
};

int app[] = {
	SET,R1,15,
	PSH,R1,
	SET,R1,5,
	POKE,R1,

	HLT,
};

//Gets the file size
int fsize(char *filename) {
	FILE *fp = fopen(filename, "r");
	if (fp != NULL) {
		fseek(fp, 0, 2);
		int fsize = ftell(fp);
		fclose(fp);
		return fsize;
	}
	return -1;
}

//Displays Hi and Lo memory
void display_memory(MicroVM *vm) {
	printf("Hi Memory (Firmware)\n");
	printf("#%d\t%02X %02X %02X %02X %02X\n", 0, vm->memory[0], vm->memory[1], vm->memory[2], vm->memory[3], vm->memory[4]);
	printf("#%d\t%02X %02X %02X %02X %02X\n", 5, vm->memory[5], vm->memory[6], vm->memory[7], vm->memory[8], vm->memory[9]);
	printf("Low Memory\n");
	for (int i = 0; i < 100; i+=5) {
		printf("#%d\t%02X %02X %02X %02X %02X\n",Entrypoint+i, vm->memory[Entrypoint + i], vm->memory[Entrypoint + i+1], vm->memory[Entrypoint + i + 2], vm->memory[Entrypoint + i + 3], vm->memory[Entrypoint + i + 4]);
	}
}

//Displays the stack
void display_stack(MicroVM *vm) {
	printf("Stack\n");
	for (int i = 0; i < 10; i++) {
		printf("#%d\t%d\n",i, vm->stack[i]);
	}
}

//Displays the registers
void display(MicroVM *vm) {
	printf("R1: %02X\tR2: %02X\tR3: %02X\tR4: %02X\n", vm->registers.r1, vm->registers.r2, vm->registers.r3, vm->registers.r4);
	printf("IP: %02X\tSP: %02X\n", vm->registers.ip, vm->registers.sp);
	printf("Zero: %d Equal: %d\n", vm->flags.zero, vm->flags.equal);
}

//Pushes a value onto the stack
void push_stack(MicroVM *vm, int value) {
	vm->stack[vm->registers.sp] = value;
	vm->registers.sp++;
}

//Pops a value off the stack
int pop_stack(MicroVM *vm) {
	int value = vm->stack[vm->registers.sp - 1];
	vm->registers.sp--;
	return value;
}

//Loads a array into memory given an offset
void load_data(MicroVM *vm,int origin, int data[], int size) {
	printf("Loading %d Bytes\n", size);
	for (int i = 0; i < size; i++) {
		vm->memory[origin + i] = data[i];
	}
}

//Loads an array from a file into memory at a given offset
//Returns file size or -1
int load_file(MicroVM *vm, int origin, char *filename) {
	FILE *programFile;
	programFile = fopen(filename, "rb");
	if (programFile) {
		int size = fsize(filename);
		if (size > 0) {
			printf("%s is %d bytes\n", filename, size);
			for (int i = 0; i < size; i++) {
				int read = 0;
				fread(&read, 1, 1, programFile);
				vm->memory[origin + i] = read;
			}
			return size;
		}
	}
	return -1;
}

//Resets the virtual machine
void reset(MicroVM *vm) {
	vm->registers.r1 = 0;
	vm->registers.r2 = 0;
	vm->registers.r3 = 0;
	vm->registers.r4 = 0;

	vm->registers.sp = 0;
	vm->registers.ip = 0;

	vm->flags.zero = 0;
	vm->flags.equal = 0;
	for (int i = 0; i < 255; i++) {
		vm->memory[i] = 0;
	}
	for (int i = 0; i < 100; i++) {
		vm->stack[i] = 0;
	}
	vm->running = 0;
}

void set_register(MicroVM *vm, int r_index, int value) {
	switch (r_index) {
	case R1:
		vm->registers.r1 = value;
		break;

	case R2:
		vm->registers.r2 = value;
		break;

	case R3:
		vm->registers.r3 = value;
		break;

	case R4:
		vm->registers.r4 = value;
		break;
	}
}

int get_register(MicroVM *vm, int r_index) {
	switch (r_index)
	{
	case R1:
		return vm->registers.r1;
		break;

	case R2:
		return vm->registers.r2;
		break;

	case R3:
		return vm->registers.r3;
		break;

	case R4:
		return vm->registers.r4;
		break;

	}
}

int main(int argc, char *argv[]) {
	MicroVM vm;
	reset(&vm);

	//Load firmware
	//load_data(&vm, 0, firmware, sizeof(firmware));
	if (load_file(&vm, 0, "fw.bin") > -1) {
		printf("Firmware loaded\n");
		load_file(&vm, Entrypoint, "main.bin");
		vm.running = 1;
	}
	else {
		printf("Firmware was not loaded\n");
		vm.running = 0;
	}
	printf("Press Enter to continue\n");
	getchar();

	while (vm.running) {

		int op = vm.memory[vm.registers.ip];

		if (op == HLT) {
			printf("Machine HLT\n");
			vm.running = 0;
			display(&vm);
			display_memory(&vm);
			display_stack(&vm);
		}

		if (op == ADD) {
			int dest = vm.memory[vm.registers.ip + 1];
			int value = vm.memory[vm.registers.ip + 2];
			int rval = get_register(&vm, dest);
			int sum = (rval + value);
			set_register(&vm, dest, sum);
			vm.registers.ip += 2;
		}

		if (op == PEEK) {
			int r_index = vm.memory[vm.registers.ip + 1];
			int value = get_register(&vm, r_index);
			int mem = vm.memory[value];
			push_stack(&vm, mem);
			printf("Peeking %d at @%d\n", mem,value);
			vm.registers.ip++;
		}

		if (op == POKE) {
			int r_index = vm.memory[vm.registers.ip + 1];
			int value = pop_stack(&vm);
			//int value = vm.stack[vm.registers.sp - 1];
			int reg = get_register(&vm, r_index);
			vm.memory[reg] = value;
			printf("Pokeing %d at @%d\n", value, reg);
			vm.registers.ip++;
		}

		if (op == SET) {
			int r_index = vm.memory[vm.registers.ip + 1];
			int value = vm.memory[vm.registers.ip + 2];
			set_register(&vm, r_index, value);
			printf("SET R%d %d\n", r_index, value);
			vm.registers.ip +=2;
		}

		if (op == PSH) {
			int r_index = vm.memory[vm.registers.ip + 1];
			int value = get_register(&vm, r_index);
			push_stack(&vm, value);
			printf("PSH R%d (%d)\n", r_index, value);
			vm.registers.ip++;

		}

		if (op == CMP) {
			int r_index = vm.memory[vm.registers.ip + 1];
			int value = vm.memory[vm.registers.ip + 2];
			if (get_register(&vm, r_index) == value) {
				vm.flags.equal = 1;
			}
			if (get_register(&vm, r_index) != value) {
				vm.flags.equal = 0;
			}
			vm.registers.ip += 2;
		}

		if (op == POP) {
			int r_index = vm.memory[vm.registers.ip + 1];
			int value = pop_stack(&vm);
			set_register(&vm, r_index, value);
			printf("POP R%d\n", value);
			vm.registers.ip++;
		}

		if (op == CALL) {
			int addr = vm.memory[vm.registers.ip + 1];
			printf("Call to %d\n", addr);
			push_stack(&vm, vm.registers.ip + 1);
			vm.registers.ip = addr - 1;
		}

		if (op == JMP) {
			int addr = vm.memory[vm.registers.ip + 1];
			printf("JMP to %d\n", addr);
			vm.registers.ip = addr;
		}

		if (op == JE) {
			int addr = vm.memory[vm.registers.ip + 1];
			if (vm.flags.equal == 1) {
				vm.registers.ip = addr;
			}
			else {
				vm.registers.ip++;
			}
		}

		if (op == JNE) {
			int addr = vm.memory[vm.registers.ip + 1];
			if (vm.flags.equal == 0) {
				vm.registers.ip = addr;
			}
			else {
				vm.registers.ip++;
			}
		}

		if (op == RET) {
			vm.registers.ip = pop_stack(&vm);
		}

		if (op == NOP) {
			vm.registers.ip++;
			printf("NOP\n");
		}

		vm.registers.ip++;
	}


	return 0;
}