#include <iostream>
#include "Player.h"
#include "Canvas.h"

int Player::idIncrement = 0;

Player::Player(){
	m_id = idIncrement;
	++idIncrement;
	m_location = {rand() % 2000 + m_radius, rand() % 2000 + m_radius};
	m_spdX = (rand() % 14) - 7;
	m_spdY = (rand() % 14) - 7;
}

void Player::update(){
	/*m_location.x += m_spdX;
	m_location.y += m_spdY;*/

	if(m_location.x < m_radius || m_location.x > 2000 - m_radius){
		m_spdX = -m_spdX;
	}
	if(m_location.y < m_radius || m_location.y > 2000 - m_radius){
		m_spdY = -m_spdY;
	}
}

void Player::draw(Camera& camera){
	Canvas::setFillStyle(Canvas::GAME, m_color.r, m_color.g, m_color.b);
	Canvas::setStrokeStyle(Canvas::GAME, 114, 114, 114);
	Canvas::setLineWidth(Canvas::GAME, 3);

	Location relativeLocation = camera.getRelativeLocation({m_location.x, m_location.y});

	Canvas::beginPath(Canvas::GAME);
	Canvas::arc(Canvas::GAME, relativeLocation.x, relativeLocation.y, m_radius);
	Canvas::fill(Canvas::GAME);
	Canvas::stroke(Canvas::GAME);
}