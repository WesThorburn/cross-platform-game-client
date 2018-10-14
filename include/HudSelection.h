#ifndef HUDSELECTION_H
#define HUDSELECTION_H

#include "HudElement.h"
#include "HudBox.h"

class HudSelection : public HudElement{
public:
	HudSelection();

	void update();
	void click();
	void draw();
	void updateVisibility(GameMode gameMode);

private:
	int m_numHudBoxes;
	std::vector<HudBox*> m_hudBoxes;

	void initializeHudBoxes();
	void updateHudBoxesVisibility(GameMode gameMode);
	void setSelected(int hudBoxId);
};

#endif