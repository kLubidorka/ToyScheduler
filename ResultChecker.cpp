#include "ResultChecker.h"


bool ResultChecker::check(std::istream &test_input, std::istream &solution_input, std::ostream &report_output) {
    bool no_mistakes = true;
    read_test(test_input);
    no_mistakes &= read_solution(solution_input, report_output);
    no_mistakes &= check_solution(report_output);
    return no_mistakes;
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

bool ResultChecker::read_solution(std::istream &in, std::ostream &out) {
    bool no_mistakes = true;
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
        if (total_time < tasks[i].execution_time) {
            out << "ERROR: task " << i << " not complete!" << std::endl;
            no_mistakes = false;
        }
        if (total_time > tasks[i].execution_time) {
            out << "ERROR: task " << i << " took more time than needed!" << std::endl;
            no_mistakes = false;
        }
        act_time[i] = act_stop - tasks[i].appear_time;
    }
    return no_mistakes;
}

bool ResultChecker::check_solution(std::ostream &out) {
    bool no_mistakes = true;
    double average_load = 0.;
    for (auto &it : res_in_use) {
        if (it.second > system_resources) {
            out << "ERROR: overload at time point " << it.first << std::endl;
            no_mistakes = false;
        }
        average_load += it.second;
    }
    out << "AVERAGE LOAD: " << average_load / res_in_use.size() << std::endl;
    double total_score = 0.;
    for (int i = 0; i < tasks.size(); i++) {
        total_score += tasks[i].priority * ((double) act_time[i] / tasks[i].execution_time);
    }
    out << "MAIN SCORE: " << total_score << std::endl;
    return no_mistakes;
}
