#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>

struct Location{
	int x;
	int y;

	void print(std::string label = ""){
		std::cout << label << " [x: " << x << ", " << y << "]" << std::endl;
	}

	bool operator==(const Location& location){
		if(x == location.x && y == location.y){
			return 1;
		}
		return 0;
	}

	void operator=(const Location& location){
		x = location.x;
		y = location.y;
	}
};

#endif