#include <functional>
#include <iostream>
 
int main()
{
    std::function<int()> f = nullptr;
    try
    {
        f();
    }
    catch (const std::bad_function_call& e)
    {
        std::cout << e.what() << '\n';
    }
}