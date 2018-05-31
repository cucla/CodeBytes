#include "stdafx.h"
#include <iostream>
#include <memory>
#include "IA.h"
#include "B.h"


std::unique_ptr<IA> factoryA(std::string implementation);
std::unique_ptr<B> makeB(std::string implementation);

int main()
{
	auto aObjPtr = factoryA("DepImpl1");
	aObjPtr->doSomething();

	auto bObjPtr = makeB("DepImpl2");
	bObjPtr->doSomething();


	std::cin.get();
}


std::unique_ptr<IA> factoryA(std::string implementation) {
	
	std::unique_ptr<IDependency> m_thing;
	if (implementation == "DepImpl1") {
		m_thing = makeImpl1();
	}
	else if (implementation == "DepImpl2") {
		m_thing = makeImpl2();
	}
	return makeA(std::move(m_thing));
}

// construct 'B' object and return 'unique_ptr' to it
std::unique_ptr<B> makeB(std::string implementation) {
	
	std::shared_ptr<IDependency> m_thing;
	if (implementation == "DepImpl1") {
		m_thing = getImpl1();
	}
	else if (implementation == "DepImpl2") {
		m_thing = getImpl2();
	}
	return std::unique_ptr<B>(new B(m_thing));
}
