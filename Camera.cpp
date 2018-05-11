#include <stdlib.h>
#include <iostream>
#include "Camera.h"
#include "Canvas.h"

Camera::Camera(){}

void Camera::update(){
	updateLocation();
	updateTrackingOffsets();
}

Location Camera::getLocationOnScreen(Location rawLocation){
	return {rawLocation.x - m_location.x, rawLocation.y - m_location.y};
}

bool Camera::isVisible(Location location){
	if(location.x < 0 || location.y < 0){
		return false;
	}
	else if(location.x > m_width || location.y > m_height){
		return false;
	}
	return true;
}

void Camera::updateLocation(){
	m_location.x = m_trackingPlayer->getLocation().x - m_trackingXOffset;
	m_location.y = m_trackingPlayer->getLocation().y - m_trackingYOffset;
}

void Camera::updateTrackingOffsets(){
	m_trackingXOffset = Canvas::scaleAttributes.scaledWidth / 2;
	m_trackingYOffset = Canvas::scaleAttributes.scaledHeight / 2;
}