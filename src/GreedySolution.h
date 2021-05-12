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
    void solve(std::istream &is, std::ostream &os) override;

    std::string get_name() override { return "greedy"; };
};

#endif //TOYSCHEDULER_GREEDYSOLUTION_H
