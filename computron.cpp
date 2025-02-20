#include "computron.h"

#include <fstream>
#include <iomanip>

void load_from_file(std::array<int, memorySize>& memory, const std::string& filename) {
    constexpr int sentinel{-99999}; // terminates reading after -99999
    size_t i{0}; 
    std::string line; 
    int instruction; 

    std::ifstream inputFile(filename);
    if(!inputFile) {
        // throw runtime_error exception with string "invalid_input"
        throw std::runtime_error("Error: this file has an invalid_input"); 
    }

    while(std::getline(inputFile, line)) {
        instruction = std::stoi(line); 
        if(instruction == sentinel) {
            break; 
        }

        // Check if the instruction is valid using the validWord function
        // If the instruction is valid, store it in memory at position 'i' and increment 'i'
        // If the instruction is invalid, throw runtime error with the message "invalid_input"
    }
    inputFile.close(); 
}

Command opCodeToCommand(size_t opCode) {
    switch(opCode) {
        case 10: 
            return Command::read; 
            break; 
        case 11:
            return Command::write; 
            break; 
        case 20:
            return Command::load; 
            break; 
        case 21:
            return Command::store; 
            break; 
        case 30:
            return Command::add; 
            break; 
        case 31:
            return Command::subtract; 
            break; 
        case 32:
            return Command::divide; 
            break; 
        case 33:
            return Command::multiply; 
            break; 
        case 40: 
            return Command::branch; 
            break; 
        case 41:
            return Command::branchNeg; 
            break; 
        case 42:
            return Command::branchZero; 
            break; 
        case 43:
            return Command::halt; 
            break; 
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

        switch(int word{}; opCodeToCommand(*opCodePtr)) {
            case Command::read:
                word = inputs[inputIndex]; 
                // Assign the value of 'word' to the memory location pointed to by 'opPtr'
                // Increment the instruction counter (icPtr) to point to the next instruction

                inputIndex++; 
                break;             
            case Command::write:
            // Dereference 'icPtr' to access the instruction counter and increment its value by 1
            // use the below cout if needed but comment before submission
            // std::cout << "Contents of " << std::setfill('0') << std::setw(2)
            //           << *opPtr << " : " << memory[*opPtr] << "\n";
                break; 
            case Command::load:
            // Load the value from the memory location pointed to by 'opPtr' into the accumulator (acPtr)
            // Incrment the instruction counter (icPtr) to point to the next instruction
                break; 
            case Command::store:
            // Store the value in the accumulator (acPtr) into the memory location pointed to by 'opPtr'
            // Increment the instruction counter (icPtr) to move to the next instruction
                break; 
            case Command::add:
            // Add the value in the accumulator (acPtr) to the value in memory at the location pointed to by 'opPtr' and store the result in 'word'
            // If the result is valid, store it in the accumulator and increment the instruction counter
            // If the result is invalid, throw a runtime error
                break; 
            case Command::subtract: 
            // Subtract the value in memory at the location pointed to by 'opPtr' from the value in the accumulator (acPtr) and store the result in 'word'
            // If the result is valid, store it in the accumulator and increment the instruction counter 
            // If the result is invalid, throw a runtime error
                break; 
            case Command::multiply:
            // as above do it for multiplication
                break; 
            case Command::divide:
            // as above do it for division
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
                break; 
            default:
            // any instruction required
                break;                 
        }; 
        // You may modify the below while condition if required 
    } while(opCodeToCommand(*opCodePtr) != Command::halt); 
}

bool validWord(int word) {
    // ToDo: Complete this
}

void dump(std::array<int, memorySize>& memory, int accumulator,
          size_t instructionCounter, size_t instructionRegister, 
          size_t operationCode, size_t operand) {
    // ToDo: Complete this 
}

void output(std::string label, int width, int value, bool sign) {
    // ToDo: Complete this 
}


