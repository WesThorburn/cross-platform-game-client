#ifndef DEBUG_VARIABLES_H
#define DEBUG_VARIABLES_H

#include "HudElement.h"

class DebugVariables: public HudElement{
public:
	DebugVariables();

	void update();
	void draw();
};

#endif