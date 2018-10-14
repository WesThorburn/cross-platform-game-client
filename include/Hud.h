#ifndef HUD_H
#define HUD_H

#include <vector>
#include "Location.h"
#include "HudElement.h"
#include "Camera.h"
#include "GameMode.h"
#include "HudSelection.h"
#include "UserPlayer.h"

class Hud{
public:
	Hud();

	void initialize(UserPlayer* userPlayer);
	void update();
	void draw();
	void setMode(GameMode mode);

private:
	std::vector<HudElement*> m_elements = {};
	GameMode m_mode = MODE_SPECTATING;
	HudSelection* m_hudSelection;
	UserPlayer* m_userPlayer;

	void setHudCursor();
	void updateElementsVisibility();
};

#endif