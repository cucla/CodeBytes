#include "stdafx.h"
#include <iostream>
#include <memory>
#include "IDependency.h"


// concrete implementation of 'IDependency'
class DepImpl1 : public IDependency {
public:
	void printit() override {
		std::cout << "[1] DepImpl1" << std::endl;
	};
};


// return unique_ptr owning the object 'DepImpl1' to which it points
std::unique_ptr<IDependency> makeImpl1() {
	return std::make_unique<DepImpl1>();
}

// return shared_ptr to the object 'DepImpl1'
std::shared_ptr<IDependency> getImpl1() {
	return std::make_shared<DepImpl1>();
}

