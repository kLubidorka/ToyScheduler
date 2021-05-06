#include "TestGenerator.h"
#include "SolutionBase.h"
#include "ResultChecker.h"
#include "KnapsackSolution.h"

const std::string test_base_name = "test";
const std::string solution_base_name = "solution";
const std::string checker_report_base_name = "solution";

void generate_tests_file_io(int test_num, const std::string &output_folder) {
    TestGenerator generator(10, 10, 10);
    for (int i = 0; i < test_num; i++) {
        std::string output_file = output_folder + test_base_name + std::to_string(i) + ".txt";
        std::ofstream out(output_file);
        generator.generateAndPrintTest(10, out);
        out.close();
    }
}

void run_solution_file_io(SolutionBase *solution, int test_num,
                          const std::string &input_folder,
                          const std::string &output_folder) {
    for (int i = 0; i < test_num; i++) {
        std::string input_file = input_folder + test_base_name + std::to_string(i) + ".txt";
        std::string output_file = output_folder + solution_base_name + std::to_string(i) + ".txt";
        std::ifstream in(input_file);
        std::ofstream out(output_file);
        solution->solve(in, out);
        in.close();
        out.close();
    }
}

void check_solution_file_io(const std::string &test_input_file,
                            const std::string &solution_input_file,
                            const std::string &report_output_file) {
    std::ifstream test_in(test_input_file);
    std::ifstream solution_in(solution_input_file);
    std::ofstream report_out(report_output_file);
    ResultChecker checker;
    checker.check(test_in, solution_in, report_out);
    test_in.close();
    solution_in.close();
    report_out.close();
}

void check_solutions_in_directory_file_io(int test_num,
                                          const std::string &tests_directory,
                                          const std::string &solutions_directory,
                                          const std::string &reports_directory) {
    for (int i = 0; i < test_num; i++) {
        check_solution_file_io(tests_directory + test_base_name + std::to_string(i) + ".txt",
                               solutions_directory + solution_base_name + std::to_string(i) + ".txt",
                               reports_directory + checker_report_base_name + std::to_string(i) + ".txt");
    }

}

int main() {
    generate_tests_file_io(10, "tests/");
    KnapsackSolution solution;
    run_solution_file_io(&solution, 10, "tests/", "solutions/");
    check_solutions_in_directory_file_io(10, "tests/", "solutions/", "reports/");
}
