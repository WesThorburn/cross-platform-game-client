#include <math.h>
#include <iostream>
#include "TouchControls.h"
#include "Canvas.h"

TouchControls::TouchControls(): HudElement(TOUCH_CONTROLS){
	
}

void TouchControls::update(){
	resetSticks();
	resetMovementControls();
	updateSticks();
}

void TouchControls::resetSticks(){
	m_leftStickAngleRadians = 0.0;
	m_rightStickAngleRadians = 0.0;
}

void TouchControls::updateSticks(){
	Controls::TouchPoint* touchPoint1 = &Controls::state.touchPoints.at(0);
	Controls::TouchPoint* touchPoint2 = &Controls::state.touchPoints.at(1);

	processTouchPoint(touchPoint1);
	processTouchPoint(touchPoint2);
}

void TouchControls::processTouchPoint(Controls::TouchPoint* touchPoint){
	if(!touchPoint->isActive){
		return;
	}
	if(touchPoint->startLocation.x <= Canvas::scaleAttributes.scaledWidth * Canvas::scaleAttributes.scaleX / 2){
		updateLeftStick(touchPoint);
	}
	else if(touchPoint->startLocation.x > Canvas::scaleAttributes.scaledWidth * Canvas::scaleAttributes.scaleX / 2){
		updateRightStick(touchPoint);
	}
}

void TouchControls::updateLeftStick(Controls::TouchPoint* touchPoint){
	Location backingPosition = getLeftStickBackingPosition();
	int deltaX = backingPosition.x - (touchPoint->currentLocation.x / Canvas::scaleAttributes.scaleX);
	int deltaY = backingPosition.y - (touchPoint->currentLocation.y / Canvas::scaleAttributes.scaleY);
	m_leftStickAngleRadians = atan2(deltaY, deltaX) + M_PI;
	updateMovementControlInput();
}

void TouchControls::updateRightStick(Controls::TouchPoint* touchPoint){
	Location backingPosition = getRightStickBackingPosition();
	int deltaX = backingPosition.x - (touchPoint->currentLocation.x / Canvas::scaleAttributes.scaleX);
	int deltaY = backingPosition.y - (touchPoint->currentLocation.y / Canvas::scaleAttributes.scaleY);
	m_rightStickAngleRadians = atan2(deltaY, deltaX) + M_PI;
}

Location TouchControls::getLeftStickBackingPosition(){
	return {
		Canvas::scaleAttributes.scaledWidth / 6, 
		(Canvas::scaleAttributes.scaledHeight/12) * 11
	};
}

Location TouchControls::getRightStickBackingPosition(){
	return {
		(Canvas::scaleAttributes.scaledWidth / 6) * 5, 
		(Canvas::scaleAttributes.scaledHeight/12) * 11
	};
}

void TouchControls::updateMovementControlInput(){
	if(m_leftStickAngleRadians >= 5.89 || m_leftStickAngleRadians < 0.393){ //337.5 -> 22.5
		Controls::state.pressingRight = 1;
	}
	else if(m_leftStickAngleRadians >= 0.393 && m_leftStickAngleRadians < 1.178){ //22.5 -> 67.5
		Controls::state.pressingRight = 1;
		Controls::state.pressingDown = 1;
	}
	else if(m_leftStickAngleRadians >= 1.178 && m_leftStickAngleRadians < 1.963){ //67.5 -> 112.5
		Controls::state.pressingDown = 1;
	}
	else if(m_leftStickAngleRadians >= 1.963 && m_leftStickAngleRadians < 2.749){ //112.5 -> 157.5
		Controls::state.pressingDown = 1;
		Controls::state.pressingLeft = 1;
	}
	else if(m_leftStickAngleRadians >= 2.749 && m_leftStickAngleRadians < 3.534){ //157.5 -> 202.5
		Controls::state.pressingLeft = 1;
	}
	else if(m_leftStickAngleRadians >= 3.534 && m_leftStickAngleRadians < 4.32){ //202.5 -> 247.5
		Controls::state.pressingUp = 1;
		Controls::state.pressingLeft = 1;
	}
	else if(m_leftStickAngleRadians >= 4.32 && m_leftStickAngleRadians < 5.105){ //247.5 -> 292.5
		Controls::state.pressingUp = 1;
	}
	else if(m_leftStickAngleRadians >= 5.105 && m_leftStickAngleRadians < 5.89){ //292.5 -> 337.5
		Controls::state.pressingUp = 1;
		Controls::state.pressingRight = 1;
	}
}

void TouchControls::resetMovementControls(){
	Controls::state.pressingLeft = 0;
	Controls::state.pressingRight = 0;
	Controls::state.pressingUp = 0;
	Controls::state.pressingDown = 0;
}

void TouchControls::draw(){
	drawStickBackings();
	drawSticks();
	Canvas::setGlobalAlpha(Canvas::HUD, 1);
}

void TouchControls::drawStickBackings(){
	drawLeftStickBacking();
	drawRightStickBacking();
}

void TouchControls::drawLeftStickBacking(){
	Location leftStickBacking = getLeftStickBackingPosition();
	drawStickBacking(leftStickBacking.x, leftStickBacking.y);
}

void TouchControls::drawRightStickBacking(){
	Location rightStickBacking = getRightStickBackingPosition();
	drawStickBacking(rightStickBacking.x, rightStickBacking.y);
}

void TouchControls::drawStickBacking(int xPos, int yPos){
	Canvas::setGlobalAlpha(Canvas::HUD, 0.4);
	Canvas::setFillStyle(Canvas::HUD, 96, 96, 96);
	Canvas::setStrokeStyle(Canvas::HUD, 0, 0, 0);
	Canvas::setLineWidth(Canvas::HUD, 15);

	Canvas::beginPath(Canvas::HUD);
	Canvas::arc(Canvas::HUD, xPos, yPos, m_backingRadius);
	Canvas::stroke(Canvas::HUD);
	Canvas::fill(Canvas::HUD);
}

void TouchControls::drawSticks(){
	drawLeftStick();
	drawRightStick();
}

void TouchControls::drawLeftStick(){
	if(m_leftStickAngleRadians == 0.0){
		return;
	}
	Location leftStickBacking = getLeftStickBackingPosition();
	int xPos = leftStickBacking.x + cos(m_leftStickAngleRadians) * m_backingRadius;
	int yPos = leftStickBacking.y + sin(m_leftStickAngleRadians) * m_backingRadius;
	drawStick(xPos, yPos);
}

void TouchControls::drawRightStick(){
	if(m_rightStickAngleRadians == 0.0){
		return;
	}
	Location rightStickBacking = getRightStickBackingPosition();
	int xPos = rightStickBacking.x + cos(m_rightStickAngleRadians) * m_backingRadius;
	int yPos = rightStickBacking.y + sin(m_rightStickAngleRadians) * m_backingRadius;
	drawStick(xPos, yPos);
}

void TouchControls::drawStick(int xPos, int yPos){
	Canvas::setGlobalAlpha(Canvas::HUD, 0.7);
	Canvas::setFillStyle(Canvas::HUD, 0, 0, 0);
	Canvas::setStrokeStyle(Canvas::HUD, 0, 0, 0);
	Canvas::setLineWidth(Canvas::HUD, 15);

	Canvas::beginPath(Canvas::HUD);
	Canvas::arc(Canvas::HUD, xPos, yPos, m_stickRadius);
	Canvas::fill(Canvas::HUD);
}