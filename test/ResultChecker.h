#ifndef TOYSCHEDULER_RESULTCHECKER_H
#define TOYSCHEDULER_RESULTCHECKER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "../src/Task.h"

class ResultChecker {
public:
    bool check(std::istream &test_input, std::istream &solution_input, std::ostream &report_output);

private:
    void read_test(std::istream &in);

    bool read_solution(std::istream &in, std::ostream &out);

    bool check_solution(std::ostream &out);

private:
    std::vector<Task> tasks;
    size_t system_resources;
    size_t total_tasks;
    std::unordered_map<int, int> res_in_use;
    std::unordered_map<int, int> act_time;
};

#endif //TOYSCHEDULER_RESULTCHECKER_H
