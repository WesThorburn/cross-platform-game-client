#include <iostream>
#include "Player.h"
#include "Canvas.h"

int Player::idIncrement = 0;

Player::Player(){
	m_id = idIncrement;
	++idIncrement;
	m_location = {rand() % 1900 + m_radius, rand() % 1900 + m_radius};
	m_spdX = (rand() % 5) + 1;
	m_spdY = (rand() % 5) + 1;
}

void Player::update(){
	updateSpeed();
	updateLocation();
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

void Player::updateSpeed(){
	if(m_location.x < m_radius || m_location.x > 2000 - m_radius){
		m_spdX = -m_spdX;
	}
	if(m_location.y < m_radius || m_location.y > 2000 - m_radius){
		m_spdY = -m_spdY;
	}
}

void Player::updateLocation(){
	m_location.x += m_spdX;
	m_location.y += m_spdY;
}