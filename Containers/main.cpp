/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */

#include <iostream>
#include <list>
#include <functional>
#include <queue> 
class PriorityTask
{
private:
    /* data */
    int priority;
    std::function<void()> taskFunc;
public:
    PriorityTask(int priority_ = 0):priority(priority_)
    {
    }
    ~PriorityTask(){}
    void SetTaskFunc(const std::function<void()>& func){
        taskFunc = func;
    }

    std::function<void()> GetTaskFunc() const{
        return taskFunc;
    }

    int GetPriority() const
    {
        return priority;
    }

    bool operator< (const PriorityTask &other) const
    {
        return this->priority < other.priority;
    }
};

int main ()
{
    std::priority_queue<PriorityTask> tasks;
    PriorityTask p1(10);
    tasks.emplace(p1);
    PriorityTask p2(20);
    tasks.emplace(p2);
    PriorityTask p3(30);
    tasks.emplace(p3);
    PriorityTask p4(5);
    tasks.emplace(p4);
    while (tasks.size())
    {
        std::cout << ' ' << tasks.top().GetPriority();
        tasks.pop();
    }
    
    return 0;
}

