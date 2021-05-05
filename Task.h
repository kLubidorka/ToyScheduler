#ifndef TOYSCHEDULER_TASK_H
#define TOYSCHEDULER_TASK_H

struct Task {
    unsigned appear_time;
    unsigned priority;
    unsigned execution_time;
    unsigned required_resources;

    Task(unsigned appear_time, unsigned priority,
         unsigned execution_time, unsigned required_resources) :
            appear_time(appear_time),
            priority(priority),
            execution_time(execution_time),
            required_resources(required_resources) {}
};

#endif //TOYSCHEDULER_TASK_H
