#ifndef TOYSCHEDULER_TASK_H
#define TOYSCHEDULER_TASK_H

struct Task {
    size_t appear_time;
    size_t priority;
    size_t execution_time;
    size_t required_resources;

    Task(size_t appear_time, size_t priority,
         size_t execution_time, size_t required_resources) :
            appear_time(appear_time),
            priority(priority),
            execution_time(execution_time),
            required_resources(required_resources) {}
};

#endif //TOYSCHEDULER_TASK_H
