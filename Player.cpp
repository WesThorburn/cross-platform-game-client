#include <iostream>
#include "Player.h"
#include "Canvas.h"
#include "Browser.h" //Temporary until non-browser size x/y position limits are set

int Player::idIncrement = 0;

Player::Player(){
	m_id = idIncrement;
	++idIncrement;
	m_x = rand() % Browser::getWidth();
	m_y = rand() % Browser::getHeight();
	m_spdX = (rand() % 14) - 7;
	m_spdY = (rand() % 14) - 7;
}

void Player::update(){
	m_x += m_spdX;
	m_y += m_spdY;

	if(m_x < 0 || m_x > Browser::getWidth()){
		m_spdX = -m_spdX;
	}
	if(m_y < 0 || m_y > Browser::getHeight()){
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