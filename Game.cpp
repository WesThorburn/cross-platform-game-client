#include <iostream>
#include "Game.h"
#include "Browser.h"
#include "Controls.h"

Game::Game(){}

void Game::initialize(){
	Browser::initialize();
	Controls::initialize(Browser::attributes.isMobile);
	spawnStartingPlayers();
	createMap();
	createHud();
	createActivePlayer();
	createCamera();
	setCameraTracking();
}

void Game::clear(){
	Browser::clearScreen();
}

void Game::update(){
	m_map.update();
	m_hud.update();
	updatePlayers();
	m_camera.update();
}

void Game::draw(){
	m_map.draw(m_camera);
	drawPlayers();
	m_hud.draw();
}

void Game::spawnStartingPlayers(){
	for(int i = 0; i < 64; ++i){
		Player player = Player();
		m_players.push_back(player);
	}
}

void Game::createMap(){
	m_map = Map();
}

void Game::createHud(){
	m_hud = Hud();
}

void Game::createActivePlayer(){
	m_activePlayer = ActivePlayer();
}

void Game::createCamera(){
	m_camera = Camera();
}

void Game::setCameraTracking(){
	m_camera.setTrackingPlayer(&m_activePlayer);
	m_activePlayer.setCamera(&m_camera);
}

void Game::updatePlayers(){
	updateActivePlayer();
	updatePassivePlayers();
}

void Game::updateActivePlayer(){
	m_activePlayer.update();
}

void Game::updatePassivePlayers(){
	for(Player& player : m_players){
		player.update();
	}
}

void Game::drawPlayers(){
	drawActivePlayer();
	drawPassivePlayers();
}

void Game::drawActivePlayer(){
	m_activePlayer.draw(m_camera);
}

void Game::drawPassivePlayers(){
	for(Player& player : m_players){
		player.draw(m_camera);
	}
}