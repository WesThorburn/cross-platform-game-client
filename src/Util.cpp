#include "Util.h"

namespace String{
	std::vector<std::string> split(std::string stringToSplit, char delimiter){
		std::vector<std::string> splitString;
		std::stringstream ss;
		ss.str(stringToSplit);
		std::string item;
		while(getline(ss, item, delimiter)){
			splitString.push_back(item);
		}
		return splitString;
	}

	std::vector<std::string> split(char charArray[], char delimiter){
		return split(std::string(charArray), delimiter);
	}
};