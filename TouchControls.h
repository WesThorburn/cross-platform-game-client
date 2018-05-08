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
	double m_leftStickAngleRadians = 0.0;
	double m_rightStickAngleRadians = 0.0;

	void resetSticks();
	void updateSticks();
	void processTouchPoint(Controls::TouchPoint* touchPoint);
	void updateLeftStick(Controls::TouchPoint* touchPoint);
	void updateRightStick(Controls::TouchPoint* touchPoint);
	void drawStickBackings();
	void drawLeftStickBacking();
	void drawRightStickBacking();
	Location getLeftStickBackingPosition();
	Location getRightStickBackingPosition();
	void updateMovementControlInput();
	void updateAngleControlInput();
	void drawStickBacking(int xPos, int yPos);
	void drawSticks();
	void drawLeftStick();
	void drawRightStick();
	void drawStick(int xPos, int yPos);
};

#endif