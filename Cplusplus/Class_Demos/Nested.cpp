#include "stdafx.h"
#include <iostream>


/* 
 * NESTED CLASSES
 *
 * Inner class can access Outer's: 
 *		static vars, 
 *		private vars via pointer or reference
 *
 * 2 Inner classes can access each other's public fields
 * or access private fields if declared as 'friend' classes
 *
 * Outer class can access Inner's private members if it is 'friend'
 *
 * static vars must be defined outside class
 *		int Outer::Inner02::epoch = 1970;
 */

int glob;

class Outer {
	int d_value = 0;
	static int s_value;  // must be defined outside class to be visible

	class PrivateInner {
		int d_privateInner;
	// public members of private nested class
	// can be accessed from Outer class & other Inner classes
	public:
		PrivateInner() : d_privateInner(55) { }
		void privateInnerFunc() { std::cout << "HI!" << std::endl; }
	};

public:
	class Inner01 {
		class Inner02;	// forward declared Inner02 in Inner01
						// if contains pointers, references, parameters or 
						// return values to objects of the other nested classes
		void mutateOuter(Outer & o);
		Inner02 * ptr;
	};

	class Inner02 {
		friend class Outer;  // to access Inner's private fields

		int innerField;
	public:
		Inner02() : innerField(22) {
			std::cout << "Created Inner02 Object" << std::endl;
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

		Inner01 in1;	// Outer::Inner02 can access Outer::Inner01
		PrivateInner privateInnerObj; // Outer::Inner02 can access public fields Outer::PrivateInner
	};

	PrivateInner privateInnerObj;
	void Outer::caller() {
		privateInnerObj.privateInnerFunc();
	}

	static Inner02 getInner() { return Inner02(); }  // Outer class can use Inner as 'return' and 'args'

	int getInnerPrivate(Inner02 * p) {
		return p->innerField; 
	}
};

int Outer::s_value;  // static var definition

void Outer::Inner01::mutateOuter(Outer & o) {
	o.d_value++; 
}


int main() 
{
	Outer outer;
	Outer * outerPtr = new Outer;
	Outer::Inner02 inner;
	Outer::Inner02 * innerPtr = new Outer::Inner02;

	inner.setOuter1(outer, 10);		// pass reference to Outer
	inner.setOuter2(outerPtr, 100);	// pass pointer to Outer

	outer.caller();
	outerPtr->caller();

	Outer::Inner02 inner2 = outer.getInner();
	auto a = outer.getInnerPrivate(innerPtr);
	std::cout << "Inner's member: " << a << std::endl;


	std::cin.get();
}
