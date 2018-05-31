#include "stdafx.h"
#include <memory>
#include "IA.h"


class A : public IA {
public:
	// ways to pass 'unique_ptr' to constructor
	// https://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function

	A(std::unique_ptr<IDependency> &&sub) : m_thing(std::move(sub)) {
		// if (!sub)  throw std::exception("null dependency");
	}

	void doSomething() override {
		m_thing->printit();
	};

private:
	std::unique_ptr<IDependency> m_thing;
};


std::unique_ptr<IA> makeA(std::unique_ptr<IDependency> &&sub) {
	return std::make_unique<A>(std::move(sub));
}
