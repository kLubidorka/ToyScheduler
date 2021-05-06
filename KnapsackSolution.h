//
// Created by Kologermansky on 06.05.2021.
//

#ifndef TOYSCHEDULER_KNAPSACKSOLUTION_H
#define TOYSCHEDULER_KNAPSACKSOLUTION_H

#include "KnapsackSolver.h"
#include "SolutionBase.h"

#include <vector>
#include <set>
#include <fstream>

class KnapsackSolution : public SolutionBase {

public:
    void solve(std::istream &is, std::ostream &os) override {
        std::size_t R, N;
        is >> R >> N;
        std::vector<Task> tasks(N);
        for (std::size_t i = 0; i < N; ++i) {
            is >> tasks[i].appear_time >> tasks[i].priority;
            is >> tasks[i].execution_time >> tasks[i].required_resources;
        }

        std::set<std::size_t> task_idxes;
        std::size_t idx = 0;
        for (std::uint64_t T = 0;; ++T) {
            if (idx == N) {
                if (task_idxes.empty()) {
                    break;
                }
            } else {
                while (idx < N && tasks[idx].appear_time <= T) {
                    task_idxes.insert(idx);
                    ++idx;
                }
            }

            if (task_idxes.empty()) {
                continue;
            }

            const std::size_t n = task_idxes.size();
            std::vector<std::size_t> idxes;
            idxes.reserve(n);
            std::vector<unsigned long long> w(n);
            std::vector<long double> c(n);
            for (const std::size_t &ind : task_idxes) {
                const std::size_t i = idxes.size();
                w[i] = tasks[ind].required_resources;
                c[i] = (long double) (tasks[ind].priority) / (long double) (tasks[ind].execution_time);
                idxes.push_back(ind);
            }
            std::vector<std::size_t> res;
            KnapsackSolver::solve(R, w, c, res);
            for (const std::size_t &ind : res) {
                const std::size_t i = idxes[ind];
                tasks[i].call_count += 1;
                auto &times = tasks[i].exec_ranges;
                if (!times.empty() && times.back().second == T) {
                    times.back().second += 1;
                } else {
                    times.emplace_back(T, T + 1);
                }
                if (tasks[i].call_count == tasks[i].execution_time) {
                    task_idxes.erase(i);
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

    std::string get_name() override { return "Knapsack"; };

private:

    class Task {
    public:
        int num;
        int t;
        int p;
        int d;
        int r;
        int c;
        std::vector<std::pair<std::size_t, std::size_t>> times;
    };
};

#endif //TOYSCHEDULER_KNAPSACKSOLUTION_H
