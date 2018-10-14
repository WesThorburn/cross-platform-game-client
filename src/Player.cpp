#include <iostream>
#include "Player.h"
#include "Canvas.h"
#include "Map.h"

int Player::idIncrement = 0;

Player::Player(){
	m_id = idIncrement;
	++idIncrement;
	m_location = {rand() % (Map::getMaxWidth() - 100) + m_radius, rand() % (Map::getMaxHeight() - 100) + m_radius};
	m_spdX = (rand() % 5) + 1;
	m_spdY = (rand() % 5) + 1;
}

void Player::update(){
	updateSpeed();
	updateLocation();
}

void Player::draw(Camera& camera){
	Canvas::setFillStyle(Canvas::GAME, m_primaryColor.r, m_primaryColor.g, m_primaryColor.b);
	Canvas::setStrokeStyle(Canvas::GAME, m_secondaryColor.r, m_secondaryColor.g, m_secondaryColor.b);
	Canvas::setLineWidth(Canvas::GAME, 3);

	Location relativeLocation = camera.getLocationOnScreen({m_location.x, m_location.y});

	Canvas::beginPath(Canvas::GAME);
	Canvas::arc(Canvas::GAME, relativeLocation.x, relativeLocation.y, m_radius);
	Canvas::fill(Canvas::GAME);
	Canvas::stroke(Canvas::GAME);
}

void Player::applyPrimaryUpdate(std::vector<std::string> data){
	m_location.x = std::stoi(data[2]);
	m_location.y = std::stoi(data[3]);
	m_spdX = std::stoi(data[4]) / 2.4;
	m_spdY = std::stoi(data[5]) / 2.4;
	m_angle = std::stoi(data[6]);
}

void Player::updateSpeed(){
	if(m_location.x < m_radius || m_location.x > Map::getMaxWidth() - m_radius){
		m_spdX = -m_spdX;
	}
	if(m_location.y < m_radius || m_location.y > Map::getMaxHeight() - m_radius){
		m_spdY = -m_spdY;
	}
}

void Player::updateLocation(){
	m_location.x += m_spdX;
	m_location.y += m_spdY;
}