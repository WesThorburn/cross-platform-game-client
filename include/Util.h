#ifndef UTIL_H
#define UTIL_H

#include <sstream>
#include <string>
#include <vector>

namespace String{
	std::vector<std::string> split(std::string stringToSplit, char delimiter);
	std::vector<std::string> split(char charArray[], char delimiter);
};

#endif