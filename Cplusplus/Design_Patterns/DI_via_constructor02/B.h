#pragma once

#include <memory>
#include "IDependency.h"


/*   ____________________________________
 *  |									                   |
 *  | class B							               |
 *  |------------------------------------|
 *  | shared_ptr<IDependency> m_thing	   |
 *  |____________________________________|
 */

class B {
public:
	B(std::shared_ptr<IDependency> sub) : m_thing(sub) {
		if (!sub)
			throw std::exception("null dependency");
	}

	void doSomething() {
		m_thing->printit();
	};

private:
	std::shared_ptr<IDependency> m_thing;
};
