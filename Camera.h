#ifndef CAMERA_H
#define CAMERA_H

#include "Location.h"
#include "Player.h"

class Player;

class Camera{
public:
	Camera();
	void update();
	void setTrackingPlayer(Player* trackingPlayer){ m_trackingPlayer = trackingPlayer; }
	int getWidth(){ return m_width; }
	int getHeight(){ return m_height; }
	Location getRelativeLocation(Location rawLocation);
private:
	Location m_location = {0, 0};
	Player* m_trackingPlayer;
	int m_width = 1366, m_height = 768;
	int m_trackingXOffset = 0, m_trackingYOffset = 0;

	void updateLocation();
	void updateTrackingOffsets();
};

#endif