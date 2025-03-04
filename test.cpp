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
    REQUIRE_THROWS(opCodeToCommand(99));  // completely invalid opcode
    REQUIRE_THROWS(opCodeToCommand(50));  // out of range opcode
    REQUIRE_THROWS(opCodeToCommand(12));  // invalid opcode in read/write range
    REQUIRE_THROWS(opCodeToCommand(22));  // invalid opcode in load/store range
    REQUIRE_THROWS(opCodeToCommand(34));  // invalid opcode in arithmetic range
    REQUIRE_THROWS(opCodeToCommand(44));  // invalid opcode in branch range
}

