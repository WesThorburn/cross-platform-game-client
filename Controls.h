#ifndef CONTROLS_H
#define CONTROLS_H

#include <vector>
#include "Location.h"

namespace Controls{
	struct TouchPoint{
		int identifier = -1;
		Location startLocation = {0, 0};
		Location currentLocation = {0, 0};
		bool isActive = 0;
	};

	struct State{
		bool pressingLeft = 0;
		bool pressingRight = 0;
		bool pressingUp = 0;
		bool pressingDown = 0;
		int cursorX = 0;
		int cursorY = 0;
		bool leftClicking = 0;
		bool rightClicking = 0;
		bool focus = 1;
		std::vector<TouchPoint> touchPoints = {{},{}}; //Max 2 points tracked
	};
	extern State state;

	void initialize();
	void addKeyEventListeners();
	void addTouchEventListeners();
	void touchStart(int identifier, int clientX, int clientY);
	void touchEnd(int identifier);
	void touchCancel(int identifier);
	void touchMove(int identifier, int clientX, int clientY);
	void onkeydown(int keyCode);
	void onkeyup(int keyCode);
	void onmousemove(int clientX, int clientY);
	void onmousedown(int clientX, int clientY, int mouseKeyCode);
	void onmouseup(int clientX, int clientY, int mouseKeyCode);
	void onwheel(int deltaY);
	void onfocus(bool state);
	void resetMovementInputs();
};

#endif