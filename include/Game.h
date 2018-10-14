#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "UserPlayer.h"
#include "GameMode.h"
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
	void reset();
	
private:
	GameMode m_gameMode = MODE_SPECTATING;
	Map m_map;
	UserPlayer m_userPlayer;
	Hud m_hud;
	Camera m_camera;
	
	std::vector<Player> m_players;

	void processUpdates();
	void setGameMode(GameMode mode);
	void updateHud();
	void updatePlayers();
	void updateUserPlayer();
	void updatePassivePlayers();
	void updateControls();
	void drawPlayers();
	void drawUserPlayer();
	void drawPassivePlayers();
	void createMap();
	void createUserPlayer();
	void createHud();
	void createCamera();
	void setCameraTracking();
};

#endif