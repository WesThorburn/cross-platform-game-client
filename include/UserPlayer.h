#ifndef ACTIVE_PLAYER_H
#define ACTIVE_PLAYER_H

#include <math.h>
#include "Player.h"
#include "Camera.h"

class UserPlayer: public Player{
public:
	UserPlayer();
	int getRadius(){ return m_radius; }
	void update();
	void draw(Camera& camera);
	void setCamera(Camera* camera){ m_camera = camera; }
	Location getScreenPosition(){ return m_screenPosition; }
	int getAngleDegrees(){ return m_angle * 180/M_PI; }

	void applyInitUpdate(std::vector<std::string> data);
private:
	double m_defaultSpeed = 3.5;
	Location m_screenPosition = {0, 0};
	double m_angle = 0.0;

	Camera* m_camera;

	void drawBody(Location relativeLocation);
	void drawBarrel(Location relativeLocation);
	void updateAngle();
	double calculateAngle();
	void updateSpeed();
	void updateLocation();
	double getClientSpeed(double serverSpeed);
	void updateScreenPosition();
	void resetSpeed();
	void updateSpeedDueToControlInput();
	double getMovementSpeedStrength();
};

#endif