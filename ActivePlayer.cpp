#include <iostream>
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
	updateSpeed();
	updateLocation();
}

void ActivePlayer::draw(Camera& camera){
	Canvas::setFillStyle(Canvas::GAME, m_primaryColor.r, m_primaryColor.g, m_primaryColor.b);
	Canvas::setStrokeStyle(Canvas::GAME, m_secondaryColor.r, m_secondaryColor.g, m_secondaryColor.b);
	Canvas::setLineWidth(Canvas::GAME, 3);

	Location relativeLocation = camera.getRelativeLocation({m_location.x, m_location.y});

	Canvas::beginPath(Canvas::GAME);
	Canvas::arc(Canvas::GAME, relativeLocation.x, relativeLocation.y, m_radius);
	Canvas::fill(Canvas::GAME);
	Canvas::stroke(Canvas::GAME);
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
	if(Controls::state.pressingLeft){
		m_spdX = -m_defaultSpeed;
	}
	if(Controls::state.pressingRight){
		m_spdX = m_defaultSpeed;
	}
	if(Controls::state.pressingUp){
		m_spdY = -m_defaultSpeed;
	}
	if(Controls::state.pressingDown){
		m_spdY = m_defaultSpeed;
	}
}