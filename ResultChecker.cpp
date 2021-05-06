#include "ResultChecker.h"


void ResultChecker::check(std::istream &test_input, std::istream &solution_input, std::ostream &report_output) {
    read_test(test_input);
    read_solution(solution_input, report_output);
    check_solution(report_output);
}

void ResultChecker::read_test(std::istream &in) {
    in >> system_resources;
    in >> total_tasks;
    tasks.reserve(total_tasks);
    size_t t, p, d, r;
    for (int i = 0; i < total_tasks; ++i) {
        in >> t >> p >> d >> r;
        tasks.emplace_back(t, p, d, r);
    }
}

void ResultChecker::read_solution(std::istream &in, std::ostream &out) {
    size_t stages;
    size_t time_start;
    size_t time_stop;

    for (int i = 0; i < tasks.size(); i++) {
        in >> stages;
        size_t total_time = 0;
        size_t act_stop;
        for (int j = 0; j < stages; j++) {
            in >> time_start >> time_stop;
            if (j == stages - 1)
                act_stop = time_stop;
            total_time += (time_stop - time_start);
            for (int k = time_start; k < time_stop; k++) {
                if (res_in_use.find(k) == res_in_use.end())
                    res_in_use[k] = tasks[i].required_resources;
                else
                    res_in_use[k] += tasks[i].required_resources;
            }
        }
        if (total_time < tasks[i].execution_time)
            out << "ERROR: task " << i << " not complete!" << std::endl;
        if (total_time > tasks[i].execution_time)
            out << "ERROR: task " << i << " took more time than needed!" << std::endl;
        act_time[i] = act_stop - tasks[i].appear_time;
    }
}

void ResultChecker::check_solution(std::ostream &out) {
    double average_load = 0.;
    for (auto &it : res_in_use) {
        if (it.second > system_resources)
            out << "ERROR: overload at time point " << it.first << std::endl;
        average_load += it.second;
    }
    out << "AVERAGE LOAD: " << average_load / res_in_use.size() << std::endl;
    double total_score = 0.;
    for (int i = 0; i < tasks.size(); i++) {
        total_score += tasks[i].priority * ((double) act_time[i] / tasks[i].execution_time);
    }
    out << "MAIN SCORE: " << total_score << std::endl;
}
