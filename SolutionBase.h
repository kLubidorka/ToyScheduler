#ifndef TOYSCHEDULER_SOLUTIONBASE_H
#define TOYSCHEDULER_SOLUTIONBASE_H

#include <string>

class SolutionBase{
    virtual void solve(const std::string &input_filename, const std::string &output_filename) = 0;
};

#endif //TOYSCHEDULER_SOLUTIONBASE_H
