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
			hud.addEventListener("touchcancel", touchCancel, false);
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
				console.log("touchend");
			}

			function touchCancel(e){
				e.preventDefault();
				console.log("touchcancel");
			}

			function touchMove(e){
				e.preventDefault();
				console.log("touchMove");
			}
		});
	}

	void touchStart(int identifier, int clientX, int clientY){
		state.leftTouchStickPosition.x = clientX;
		state.leftTouchStickPosition.y = clientY;
	}
	EMSCRIPTEN_BINDINGS(touchStart){
		emscripten::function("touchStart", &touchStart);
	}

	void touchEnd(int identifier){
		std::cout << "touchEnd" << std::endl;
	}
	EMSCRIPTEN_BINDINGS(touchEnd){
		emscripten::function("touchEnd", &touchEnd);
	}

	void touchCancel(int identifier){
		std::cout << "touchCancel" << std::endl;
	}
	EMSCRIPTEN_BINDINGS(touchCancel){
		emscripten::function("touchCancel", &touchCancel);
	}

	void touchMove(int identifier){
		std::cout << "touchMove" << std::endl;
	}
	EMSCRIPTEN_BINDINGS(touchMove){
		emscripten::function("touchMove", &touchMove);
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
};