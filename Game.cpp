#include "Game.h"
#include "Browser.h"

Game::Game(){}

void Game::initialize(){
	Browser::initialize();
	spawnStartingPlayers();
	createMap();
}

void Game::clear(){
	Browser::clearScreen();
}

void Game::update(){
	m_map->update();
	for(Player& player : m_players){
		player.update();
	}
}

void Game::draw(){
	m_map->draw();
	for(Player& player : m_players){
		player.draw();
	}
}

void Game::spawnStartingPlayers(){
	for(int i = 0; i < 25; ++i){
		Player player = Player();
		m_players.push_back(player);
	}
}

void Game::createMap(){
	Map map = Map();
	m_map = &map;
}