#include <iostream>
#include <math.h>
#include "ActivePlayer.h"
#include "Controls.h"
#include "Canvas.h"
#include "Map.h"

ActivePlayer::ActivePlayer(): Player(){
	m_location = {1000, 1000};
	m_radius = 20;
	m_primaryColor = {59, 179, 229};
	m_secondaryColor = {42, 133, 172};
}

void ActivePlayer::update(){
	updateAngle();
	updateSpeed();
	updateLocation();
}

void ActivePlayer::draw(Camera& camera){
	Location relativeLocation = camera.getLocationOnScreen({m_location.x, m_location.y});
	drawBarrel(relativeLocation);
	drawBody(relativeLocation);
}

void ActivePlayer::drawBody(Location relativeLocation){
	Canvas::setFillStyle(Canvas::GAME, m_primaryColor.r, m_primaryColor.g, m_primaryColor.b);
	Canvas::setStrokeStyle(Canvas::GAME, m_secondaryColor.r, m_secondaryColor.g, m_secondaryColor.b);
	Canvas::setLineWidth(Canvas::GAME, 3);

	Canvas::beginPath(Canvas::GAME);
	Canvas::arc(Canvas::GAME, relativeLocation.x, relativeLocation.y, m_radius);
	Canvas::fill(Canvas::GAME);
	Canvas::stroke(Canvas::GAME);
}

void ActivePlayer::drawBarrel(Location relativeLocation){
	int barrelLength = m_radius * 1.5;
	double barrelTipX = relativeLocation.x + barrelLength * cos(m_angle);
	double barrelTipY = relativeLocation.y + barrelLength * sin(m_angle);
	Canvas::setLineWidth(Canvas::GAME, 16);
	Canvas::setStrokeStyle(Canvas::GAME, 144, 144, 144);
	Canvas::drawLine(Canvas::GAME, relativeLocation.x, relativeLocation.y, barrelTipX, barrelTipY);
}

void ActivePlayer::updateAngle(){
	if(Controls::state.touchEnabled){
		m_angle = Controls::state.inputAngleRadians;
	}
	else{
		m_angle = calculateAngle();
	}
}

double ActivePlayer::calculateAngle(){
	Location playerScreenPosition = m_camera->getLocationOnScreen({m_location.x, m_location.y});
	int deltaX = playerScreenPosition.x * Canvas::scaleAttributes.scaleX - Controls::state.cursorX;
	int deltaY = playerScreenPosition.y * Canvas::scaleAttributes.scaleY - Controls::state.cursorY;
	return atan2(deltaY, deltaX) + M_PI;
}

void ActivePlayer::updateSpeed(){
	resetSpeed();
	updateSpeedDueToControlInput();
}

void ActivePlayer::updateLocation(){
	if(m_location.x + m_spdX > m_radius && m_location.x + m_spdX < Map::getMaxWidth() - m_radius){
		m_location.x += m_spdX;
	}
	if(m_location.y + m_spdY > m_radius && m_location.y + m_spdY < Map::getMaxHeight() - m_radius){
		m_location.y += m_spdY;
	}
}

void ActivePlayer::resetSpeed(){
	m_spdX = 0;
	m_spdY = 0;
}

void ActivePlayer::updateSpeedDueToControlInput(){
	double speed = getMovementSpeedStrength();

	if(Controls::state.pressingLeft){
		m_spdX = -speed;
	}
	if(Controls::state.pressingRight){
		m_spdX = speed;
	}
	if(Controls::state.pressingUp){
		m_spdY = -speed;
	}
	if(Controls::state.pressingDown){
		m_spdY = speed;
	}
}

double ActivePlayer::getMovementSpeedStrength(){
	double speed = m_defaultSpeed;
	if(Controls::state.movementInputStrength == Controls::WEAK){
		return speed *= 0.3;
	}
	else if(Controls::state.movementInputStrength == Controls::MEDIUM){
		return speed *= 0.6;
	}
	return speed;
}