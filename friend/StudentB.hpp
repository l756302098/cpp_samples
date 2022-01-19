#ifndef __STUDENT_B_
#define __STUDENT_B_

#include <iostream>
#include "StudentA.hpp"

namespace aa
{
    namespace bbb
    {
        class StudentB
        {
        private:
            /* data */
            
        public:
            StudentB(/* args */);
            ~StudentB();
            bool Print(){
                aa::aaa::StudentA a;
                a.Print("hello world.");
            }
        };

        StudentB::StudentB(/* args */)
        {
        }

        StudentB::~StudentB()
        {
        }
    }
}

#endif
