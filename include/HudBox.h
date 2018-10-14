#ifndef HUDBOX_H
#define HUDBOX_H

#include "HudElement.h"
#include "Controls.h"

class HudBox : public HudElement{
public:
	HudBox();

	void update();
	void click();
	void draw();

	int getId(){ return m_id; }
	void setSize(int size);
	void setXMargin(int xMargin){ m_xMargin = xMargin; }
	void setYMargin(int yMargin){ m_yMargin = yMargin; }
private:
	static int id;
	int m_id;
	int m_fontSize = 11;
	std::string m_text = "";

	Location m_textOffset = {4, 8};

	bool isSelected(){ return Controls::hudState.selectedHudBox == m_id; }
	void drawBacking();
	void drawNumber();
	void drawImage();
};

#endif