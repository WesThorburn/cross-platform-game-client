#ifndef HUD_ELEMENT_H
#define HUD_ELEMENT_H

#include <string>

class HudElement{
public:
	enum Type{ DEBUG_VARIABLES, TOUCH_CONTROLS };
	enum HoriztonalPosition{ H_LEFT, H_CENTER, H_RIGHT };
	enum VerticalPosition{ V_TOP, V_CENTER, V_BOTTOM };

	HudElement(Type type){
		setMemberVariables(type);
	}

	void setMemberVariables(Type type){
		switch(type){
			case DEBUG_VARIABLES:
				m_horizontalPosition = H_LEFT;
				m_verticalPosition = V_TOP;
				break;
			case TOUCH_CONTROLS:
				m_verticalPosition = V_BOTTOM;
				break;
		}
	}

	virtual void update() =0;
	virtual void draw() =0;
private:
	int m_width = 0, m_height = 0;
	bool m_visible = false;
	HoriztonalPosition m_horizontalPosition = H_CENTER;
	VerticalPosition m_verticalPosition = V_CENTER;
};

#endif