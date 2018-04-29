#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Map.h"

class Game{
public:
	Game();
	void initialize();
	void clear();
	void update();
	void draw();
private:
	Map* m_map;
	std::vector<Player> m_players;

	void spawnStartingPlayers();
	void createMap();
};

#endif