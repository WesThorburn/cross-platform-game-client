#ifndef PLAYER_H
#define PLAYER_H

#include "Color.h"

class Player{
public:
	Player();
	void update();
	void draw();
	
private:
	static int idIncrement;
	int m_id = -1, m_x = 0, m_y = 0, m_radius = 20;
	double m_spdX = 0.0, m_spdY = 0.0;
	Color m_color = {rand() % 255, rand() % 255, rand() % 255};
};

#endif