#include "stdafx.h"
#include <iostream>
#include <memory>
#include "IA.h"


class MockImpl : public IDependency {
public:
	void printit() override {
		std::cout << "Mock Test" << std::endl;
	};
};

void Test() {
	auto aObj = makeA(std::make_unique<MockImpl>());

	// Test aObj without a real implementation
}
