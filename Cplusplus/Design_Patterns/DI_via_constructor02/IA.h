#pragma once

#include <memory>
#include "IDependency.h"

/*   ____________________________________
 *  |									                   |
 *  | interface class IA				         |
 *  |____________________________________|
 *					           A
 *   __________________|_________________
 *  |									                   |
 *  | class A : public IA				         |
 *  |------------------------------------|
 *  | unique_ptr<IDependency> m_thing	   |
 *  |____________________________________|
 */

class IA {
public:
	virtual ~IA() = default;
	virtual void doSomething() = 0;
};

std::unique_ptr<IA> makeA(std::unique_ptr<IDependency> &&sub);
