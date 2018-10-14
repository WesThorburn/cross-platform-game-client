#include <iostream>
#include "Game.h"
#include "Util.h"
#include "GameMode.h"
#include "Browser.h"
#include "Controls.h"
#include "Connection.h"

Game::Game(){}

void Game::initialize(){
	Browser::initialize();
	Controls::initialize();
	createMap();
	createUserPlayer();
	createHud();
	createCamera();
	setCameraTracking();
	Browser::hideElement("loading");
}

void Game::createMap(){
	m_map = Map();
}

void Game::createUserPlayer(){
	m_userPlayer = UserPlayer();
}

void Game::createHud(){
	m_hud = Hud();
	m_hud.initialize(&m_userPlayer);
}

void Game::createCamera(){
	m_camera = Camera();
}

void Game::setCameraTracking(){
	m_camera.setTrackingPlayer(&m_userPlayer);
	m_userPlayer.setCamera(&m_camera);
}

void Game::clear(){
	Browser::clearScreen();
}

void Game::update(){
	processUpdates();
	m_map.update();
	m_hud.update();
	updatePlayers();
	updateControls();
	m_camera.update();
	Browser::update();
	Connection::update();
}

void Game::processUpdates(){
	for(std::string message : Connection::messages){
		std::vector<std::string> messageData = String::split(message, ',');
		//Ordered by frequency
		if(messageData[0] == "b"){
			m_userPlayer.applyPrimaryUpdate(messageData);
		}
		else if(messageData[0] == "a"){
			m_userPlayer.applyInitUpdate(messageData);
			setGameMode(MODE_IN_GAME);
		}
	}
	Connection::messages.clear();
}

void Game::setGameMode(GameMode mode){
	m_hud.setMode(MODE_IN_GAME);
	m_gameMode = MODE_IN_GAME;
}

void Game::reset(){
	Controls::resetTickVariables();
}

void Game::updatePlayers(){
	updateUserPlayer();
	updatePassivePlayers();
}

void Game::updateUserPlayer(){
	m_userPlayer.update();
}

void Game::updatePassivePlayers(){
	for(Player& player : m_players){
		player.update();
	}
}

void Game::updateControls(){
	Controls::setPlayerRelativeCursorLocation(m_userPlayer.getScreenPosition());
	Controls::setCursorAngle(m_userPlayer.getAngleDegrees());
	Controls::sendStateToServer();
}

void Game::draw(){
	m_map.draw(m_camera);
	drawPlayers();
	m_hud.draw();
}

void Game::drawPlayers(){
	if(m_gameMode == MODE_IN_GAME){
		drawUserPlayer();
	}
	drawPassivePlayers();
}

void Game::drawUserPlayer(){
	m_userPlayer.draw(m_camera);
}

void Game::drawPassivePlayers(){
	for(Player& player : m_players){
		player.draw(m_camera);
	}
}