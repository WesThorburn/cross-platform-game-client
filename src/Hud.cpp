#include <iostream>
#include "Hud.h"
#include "SpawnButton.h"
#include "DebugVariables.h"
#include "TouchControls.h"
#include "HudSelection.h"
#include "MiniMap.h"

Hud::Hud(){}

void Hud::initialize(UserPlayer* userPlayer){
	HudElement* spawnButton = new SpawnButton();
	m_elements.push_back(spawnButton);

	HudElement* debugVariables = new DebugVariables();
	m_elements.push_back(debugVariables);

	HudElement* touchControls = new TouchControls();
	m_elements.push_back(touchControls);

	m_hudSelection = new HudSelection();
	m_elements.push_back(m_hudSelection);

	MiniMap* miniMap = new MiniMap();
	miniMap->setUserPlayer(userPlayer);
	m_elements.push_back(miniMap);

	updateElementsVisibility();
}

void Hud::update(){
	std::vector<HudElement*>::iterator it;
	for(it = m_elements.begin(); it != m_elements.end(); it++){
		(*it)->update();
	}
}

void Hud::draw(){
	std::vector<HudElement*>::iterator it;
	for(it = m_elements.begin(); it != m_elements.end(); it++){
		if((*it)->isVisible()){
			(*it)->draw();
		}
	}
	setHudCursor();
}

void Hud::setHudCursor(){
	if(Controls::hudState.hoveringOnHudElement){
		Canvas::setCursorPointer();
	}
	else{
		Canvas::setCursorDefault();
	}
}

void Hud::setMode(GameMode mode){
	m_mode = mode;
	updateElementsVisibility();
}

void Hud::updateElementsVisibility(){
	std::vector<HudElement*>::iterator it;
	for(it = m_elements.begin(); it != m_elements.end(); it++){
		(*it)->updateVisibility(m_mode);
	}
}