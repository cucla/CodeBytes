#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <iomanip>
#include <limits>
#include <array>
#include <cmath>
#include <cstring>
#include <cstdlib> 
#include <cctype>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <numeric>
#include <iterator>
#include <memory> 

#include "Char_traits.h"
#include "String_view.h"


void* operator new(std::size_t count) {
	std::cout << "allocated " << count << " bytes" << std::endl;
	return malloc(count);
}


int main()
{
				std::cout << "1" << std::endl;
	std::string S01{ "trader" };
	std::string S02{ "dev" };

				std::cout << "2" << std::endl;
	space::string_view S03 = "simple joy";

				std::cout << "3" << std::endl;
	for (auto el : S03)
		std::cout << el << " ";






	std::cout << "" << std::endl;




	std::cin.get();
}

