#ifndef CONTROLS_H
#define CONTROLS_H

#include <vector>
#include "Location.h"

namespace Controls{
	struct TouchPoint{
		int identifier = -1;
		Location startLocation = {0, 0};
		Location currentLocation = {0, 0};
	};

	enum InputStrength{ WEAK, MEDIUM, STRONG };

	struct InputState{
		bool pressingLeft = 0;
		bool pressingRight = 0;
		bool pressingUp = 0;
		bool pressingDown = 0;
		bool pressingSpace = 0;
		int pressingNum = -1;
		Location newCursorLocation = {0, 0};
		Location oldCursorLocation = {0, 0};
		Location relativeCursorLocation = {0, 0};
		Location clickLocation = {};
		double cursorAngle = 0.0;
		bool leftClicking = 0;
		bool rightClicking = 0;
		bool focus = 1;
		bool touchEnabled = 0;
		std::vector<TouchPoint> touchPoints = {};
		double inputAngleRadians = 0.0;
		InputStrength movementInputStrength = STRONG;
	};

	struct HudState{
		Location hudCursorLocation = {};
		Location hudClickLocation = {};
		bool hoveringOnHudElement = 0;
		bool clickFired = 0;
		bool spawnClicked = 0;
		int selectedHudBox = 1;
	};

	extern InputState inputState;
	extern HudState hudState;

	void initialize();
	void sendStateToServer();
	void sendCursorStateToServer();
	int getTouchPointId(int identifier);
	void resetMovementInputs();
	void setPlayerRelativeCursorLocation(Location location);
	void setGameCursorLocation(Location cursorLocation);
	void setHudCursorLocation(Location cursorLocation);
	void setCursorAngle(double angle);
	void registerGameClick(Location clickLocation);
	void registerHudClick(Location clickLocation);
	void finishClick(Location clickLocation);
	void resetTickVariables();

	extern "C"{
		void onkeydown(int keyCode);
		void onkeyup(int keyCode);
		void onmousemove(int clientX, int clientY);
		void onmousedown(int clientX, int clientY, int mouseKeyCode);
		void onmouseup(int clientX, int clientY, int mouseKeyCode);
		void onwheel(int deltaY);
		void onblur();
		void onfocus();

		void touchstart(int identifier, int clientX, int clientY);
		void touchend(int identifier);
		void touchmove(int identifier, int clientX, int clientY);
	}

	void handleDirectionalMovement(int keyCode, bool state);
	void handleHudBoxClick(int keyCode);
	void handleAction(int keyCode, bool state);
};

#endif