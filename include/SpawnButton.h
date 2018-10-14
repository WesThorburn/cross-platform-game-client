#ifndef SPAWN_BUTTON_H
#define SPAWN_BUTTON_H

#include "HudElement.h"

class SpawnButton: public HudElement{
public:
	SpawnButton();

	void setText(std::string text){ m_text = text; }
	void click();
	void draw();

private:
	std::string m_text;

	void drawBacking();
	void drawText();
};

#endif