#include <iostream>
#include "ActivePlayer.h"
#include "Controls.h"
#include "Canvas.h"

ActivePlayer::ActivePlayer(): Player(){
	m_location = {1000, 1000};
	m_radius = 20;
	m_color = {59, 179, 229};
}

void ActivePlayer::update(){
	updateSpeed();
	updateLocation();
}

void ActivePlayer::draw(Camera& camera){
	Canvas::setFillStyle(Canvas::GAME, m_color.r, m_color.g, m_color.b);
	Canvas::setStrokeStyle(Canvas::GAME, 42, 133, 172);
	Canvas::setLineWidth(Canvas::GAME, 3);

	Location relativeLocation = camera.getRelativeLocation({m_location.x, m_location.y});

	Canvas::beginPath(Canvas::GAME);
	Canvas::arc(Canvas::GAME, relativeLocation.x, relativeLocation.y, m_radius);
	Canvas::fill(Canvas::GAME);
	Canvas::stroke(Canvas::GAME);
}

void ActivePlayer::updateSpeed(){
	m_spdX = 0;
	m_spdY = 0;

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

void ActivePlayer::updateLocation(){
	if(m_location.x + m_spdX > m_radius && m_location.x + m_spdX < 2000 - m_radius){
		m_location.x += m_spdX;
	}
	if(m_location.y + m_spdY > m_radius && m_location.y + m_spdY < 2000 - m_radius){
		m_location.y += m_spdY;
	}
}