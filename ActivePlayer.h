#ifndef ACTIVE_PLAYER_H
#define ACTIVE_PLAYER_H

#include "Player.h"
#include "Camera.h"

class ActivePlayer: public Player{
public:
	ActivePlayer();
	void update();
	void draw(Camera& camera);
private:
	double m_defaultSpeed = 3.5;

	void updateSpeed();
	void updateLocation();
	void resetSpeed();
	void updateSpeedDueToControlInput();
};

#endif