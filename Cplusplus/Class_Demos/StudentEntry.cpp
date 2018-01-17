#include <iostream>
#include <string>

struct StudentEntry {
	// constructors
	StudentEntry() = default;
	StudentEntry(const std::string &s): name(s) { }
	StudentEntry(const std::string &s, unsigned n, std::initializer_list<double> li):
		name(s), passCources(n) {
		for (auto &el: li) {
			markSum += el;
		}
	}
	StudentEntry(std::istream &);

	// member functions
	std::string getStudentName() const { return name; }
	StudentEntry& combine (const StudentEntry&);
	double avgMark() const;

	// data members
	std::string name = "";
	unsigned passCources = 0;
	double markSum = 0.0;
};

StudentEntry& StudentEntry::combine(const StudentEntry& st) {
	passCources += st.passCources;
	markSum += st.markSum;
	return *this;
}

double StudentEntry::avgMark() const {
	if (passCources)
		return markSum/passCources;
	else
		return 0;
}

// nonmember interface functions
StudentEntry add(const StudentEntry &st1, const StudentEntry &st2) {
	StudentEntry sum = st1;
	sum.combine(st2);
	return sum;
}

std::ostream& print(std::ostream &os, const StudentEntry &st) {
	os << st.getStudentName() << " " << st.passCources << " " << st.markSum
			<< "\t | Average: " << st.avgMark() <<"\n";
	return os;
}

std::istream& read(std::istream &is, StudentEntry &st) {
	std::cout << "Enter next student data: " << std::endl;
	is >> st.name >> st.passCources;
	double mark;
	for (unsigned i = 0; i < st.passCources; ++i) {
		is >> mark;
		st.markSum += mark;
	}
	return is;
}

StudentEntry::StudentEntry(std::istream &is) {
	read(is, *this);
}

int main() {
	// object demos
	StudentEntry st01,
				 st02("Joe_Jonas"),
				 st03("Diplo", 3, {87, 94, 88});
	// G-Easy 2 90 80, Joe_Jonas 1 90, Joe_Jonas 2 88 94, Diplo 2 92 88

	// combine same student data from input, if followed one-by-one
	StudentEntry student;
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
