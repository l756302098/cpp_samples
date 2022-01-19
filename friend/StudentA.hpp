#ifndef __STUDENT_A_
#define __STUDENT_A_

#include <iostream>
#include "StudentB.hpp"

//forward declaration
namespace aa {
    namespace bbb
    {   
        class StudentB;
    }
}

namespace aa
{
    namespace aaa
    {
        class StudentA
        {
            friend class aa::bbb::StudentB;
        private:
            /* data */
            bool Print(const std::string& name){
                std::cout << name << std::endl;
            }
        public:
            StudentA(/* args */);
            ~StudentA();
        };

        StudentA::StudentA(/* args */)
        {
        }

        StudentA::~StudentA()
        {
        }
    }
}


#endif
