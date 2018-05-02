#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "ActivePlayer.h"
#include "Map.h"
#include "Camera.h"

class Game{
public:
	Game();
	void initialize();
	void clear();
	void update();
	void draw();
private:
	Map m_map;
	ActivePlayer m_activePlayer;
	Camera m_camera;
	
	std::vector<Player> m_players;

	void spawnStartingPlayers();
	void createMap();
	void createActivePlayer();
	void createCamera();
	void setCameraTracking();

	void updatePlayers();
	void updateActivePlayer();
	void updatePassivePlayers();
	void drawPlayers();
	void drawActivePlayer();
	void drawPassivePlayers();
};

#endif