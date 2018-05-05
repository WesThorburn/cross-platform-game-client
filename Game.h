#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "ActivePlayer.h"
#include "Map.h"
#include "Hud.h"
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
	Hud m_hud;
	Camera m_camera;
	
	std::vector<Player> m_players;

	void spawnStartingPlayers();
	void createMap();
	void createHud();
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