#ifndef HUD_ELEMENT_H
#define HUD_ELEMENT_H

#include <iostream>
#include <string>
#include "Canvas.h"
#include "Location.h"
#include "GameMode.h"

class HudElement{
public:
	enum HoriztonalPosition{ H_LEFT, H_CENTER, H_RIGHT };
	enum VerticalPosition{ V_TOP, V_CENTER, V_BOTTOM };

	virtual void update();
	virtual void click();
	virtual void draw();
	void hide(){ m_visible = 0; }
	void show(){ m_visible = 1; }
	int getWidth(){ return m_width; }
	int getHeight(){ return m_height; }
	bool isVisible(){ return m_visible; }
	virtual void updateVisibility(GameMode gameMode);

protected:
	HoriztonalPosition m_horizontalPosition = H_CENTER;
	VerticalPosition m_verticalPosition = V_CENTER;
	std::vector<GameMode> m_gameModeVisibility = {MODE_IN_GAME};

	bool m_visible = 0, m_hoverable = 0, m_beingHoveredOn = 0;
	int m_padding = 0, m_xMargin = 0, m_yMargin = 0;
	Location m_screenLocation;

	void updateScreenLocation();
	void checkForHover();
	void checkForClick();
	bool elementContains(Location location);
	void setHeight(int height);
	void setWidth(int width);

private:
	int m_width = 0, m_height = 0;
};

#endif