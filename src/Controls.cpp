#include <iostream>
#include <emscripten.h>
#include "Controls.h"
#include "Browser.h"
#include "Canvas.h"
#include "Connection.h"

namespace Controls{
	InputState inputState;
	HudState hudState;

	void initialize(){
		if(Browser::attributes.isMobile){
			inputState.touchEnabled = 1;
		}
	}

	void sendStateToServer(){
		sendCursorStateToServer();
	}

	void sendCursorStateToServer(){
		if(inputState.newCursorLocation == inputState.oldCursorLocation) return;

		inputState.oldCursorLocation = inputState.newCursorLocation;

		std::string cursorMessage = "m,"
			+ std::to_string(inputState.relativeCursorLocation.x) + ","
			+ std::to_string(inputState.relativeCursorLocation.y) + ","
			+ std::to_string(static_cast<int>(inputState.cursorAngle));
		Connection::send(cursorMessage);
	}

	int getTouchPointId(int identifier){
		for(int i = 0; i < inputState.touchPoints.size(); i++){
			TouchPoint* touchPoint = &inputState.touchPoints.at(i);
			if(touchPoint->identifier == identifier){
				return i;
			}
		}
		return -1;
	}

	void resetMovementInputs(){
		inputState.pressingLeft = 0;
		inputState.pressingRight = 0;
		inputState.pressingUp = 0;
		inputState.pressingDown = 0;
	}

	void setPlayerRelativeCursorLocation(Location playerLocation){
		inputState.relativeCursorLocation.x = inputState.oldCursorLocation.x - playerLocation.x;
		inputState.relativeCursorLocation.y = inputState.oldCursorLocation.y - playerLocation.y;
	};

	void setCursorAngle(double angle){
		inputState.cursorAngle = angle;
	}

	void setGameCursorLocation(Location cursorLocation){
		inputState.newCursorLocation.x = cursorLocation.x;
		inputState.newCursorLocation.y = cursorLocation.y;
	}

	void setHudCursorLocation(Location cursorLocation){
		hudState.hudCursorLocation = {
			static_cast<int>(cursorLocation.x / Canvas::scaleAttributes.scaleX),
			static_cast<int>(cursorLocation.y / Canvas::scaleAttributes.scaleY)
		};
	}

	void registerGameClick(Location clickLocation){
		inputState.clickLocation = clickLocation;
	}

	void registerHudClick(Location clickLocation){
		hudState.hudClickLocation = {
			static_cast<int>(clickLocation.x / Canvas::scaleAttributes.scaleX),
			static_cast<int>(clickLocation.y / Canvas::scaleAttributes.scaleY)
		};
	}

	void finishClick(Location clickLocation){
		hudState.clickFired = 1;
		inputState.clickLocation = {0, 0};
	}

	void resetTickVariables(){
		if(hudState.clickFired){
			hudState.hudClickLocation = {0, 0};
			hudState.clickFired = 0;
		}
		hudState.hoveringOnHudElement = 0;
	}

	extern "C"{
		void onkeydown(int keyCode){
			if(keyCode == 87 || keyCode == 65 || keyCode == 83 || keyCode == 68){ //w a s d
				handleDirectionalMovement(keyCode, 1);
			}
			else if(keyCode >= 37 && keyCode <= 40){ //left right up down
				handleDirectionalMovement(keyCode, 1);
			}
			else if(keyCode >= 49 && keyCode <= 53){ //digit keys
				handleHudBoxClick(keyCode);
			}
			else if(keyCode >= 97 && keyCode <= 101){ //numpad keys
				handleHudBoxClick(keyCode);
			}
			else if(keyCode == 32){ //space
				handleAction(keyCode, 1);
			}
		}

		void onkeyup(int keyCode){
			if(keyCode == 87 || keyCode == 65 || keyCode == 83 || keyCode == 68){ //w a s d
				handleDirectionalMovement(keyCode, 0);
			}
			else if(keyCode >= 37 && keyCode <= 40){ //left right up down
				handleDirectionalMovement(keyCode, 0);
			}
			else if(keyCode == 32){ //space
				handleAction(keyCode, 0);
			}
		}
		
		void onmousemove(int clientX, int clientY){
			setGameCursorLocation({clientX, clientY});
			setHudCursorLocation({clientX, clientY});
		}

		void onmousedown(int clientX, int clientY, int mouseKeyCode){
			registerGameClick({clientX, clientY});
			registerHudClick({clientX, clientY});
		}
		
		void onmouseup(int clientX, int clientY, int mouseKeyCode){
			finishClick({clientX, clientY});
		}
		
		void onwheel(int deltaY){

		}

		void onblur(){

		}
		
		void onfocus(){

		}

		void touchstart(int identifier, int clientX, int clientY){
			if(inputState.touchPoints.size() >= 2){
				return;
			}

			TouchPoint touchPoint;
			touchPoint.identifier = identifier;
			touchPoint.startLocation = {clientX, clientY};
			touchPoint.currentLocation = {clientX, clientY};
			inputState.touchPoints.push_back(touchPoint);
		}

		void touchend(int identifier){
			for(std::vector<TouchPoint>::iterator it=inputState.touchPoints.begin(); it!=inputState.touchPoints.end();){
				if(it->identifier == identifier){
					it = inputState.touchPoints.erase(it);
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
				TouchPoint* touchPoint = &inputState.touchPoints.at(touchPointId);
				touchPoint->currentLocation.x = clientX;
				touchPoint->currentLocation.y = clientY;
			}
		}
	}

	void handleDirectionalMovement(int keyCode, bool state){
		std::string keyMessage = "";
		switch(keyCode){
			case 65: //a
				inputState.pressingLeft = state;
				keyMessage = "k,0," + std::to_string(state);
				break;
			case 68: //d
				inputState.pressingRight = state;
				keyMessage = "k,1," + std::to_string(state);
				break;
			case 87: //w
				inputState.pressingUp = state;
				keyMessage = "k,2," + std::to_string(state);
				break;
			case 83: //s
				inputState.pressingDown = state;
				keyMessage = "k,3," + std::to_string(state);
				break;
			case 37: //left
				inputState.pressingLeft = state;
				keyMessage = "k,0," + std::to_string(state);
				break;
			case 39: //right
				inputState.pressingRight = state;
				keyMessage = "k,1," + std::to_string(state);
				break;
			case 38: //up
				inputState.pressingUp = state;
				keyMessage = "k,2," + std::to_string(state);
				break;
			case 40: //down
				inputState.pressingDown = state;
				keyMessage = "k,3," + std::to_string(state);
				break;
		}
		Connection::send(keyMessage);
	}

	void handleHudBoxClick(int keyCode){
		std::string keyMessage = "";
		if(keyCode == 49 || keyCode == 97){
			inputState.pressingNum = 1;
			hudState.selectedHudBox = 1;
			keyMessage = "k,11,1";
		}
		else if(keyCode == 50 || keyCode == 98){
			inputState.pressingNum = 2;
			hudState.selectedHudBox = 2;
			keyMessage = "k,12,1";
		}
		else if(keyCode == 51 || keyCode == 99){
			inputState.pressingNum = 3;
			hudState.selectedHudBox = 3;
			keyMessage = "k,13,1";
		}
		else if(keyCode == 52 || keyCode == 100){
			inputState.pressingNum = 4;
			hudState.selectedHudBox = 4;
			keyMessage = "k,14,1";
		}
		else if(keyCode == 53 || keyCode == 101){
			inputState.pressingNum = 5;
			hudState.selectedHudBox = 5;
			keyMessage = "k,15,1";
		}
		Connection::send(keyMessage);
	}

	void handleAction(int keyCode, bool state){
		std::string keyMessage = "";
		switch(keyCode){
			case 32:
				inputState.pressingSpace = 0;
				keyMessage = "k,5," + std::to_string(state);
				break;
		}
		Connection::send(keyMessage);
	}
};