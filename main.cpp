#include "TestGenerator.h"
#include "SolutionBase.h"
#include <fstream>

void generate_tests_file_io(int test_num, const std::string &output_folder) {
    TestGenerator generator(10, 10, 100);
    for (int i = 0; i < test_num; i++) {
        std::string output_file = output_folder + "test" + std::to_string(i) + ".txt";
        std::ofstream out(output_file);
        generator.generateAndPrintTest(10, out);
        out.close();
    }
}

void run_solution_file_io(SolutionBase *solution, int test_num,
                          const std::string &input_folder,
                          const std::string &output_folder) {
    for (int i = 0; i < test_num; i++) {
        std::string input_file = input_folder + "test" + std::to_string(i) + ".txt";
        std::string output_file = output_folder + "out" + std::to_string(i) + ".txt";
        std::ifstream in(input_file);
        std::ofstream out(output_file);
        solution->solve(in, out);
        in.close();
        out.close();
    }
}

int main() {
    int num_test = 10;
    generate_tests_file_io(num_test, "tests/");
//    SomeSolution solution;
//    run_solution(&solution, num_test, "tests/", "output/");
}
