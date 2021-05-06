#ifndef TOYSCHEDULER_SOLUTIONBASE_H
#define TOYSCHEDULER_SOLUTIONBASE_H

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include "Task.h"

class SolutionBase {
public:
    /**
     * @brief base method that solves the problem
     * All the solution classes must be subclasses of "SolutionBase" and override "solve" method
     * @see README.md
     * @param in -- input stream
     * @param out -- output stream
     */
    virtual void solve(std::istream &in, std::ostream &out) {};

    virtual std::string get_name() { return "base"; };
};

#endif //TOYSCHEDULER_SOLUTIONBASE_H
