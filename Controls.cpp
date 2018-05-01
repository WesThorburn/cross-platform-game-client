#include <iostream>
#include <emscripten.h>
#include <emscripten/bind.h>
#include "Controls.h"

namespace Controls{
	void initialize(){
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

	void onkeydown(int keyCode){
		std::cout << "keydown: " << keyCode << std::endl;
	}
	EMSCRIPTEN_BINDINGS(onkeydown){
		emscripten::function("onkeydown", &onkeydown);
	}

	void onkeyup(int keyCode){
		std::cout << "keyup: " << keyCode << std::endl;
	}
	EMSCRIPTEN_BINDINGS(onkeyup){
		emscripten::function("onkeyup", &onkeyup);
	}
	
	void onmousemove(int clientX, int clientY){
		std::cout << "mousemove: x: " << clientX << " y: " << clientY << std::endl;
	}
	EMSCRIPTEN_BINDINGS(onmousemove){
		emscripten::function("onmousemove", &onmousemove);
	}
	
	void onmousedown(int clientX, int clientY, int mouseKeyCode){
		std::cout << "onmousedown: x: " << clientX << " y: " << clientY << " code: " << mouseKeyCode << std::endl;
	}
	EMSCRIPTEN_BINDINGS(onmousedown){
		emscripten::function("onmousedown", &onmousedown);
	}
	
	void onmouseup(int clientX, int clientY, int mouseKeyCode){
		std::cout << "onmouseup: x: " << clientX << " y: " << clientY << " code: " << mouseKeyCode << std::endl;
	}
	EMSCRIPTEN_BINDINGS(onmouseup){
		emscripten::function("onmouseup", &onmouseup);
	}
	
	void onwheel(int deltaY){
		std::cout << "scroll deltaY: " << deltaY << std::endl;
	}
	EMSCRIPTEN_BINDINGS(onwheel){
		emscripten::function("onwheel", &onwheel);
	}
	
	void onfocus(bool state){
		std::cout << "onfocus: state" << state << std::endl;
	}
	EMSCRIPTEN_BINDINGS(onfocus){
		emscripten::function("onfocus", &onfocus);
	}
};