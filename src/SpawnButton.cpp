#include "SpawnButton.h"
#include "Connection.h"

SpawnButton::SpawnButton(): HudElement(){
	m_text = "Enter Game";
	m_hoverable = 1;
	setWidth(200);
	setHeight(40);
	m_gameModeVisibility = {MODE_SPECTATING};
}

void SpawnButton::click(){
	std::cout << "fired click" << std::endl;
	Connection::send("s");
	HudElement::click();
}

void SpawnButton::draw(){
	drawBacking();
	drawText();
}

void SpawnButton::drawBacking(){
	Canvas::setLineWidth(Canvas::HUD, 5);
	Canvas::setStrokeStyle(Canvas::HUD, 0, 0, 0);

	if(m_beingHoveredOn){
		Canvas::setFillStyle(Canvas::HUD, 38, 193, 27);
	}
	else{
		Canvas::setFillStyle(Canvas::HUD, 100, 255, 90);
	}
	
	Canvas::drawFilledCurvedRectangle(
		Canvas::HUD,
		m_screenLocation.x,
		m_screenLocation.y,
		getWidth(), 
		getHeight(),
		4
	);
}

void SpawnButton::drawText(){
	Canvas::setFont(Canvas::HUD, 28, "bolder");
	Canvas::setLineWidth(Canvas::HUD, 3);
	Canvas::setTextBaseline(Canvas::HUD, "middle");
	Canvas::setTextAlign(Canvas::HUD, "center");

	Location textLocation = {
		m_screenLocation.x + (getWidth() / 2),
		m_screenLocation.y + (getHeight() / 2)
	};

	Canvas::setStrokeStyle(Canvas::HUD, 0, 0, 0);
	Canvas::strokeText(Canvas::HUD, m_text, textLocation.x, textLocation.y);

	Canvas::setFillStyle(Canvas::HUD, 255, 255, 255);
	Canvas::fillText(Canvas::HUD, m_text, textLocation.x, textLocation.y);
}