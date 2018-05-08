#include <iostream>
#include "DebugVariables.h"
#include "Canvas.h"
#include "Browser.h"
#include "Controls.h"

DebugVariables::DebugVariables(): HudElement(DEBUG_VARIABLES){
	std::cout << "created debug variables" << std::endl;
}

void DebugVariables::update(){
	
}

void DebugVariables::draw(){
	Canvas::setTextBaseline(Canvas::HUD, "middle");
	Canvas::setFillStyle(Canvas::HUD, 104, 104, 104);
	Canvas::setFontSize(Canvas::HUD, 18);
	Canvas::fillText(Canvas::HUD, "Screen Width: " + std::to_string(Browser::attributes.width), 4, 13);
	Canvas::fillText(Canvas::HUD, "Screen Height: " + std::to_string(Browser::attributes.height), 4, 30);
	Canvas::fillText(Canvas::HUD, "Scale Width: " + std::to_string(Canvas::scaleAttributes.scaledWidth), 4, 47);
	Canvas::fillText(Canvas::HUD, "Scale Height: " + std::to_string(Canvas::scaleAttributes.scaledHeight), 4, 64);
	Canvas::fillText(Canvas::HUD, "X Scale: " + std::to_string(Canvas::scaleAttributes.scaleX), 4, 81);
	Canvas::fillText(Canvas::HUD, "Y Scale: " + std::to_string(Canvas::scaleAttributes.scaleY), 4, 98);
	Canvas::fillText(Canvas::HUD, "Pixel Ratio: " + std::to_string(Browser::attributes.devicePixelRatio), 4, 115);
	Canvas::fillText(Canvas::HUD, "isMobile: " + std::to_string(Browser::attributes.isMobile), 4, 132);

	if(Controls::state.touchPoints.size() > 0){
		Canvas::fillText(Canvas::HUD, "Stick One", 200, 13);
		Canvas::fillText(Canvas::HUD, "Screen X: " + std::to_string(Controls::state.touchPoints.at(0).currentLocation.x), 200, 30);
		Canvas::fillText(Canvas::HUD, "Screen Y: " + std::to_string(Controls::state.touchPoints.at(0).currentLocation.y), 200, 47);
	}

	if(Controls::state.touchPoints.size() > 1){
		Canvas::fillText(Canvas::HUD, "Stick Two", 330, 13);
		Canvas::fillText(Canvas::HUD, "Screen X: " + std::to_string(Controls::state.touchPoints.at(1).currentLocation.x), 330, 30);
		Canvas::fillText(Canvas::HUD, "Screen Y: " + std::to_string(Controls::state.touchPoints.at(1).currentLocation.y), 330, 47);
	}
}