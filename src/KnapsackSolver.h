//
// Created by Kologermansky on 06.05.2021.
//

#include <algorithm>
#include <vector>
#include <iostream>

#ifndef TOYSCHEDULER_KNAPSACK_SOLVER_H
#define TOYSCHEDULER_KNAPSACK_SOLVER_H

class KnapsackSolver {
    typedef unsigned long long WeightType;
    typedef long double CostType;

public:
    /**
     * @brief solve task
     * @param W - size of knapsack
     * @param W - array of weights
     * @param c - array of costs
     * @param res - result of KnapsackTask. Contains indexes of items, which were taken
     */
    static void solve(const WeightType &W, const std::vector<WeightType> &w,
                      const std::vector<CostType> &c, std::vector<std::size_t> &res);
};

#endif //TOYSCHEDULER_KNAPSACK_SOLVER_H
