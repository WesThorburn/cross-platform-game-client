#include <stdlib.h>
#include <iostream>
#include "Camera.h"

Camera::Camera(){
}

void Camera::update(){
	updateSpeed();
	updateLocation();
}

Location Camera::getRelativeLocation(Location rawLocation){
	return {rawLocation.x - m_location.x, rawLocation.y - m_location.y};
}

void Camera::setXYOffset(int xOffset, int yOffset){
	m_xOffset = xOffset;
	m_yOffset = yOffset;
}

void Camera::updateSpeed(){
	if(m_location.x < -m_width/2 || m_location.x > 2000 - m_width/2){
		m_spdX = -m_spdX;
	}
	if(m_location.y < -m_height/2 || m_location.y > 2000 - m_height/2){
		m_spdY = -m_spdY;
	}
}

void Camera::updateLocation(){
	m_location.x += m_spdX;
	m_location.y += m_spdY;
}
