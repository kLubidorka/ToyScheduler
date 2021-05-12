#include "GreedySolution.h"

void GreedySolution::solve(std::istream &is, std::ostream &os) {
    std::size_t R, N;
    is >> R >> N;
    std::vector<Task> tasks(N);
    std::set<std::size_t> time_snapshots;
    for (std::size_t i = 0; i < N; ++i) {
        is >> tasks[i].appear_time >> tasks[i].priority;
        is >> tasks[i].execution_time >> tasks[i].required_resources;
        time_snapshots.insert(tasks[i].appear_time);
    }

    auto cmp = [&tasks](const std::size_t &a, const std::size_t &b) {
        if (tasks[a].priority * tasks[b].execution_time > tasks[a].execution_time * tasks[b].priority) {
            return true;
        }
        if (tasks[a].priority * tasks[b].execution_time < tasks[a].execution_time * tasks[b].priority) {
            return false;
        }
        return a < b;
    };
    std::set<std::size_t, decltype(cmp)> pull_tasks(cmp);
    std::vector<std::size_t> working_tasks;
    std::size_t idx = 0;
    std::size_t T = 0;
    while (!time_snapshots.empty()) {
        std::size_t next_T = *time_snapshots.begin();
        time_snapshots.erase(time_snapshots.begin());

        // process working tasks
        for (const auto &task_id : working_tasks) {
            tasks[task_id].call_count += (int) (next_T - T);
            if (!tasks[task_id].exec_ranges.empty() && tasks[task_id].exec_ranges.back().second == T) {
                tasks[task_id].exec_ranges.back().second = next_T;
            } else {
                tasks[task_id].exec_ranges.emplace_back(T, next_T);
            }
            if (tasks[task_id].execution_time == tasks[task_id].call_count) {
                pull_tasks.erase(task_id);
            }
        }
        working_tasks.clear();
        T = next_T;

        // add new tasks from input in queue
        while (idx < N && tasks[idx].appear_time <= T) {
            pull_tasks.insert(idx);
            ++idx;
        }

        // choose new working tasks
        std::size_t curr_R = 0;
        for (const auto &task_id : pull_tasks) {
            auto &task = tasks[task_id];
            if (curr_R + task.required_resources <= R) {
                curr_R += task.required_resources;
                working_tasks.push_back(task_id);
                time_snapshots.insert(T + task.execution_time - task.call_count);
            }
        }
    }

    for (std::size_t i = 0; i < N; ++i) {
        os << tasks[i].exec_ranges.size() << " ";
        for (const auto &ind : tasks[i].exec_ranges) {
            os << ind.first << " " << ind.second << " ";
        }
        os << std::endl;
    }
}