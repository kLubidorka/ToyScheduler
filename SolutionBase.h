#ifndef TOYSCHEDULER_SOLUTIONBASE_H
#define TOYSCHEDULER_SOLUTIONBASE_H

#include <string>

class SolutionBase {
public:
    virtual void solve(const std::string &input_filename, const std::string &output_filename);
};

#endif //TOYSCHEDULER_SOLUTIONBASE_H
