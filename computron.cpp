#include "computron.h"

#include <fstream>
#include <iomanip>
#include <algorithm>

void load_from_file(std::array<int, memorySize>& memory, const std::string& filename) {
    constexpr int sentinel{-99999}; // terminates reading after -99999
    size_t i{0}; 
    std::string line; 
    int instruction; 

    std::ifstream inputFile(filename);
    if(!inputFile) {
        // throw runtime_error exception with string "invalid_input"
        throw std::runtime_error("Error: could not open input file: " + filename + " likely due to an invalid_input"); 
    }

    while(std::getline(inputFile, line)) {
        try {      
            // convert string to integer
            instruction = std::stoi(line); 

            // // Temporary Debug output
            // std::cout << "Read instruction: " << instruction << std::endl;

            if(instruction == sentinel) {
                break; 
            }

            // Check if the instruction is valid
            if (!validWord(instruction)) {
                throw std::runtime_error("Error: instruction is an invalid_input"); 
            }

            // check the storage of the memory 
            if (i >= memorySize) {
                throw std::runtime_error("Error: ran out of memory"); 
            }

            memory[i++] = instruction; 
        } 
        catch (const std::invalid_argument& e) {
            throw std::runtime_error("Error: input file contains an invalid_input (input value is non-numeric)"); 
        }
    }
}

Command opCodeToCommand(size_t opCode) {
    switch(opCode) {
        case 10: 
            return Command::read; 
        case 11:
            return Command::write; 
        case 20:
            return Command::load; 
        case 21:
            return Command::store; 
        case 30:
            return Command::add; 
        case 31:
            return Command::subtract; 
        case 32:
            return Command::divide; 
        case 33:
            return Command::multiply; 
        case 40: 
            return Command::branch; 
        case 41:
            return Command::branchNeg; 
        case 42:
            return Command::branchZero; 
        case 43:
            return Command::halt; 
        default:
            throw std::runtime_error("Error:  Invalid opcode: " + std::to_string(opCode)); 
    } 
}

void execute(std::array<int, memorySize>& memory, 
             int* const acPtr, size_t* const icPtr, 
             int* const irPtr, size_t* const opCodePtr, 
             size_t* const opPtr, 
             const std::vector<int>& inputs) {
    size_t inputIndex{0}; // Tracks input

    do {
        // instruction counter to register
        // instructionRegister = memory[instructionCounter]; 
        // operationCode = instructionRegister / 100; // divide
        // operand = instructionRegister % 100; // remainder
        *irPtr = memory[*icPtr]; 
        *opCodePtr = *irPtr / 100; 
        *opPtr = *irPtr % 100; 

        switch(int word{}; opCodeToCommand(*opCodePtr)) {
            case Command::read:
                // Assign the value of 'word' to the memory location pointed to by 'opPtr'
                // Increment the instruction counter (icPtr) to point to the next instruction
                word = inputs[inputIndex]; 
                memory[*opPtr] = word; 
                inputIndex++; 
                (*icPtr)++; 
                break;             
            case Command::write:
            // Dereference 'icPtr' to access the instruction counter and increment its value by 1
            // use the below cout if needed but comment before submission
            // std::cout << "Contents of " << std::setfill('0') << std::setw(2)
            //           << *opPtr << " : " << memory[*opPtr] << "\n";
                (*icPtr)++; 
                break; 
            case Command::load:
            // Load the value from the memory location pointed to by 'opPtr' into the accumulator (acPtr)
            // Incrment the instruction counter (icPtr) to point to the next instruction
                *acPtr = memory[*opPtr]; 
                (*icPtr)++; 
                break; 
            case Command::store:
            // Store the value in the accumulator (acPtr) into the memory location pointed to by 'opPtr'
            // Increment the instruction counter (icPtr) to move to the next instruction
                memory[*opPtr] = *acPtr; 
                (*icPtr)++; 
                break; 
            case Command::add:
            // Add the value in the accumulator (acPtr) to the value in memory at the location pointed to by 'opPtr' and store the result in 'word'
            // If the result is valid, store it in the accumulator and increment the instruction counter
            // If the result is invalid, throw a runtime error
                word = *acPtr + memory[*opPtr]; 
                if (word < -9999 || word > 9999) {
                    throw std::runtime_error("Error: Addition overflow, invalid_input"); 
                }
                *acPtr = word; 
                (*icPtr)++; 
                break; 
            case Command::subtract: 
            // Subtract the value in memory at the location pointed to by 'opPtr' from the value in the accumulator (acPtr) and store the result in 'word'
            // If the result is valid, store it in the accumulator and increment the instruction counter 
            // If the result is invalid, throw a runtime error
                word = *acPtr - memory[*opPtr]; 
                if (word < -9999 || word > 9999) {
                    throw std::runtime_error("Error: Subtraction overflow, invalid_input"); 
                }
                *acPtr = word; 
                (*icPtr)++; 
                break; 
            case Command::multiply:
            // as above do it for multiplication
                word = *acPtr * memory[*opPtr]; 
                if (word < -9999 || word > 9999) {
                    throw std::runtime_error("Error: Multiplication overflow, invalid_input"); 
                }
                *acPtr = word; 
                (*icPtr)++; 
                break; 
            case Command::divide:
            // as above do it for division
                if (memory[*opPtr] == 0) {
                    throw std::runtime_error("Error: cannot divide by zero, invalid_input");
                }
                word = *acPtr / memory[*opPtr]; 
                if (word < -9999 || word > 9999) {
                    throw std::runtime_error("Error: Division overflow, invalid_input"); 
                }
                *acPtr = word; 
                (*icPtr)++; 
                break; 
            case Command::branch:
                *icPtr = *opPtr; 
                break; 
            case Command::branchNeg:
                *acPtr < 0 ? *icPtr = *opPtr : ++(*icPtr); 
                break; 
            case Command::branchZero:
                *acPtr == 0 ? *icPtr = *opPtr : ++(*icPtr); 
                break; 
            case Command::halt:
                return; 
                break; 
            default:
            // any instruction required
                throw std::runtime_error("Error: Unknown operation, invalid_input"); 
                break;                 
        }; 
        // You may modify the below while condition if required 
    } while(opCodeToCommand(*opCodePtr) != Command::halt); 
}

bool validWord(int word) {
    std::vector<size_t> validOpCodes = {10, 11, 20, 21, 30, 31, 32, 33, 40, 41, 42, 43};  
    if (word < -9999 || word > 9999) {
        return false; 
    }

    size_t wordOpCode = std::abs(word) / 100; // divide to get the first two digits of the input word 
    // size_t wordOperand = absWord % 100;  // remainder to get the last two digits of the input word

    if (std::find(validOpCodes.begin(), validOpCodes.end(), wordOpCode) == validOpCodes.end()) {
        return false;
    }

    return true; 
}

void dump(std::array<int, memorySize>& memory, int accumulator,
          size_t instructionCounter, size_t instructionRegister, 
          size_t operationCode, size_t operand) {
    // ToDo: Complete this 
    std::cout << "Registers" << "\n"
              << "accumulator          " << accumulator << "\n"
              << "instructionCounter   " << instructionCounter << "\n"
              << "instructionRegister  " << instructionRegister << "\n"
              << "operationCode        " << operationCode << "\n"
              << "operand              " << operand << "\n\n"; 

}

void output(std::string label, int width, int value, bool sign) {
    // ToDo: Complete this 
}


