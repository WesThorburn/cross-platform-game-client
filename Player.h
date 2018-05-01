#ifndef PLAYER_H
#define PLAYER_H

#include "Color.h"
#include "Location.h"
#include "Camera.h"

class Player{
public:
	Player();
	void update();
	void draw(Camera& camera);
	
private:
	static int idIncrement;
	int m_id = -1;
	Location m_location = {0, 0};
	int m_radius = 20;
	double m_spdX = 0.0, m_spdY = 0.0;
	Color m_color = {rand() % 255, rand() % 255, rand() % 255};
};

#endif