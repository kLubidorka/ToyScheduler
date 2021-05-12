#include "test/TestGenerator.h"
#include "src/SolutionBase.h"
#include "test/ResultChecker.h"
#include "src/KnapsackSolution.h"
#include "src/GreedySolution.h"

#include <ctime>

const std::string test_base_name = "test";
const std::string solution_base_name = "solution";
const std::string checker_report_base_name = "report";

void generate_tests_file_io(int test_num, const std::string &output_folder,
                            int max_appear_time,
                            int max_res_per_task,
                            int system_resources,
                            int max_priority,
                            int max_execution_time,
                            int max_tasks_in_test) {
    TestGenerator generator(max_appear_time, max_res_per_task, system_resources, max_priority, max_execution_time);
    for (int i = 0; i < test_num; i++) {
        std::string output_file = output_folder + test_base_name + std::to_string(i) + ".txt";
        std::ofstream out(output_file);
        generator.generateAndPrintTest(1 + rand() % max_tasks_in_test, out);
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

bool check_solution_file_io(const std::string &test_input_file,
                            const std::string &solution_input_file,
                            const std::string &report_output_file) {
    std::ifstream test_in(test_input_file);
    std::ifstream solution_in(solution_input_file);
    std::ofstream report_out(report_output_file);
    ResultChecker checker;
    bool no_mistakes = checker.check(test_in, solution_in, report_out);
    test_in.close();
    solution_in.close();
    report_out.close();
    return no_mistakes;
}

void check_solutions_in_directory_file_io(int test_num,
                                          const std::string &tests_directory,
                                          const std::string &solutions_directory,
                                          const std::string &reports_directory) {
    for (int i = 0; i < test_num; i++) {
        bool test_passed = check_solution_file_io(tests_directory + test_base_name + std::to_string(i) + ".txt",
                                                  solutions_directory + solution_base_name + std::to_string(i) + ".txt",
                                                  reports_directory + checker_report_base_name + std::to_string(i) +
                                                  ".txt");
        if (!test_passed) {
            std::cout << "FAIL" << std::endl;
            std::cout << "Fist failed test: " << i << std::endl;
            return;
        }

    }
}

void run_solutions(int test_num, const std::vector<SolutionBase *> &solutions) {
    for (auto solution : solutions) {
        std::clock_t c_start = std::clock();
        run_solution_file_io(solution, test_num, "tests/", solution->get_name() + "Solutions/");
        std::clock_t c_end = std::clock();
        u_long time_elapsed_ms = 1000 * (c_end - c_start) / CLOCKS_PER_SEC;
        std::cout << "CPU time used by " << solution->get_name() << " on " << test_num << " tests: " << time_elapsed_ms
                  << " ms\n";

        check_solutions_in_directory_file_io(test_num, "tests/", solution->get_name() + "Solutions/",
                                             solution->get_name() + "Reports/");
    }
}

std::string lower_or_greater(double value) {
    return value >= 0 ? "greater" : "lower";
}

std::string better_or_worse(double value) {
    return value >= 0 ? "worse" : "better";
}

void compare_reports(int test_num, const std::vector<SolutionBase *> &solutions) {
    std::vector<std::vector<std::pair<double, double>>> results;
    results.resize(test_num);
    for (int i = 0; i < test_num; i++) {
        results[i].reserve(solutions.size());
        for (auto solution : solutions) {
            std::string input_file =
                    solution->get_name() + "Reports/" + checker_report_base_name + std::to_string(i) + ".txt";
            std::ifstream in(input_file);
            std::string trash;
            double avg_load, score;
            in >> trash >> trash >> avg_load >> trash >> trash >> score;
            results[i].emplace_back(avg_load, score);
            in.close();
        }
    }
    for (auto &elem : results) {
        double first_solution_avg_load = elem[0].first;
        double first_solution_score = elem[0].second;
        for (auto &elem2 : elem) {
            elem2.first = (elem2.first - first_solution_avg_load) / first_solution_avg_load * 100;
            elem2.second = (elem2.second - first_solution_score) / first_solution_score * 100;
        }
    }
    std::vector<std::pair<double, double>> final_results(solutions.size());
    for (auto &elem : results) {
        for (int i = 0; i < elem.size(); i++) {
            final_results[i].first += elem[i].first / test_num;
            final_results[i].second += elem[i].second / test_num;
        }
    }
    std::string first_solution_name = solutions[0]->get_name();
    for (int i = 1; i < solutions.size(); i++) {
        std::cout << solutions[i]->get_name() << " has average load " << std::fixed << std::setprecision(2)
                  << abs(final_results[i].first) << "% " << lower_or_greater(final_results[i].first) << " than "
                  << first_solution_name << " on average" << std::endl;
        std::cout << solutions[i]->get_name() << " has total score " << abs(final_results[i].second) << "% "
                  << better_or_worse(final_results[i].second) << " than "
                  << first_solution_name << " on average" << std::endl << std::endl;
    }
}

int main(int argc, char* argv[]) {
    int test_num = 1000;
    if (argc > 1){
        test_num = atoi(argv[1]);
    }

    generate_tests_file_io(test_num, "tests/", 100, 50, 150, 20, 40, 100);

    KnapsackSolution knapsackSolution;
    GreedySolution greedySolution;
    std::vector<SolutionBase *> solutions = {&knapsackSolution, &greedySolution};

    run_solutions(test_num, solutions);
    compare_reports(test_num, solutions);
}
