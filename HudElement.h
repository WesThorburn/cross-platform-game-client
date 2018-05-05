#ifndef HUD_ELEMENT_H
#define HUD_ELEMENT_H

#include <string>

class HudElement{
public:
	enum HoriztonalPosition{ H_LEFT, H_CENTER, H_RIGHT };
	enum VerticalPosition{ V_TOP, V_CENTER, V_BOTTOM };

	HudElement(std::string name, HoriztonalPosition hPos, VerticalPosition vPos, int width, int height){
		m_name = name;
		m_horizontalPosition = hPos;
		m_verticalPosition = vPos;
		m_width = width;
		m_height = height;
	}

	virtual void update() =0;
	virtual void draw() =0;
private:
	std::string m_name = "";
	int m_width = 0, m_height = 0;
	bool m_visible = false;
	HoriztonalPosition m_horizontalPosition = H_CENTER;
	VerticalPosition m_verticalPosition = V_CENTER;
};

#endif