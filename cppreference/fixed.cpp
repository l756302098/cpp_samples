#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
 
int main()
{
    constexpr long double pi{3.141592653589793239};
    constexpr double pi1{3.14159200};
 
    std::cout << std::fixed << "time stamp: " << std::setprecision(10)  << pi << std::endl; 
    std::cout << std::fixed << "time stamp: " << std::setprecision(10)  << pi1 << std::endl; 

    // std::cout << std::setprecision(10) << pi1 << " " << pi << std::endl;
    // std::cout << std::fixed << pi1 << std::endl; 
    // std::cout << std::setprecision(10) << pi1 << " " << pi << std::endl;
    
    
}