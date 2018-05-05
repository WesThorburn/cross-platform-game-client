#include <iostream>
#include "DebugVariables.h"
#include "Canvas.h"

DebugVariables::DebugVariables(): HudElement("debug", H_LEFT, V_TOP, 200, 100){
	std::cout << "created debug variables" << std::endl;
}

void DebugVariables::update(){
	std::cout << "updating debug variables" << std::endl;
}

void DebugVariables::draw(){
	std::cout << "drawing debug variables" << std::endl;
}