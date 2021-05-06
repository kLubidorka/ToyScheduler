#include "TestGenerator.h"
#include "SolutionBase.h"
#include <fstream>

void generate_tests(int test_num) {
    TestGenerator generator(10, 10, 100);
    for (int i = 0; i < test_num; i++) {
        generator.generateAndPrintTest(10, "tests/test" + std::to_string(i) + ".txt");
    }
}

void run_solution_file_io(SolutionBase *solution, int test_num,
                          const std::string &input_folder,
                          const std::string &output_folder) {
    for (int i = 0; i < test_num; i++) {
        std::string input_file = input_folder + std::to_string(i) + ".txt";
        std::filebuf fb_in;
        fb_in.open(input_file, std::ios::in);
        std::istream is(&fb_in);

        std::string output_file = output_folder + std::to_string(i) + ".txt";
        std::filebuf fb_out;
        fb_out.open(output_file, std::ios::out);
        std::ostream os(&fb_out);

        solution->solve(is, os);
        fb_in.close();
        fb_out.close();
    }
}


int main() {
    int num_test = 10;
    generate_tests(num_test);
//    SomeSolution solution;
//    run_solution(&solution, num_test, "tests/test", "output/out");
}
