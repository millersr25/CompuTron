#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "computron.h"

TEST_CASE("Load from File valid", "[loadFromFile][valid]") {
    std::array<int, memorySize> memory{0}; 
    load_from_file(memory, "/home/millersam/CompuTron/p1.txt"); 

}