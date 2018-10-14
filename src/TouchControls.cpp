#include <math.h>
#include <iostream>
#include "TouchControls.h"

TouchControls::TouchControls(): HudElement(){
	m_verticalPosition = V_BOTTOM;
}

void TouchControls::update(){
	if(Controls::inputState.touchEnabled){
		resetSticks();
		updateSticks();
	}
}

void TouchControls::resetSticks(){
	m_leftStickAngleRadians = 0.0;
	m_rightStickAngleRadians = 0.0;
}

void TouchControls::updateSticks(){
	for(int i = 0; i < Controls::inputState.touchPoints.size(); i++){
		Controls::TouchPoint* touchPoint = &Controls::inputState.touchPoints.at(i);
		processTouchPoint(touchPoint);
	}
}

void TouchControls::processTouchPoint(Controls::TouchPoint* touchPoint){
	if(touchPoint->startLocation.x <= Canvas::scaleAttributes.scaledWidth * Canvas::scaleAttributes.scaleX / 2){
		updateLeftStick(touchPoint);
	}
	else if(touchPoint->startLocation.x > Canvas::scaleAttributes.scaledWidth * Canvas::scaleAttributes.scaleX / 2){
		updateRightStick(touchPoint);
	}
}

void TouchControls::updateLeftStick(Controls::TouchPoint* touchPoint){
	m_leftStickAngleRadians = getAngleRadians(getLeftStickBackingPosition(), touchPoint->currentLocation);
	m_leftStickInputDistance = getInputDistance(getLeftStickBackingPosition(), touchPoint->currentLocation);
	updateMovementInputStrength();
	updateMovementControlInput();
}

void TouchControls::updateRightStick(Controls::TouchPoint* touchPoint){
	m_rightStickAngleRadians = getAngleRadians(getRightStickBackingPosition(), touchPoint->currentLocation);
	m_rightStickInputDistance = getInputDistance(getRightStickBackingPosition(), touchPoint->currentLocation);
	updateAngleControlInput();
}

double TouchControls::getAngleRadians(Location backingLocation, Location touchLocation){
	int deltaX = backingLocation.x - (touchLocation.x / Canvas::scaleAttributes.scaleX);
	int deltaY = backingLocation.y - (touchLocation.y / Canvas::scaleAttributes.scaleY);
	return atan2(deltaY, deltaX) + M_PI;
}

int TouchControls::getInputDistance(Location backingLocation, Location touchLocation){
	int deltaX = backingLocation.x - (touchLocation.x / Canvas::scaleAttributes.scaleX);
	int deltaY = backingLocation.y - (touchLocation.y / Canvas::scaleAttributes.scaleY);
	int distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	if(distance > m_backingRadius){
		distance = m_backingRadius;
	}
	return distance;
}

void TouchControls::updateMovementInputStrength(){
	if(m_leftStickInputDistance < m_backingRadius * 0.4){
		Controls::inputState.movementInputStrength = Controls::WEAK;
	}
	else if(m_leftStickInputDistance < m_backingRadius * 0.8){
		Controls::inputState.movementInputStrength = Controls::MEDIUM;
	}
	else{
		Controls::inputState.movementInputStrength = Controls::STRONG;
	}
}

void TouchControls::updateMovementControlInput(){
	Controls::resetMovementInputs();
	if(m_leftStickAngleRadians >= 5.89 || m_leftStickAngleRadians < 0.393){ //337.5 -> 22.5
		Controls::inputState.pressingRight = 1;
	}
	else if(m_leftStickAngleRadians >= 0.393 && m_leftStickAngleRadians < 1.178){ //22.5 -> 67.5
		Controls::inputState.pressingRight = 1;
		Controls::inputState.pressingDown = 1;
	}
	else if(m_leftStickAngleRadians >= 1.178 && m_leftStickAngleRadians < 1.963){ //67.5 -> 112.5
		Controls::inputState.pressingDown = 1;
	}
	else if(m_leftStickAngleRadians >= 1.963 && m_leftStickAngleRadians < 2.749){ //112.5 -> 157.5
		Controls::inputState.pressingDown = 1;
		Controls::inputState.pressingLeft = 1;
	}
	else if(m_leftStickAngleRadians >= 2.749 && m_leftStickAngleRadians < 3.534){ //157.5 -> 202.5
		Controls::inputState.pressingLeft = 1;
	}
	else if(m_leftStickAngleRadians >= 3.534 && m_leftStickAngleRadians < 4.32){ //202.5 -> 247.5
		Controls::inputState.pressingUp = 1;
		Controls::inputState.pressingLeft = 1;
	}
	else if(m_leftStickAngleRadians >= 4.32 && m_leftStickAngleRadians < 5.105){ //247.5 -> 292.5
		Controls::inputState.pressingUp = 1;
	}
	else if(m_leftStickAngleRadians >= 5.105 && m_leftStickAngleRadians < 5.89){ //292.5 -> 337.5
		Controls::inputState.pressingUp = 1;
		Controls::inputState.pressingRight = 1;
	}
}

void TouchControls::updateAngleControlInput(){
	Controls::inputState.inputAngleRadians = m_rightStickAngleRadians;
}

void TouchControls::draw(){
	if(Controls::inputState.touchEnabled){
		drawStickBackings();
		drawSticks();
		Canvas::setGlobalAlpha(Canvas::HUD, 1);
	}
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

Location TouchControls::getLeftStickBackingPosition(){
	return {
		Canvas::scaleAttributes.scaledWidth / 6, 
		(Canvas::scaleAttributes.scaledHeight / 6) * 5
	};
}

Location TouchControls::getRightStickBackingPosition(){
	return {
		(Canvas::scaleAttributes.scaledWidth / 6) * 5, 
		(Canvas::scaleAttributes.scaledHeight / 6) * 5
	};
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
	int xPos = leftStickBacking.x + cos(m_leftStickAngleRadians) * m_leftStickInputDistance;
	int yPos = leftStickBacking.y + sin(m_leftStickAngleRadians) * m_leftStickInputDistance;
	drawStick(xPos, yPos);
}

void TouchControls::drawRightStick(){
	if(m_rightStickAngleRadians == 0.0){
		return;
	}
	Location rightStickBacking = getRightStickBackingPosition();
	int xPos = rightStickBacking.x + cos(m_rightStickAngleRadians) * m_rightStickInputDistance;
	int yPos = rightStickBacking.y + sin(m_rightStickAngleRadians) * m_rightStickInputDistance;
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