#include <iostream>
#include "Hud.h"
#include "DebugVariables.h"
#include "TouchControls.h"

Hud::Hud(){
	initializeElements();
}

void Hud::initializeElements(){
	HudElement* debugVariables = new DebugVariables();
	m_elements.push_back(debugVariables);

	TouchControls* touchControls = new TouchControls();
	m_elements.push_back(touchControls);
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
		(*it)->draw();
	}
}