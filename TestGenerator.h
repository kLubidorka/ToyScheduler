#ifndef TOYSCHEDULER_TESTGENERATOR_H
#define TOYSCHEDULER_TESTGENERATOR_H

#include <vector>
#include "Task.h"

class TestGenerator {
public:
    TestGenerator(size_t max_appear_time, size_t max_res_per_task, size_t system_resources);

    void generateAndPrintTest(size_t tasks_num, const std::string &filename) const;

private:
    void generateTasks(std::vector<Task> *tasks, size_t tasks_num) const;

private:
    size_t max_appear_time;
    size_t max_res_per_task;
    size_t system_resources;
private:
    static const size_t MAX_PRIORITY = 20;
    static const size_t MAX_EXEC_TIME = 50;
};


#endif //TOYSCHEDULER_TESTGENERATOR_H
