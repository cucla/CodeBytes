#include "stdafx.h"
#include <iostream>
#include <string>

struct StudentEntry {
	StudentEntry() = default;						// constructors (1/2)
	StudentEntry(const std::string &s): name(s) { }
	StudentEntry(const std::string &s, unsigned n, std::initializer_list<double> li):
		name(s), passCources(n) {
		for (auto &el: li) {
			markSum += el;
		}
	}
	StudentEntry(std::istream &);

	std::string getStudentName() const { return name; }			// member functions
	StudentEntry& combine (const StudentEntry&);
	double avgMark() const;

	std::string name = "";							// data members
	unsigned passCources = 0;
	double markSum = 0.0;
};

StudentEntry& StudentEntry::combine(const StudentEntry& st) {			// combine function
	passCources += st.passCources;
	markSum += st.markSum;
	return *this;	// returns object on which the function was called -> this.combine(next)
}

double StudentEntry::avgMark() const {						// avgMark function
	return passCources ? markSum / passCources : 0;
}

StudentEntry add(const StudentEntry &st1, const StudentEntry &st2) {		// nonmember interface functions // add function
	StudentEntry sum = st1;
	sum.combine(st2);
	return sum;
}

std::ostream& print(std::ostream &os, const StudentEntry &st) {			// print function
	os << st.getStudentName() << " " << st.passCources << " " << st.markSum
			<< "\t | Average: " << st.avgMark() <<"\n";
	return os;
}

std::istream& read(std::istream &is, StudentEntry &st) {			// read function
	std::cout << "Enter next student data: " << std::endl;
	is >> st.name >> st.passCources;
	st.markSum = 0.0f;
	double mark;
	for (unsigned i = 0; i < st.passCources; ++i) {
		is >> mark;
		st.markSum += mark;
	}
	return is;
}

StudentEntry::StudentEntry(std::istream &is) {					// constructor (2/2)
	read(is, *this);     // use this to access object as a whole (because 'read' second parameter is a ref to obj)
}

int main() {
	// object demos
	StudentEntry st01,
		     st02("Joe_Jonas"),
		     st03("Diplo", 3, {87, 94, 88});
	// G-Easy 2 90 80, Joe_Jonas 1 90, Joe_Jonas 2 88 94, Diplo 2 92 88

	StudentEntry student; 							// combine same student data
	if (read(std::cin, student)) {
		StudentEntry nextStudent;
		while (read(std::cin, nextStudent)) {
			if (student.getStudentName() == nextStudent.getStudentName())
				student.combine(nextStudent);
			else {
				print(std::cout, student);
				student = nextStudent;
			}
		}
		print(std::cout, student);  // last transaction
	} else {
		std::cerr << "No data?!" << std::endl;
	}
}
