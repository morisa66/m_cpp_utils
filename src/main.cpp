#include<iostream>
#include "m_shared_ptr.h"

class Base
{
public:
	virtual ~Base(){}
};

class A : public Base 
{
public:
	~A() { std::cout << "~A" << std::endl; }
};

void test()
{
	morisa::m_shared_ptr<A> p1(new A());
	std::cout << "p1:" << p1.get_counter() << std::endl;
	morisa::m_shared_ptr<Base> p2;
	std::cout << "p2:" << p2.get_counter() << std::endl;
	p2 = p1;
	std::cout << "p2:" << p2.get_counter() << std::endl;
	morisa::m_shared_ptr<A> p3 = morisa::utils::m_static_cast<A>(p2);
	std::cout << "p3:" << p3.get_counter() << std::endl;
	p3.release();
	std::cout << "p2:" << p2.get_counter() << std::endl;
	p2.release();
	std::cout << "p1:" << p1.get_counter() << std::endl;
	p1.release();
	std::cout << "end test" << std::endl;
}

int main(int argc, char** argv) 
{
	test();
}		

/*
p1:1
p2:0
p2:2
p3:3
p2:2
p1:1
~A
end test
*/