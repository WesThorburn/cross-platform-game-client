#include <stdlib.h>
#include <iostream>
#include "Camera.h"
#include "Canvas.h"

Camera::Camera(){}

void Camera::update(){
	updateSpeed();
	updateLocation();
	updateTrackingOffsets();
}

Location Camera::getRelativeLocation(Location rawLocation){
	return {rawLocation.x - m_location.x, rawLocation.y - m_location.y};
}

void Camera::updateSpeed(){
	if(m_trackingLocation.x < 0 || m_trackingLocation.x > 2000){
		m_spdX = -m_spdX;
	}
	if(m_trackingLocation.y < 0 || m_trackingLocation.y > 2000){
		m_spdY = -m_spdY;
	}
}

void Camera::updateLocation(){
	m_trackingLocation.x += m_spdX;
	m_trackingLocation.y += m_spdY;

	m_location.x = m_trackingLocation.x - m_trackingXOffset;
	m_location.y = m_trackingLocation.y - m_trackingYOffset;
}

void Camera::updateTrackingOffsets(){
	m_trackingXOffset = Canvas::scaleAttributes.scaledWidth / 2;
	m_trackingYOffset = Canvas::scaleAttributes.scaledHeight / 2;
}