#include <iostream>
#include "TouchControls.h"
#include "Canvas.h"
#include "Controls.h"

TouchControls::TouchControls(): HudElement(TOUCH_CONTROLS){
	
}

void TouchControls::update(){
	
}

void TouchControls::draw(){
	Canvas::setGlobalAlpha(Canvas::HUD, 0.4);
	Canvas::setFillStyle(Canvas::HUD, 0, 0, 0);
	Canvas::setStrokeStyle(Canvas::HUD, 0, 0, 0);
	drawLeftStick();
	drawRightStick();
}

void TouchControls::drawLeftStick(){
	int xPos = Controls::state.leftTouchStickPosition.x;
	int yPos = Controls::state.leftTouchStickPosition.y;

	if(xPos == 0 && yPos == 0){
		return;
	}

	Canvas::beginPath(Canvas::HUD);
	Canvas::arc(Canvas::HUD, xPos, yPos, m_backingRadius);
	Canvas::fill(Canvas::HUD);
	Canvas::stroke(Canvas::HUD);
}

void TouchControls::drawRightStick(){
	int xPos = Controls::state.rightTouchStickPosition.x;
	int yPos = Controls::state.rightTouchStickPosition.y;

	if(xPos == 0 && yPos == 0){
		return;
	}

	Canvas::beginPath(Canvas::HUD);
	Canvas::arc(Canvas::HUD, xPos, yPos, m_backingRadius);
	Canvas::fill(Canvas::HUD);
	Canvas::stroke(Canvas::HUD);
}