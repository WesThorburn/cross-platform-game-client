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
	void setXYOffset(int xOffset, int yOffset);
private:
	Location m_location = {1000, 1000};
	double m_spdX = 2.5, m_spdY = 2.5;
	int m_width = 1366, m_height = 768;
	int m_xOffset = 0, m_yOffset = 0;

	void updateSpeed();
	void updateLocation();
};

#endif