#include "TestGenerator.h"

#include <iostream>
#include <algorithm>

TestGenerator::TestGenerator(size_t max_appear_time, size_t max_res_per_task, size_t system_resources,
                             size_t max_priority, size_t max_execution_time) :
        max_appear_time(max_appear_time),
        max_res_per_task(max_res_per_task),
        system_resources(system_resources),
        max_priority(max_priority),
        max_execution_time(max_execution_time){}

void TestGenerator::generateAndPrintTest(size_t tasks_num, std::ostream &out) const {
    out << system_resources << std::endl;
    out << tasks_num << std::endl;
    std::vector<Task> tasks;
    generateTasks(&tasks, tasks_num);
    for (auto task : tasks) {
        out << task.appear_time << " " << task.priority << " " << task.execution_time << " "
            << task.required_resources
            << std::endl;
    }
}

void TestGenerator::generateTasks(std::vector<Task> *tasks, size_t tasks_num) const {
    tasks->reserve(tasks_num);
    for (int i = 0; i < tasks_num; ++i) {
        tasks->emplace_back(1 + rand() % max_appear_time,
                            1 + rand() % max_priority,
                            1 + rand() % max_execution_time,
                            1 + rand() % max_res_per_task);
    }
    std::sort(tasks->begin(), tasks->end(),
              [](const Task &a, const Task &b) -> bool { return a.appear_time < b.appear_time; });
}
