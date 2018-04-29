#include <iostream>
#include "Player.h"
#include "Canvas.h"

int Player::idIncrement = 0;

Player::Player(){
	m_id = idIncrement;
	++idIncrement;
	m_x = rand() % 2000 + m_radius;
	m_y = rand() % 2000 + m_radius;
	m_spdX = (rand() % 14) - 7;
	m_spdY = (rand() % 14) - 7;
}

void Player::update(){
	m_x += m_spdX;
	m_y += m_spdY;

	if(m_x < m_radius || m_x > 2000 - m_radius){
		m_spdX = -m_spdX;
	}
	if(m_y < m_radius || m_y > 2000 - m_radius){
		m_spdY = -m_spdY;
	}
}

void Player::draw(){
	Canvas::setFillStyle(Canvas::GAME, m_color.r, m_color.g, m_color.b);
	Canvas::setStrokeStyle(Canvas::GAME, 114, 114, 114);
	Canvas::setLineWidth(Canvas::GAME, 3);
	Canvas::beginPath(Canvas::GAME);
	Canvas::arc(Canvas::GAME, m_x, m_y, m_radius);
	Canvas::fill(Canvas::GAME);
	Canvas::stroke(Canvas::GAME);
}