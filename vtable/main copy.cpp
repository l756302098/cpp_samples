/*
 * main.cpp
 *
 *  Created on: 12 01, 2021
 *      Author: liyanlong
 */
#include <iostream>
using namespace std;
class Base
{
public :
     virtual void func1()
	 {
		 cout<<"Base::func1" <<endl;
	 }
     virtual void func2()
	 {
		 cout<<"Base::func2" <<endl;
	 } 
private :
     int a ;
};
 
class Derive :public Base
 { 
 public :
	virtual void func1()
    {
		cout<<"Derive::func1" <<endl;
	}
     virtual void func3()
	{ 
	cout<<"Derive::func3" <<endl;
	}
    virtual void func4()
	{
		 cout<<"Derive::func4" <<endl;
	}
private :
     int b ;
};
 
typedef void (* FUNC) ();
void PrintVTable (int* VTable)
 {
     cout<<" 虚表地址>"<< VTable<<endl ;
	 
     for (int i = 0; VTable[i ] != 0; ++i)
		{
			 printf(" 第%d个虚函数地址 :0X%x,->", i , VTable[i ]);
			 FUNC f = (FUNC) VTable[i ];
			 f();
		}
     cout<<endl ;
}

int main(int argc, char *argv[])
{
    std::cout << "start ...!" << std::endl;
    Base b1 ;
    Derive d1 ;
    int* VTable1 = (int*)(*( int*)&b1 );
    int* VTable2 = (int*)(*( int*)&d1 );
    PrintVTable(VTable1 );
    PrintVTable(VTable2 );

    return 0;
}

