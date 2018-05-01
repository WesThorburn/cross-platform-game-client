#include <iostream>
#include "Game.h"
#include "Browser.h"

Game::Game(){}

void Game::initialize(){
	Browser::initialize();
	spawnStartingPlayers();
	createMap();
	createCamera();
}

void Game::clear(){
	Browser::clearScreen();
}

void Game::update(){
	m_map.update();
	m_camera.update();
	for(Player& player : m_players){
		player.update();
	}
}

void Game::draw(){
	m_map.draw(m_camera);
	for(Player& player : m_players){
		player.draw(m_camera);
	}
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

void Game::createCamera(){
	m_camera = Camera();
}