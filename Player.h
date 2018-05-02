#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include "Color.h"
#include "Location.h"
#include "Camera.h"

class Camera;

class Player{
public:
	Player();
	void update();
	void draw(Camera& camera);
	Location getLocation(){ return m_location; }
	
private:
	static int idIncrement;
	int m_id = -1;

	void updateSpeed();

protected:
	double m_spdX = 0.0, m_spdY = 0.0;
	Location m_location = {0, 0};
	int m_radius = 20;
	Color m_color = {243, 118, 118};

	void updateLocation();
};

#endif