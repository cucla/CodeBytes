#include "stdafx.h"
#include <iostream>


/* NESTED CLASSES
 *
 * Inner class can access Outer's fields 
 * 2 Inner classes can access each other if both public
 * Outer class can access Inner's private members if it is 'friend'
 */

int glob;

class Outer {
	int d_value = 0;
	static int s_value;

public:
	class Inner01 {
		void mutateOuter(Outer & o);
	};

	class Inner02 {
		friend class Outer;  // to access Inner's private fields

		int innerField;
	public:
		Inner02() : innerField(22) {
			std::cout << "Created Inner Object" << std::endl;
		}

		// No.1 reference to access Outer's private
		void setOuter1(Outer & outer, int i) {
			outer.d_value = i;
			std::cout << "Outer's d_value: " << outer.d_value << std::endl;

			s_value = i;
			std::cout << "Outer's s_value: " << s_value << std::endl;

			glob = i;
			std::cout << "Global's s_value: " << glob << std::endl;
		}

		// No.2 pointer to access Outer's private
		void setOuter2(Outer * p, int i) {
			p->d_value = i;
			std::cout << "Outer's d_value: " << p->d_value << std::endl;
		}

		Inner01 in1; // Outer::Inner02 can access Outer::Inner01
	};

	static Inner02 getInner() { return Inner02(); }  // Outer class can use Inner as 'return' and 'args'

	int getInnerPrivate(Inner02 * p) {
		return p->innerField; 
	}
};

int Outer::s_value;  // to make Outer static field visible to Inner class

void Outer::Inner01::mutateOuter(Outer & o) {
	o.d_value++; 
}


int main() 
{
	Outer outer;
	Outer * outerPtr = new Outer;
	Outer::Inner02 inner;
	Outer::Inner02 * innerPtr = new Outer::Inner02;

	inner.setOuter1(outer, 10);
	inner.setOuter2(outerPtr, 100);

	Outer::Inner02 inner2 = outer.getInner();
	auto a = outer.getInnerPrivate(innerPtr);
	std::cout << "Inner's member: " << a << std::endl;


	std::cin.get();
}

