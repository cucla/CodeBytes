#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


class StudentEntry {
public:
	// constructors
	StudentEntry() = default;
	StudentEntry(const std::string &s, unsigned n, std::initializer_list<double> li) :
		name(s), passCources(n) { 
		for (auto el : li) {
			marks.push_back(el);
			markSum += el;
		}
	}
	StudentEntry(std::istream &);

	// member functions (1/2)
	std::string getStudentName() const { return name; }; 
	unsigned getPassCources() const { return passCources; };
	const std::vector<unsigned> & getMarks() const;
	std::vector<unsigned> & getMarks();
	double & getMarkSum() { return markSum; };  // read-write reference

	void setName(std::string s) { this->name = s; };
	void setPassCources(unsigned n) { this->passCources = n; };

	StudentEntry & combine(const StudentEntry &st);
	double avgMark() const;

	// data members
private:
	std::string				name;						
	unsigned				passCources = 0;
	std::vector<unsigned>	marks;
	double					markSum = 0;
};

// member function definitions (2/2)
const std::vector<unsigned> & StudentEntry::getMarks() const {
	return marks;
}

std::vector<unsigned> & StudentEntry::getMarks() {
	return marks;
}

StudentEntry & StudentEntry::combine(const StudentEntry &st) {
	passCources += st.passCources;
	for (auto i : st.marks) {
		marks.push_back(i);
		markSum += i;
	}
	return *this;
}

double StudentEntry::avgMark() const {
	return passCources ? markSum / passCources : 0;
}

// nonmember functions
StudentEntry add(const StudentEntry &st1, const StudentEntry &st2) {
	StudentEntry sum = st1;
	sum.combine(st2);
	return sum;
}

std::ostream & print(std::ostream &os, const StudentEntry &st) {
	os << st.getStudentName() << '\t' << st.getPassCources() << '\t';
	for (auto i : st.getMarks()) {
		os << i << " ";
	}
	os << "\tAverage [ " << st.avgMark()  << " ]" << std::endl;
	return os;
}

std::istream & read(std::istream &is, StudentEntry &st) {
	std::cout << "Enter student name & passed cources: " << std::endl;
	std::string e_name;
	unsigned e_passCources;
	is >> e_name >> e_passCources;
	st.setName(e_name);
	st.setPassCources(e_passCources);

	unsigned mark;
	st.getMarkSum() = 0.0f;
	if (!st.getMarks().empty())
		st.getMarks().clear();
	for (unsigned i = 0; i < st.getPassCources(); ++i) {
		is >> mark;
		st.getMarks().push_back(mark);
		st.getMarkSum() += mark;
	}
	return is;
}

// constructor
StudentEntry::StudentEntry(std::istream &is) {					
	read(is, *this);
}


int main() {
	std::cout << "1. Show List\n2. Add Entry\n3. Add Mark\n4. Delete Entry\n"
		"5. Search by Name\n6. Search by Mark\n7. Exit\n" << std::endl;
	std::cout << "Choose option: " << std::endl;
	int userChoice;
	std::cin >> userChoice;
	switch (userChoice) {
	case 1: break; // show list
	case 2: break; // add entry -> add new name
	case 3: break; // add mark -> to existing name
	case 4: break; // delete entry
	case 5: break; // search by name
	case 6: break; // search by mark
	case 7: break;
	}




	StudentEntry student;
	if (read(std::cin, student)) {
		StudentEntry nextStudent;
		while (read(std::cin, nextStudent)) {
			if (student.getStudentName() == nextStudent.getStudentName()) {
				student.combine(nextStudent);
			}
			else {
				print(std::cout, student);
				student = nextStudent;
			}
		}
		print(std::cout, student);
	}
	else {
		throw std::invalid_argument("Can't read student data");
	}


	// VisualStudio tail
	std::cout << "\nPress Enter..." << std::endl;		
	std::cin.get();
	return 0;
}
