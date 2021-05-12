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
    void solve(std::istream &is, std::ostream &os) override;

    std::string get_name() override { return "knapsack"; };
};

#endif //TOYSCHEDULER_KNAPSACKSOLUTION_H
