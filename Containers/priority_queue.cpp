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
#include <algorithm>
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

struct IceEvent
{
    std::uint32_t   eventTime;
    std::uint8_t    timeBeat;
    std::uint16_t   eventCode;
    std::uint8_t    eventVal;
    std::string     workRunId;
    bool operator< (const IceEvent &other) const
    {
        return this->eventTime < other.eventTime;
    }
};

int main ()
{
    // std::priority_queue<PriorityTask> tasks;
    // PriorityTask p1(10);
    // tasks.emplace(p1);
    // PriorityTask p2(20);
    // tasks.emplace(p2);
    // PriorityTask p3(30);
    // tasks.emplace(p3);
    // PriorityTask p4(5);
    // tasks.emplace(p4);
    // while (tasks.size())
    // {
    //     std::cout << ' ' << tasks.top().GetPriority();
    //     tasks.pop();
    // }

    std::vector<std::string> logFiles;
    logFiles.emplace_back("202309");
    logFiles.emplace_back("202308");
    logFiles.emplace_back("202307");
    logFiles.emplace_back("202401");
    logFiles.emplace_back("202301");
    std::sort(logFiles.begin(),logFiles.end());

    for (auto i = logFiles.begin(); i != logFiles.end(); i++)
    {
        std::cout << " " << *i << std::endl;
    }
    

    std::priority_queue<IceEvent> tasks;
    IceEvent event1;
    event1.eventTime = 10;
    tasks.emplace(event1);
    IceEvent event2;
    event2.eventTime = 20;
    tasks.emplace(event2);
    // while (tasks.size())
    // {
    //     std::cout << ' ' << tasks.top().eventTime << std::endl;
    //     tasks.pop();
    // }

    std::list<IceEvent> eventList;
    while (tasks.size())
    {
        std::cout << ' ' << tasks.top().eventTime << std::endl;
        auto e = tasks.top();
        eventList.emplace_back(e);
        tasks.pop();
    }
    IceEvent event3;
    event3.eventTime = 200;
    eventList.emplace_back(event3);
    while (eventList.size())
    {
        IceEvent item = eventList.front();
        std::cout << "time:" << item.eventTime << std::endl;
        eventList.pop_front();
    }
    
    return 0;
}

