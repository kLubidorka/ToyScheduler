#include <iostream>

#include "TestGenerator.h"
#include "SolutionBase.h"

void generate_tests(int test_num){
    TestGenerator generator(10, 10, 100);
    for (int i = 0; i < test_num; i++){
        generator.generateAndPrintTest(10, "tests/test" + std::to_string(i) +  ".txt");
    }
}

void run_solution(SolutionBase solution, int test_num){
    for (int i = 0; i < test_num; i++){
        solution.solve("tests/test" + std::to_string(i) +  ".txt", "output/out" + std::to_string(i) +  ".txt");
    }
}

int main() {
    generate_tests(10);
    //run_solution();
}
