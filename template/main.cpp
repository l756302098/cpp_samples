/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */
#include <iostream>

//声明模板类demo
template<typename... Values> class demo;
//继承式递归的出口
template<> class demo<> {};
//以继承的方式解包
template<typename Head, typename... Tail>
class demo<Head, Tail...>
    : private demo<Tail...>
{
public:
    demo(Head v, Tail... vtail) : m_head(v), demo<Tail...>(vtail...) {
        dis_head();
    }
    void dis_head() { std::cout << m_head << std::endl; }
protected:
    Head m_head;
};
int main() {
    demo<int, float, std::string> t(1, 2.34, "http://www.biancheng.net");
    return 0;
}
