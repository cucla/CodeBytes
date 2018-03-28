#include "stdafx.h"
#include "StudentEntry.h"


std::fstream	  entryFile;
const char	  FILE_PATH[] = "C:\\Users\\011256\\Desktop\\filesC++\\studentList.dat";
const int	  MAX_STUDENT = 50;
int		  entryCount = -1;		// -1 means the list is empty
size_t		  idx = 51;			// 51 means not pointing to any element, cuz only 50 students
StudentEntry *	  entryList[MAX_STUDENT];	// array of pointers to class objects


StudentEntry & StudentEntry::operator = (StudentEntry & st) {
	name = st.name;
	marks = st.marks;
	passCources = st.passCources;
	markSum = st.markSum;
	return *this;
}

StudentEntry & StudentEntry::addNewMark(int newMark) {
	marks.push_back(newMark);
	++passCources;
	markSum += newMark;
	return *this;
}

StudentEntry & StudentEntry::changeMark(int newMark, size_t idx) {
	markSum -= marks[idx];
	marks[idx] = newMark;
	markSum += newMark;
	return *this;
}

double StudentEntry::averageMark() {
	return passCources > 0 ? markSum / passCources : 0;
}


std::ostream & showRecord(std::ostream &os, size_t i) {
	os << entryList[i]->name << "\t";
	for (auto el : entryList[i]->marks)
		os << el << "\t";
	os << "[ " << entryList[i]->averageMark() << " ]" << "\t";
	os << "\n";
	return os;
}

std::ostream & showList(std::ostream &os) {
	if (entryCount > 0) {
		for (size_t i = 0; i < entryCount; ++i) {
			showRecord(os, i);
		}
	}
	else {
		os << "List is empty. ";
	}
	return os;
}

std::string getName() {
	std::string input;
	std::cout << "Enter student name: ";
	std::cin >> input;
	return input;
}

int getMark() {
	int input;
	std::cout << "Enter new mark: ";
	std::cin >> input;
	return input;
}

double getAverageMark() {
	double input;
	std::cout << "Enter student average mark: ";
	std::cin >> input;
	return input;
}

std::vector<int> getMarks() {
	std::string line;
	int number;
	std::vector<int> input;

	std::cout << "Enter student marks separated by spaces: ";
	getline(std::cin, line);
	std::istringstream ss(line);
	while (ss >> number) {
		input.push_back(number);
	}
	return input;
}

void searchName(size_t &idx) {
	std::string input = getName();
	bool foundMatch = false;
	for (size_t i = 0; i < entryCount; ++i) {
		if (entryList[i]->getStudentName() == input) {
			showRecord(std::cout, i);
			foundMatch = true;
			idx = i;
		}
	}
	if (!foundMatch)
		std::cout << "No such student in a list" << std::endl;
}

bool sortDescending(const std::pair <double, size_t> &a,  // to sort 'temp' in searchMark()
	const std::pair <double, size_t> &b) {
	return (a.first > b.first);
}

void searchMark() {
	double input = getAverageMark();
	std::vector< std::pair <double, size_t> > temp;  // keep -> pairs (average mark, index)

	bool foundMatch = false;
	for (size_t i = 0; i < entryCount; ++i) {
		if (entryList[i]->averageMark() == input) {
			showRecord(std::cout, i);
			foundMatch = true;
		}
		else {
			if (entryList[i]->averageMark() < input)
				temp.push_back(std::make_pair(entryList[i]->averageMark(), i));
		}
	}
	if (!foundMatch) {
		// sort 'temp' by average mark
		std::sort(temp.begin(), temp.end(), sortDescending);
		for (auto it = temp.begin(); it != temp.end(); it++) {
			showRecord(std::cout, it->second);
		}
	}
}

void sortList() {
	// Sort array of pointers [entryList] using lambda
	std::sort(entryList, entryList + entryCount, [](StudentEntry * a, StudentEntry * b) {
		return a->getStudentName() < b->getStudentName(); });
}

void addRec() {
	std::string in_name = getName();
	std::cin.ignore();		// cuz getline() [in getMarks()] consumes '\n' and ceases
	++entryCount;
	if (entryCount > 0)
		entryList[entryCount - 1] = new StudentEntry(in_name, getMarks());
	else {
		entryCount = 0;
		entryList[entryCount] = new StudentEntry(in_name, getMarks());
		++entryCount;
	}
	sortList();
}

void changeName() {
	searchName(idx);
	if (idx < 51) {
		std::string new_name = getName();
		entryList[idx]->setStudentName(new_name);
		idx = 51;
	}
	sortList();
}

void changeMark() {  // happens to be overloaded
	searchName(idx);
	if (idx < 51) {
		size_t mark_idx;
		std::cout << "Which mark? [index] ";
		std::cin >> mark_idx;
		int new_mark = getMark();
		entryList[idx]->changeMark(new_mark, mark_idx);
	}
}

void addMark() {
	searchName(idx);
	if (idx < 51) {
		int new_mark = getMark();
		entryList[idx]->addNewMark(new_mark);
		idx = 51;
	}
}

int GetUserChoice() {
	int choice;
	std::cout << "Choose the option and press Enter: ";
	std::cin >> choice;
	return choice;
}

void changeRec() {
	std::cout << "\n1. Change Name\n2. Change Mark\n3. Add Mark" << std::endl;
	int userChoice = GetUserChoice();
	switch (userChoice) {
	case 1:
		changeName();
		break;
	case 2:
		changeMark();
		break;
	case 3:
		addMark();
		break;
	}
}

void deleteRec() {
	std::string in_name = getName();
	for (size_t i = 0; i < entryCount; ++i) {
		if (entryList[i]->getStudentName() == in_name) {
			if (i != (entryCount - 1)) {
				for (size_t j = i; j < entryCount - 1; ++j) {
					*(entryList[j]) = *(entryList[j + 1]);	// operator = is overloaded
															// or entryList[j]->name = entryList[j + 1]->name; ...
				}
			}
			delete entryList[entryCount - 1];
			--entryCount;
		}
	}
}

void clearList() {
	for (size_t i = 0; i < entryCount; i++) {
		delete entryList[i];
	}
	entryCount = -1;
}

void loadDataFromFile() {
	entryFile.open(FILE_PATH, std::fstream::in);
	if (entryFile.is_open()) {
		std::cout << "File opened" << std::endl;
		entryCount = 0;
		for (std::string line; getline(entryFile, line); ) {  // read line-by-line
			std::string buf;
			std::stringstream ss(line);
			if (ss >> buf) {		// first tocken in a line as a name
				entryList[entryCount] = new StudentEntry(buf, {});
			}
			while (ss >> buf) {		// other tockens as marks
				int iBuf = std::stoi(buf, nullptr);
				entryList[entryCount]->addNewMark(iBuf);
			}
			++entryCount;
		}
		sortList();  // keep sorted list in memory

		std::cout << std::endl;
		entryFile.close();
		entryFile.clear();
	}
	else {
		entryFile.clear();
		std::cout << "File not found in [ " << FILE_PATH << " ]\n" << std::endl;
	}
}

void saveDataToFile() {
	entryFile.open(FILE_PATH, std::fstream::out);
	if (entryFile.is_open()) {
		if (!entryFile.good()) {
			std::cout << "Error writing file." << std::endl;
		}
		else
			for (size_t i = 0; i < entryCount; i++) {
				entryFile << entryList[i]->name << "\t";
				for (int j = 0; j < entryList[i]->passCources; j++)
					entryFile << entryList[i]->marks[j] << "\t";
				entryFile << "\n";
			}
		entryFile.close();
	}
}

