#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "computron.h"


TEST_CASE("Testing valid words", "[validWord][valid]") {
    REQUIRE(validWord(1000)); 
    REQUIRE(validWord(2104)); 
    REQUIRE(validWord(9999)); 
    REQUIRE(validWord(-9999)); 
    REQUIRE(validWord(1234)); 
    REQUIRE(validWord(-5433)); 
}

TEST_CASE("Testing invalid words", "[validWord][invalid]") {
    REQUIRE_FALSE(validWord(-10000)); 
    REQUIRE_FALSE(validWord(10000)); 
}

TEST_CASE("Testing valid opcodes", "[opCodeToCommand][valid]") {
    REQUIRE(opCodeToCommand(10) == Command::read); 
    REQUIRE(opCodeToCommand(11) == Command::write); 
    REQUIRE(opCodeToCommand(20) == Command::load); 
    REQUIRE(opCodeToCommand(21) == Command::store); 
    REQUIRE(opCodeToCommand(30) == Command::add); 
    REQUIRE(opCodeToCommand(31) == Command::subtract); 
    REQUIRE(opCodeToCommand(32) == Command::divide); 
    REQUIRE(opCodeToCommand(33) == Command::multiply); 
    REQUIRE(opCodeToCommand(40) == Command::branch); 
    REQUIRE(opCodeToCommand(41) == Command::branchNeg); 
    REQUIRE(opCodeToCommand(42) == Command::branchZero); 
    REQUIRE(opCodeToCommand(43) == Command::halt); 
}

TEST_CASE("Testing invalid opcodes", "[opCodeToCommand][invalid]") {
    REQUIRE(opCodeToCommand(99) == Command::halt);  // completely invalid opcode
    REQUIRE(opCodeToCommand(50) == Command::halt);  // out of range opcode
    REQUIRE(opCodeToCommand(12) == Command::halt);  // invalid opcode in read/write range
    REQUIRE(opCodeToCommand(22) == Command::halt);  // invalid opcode in load/store range
    REQUIRE(opCodeToCommand(34) == Command::halt);  // invalid opcode in arithmetic range
    REQUIRE(opCodeToCommand(44) == Command::halt);  // invalid opcode in branch range
}

TEST_CASE("Testing valid load from file", "[load_from_file][valid]") {
    std::array<int, memorySize> memory{0}; 
    REQUIRE_NOTHROW(memory, "/home/millersam/CompuTron/p1.txt"); 
}

TEST_CASE("Testing invalid load from file", "[load_from_file][invalid]") {
    std::array<int, memorySize> memory{0}; 
    REQUIRE_THROWS(load_from_file(memory, "/home/millersam/CompuTron/p2.txt")); 
}

TEST_CASE("Testing valid read execute","[execute][read][valid]") {
    std::array<int, memorySize> memory{0};  // Initialize memory with zeros
    int ac = 0;  // Accumulator
    size_t ic = 0;  // Instruction counter
    int ir = 0;  // Instruction register
    size_t opCode = 0;  // Operation code
    size_t op = 0;  // Operand
    std::vector<int> inputs = {5, 10, 15, 20};  // Example inputs for read commands
    
    // Test for 'read' command
    memory[0] = 1005;  // Example read instruction
    memory[1] = 1006;  // Example read instruction
    memory[2] = 1007;  // Example read instruction
    memory[3] = 4300; 
    execute(memory, &ac, &ic, &ir, &opCode, &op, inputs);
    REQUIRE(memory[5] == 5);
    REQUIRE(memory[6] == 10);
    REQUIRE(memory[7] == 15);
    REQUIRE(ic == 3);  // Instruction counter should increment  

    // clear the memory array
    std::fill(std::begin(memory), std::end(memory), 0);  
}

TEST_CASE("Testing valid load execute","[execute][load][valid]") {
    std::array<int, memorySize> memory{0};  // Initialize memory with zeros
    int ac = 0;  // Accumulator
    size_t ic = 0;  // Instruction counter
    int ir = 0;  // Instruction register
    size_t opCode = 0;  // Operation code
    size_t op = 0;  // Operand
    std::vector<int> inputs = {5, 10, 15, 20};  // Example inputs for read commands

    // Test for 'load' command
    memory[0] = 2005; 
    memory[1] = 4300; 
    memory[5] = 15;
    
    execute(memory, &ac, &ic, &ir, &opCode, &op, inputs);
    
    REQUIRE(ac == 15);  // Accumulator should be loaded with the value 5

    // clear the memory array
    std::fill(std::begin(memory), std::end(memory), 0);
}

TEST_CASE("Testing valid store execute","[execute][store][valid]") {
    std::array<int, memorySize> memory{0};  // Initialize memory with zeros
    int ac = 30;  // Accumulator
    size_t ic = 0;  // Instruction counter
    int ir = 0;  // Instruction register
    size_t opCode = 0;  // Operation code
    size_t op = 0;  // Operand
    std::vector<int> inputs = {5, 10, 15, 20};  // Example inputs for read commands

    memory[0] = 2105; 
    memory[1] = 4300; 
    
    execute(memory, &ac, &ic, &ir, &opCode, &op, inputs);
    
    REQUIRE(memory[5] == 30);  

    // clear the memory array
    std::fill(std::begin(memory), std::end(memory), 0);
}

TEST_CASE("Testing valid add execute","[execute][add][valid]") {
    std::array<int, memorySize> memory{0};  // Initialize memory with zeros
    int ac = 15;  // Accumulator
    size_t ic = 0;  // Instruction counter
    int ir = 0;  // Instruction register
    size_t opCode = 0;  // Operation code
    size_t op = 0;  // Operand
    std::vector<int> inputs = {5, 10, 15, 20};  // Example inputs for read commands

    memory[0] = 3001; 
    memory[1] = 30; 
    
    execute(memory, &ac, &ic, &ir, &opCode, &op, inputs);
    
    REQUIRE(ac == 45);  

    // clear the memory array
    std::fill(std::begin(memory), std::end(memory), 0);
}

TEST_CASE("Testing valid subtract execute","[execute][subtract][valid]") {
    std::array<int, memorySize> memory{0};  // Initialize memory with zeros
    int ac = 15;  // Accumulator
    size_t ic = 0;  // Instruction counter
    int ir = 0;  // Instruction register
    size_t opCode = 0;  // Operation code
    size_t op = 0;  // Operand
    std::vector<int> inputs = {5, 10, 15, 20};  // Example inputs for read commands

    memory[0] = 3101; 
    memory[1] = 30; 
    
    execute(memory, &ac, &ic, &ir, &opCode, &op, inputs);
    
    REQUIRE(ac == -15);  

    // clear the memory array
    std::fill(std::begin(memory), std::end(memory), 0);
}

TEST_CASE("Testing valid divide execute","[execute][divide][valid]") {
    std::array<int, memorySize> memory{0};  // Initialize memory with zeros
    int ac = 30;  // Accumulator
    size_t ic = 0;  // Instruction counter
    int ir = 0;  // Instruction register
    size_t opCode = 0;  // Operation code
    size_t op = 0;  // Operand
    std::vector<int> inputs = {5, 10, 15, 20};  // Example inputs for read commands

    memory[0] = 3201; 
    memory[1] = 3; 
    
    execute(memory, &ac, &ic, &ir, &opCode, &op, inputs);
    
    REQUIRE(ac == 10);  

    // clear the memory array
    std::fill(std::begin(memory), std::end(memory), 0);
}

TEST_CASE("Testing valid multiply execute","[execute][multiply][valid]") {
    std::array<int, memorySize> memory{0};  // Initialize memory with zeros
    int ac = 30;  // Accumulator
    size_t ic = 0;  // Instruction counter
    int ir = 0;  // Instruction register
    size_t opCode = 0;  // Operation code
    size_t op = 0;  // Operand
    std::vector<int> inputs = {5, 10, 15, 20};  // Example inputs for read commands

    memory[0] = 3301; 
    memory[1] = 3; 
    
    execute(memory, &ac, &ic, &ir, &opCode, &op, inputs);
    
    REQUIRE(ac == 90);  

    // clear the memory array
    std::fill(std::begin(memory), std::end(memory), 0);
}
