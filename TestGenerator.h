#ifndef TOYSCHEDULER_TESTGENERATOR_H
#define TOYSCHEDULER_TESTGENERATOR_H

#include <vector>
#include <string>
#include "Task.h"

class TestGenerator {
public:
    /**
     * @see Task.h
     *
     * @param max_appear_time -- tasks cannot appear after this time moment
     *      1 <= appear_time <= max_appear_time
     * @param max_res_per_task -- maximal amount of system resources, that a task can consume at each time moment.
     *      1 <= required_resources <= max_res_per_task
     * @param system_resources -- total resources available to scheduler
     */
    TestGenerator(size_t max_appear_time, size_t max_res_per_task, size_t system_resources, size_t max_priority, size_t max_execution_time);

    /**
     * @brief generate test with specified amount of tasks
     * @param tasks_num -- number of tasks in test
     * @param out -- output stream where the test will be printed
     */
    void generateAndPrintTest(size_t tasks_num, std::ostream &out) const;

private:
    void generateTasks(std::vector<Task> *tasks, size_t tasks_num) const;

private:
    size_t max_appear_time;
    size_t max_res_per_task;
    size_t system_resources;
    size_t max_priority;
    size_t max_execution_time;
};


#endif //TOYSCHEDULER_TESTGENERATOR_H
