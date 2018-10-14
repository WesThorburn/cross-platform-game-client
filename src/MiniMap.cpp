#include "Map.h"
#include "MiniMap.h"

MiniMap::MiniMap(): HudElement(){
	setWidth(150);
	setHeight(150);
	m_xMargin = -10;
	m_yMargin = -10;
	m_hoverable = 0;
	m_horizontalPosition = H_RIGHT;
	m_verticalPosition = V_BOTTOM;
	m_gameModeVisibility = {MODE_IN_GAME};
}

void MiniMap::update(){
	HudElement::update();
	updatePlayerIconLocation();
}

void MiniMap::updatePlayerIconLocation(){
	double relativeXLocation = static_cast<double>(m_userPlayer->getLocation().x) / Map::getMaxWidth();
	double relativeYLocation = static_cast<double>(m_userPlayer->getLocation().y) / Map::getMaxHeight();

	Location mapLocation = { 
		static_cast<int>(relativeXLocation * getWidth()),
		static_cast<int>(relativeYLocation * getHeight())
	};

	m_playerIconLocation = {
		m_screenLocation.x + mapLocation.x,
		m_screenLocation.y + mapLocation.y
	};
}

void MiniMap::draw(){
	drawBacking();
	drawUserPlayerIcon();
}

void MiniMap::setUserPlayer(UserPlayer* userPlayer){
	m_userPlayer = userPlayer;
}

void MiniMap::drawBacking(){
	Canvas::setStrokeStyle(Canvas::HUD, 50, 50, 50);
	Canvas::setLineWidth(Canvas::HUD, 2);

	Canvas::drawCurvedRectangle(
		Canvas::HUD,
		m_screenLocation.x,
		m_screenLocation.y,
		getWidth(), 
		getHeight(),
		4
	);

	Canvas::setFillStyle(Canvas::HUD, 50, 50, 50);
	Canvas::setGlobalAlpha(Canvas::HUD, 0.3);
	Canvas::fill(Canvas::HUD);
}

void MiniMap::drawUserPlayerIcon(){
	Canvas::setLineWidth(Canvas::HUD, 2);
	Canvas::setGlobalAlpha(Canvas::HUD, 1);

	Canvas::beginPath(Canvas::HUD);
	Canvas::arc(Canvas::HUD, m_playerIconLocation.x, m_playerIconLocation.y, m_playerIconRadius);
	Canvas::stroke(Canvas::HUD);
	Canvas::fill(Canvas::HUD);
}