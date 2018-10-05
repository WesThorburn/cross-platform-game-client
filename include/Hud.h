#ifndef HUD_H
#define HUD_H

#include <vector>
#include "HudElement.h"
#include "Camera.h"

class Hud{
public:
	Hud();

	void initializeElements();
	void update();
	void draw();
private:
	std::vector<HudElement*> m_elements = {};
};

#endif