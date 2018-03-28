#include "stdafx.h"
#include "StudentEntry.h"


int main() {

	loadDataFromFile();	
	int userChoice;
	do {
		std::cout << "\n1. Show List\n2. Search by Name\n3. Search by Average Mark\n4. Add New Record\n"
			"5. Change Record\n6. Delete Record\n7. Clear List\n8. Exit\n" << std::endl;
		userChoice = GetUserChoice();
		switch (userChoice) {
		case 1: 
			showList(std::cout);
			break;	
		case 2: {
			searchName(idx);  // need 'extern' idx in .h file
			idx = 51;
			}
			break;		
		case 3: 
			searchMark();
			break;		
		case 4: 
			addRec();
			break;		
		case 5: 
			changeRec();
			break;		
		case 6: 
			deleteRec();
			break;		
		case 7: 
			clearList();
			break;		
		case 8: break;
		}
	} while (userChoice != 8);
	saveDataToFile();


	std::cin.get();
}
