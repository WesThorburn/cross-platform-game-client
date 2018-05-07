#ifndef TOUCH_CONTROLS_H
#define TOUCH_CONTROLS_H

#include "HudElement.h"

class TouchControls: public HudElement{
public:
	TouchControls();

	void update();
	void draw();
private:
	int m_backingRadius = 60;
	int m_stickRadius = 10;

	void drawLeftStick();
	void drawRightStick();
};

#endif