#include <iostream>
#include <math.h>
#include "UserPlayer.h"
#include "Controls.h"
#include "Canvas.h"
#include "Map.h"

UserPlayer::UserPlayer(): Player(){
	m_location = {1000, 1000};
	m_radius = 20;
	m_primaryColor = {59, 179, 229};
	m_secondaryColor = {42, 133, 172};
}

void UserPlayer::update(){
	updateAngle();
	updateSpeed();
	updateLocation();
	updateScreenPosition();
}

void UserPlayer::applyInitUpdate(std::vector<std::string> data){
	m_location.x = std::stoi(data[3]);
	m_location.y = std::stoi(data[4]);
	m_angle = std::stoi(data[6]);
}

void UserPlayer::draw(Camera& camera){
	Location relativeLocation = camera.getLocationOnScreen({m_location.x, m_location.y});
	drawBarrel(relativeLocation);
	drawBody(relativeLocation);
}

void UserPlayer::drawBody(Location relativeLocation){
	Canvas::setFillStyle(Canvas::GAME, m_primaryColor.r, m_primaryColor.g, m_primaryColor.b);
	Canvas::setStrokeStyle(Canvas::GAME, m_secondaryColor.r, m_secondaryColor.g, m_secondaryColor.b);
	Canvas::setLineWidth(Canvas::GAME, 3);

	Canvas::beginPath(Canvas::GAME);
	Canvas::arc(Canvas::GAME, relativeLocation.x, relativeLocation.y, m_radius);
	Canvas::fill(Canvas::GAME);
	Canvas::stroke(Canvas::GAME);
}

void UserPlayer::drawBarrel(Location relativeLocation){
	int barrelLength = m_radius * 1.5;
	double barrelTipX = relativeLocation.x + barrelLength * cos(m_angle);
	double barrelTipY = relativeLocation.y + barrelLength * sin(m_angle);
	Canvas::setLineWidth(Canvas::GAME, 16);
	Canvas::setStrokeStyle(Canvas::GAME, 144, 144, 144);
	Canvas::drawLine(Canvas::GAME, relativeLocation.x, relativeLocation.y, barrelTipX, barrelTipY);
}

void UserPlayer::updateAngle(){
	if(Controls::inputState.touchEnabled){
		m_angle = Controls::inputState.inputAngleRadians;
	}
	else{
		m_angle = calculateAngle();
	}
}

double UserPlayer::calculateAngle(){
	int deltaX = m_screenPosition.x * Canvas::scaleAttributes.scaleX - Controls::inputState.oldCursorLocation.x;
	int deltaY = m_screenPosition.y * Canvas::scaleAttributes.scaleY - Controls::inputState.oldCursorLocation.y;
	return atan2(deltaY, deltaX) + M_PI;
}

void UserPlayer::updateSpeed(){
	resetSpeed();
	updateSpeedDueToControlInput();
}

void UserPlayer::updateLocation(){
	double clientSpeedX = getClientSpeed(m_spdX);
	double clientSpeedY = getClientSpeed(m_spdY);

	if(m_location.x + m_spdX > m_radius && m_location.x + m_spdX < Map::getMaxWidth() - m_radius){
		m_location.x += clientSpeedX;
	}
	if(m_location.y + m_spdY > m_radius && m_location.y + m_spdY < Map::getMaxHeight() - m_radius){
		m_location.y += clientSpeedY;
	}
}

double UserPlayer::getClientSpeed(double serverSpeed){
	return serverSpeed / 2.4;
}

void UserPlayer::updateScreenPosition(){
	m_screenPosition = m_camera->getLocationOnScreen(m_location);
}

void UserPlayer::resetSpeed(){
	m_spdX = 0;
	m_spdY = 0;
}

void UserPlayer::updateSpeedDueToControlInput(){
	double speed = getMovementSpeedStrength();

	if(Controls::inputState.pressingLeft){
		m_spdX = -speed;
	}
	if(Controls::inputState.pressingRight){
		m_spdX = speed;
	}
	if(Controls::inputState.pressingUp){
		m_spdY = -speed;
	}
	if(Controls::inputState.pressingDown){
		m_spdY = speed;
	}
}

double UserPlayer::getMovementSpeedStrength(){
	double speed = m_defaultSpeed;
	if(Controls::inputState.movementInputStrength == Controls::WEAK){
		return speed *= 0.3;
	}
	else if(Controls::inputState.movementInputStrength == Controls::MEDIUM){
		return speed *= 0.6;
	}
	return speed;
}