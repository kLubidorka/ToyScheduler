#ifndef TOYSCHEDULER_SOLUTIONBASE_H
#define TOYSCHEDULER_SOLUTIONBASE_H

#include <string>
#include <iostream>

class SolutionBase {
public:
    /**
     * @brief base method that solves the problem
     * @see README.md
     * @param in -- input stream
     * @param out -- output stream
     */
    virtual void solve(std::istream &in, std::ostream &out) {};
};

#endif //TOYSCHEDULER_SOLUTIONBASE_H
