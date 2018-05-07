#ifndef TOUCH_CONTROLS_H
#define TOUCH_CONTROLS_H

#include "HudElement.h"

class TouchControls: public HudElement{
public:
	TouchControls();

	void update();
	void draw();
private:
	int m_backingRadius = 90;
	int m_stickRadius = 50;

	void drawLeftStick();
	void drawRightStick();
};

#endif