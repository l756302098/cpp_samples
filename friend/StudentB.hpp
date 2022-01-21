#ifndef __STUDENT_B_
#define __STUDENT_B_

#include <iostream>
#include "StudentA.hpp"
#include "Student.h"

namespace aa
{
    namespace bbb
    {
        class StudentB :public Student
        {
        private:
            /* data */
            
        public:
            StudentB(/* args */);
            ~StudentB();
            void Test() override
            {
                aa::aaa::StudentA a;
                a.Print("hello world.");
            }
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
