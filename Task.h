#ifndef TOYSCHEDULER_TASK_H
#define TOYSCHEDULER_TASK_H

#include <vector>

/**
 * @brief task for scheduler
 * @see README.md
 */
struct Task {
    size_t appear_time;
    size_t priority;
    size_t execution_time;
    size_t required_resources;
    size_t call_count;
    std::vector<std::pair<size_t, size_t>> exec_ranges;

    explicit Task(size_t appear_time = 0, size_t priority = 0,
         size_t execution_time = 0, size_t required_resources = 0) :
            appear_time(appear_time),
            priority(priority),
            execution_time(execution_time),
            required_resources(required_resources),
            call_count(0) {}
};

#endif //TOYSCHEDULER_TASK_H
