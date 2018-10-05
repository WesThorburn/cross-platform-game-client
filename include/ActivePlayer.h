#ifndef ACTIVE_PLAYER_H
#define ACTIVE_PLAYER_H

#include "Player.h"
#include "Camera.h"

class ActivePlayer: public Player{
public:
	ActivePlayer();
	void update();
	void draw(Camera& camera);
	void setCamera(Camera* camera){ m_camera = camera; }
private:
	double m_defaultSpeed = 3.5;
	double m_angle = 0.0;

	Camera* m_camera;

	void drawBody(Location relativeLocation);
	void drawBarrel(Location relativeLocation);
	void updateAngle();
	double calculateAngle();
	void updateSpeed();
	void updateLocation();
	void resetSpeed();
	void updateSpeedDueToControlInput();
	double getMovementSpeedStrength();
};

#endif