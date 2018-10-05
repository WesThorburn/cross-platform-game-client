#include <iostream>
#include <emscripten.h>
#include "Controls.h"

namespace Controls{
	State state;

	void initialize(bool mobileClient){
		if(mobileClient){
			state.touchEnabled = 1;
		}
	}

	int getTouchPointId(int identifier){
		for(int i = 0; i < state.touchPoints.size(); i++){
			TouchPoint* touchPoint = &state.touchPoints.at(i);
			if(touchPoint->identifier == identifier){
				return i;
			}
		}
		return -1;
	}

	void resetMovementInputs(){
		state.pressingLeft = 0;
		state.pressingRight = 0;
		state.pressingUp = 0;
		state.pressingDown = 0;
	}

	extern "C"{
		void onkeydown(int keyCode){
			switch(keyCode){
				case 65: //a
					state.pressingLeft = 1;
					break;
				case 68: //d
					state.pressingRight = 1;
					break;
				case 87: //w
					state.pressingUp = 1;
					break;
				case 83: //s
					state.pressingDown = 1;
					break;
				case 37: //left
					state.pressingLeft = 1;
					break;
				case 39: //right
					state.pressingRight = 1;
					break;
				case 38: //up
					state.pressingUp = 1;
					break;
				case 40: //down
					state.pressingDown = 1;
					break;
			}
		}

		void onkeyup(int keyCode){
			switch(keyCode){
				case 65: //a
					state.pressingLeft = 0;
					break;
				case 68: //d
					state.pressingRight = 0;
					break;
				case 87: //w
					state.pressingUp = 0;
					break;
				case 83: //s
					state.pressingDown = 0;
					break;
				case 37: //left
					state.pressingLeft = 0;
					break;
				case 39: //right
					state.pressingRight = 0;
					break;
				case 38: //up
					state.pressingUp = 0;
					break;
				case 40: //down
					state.pressingDown = 0;
					break;
			}
		}
		
		void onmousemove(int clientX, int clientY){
			state.cursorX = clientX;
			state.cursorY = clientY;
		}

		void onmousedown(int clientX, int clientY, int mouseKeyCode){

		}
		
		void onmouseup(int clientX, int clientY, int mouseKeyCode){

		}
		
		void onwheel(int deltaY){

		}

		void onblur(){

		}
		
		void onfocus(){

		}

		void touchstart(int identifier, int clientX, int clientY){
			if(state.touchPoints.size() >= 2){
				return;
			}

			TouchPoint touchPoint;
			touchPoint.identifier = identifier;
			touchPoint.startLocation = {clientX, clientY};
			touchPoint.currentLocation = {clientX, clientY};
			state.touchPoints.push_back(touchPoint);
		}

		void touchend(int identifier){
			for(std::vector<TouchPoint>::iterator it=state.touchPoints.begin(); it!=state.touchPoints.end();){
				if(it->identifier == identifier){
					it = state.touchPoints.erase(it);
				}
				else{
					++it;
				}
			}
			resetMovementInputs();
		}

		void touchmove(int identifier, int clientX, int clientY){
			int touchPointId = getTouchPointId(identifier);
			if(touchPointId >= 0 && touchPointId <= 1){
				TouchPoint* touchPoint = &state.touchPoints.at(touchPointId);
				touchPoint->currentLocation.x = clientX;
				touchPoint->currentLocation.y = clientY;
			}
		}
	}
};