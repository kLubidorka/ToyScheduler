//
// Created by Kologermansky on 06.05.2021.
//

#ifndef TOYSCHEDULER_GREEDYSOLUTION_H
#define TOYSCHEDULER_GREEDYSOLUTION_H

#include <vector>
#include <set>
#include <fstream>

#include "SolutionBase.h"

class GreedySolution : public SolutionBase {

public:
    void solve(std::istream &is, std::ostream &os) override {
        std::size_t R, N;
        is >> R >> N;
        std::vector<Task> tasks(N);
        std::set<std::size_t> time_snapshots;
        for (std::size_t i = 0; i < N; ++i) {
            tasks[i].num = i;
            is >> tasks[i].t >> tasks[i].p >> tasks[i].d >> tasks[i].r;
            tasks[i].c = 0;
            time_snapshots.insert(tasks[i].t);
        }

        auto cmp = [&tasks](const std::size_t& a, const std::size_t& b) {
            if (tasks[a].p * tasks[b].d > tasks[a].d * tasks[b].p) {
                return true;
            }
            if (tasks[a].p * tasks[b].d < tasks[a].d * tasks[b].p) {
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
                tasks[task_id].c += (int) (next_T - T);
                if (!tasks[task_id].times.empty() && tasks[task_id].times.back().second == T) {
                    tasks[task_id].times.back().second = next_T;
                } else {
                    tasks[task_id].times.emplace_back(T, next_T);
                }
                if (tasks[task_id].d == tasks[task_id].c) {
                    pull_tasks.erase(task_id);
                }
            }
            working_tasks.clear();
            T = next_T;

            // add new tasks from input in queue
            while (idx < N && tasks[idx].t <= T) {
                pull_tasks.insert(idx);
                ++idx;
            }

            // choose new working tasks
            std::size_t curr_R = 0;
            for (const auto & task_id : pull_tasks) {
                auto & task = tasks[task_id];
                if (curr_R + task.r <= R) {
                    curr_R += task.r;
                    working_tasks.push_back(task_id);
                    time_snapshots.insert(T + task.d - task.c);
                }
            }
        }

        for (std::size_t i = 0; i < N; ++i) {
            os << tasks[i].times.size() << " ";
            for (const auto &ind : tasks[i].times) {
                os << ind.first << " " << ind.second << " ";
            }
            os << std::endl;
        }
    }

};

#endif //TOYSCHEDULER_GREEDYSOLUTION_H
