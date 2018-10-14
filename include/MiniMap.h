#ifndef MINIMAP_H
#define MINIMAP_H

#include "HudElement.h"
#include "Location.h"
#include "UserPlayer.h"

class MiniMap : public HudElement{
public:
	MiniMap();

	void update();
	void draw();
	void setUserPlayer(UserPlayer* UserPlayer);

private:
	UserPlayer* m_userPlayer;
	Location m_playerIconLocation = {0, 0};
	int m_playerIconRadius = 2;

	void updatePlayerIconLocation();
	void drawBacking();
	void drawUserPlayerIcon();
};

#endif