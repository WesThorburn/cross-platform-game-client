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
		bool touchEnabled = 0;
		std::vector<TouchPoint> touchPoints = {};
		double inputAngleRadians = 0.0;
		InputStrength movementInputStrength = STRONG;
	};
	extern State state;

	void initialize(bool enableMobile);
	int getTouchPointId(int identifier);
	void resetMovementInputs();

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
};

#endif