#include <iostream>

#include "TestGenerator.h"

int main() {
    TestGenerator generator(10, 10, 100);
    generator.generateAndPrintTest(10, "test.txt");
}
