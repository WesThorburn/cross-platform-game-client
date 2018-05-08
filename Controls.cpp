#include <iostream>
#include <emscripten.h>
#include <emscripten/bind.h>
#include "Controls.h"

namespace Controls{
	State state;

	void initialize(){
		addKeyEventListeners();
		addTouchEventListeners();
	}

	void addKeyEventListeners(){
		EM_ASM(
			document.onkeydown = function(event){
				if(event.keyCode){
					Module.onkeydown(event.keyCode);
				}
				if(event.keyCode == 32){
					event.preventDefault(); //Disables spacebar scrolling
				}
			};
			document.onkeyup = function(event){
				if(event.keyCode){
					Module.onkeyup(event.keyCode);
				}
				if(event.keyCode == 32){
					event.preventDefault(); //Disables spacebar scrolling
				}
			};
			document.onmousemove = function(event){
				Module.onmousemove(event.clientX, event.clientY);
			};
			document.onmousedown = function(event){
				Module.onmousedown(event.clientX, event.clientY, event.which);
			};
			document.onmouseup = function(event){
				Module.onmouseup(event.clientX, event.clientY, event.which);
			};
			document.onwheel = function(event){
				Module.onwheel(event.deltaY);
				event.preventDefault();
			};
			window.onblur = function(){
				Module.onfocus(0);
			};
			window.onfocus = function(){
				Module.onfocus(1);
			};
		);
	}

	void addTouchEventListeners(){
		EM_ASM({
			var hud = document.getElementById("hudCanvas");
			hud.addEventListener("touchstart", touchStart, false);
			hud.addEventListener("touchend", touchEnd, false);
			hud.addEventListener("touchcancel", touchEnd, false);
			hud.addEventListener("touchmove", touchMove, false);

			function touchStart(e){
				e.preventDefault();
				for(var i = 0; i < e.changedTouches.length; i++){
					var touch = e.changedTouches[i];
					Module.touchStart(touch.identifier, touch.clientX, touch.clientY);
				}
			}

			function touchEnd(e){
				e.preventDefault();
				for(var i = 0; i < e.changedTouches.length; i++){
					var touch = e.changedTouches[i];
					Module.touchEnd(touch.identifier);
				}
			}

			function touchMove(e){
				e.preventDefault();
				for(var i = 0; i < e.changedTouches.length; i++){
					var touch = e.changedTouches[i];
					Module.touchMove(touch.identifier, touch.clientX, touch.clientY);
				}
			}
		});
	}

	void touchStart(int identifier, int clientX, int clientY){
		if(state.touchPoints.size() >= 2){
			return;
		}

		TouchPoint touchPoint;
		touchPoint.identifier = identifier;
		touchPoint.startLocation = {clientX, clientY};
		touchPoint.currentLocation = {clientX, clientY};
		state.touchPoints.push_back(touchPoint);
	}
	EMSCRIPTEN_BINDINGS(touchStart){
		emscripten::function("touchStart", &touchStart);
	}

	void touchEnd(int identifier){
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
	EMSCRIPTEN_BINDINGS(touchEnd){
		emscripten::function("touchEnd", &touchEnd);
	}

	void touchMove(int identifier, int clientX, int clientY){
		int touchPointId = getTouchPointId(identifier);
		if(touchPointId >= 0 && touchPointId <= 1){
			TouchPoint* touchPoint = &state.touchPoints.at(touchPointId);
			touchPoint->currentLocation.x = clientX;
			touchPoint->currentLocation.y = clientY;
		}
	}
	EMSCRIPTEN_BINDINGS(touchMove){
		emscripten::function("touchMove", &touchMove);
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
	EMSCRIPTEN_BINDINGS(onkeydown){
		emscripten::function("onkeydown", &onkeydown);
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
	EMSCRIPTEN_BINDINGS(onkeyup){
		emscripten::function("onkeyup", &onkeyup);
	}
	
	void onmousemove(int clientX, int clientY){
		state.cursorX = clientX;
		state.cursorY = clientY;
	}
	EMSCRIPTEN_BINDINGS(onmousemove){
		emscripten::function("onmousemove", &onmousemove);
	}
	
	void onmousedown(int clientX, int clientY, int mouseKeyCode){

	}
	EMSCRIPTEN_BINDINGS(onmousedown){
		emscripten::function("onmousedown", &onmousedown);
	}
	
	void onmouseup(int clientX, int clientY, int mouseKeyCode){

	}
	EMSCRIPTEN_BINDINGS(onmouseup){
		emscripten::function("onmouseup", &onmouseup);
	}
	
	void onwheel(int deltaY){

	}
	EMSCRIPTEN_BINDINGS(onwheel){
		emscripten::function("onwheel", &onwheel);
	}
	
	void onfocus(bool state){

	}
	EMSCRIPTEN_BINDINGS(onfocus){
		emscripten::function("onfocus", &onfocus);
	}

	void resetMovementInputs(){
		state.pressingLeft = 0;
		state.pressingRight = 0;
		state.pressingUp = 0;
		state.pressingDown = 0;
	}
};