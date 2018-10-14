#include "HudBox.h"

int HudBox::id = 0;

HudBox::HudBox(){
	m_id = ++HudBox::id;
	m_hoverable = 1;
	m_padding = 3;
	m_gameModeVisibility = {MODE_IN_GAME};
	m_verticalPosition = V_BOTTOM;
	m_text = std::to_string(m_id) + ".";
}

void HudBox::update(){
	HudElement::update();
}

void HudBox::click(){
	Controls::hudState.selectedHudBox = m_id;
}

void HudBox::draw(){
	drawBacking();
	drawNumber();
}

void HudBox::drawBacking(){
	Canvas::setGlobalAlpha(Canvas::HUD, 0.7);
	Canvas::setLineWidth(Canvas::HUD, 1);
	Canvas::setStrokeStyle(Canvas::HUD, 130, 130, 130);
	if(isSelected() || m_beingHoveredOn){
		Canvas::setFillStyle(Canvas::HUD, 255, 248, 124);
	}
	else{
		Canvas::setFillStyle(Canvas::HUD, 130, 130, 130);
	}

	Canvas::drawFilledCurvedRectangle(Canvas::HUD,
		m_screenLocation.x,
		m_screenLocation.y,
		getWidth(),
		getHeight(),
		4
	);
}

void HudBox::drawNumber(){
	Canvas::setGlobalAlpha(Canvas::HUD, 0.9);
	Canvas::setFont(Canvas::HUD, m_fontSize, "bolder");
	Canvas::setLineWidth(Canvas::HUD, 2);

	Location textLocation = {
		m_screenLocation.x + m_textOffset.x,
		m_screenLocation.y + m_textOffset.y
	};

	Canvas::setStrokeStyle(Canvas::HUD, 0, 0, 0);
	Canvas::strokeText(Canvas::HUD, m_text, textLocation.x, textLocation.y);

	Canvas::setFillStyle(Canvas::HUD, 255, 255, 255);
	Canvas::fillText(Canvas::HUD, m_text, textLocation.x, textLocation.y);
}

void HudBox::drawImage(){

}

void HudBox::setSize(int size){
	setWidth(size);
	setHeight(size);
}