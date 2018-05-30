#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>


class Sub {
public:
	virtual void printit() = 0;
	virtual std::string name() const = 0;
};

class SubImpl1 : public Sub {
public:
	void printit() {
		std::cout << "SubImpl1: implementation [1]" << std::endl;
	};
	std::string name() const {
		return "SubImpl1";
	}
};
class SubImpl2 : public Sub {
public:
	void printit() {
		std::cout << "SubImpl2: implementation [2]" << std::endl;
	};
	std::string name() const {
		return "SubImpl2";
	}
};


// Sub * sub; -> /raw pointer/ 
class A {
public:
	A(Sub * sub) : sub(sub) {
		if (!sub)
			throw std::exception("null dependency");
	}

	void doSomething() {
		sub->printit();
	};

private:
	Sub * sub; 
};

// function to construct 'A' object and return 'unique' pointer to it
std::unique_ptr<A> factoryA(Sub * sub) {
	return std::unique_ptr<A>(new A(sub));
}


// std::shared_ptr<Sub> sub; -> /shared pointer/
class B {
public:
	B(std::shared_ptr<Sub> sub) : sub(sub) {
		if (!sub)
			throw std::exception("null dependency");
	}

	void doSomething() {
		sub->printit();
	};

private:
	std::shared_ptr<Sub> sub;
};

std::unique_ptr<B> factoryB(Sub * sub) {
	// don't initialize several shared_ptr objects with the same raw pointer
	// or raw pointer will be deleted several times
	std::shared_ptr<Sub> val;
	if (sub->name() == "SubImpl1") {
		val = std::make_shared<SubImpl1>();
	}
	else {
		val = std::make_shared<SubImpl2>();
	}
	return std::unique_ptr<B>(new B(val));
}


// std::unique_ptr<Sub> sub; -> /unique pointer/
class C {
public:
	// ways to pass 'unique_ptr' to constructor
	// https://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function
	C(std::unique_ptr<Sub> &&sub) : sub(std::move(sub)) {
		//if (!sub)  throw std::exception("null dependency");
	}

	void doSomething() {
		sub->printit();
	};

private:
	std::unique_ptr<Sub> sub;
};

std::unique_ptr<C> factoryC(Sub * sub) {	
	std::unique_ptr<Sub> val;
	if (sub->name() == "SubImpl1") {
		val = std::make_unique<SubImpl1>();
	}
	else {
		val = std::make_unique<SubImpl2>();
	}

	return std::make_unique<C>(std::move(val));
}


int main()
{
	SubImpl1 * sub1 = new SubImpl1;
	SubImpl2 * sub2 = new SubImpl2;
	
	auto a1a = factoryA(sub1);
	a1a->doSomething();
	auto a1b = factoryA(sub1);
	a1b->doSomething();
	auto a2 = factoryA(sub2);
	a2->doSomething();

	auto b1a = factoryB(sub1);
	b1a->doSomething();
	auto b1b = factoryB(sub1);
	b1b->doSomething();
	auto b2 = factoryB(sub2);
	b2->doSomething();

	auto c1a = factoryC(sub1);
	a1a->doSomething();
	auto c1b = factoryC(sub1);
	a1b->doSomething();
	auto c2 = factoryC(sub2);
	a2->doSomething();


	std::cin.get();
}
