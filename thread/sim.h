#include <mutex>
#include <condition_variable>
#include <thread>

class sim
{
private:
    std::mutex mutex;
    std::condition_variable condition;
    int index;
public:
    sim(/* args */);
    ~sim();
    void Start();
    void Inter();
    void Start2();
    void Inter2();
    void Test2();
};
