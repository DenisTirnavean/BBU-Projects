#include <iostream>

#include "TestScurt.h"
#include "TestExtins.h"
#include "Iterator.h"
#include "LO.h"
bool rel(int a, int b)
{
    return a <= b;
}
int main() {
    testAll();
    testAllExtins();
    test_task();
    std::cout << "Finished LI Tests!" << std::endl;
    
}