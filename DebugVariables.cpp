#include <iostream>
#include "DebugVariables.h"
#include "Canvas.h"
#include "Browser.h"

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
}