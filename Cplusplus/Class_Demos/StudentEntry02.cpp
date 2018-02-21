#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

// get & set methods --> http://www.walletfox.com/course/getset.php

class StudentEntry {
public:
	StudentEntry() = default;									// constructors
	StudentEntry(const std::string &s, unsigned n, std::initializer_list<unsigned> li) :
		name(s), passCources(n) {
		for (auto el : li) {
			marks.push_back(el);
			markSum += el;
		}
	}

	std::string getStudentName() const { return name; };						// member functions
	unsigned getPassCources() const { return passCources; };					// accessor methods
	const std::vector<unsigned> & getMarks() const;
	std::vector<unsigned> & getMarks();
	double & getMarkSum() { return markSum; };  // read-write reference
	double avgMark() const;
	void setName(std::string s) { this->name = s; };						// mutator methods
	void setPassCources(unsigned n);

private:												// data members
	std::string				name;
	unsigned				passCources = 0;
	std::vector<unsigned>	marks;
	double					markSum = 0;
};

const std::vector<unsigned> & StudentEntry::getMarks() const {
	return marks;
}

std::vector<unsigned> & StudentEntry::getMarks() {
	return marks;
}

double StudentEntry::avgMark() const {
	return passCources ? markSum / passCources : 0;
}

void StudentEntry::setPassCources(unsigned n) { 
	assert(n >= 0);																// assert (debugging phase)
	this->passCources = n; 
};

std::ostream & print(std::ostream &os, const StudentEntry &st) {
	os << st.getStudentName() << '\t' << st.getPassCources() << '\t';
	for (auto i : st.getMarks()) {
		os << i << " ";
	}
	os << "\tAverage [ " << st.avgMark() << " ]" << std::endl;
	return os;
}

std::istream & read(std::istream &is, StudentEntry &st) {
	std::cout << "Enter student name & passed courses: " << std::endl;
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


int main()
{
	const int MAX_STUDENT = 50;									// declarations
	int entryCount = -1;		//-1 means the list is empty	
	const char FILE_PATH[] = "C:\\Users\\011256\\Desktop\\C++\\student_list.txt";
	std::fstream entryFile;


	StudentEntry *entryList[MAX_STUDENT] = {};							// arr of pointers to class objects?
	
	entryList[0] = new StudentEntry();
	read(std::cin, *entryList[0]);
	print(std::cout, *entryList[0]);

	// saveDataToFile()
	entryFile.open(FILE_PATH, std::fstream::out);
	if (entryFile.is_open()) {
		if (!entryFile.good()) {
			std::cout << "Error writing file" << std::endl;
		}
		else {
			for (int i = 0; i < MAX_STUDENT; i++) {
				if (entryList[i]) {
					entryFile << entryList[i]->getStudentName() << '\t';
					for (auto i : entryList[i]->getMarks()) entryFile << i << '\t';
					entryFile << std::endl;
				}
			}
		}
	}



	/*
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
	case 6: break; // search by average mark
	case 7: break;
	}
	*/
	std::cin.get();
}
