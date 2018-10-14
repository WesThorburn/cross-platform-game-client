#include "HudElement.h"
#include "Controls.h"

void HudElement::update(){
	if(!m_visible) return;

	updateScreenLocation();
	checkForHover();
	checkForClick();
}

void HudElement::updateScreenLocation(){
	int xLocation = 0, yLocation = 0;

	switch(m_horizontalPosition){
		case H_LEFT:
			xLocation = 0;
			break;
		case H_CENTER:
			xLocation = (Canvas::scaleAttributes.scaledWidth / 2) - (m_width / 2);
			break;
		case H_RIGHT:
			xLocation = Canvas::scaleAttributes.scaledWidth - m_width;
			break;
	}

	switch(m_verticalPosition){
		case V_TOP:
			yLocation = 0;
			break;
		case V_CENTER:
			yLocation = (Canvas::scaleAttributes.scaledHeight / 2) - (m_height / 2);
			break;
		case V_BOTTOM:
			yLocation = Canvas::scaleAttributes.scaledHeight - m_height;
			break;
	}

	m_screenLocation = {xLocation + m_xMargin, yLocation + m_yMargin};
}

void HudElement::checkForHover(){
	if(!m_hoverable) return;
	
	m_beingHoveredOn = elementContains(Controls::hudState.hudCursorLocation);

	if(m_beingHoveredOn){
		Controls::hudState.hoveringOnHudElement = 1;
	}
}

void HudElement::checkForClick(){
	if(!Controls::hudState.clickFired) return;
	if(!Controls::hudState.hoveringOnHudElement) return;

	if(elementContains(Controls::hudState.hudClickLocation)){
		click();
	}
}

bool HudElement::elementContains(Location location){
	if(location.x < m_screenLocation.x) return false;
	else if(location.x > m_screenLocation.x + m_width) return false;
	else if(location.y < m_screenLocation.y) return false;
	else if(location.y > m_screenLocation.y + m_height) return false;
	return true;
}

void HudElement::setHeight(int height){
	m_height = height - (2 * m_padding);
}

void HudElement::setWidth(int width){
	m_width = width - (2 * m_padding);
}

void HudElement::click(){

}

void HudElement::draw(){
	
}

void HudElement::updateVisibility(GameMode gameMode){
	for(GameMode visibleInMode : m_gameModeVisibility){
		if(visibleInMode == gameMode){
			m_visible = 1;
			return;
		}
	}
	m_visible = 0;
}