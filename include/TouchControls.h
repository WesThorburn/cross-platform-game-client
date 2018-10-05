#ifndef TOUCH_CONTROLS_H
#define TOUCH_CONTROLS_H

#include "HudElement.h"
#include "Location.h"
#include "Controls.h"

class TouchControls: public HudElement{
public:
	TouchControls();

	void update();
	void draw();

	double getLeftStickAngleRadians(){ return m_leftStickAngleRadians; }
	double getRightStickAngleRadians(){ return m_rightStickAngleRadians; }
private:
	int m_backingRadius = 100;
	int m_stickRadius = 50;
	int m_leftStickInputDistance = 0;
	int m_rightStickInputDistance = 0;
	double m_leftStickAngleRadians = 0.0;
	double m_rightStickAngleRadians = 0.0;

	void resetSticks();
	void updateSticks();
	void processTouchPoint(Controls::TouchPoint* touchPoint);
	void updateLeftStick(Controls::TouchPoint* touchPoint);
	void updateRightStick(Controls::TouchPoint* touchPoint);
	double getAngleRadians(Location backingLocation, Location touchLocation);
	int getInputDistance(Location backingLocation, Location touchLocation);
	void updateMovementInputStrength();
	void updateMovementControlInput();
	void updateAngleControlInput();
	void drawStickBackings();
	void drawLeftStickBacking();
	void drawRightStickBacking();
	Location getLeftStickBackingPosition();
	Location getRightStickBackingPosition();
	void drawStickBacking(int xPos, int yPos);
	void drawSticks();
	void drawLeftStick();
	void drawRightStick();
	void drawStick(int xPos, int yPos);
};

#endif