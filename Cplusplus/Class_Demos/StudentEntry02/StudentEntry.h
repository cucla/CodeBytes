#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>	


extern size_t idx;


class StudentEntry {
	friend std::ostream & showRecord(std::ostream &os, size_t i);
	friend void saveDataToFile();
public:
	StudentEntry(const std::string &s, std::vector<int> li) :		// constructor
		name(s), marks(li) {
		for (auto &el : li) {
			++passCources;
			markSum += el;
		}
	}
	// member functions
	std::string getStudentName() const { return name; }	// returns copy of name
	void setStudentName(std::string input) { name = input; }
	StudentEntry & addNewMark(int newMark);
	StudentEntry & changeMark(int newMark, size_t idx);
	double averageMark();
	// overloading operator
	StudentEntry & operator = (StudentEntry & st);

private:
	std::string			name;										// data members
	std::vector<int>	marks;
	unsigned			passCources = 0;
	double				markSum = 0.0;
};	

std::ostream & showRecord(std::ostream &os, size_t i);				// friend functions again
void saveDataToFile();

std::ostream & showList(std::ostream &os);
std::string getName();
int getMark();
double getAverageMark();
std::vector<int> getMarks();
void searchName(size_t &idx);
bool sortDescending(const std::pair <double, size_t> &a, const std::pair <double, size_t> &b);
void searchMark();
void sortList();
void addRec();
void changeName();
void changeMark();
void addMark();
int GetUserChoice();
void changeRec();
void deleteRec();
void clearList();
void loadDataFromFile();
void saveDataToFile();

