#include "stdafx.h"
#include <iostream>
#include <memory>
#include "IDependency.h"


// concrete implementation of 'IDependency'
class DepImpl2 : public IDependency {
public:
	void printit() override {
		std::cout << "[2] DepImpl2" << std::endl;
	};
};


// return unique_ptr owning the object 'DepImpl2' to which it points
std::unique_ptr<IDependency> makeImpl2() {
	return std::make_unique<DepImpl2>();
}

// return shared_ptr to the object 'DepImpl2'
std::shared_ptr<IDependency> getImpl2() {
	return std::make_shared<DepImpl2>();
}
