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
            tasks[i].num = i;
            is >> tasks[i].t >> tasks[i].p >> tasks[i].d >> tasks[i].r;
            tasks[i].c = 0;
        }

        std::set<std::size_t> task_idxes;
        std::size_t idx = 0;
        for (std::uint64_t T = 0;; ++T) {
            if (idx == N) {
                if (task_idxes.empty()) {
                    break;
                }
            } else {
                while (idx < N && tasks[idx].t <= T) {
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
                w[i] = tasks[ind].r;
                c[i] = (long double) (tasks[ind].p) / (long double) (tasks[ind].d);
                idxes.push_back(ind);
            }
            std::vector<std::size_t> res;
            KnapsackSolver::solve(R, w, c, res);
            for (const std::size_t &ind : res) {
                const std::size_t i = idxes[ind];
                tasks[i].c += 1;
                auto &times = tasks[i].times;
                if (!times.empty() && times.back().second + 1 == T) {
                    times.back().second += 1;
                } else {
                    times.emplace_back(T, T);
                }
                if (tasks[i].c == tasks[i].d) {
                    task_idxes.erase(i);
                }
            }
        }

        for (std::size_t i = 0; i < N; ++i) {
            os << tasks[i].times.size() << " ";
            for (const auto& ind : tasks[i].times) {
                os << ind.first << " " << ind.second + 1 << " ";
            }
            os << std::endl;
        }
    }

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
