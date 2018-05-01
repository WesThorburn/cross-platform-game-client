#ifndef CAMERA_H
#define CAMERA_H

#include "Location.h"

class Camera{
public:
	Camera();
	void update();
	int getWidth(){ return m_width; }
	int getHeight(){ return m_height; }
	Location getRelativeLocation(Location rawLocation);
private:
	Location m_location = {0, 0};
	Location m_trackingLocation = {1000, 1000};
	double m_spdX = 1.5, m_spdY = 1.5;
	int m_width = 1366, m_height = 768;
	int m_trackingXOffset = 0, m_trackingYOffset = 0;

	void updateSpeed();
	void updateLocation();
	void updateTrackingOffsets();
};

#endif