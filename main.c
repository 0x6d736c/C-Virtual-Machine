/**
 * Implementation of a simple virtual machine, with PUSH, ADD, POP, SET, and HALT instructions exposeed.
 **/

/**
 * Defines the enum of the instruction set.
 * PSH == Push to stack.
 * ADD == Add values on stack, and push to stack.
 * POP == Pop the top value from the stack.
 * SET == Set the value at a specific register.
 * HLT == Halt the program and exit.
 **/
typedef enum {
    PSH,
    ADD,
    POP,
    SET,
    HLT
} ISA;

/**
 * Defines the enum of the virtual machine's registers.
 **/
typedef enum {
    R0, R1, R2, R3, R4, R5, R6, R7,
    REGISTER_COUNT
} Register;

//Creates a test program to process via ISA.
const int program[] = {
    PSH, 30,
    PSH, 5,
    ADD,
    POP,
    SET, R0, 5,
    SET, R1, 10,
    SET, R2, 15,
    HLT
    };

Register registers[REGISTER_COUNT]; //Create an array containing the virtual machine's registers.

int programCounter = 0;         //Program counter. Begins at 0. Used to access instruction to execute.
ISA instruction = 0;            //Initialize instruction to 0. Used to store result of fetchInstruction.
int stack[256];                 //A stack representation with 256 (0-255) spaces for operations.
int stackPointer = -1;          //Pointer for stack operations. 

/**
 * Fetches the instruction at programCounter index. 
 **/
int fetchInstruction(const int program[], int * programCounter) {
    return program[*programCounter];
}

void decodeInstruction(ISA instruction) {
    switch (instruction) {
        case PSH:
            stack[++stackPointer] = program[++programCounter];                          //Move stackPointer up 1, push the value of programCounter + 1.
            break;
        case ADD:
            stack[stackPointer - 1] = stack[stackPointer] + stack[stackPointer - 1];    //Set stackPointer - 1's stack value to the addition of
                                                                                        //value at stackPointer and value of (stackPointer + 1)

            --stackPointer;                                                             //Decrement stackPointer, "popping" the stack.
            break;                   
        case POP:
            stack[stackPointer] = 0;                                                    //Set stack value at stackPointer index to 0.
            --stackPointer;                                                             //Decrement stackPointer, "popping" the stack.
            break;
        case SET:
            registers[program[programCounter + 1]] = program[programCounter + 2];       //Set Register to appropriate value.
            programCounter = programCounter + 2;                                        //Increment programCounter by 2.
            break;
        default:
            break;
    }
}

void evaluate(const int program[]) {
    do {
        instruction = fetchInstruction(program, &programCounter);
        decodeInstruction(instruction);
        ++programCounter;
    } while(instruction != HLT);
}

/**
 * Begin machine execution. Stop once a HLT is reached. 
 **/
int main() {
    evaluate(program);
    return 0;
}