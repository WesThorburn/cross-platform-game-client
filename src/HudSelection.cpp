#include "HudSelection.h"

HudSelection::HudSelection(){
	setWidth(350);
	setHeight(70);
	m_numHudBoxes = 5;
	m_yMargin = -5;
	m_verticalPosition = V_BOTTOM;
	m_gameModeVisibility = {MODE_IN_GAME};
	initializeHudBoxes();
}

void HudSelection::initializeHudBoxes(){
	int boxSize = getHeight();
	for(int i = 0; i < m_numHudBoxes; ++i){
		HudBox* hudBox = new HudBox();

		int startingX = -getWidth()/2; //Left most box
		int xMargin = startingX + (boxSize * i) + (boxSize / 2);
		hudBox->setSize(boxSize);
		hudBox->setXMargin(xMargin);
		hudBox->setYMargin(m_yMargin);

		m_hudBoxes.push_back(hudBox);
	}
}

void HudSelection::update(){
	std::vector<HudBox*>::iterator it;
	for(it = m_hudBoxes.begin(); it != m_hudBoxes.end(); it++){
		(*it)->update();
	}
}

void HudSelection::click(){
	std::cout << "clicked HudSelection" << std::endl;
}

void HudSelection::draw(){
	std::vector<HudBox*>::iterator it;
	for(it = m_hudBoxes.begin(); it != m_hudBoxes.end(); it++){
		if((*it)->isVisible())
			(*it)->draw();
	}
}

void HudSelection::updateVisibility(GameMode gameMode){
	HudElement::updateVisibility(gameMode);
	updateHudBoxesVisibility(gameMode);
}

void HudSelection::updateHudBoxesVisibility(GameMode gameMode){
	std::vector<HudBox*>::iterator it;
	for(it = m_hudBoxes.begin(); it != m_hudBoxes.end(); it++){
		(*it)->updateVisibility(gameMode);
	}
}