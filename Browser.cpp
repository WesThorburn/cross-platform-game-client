#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream>
#include "Browser.h"
#include "Canvas.h"

namespace Browser{
	void initialize(){
		addResizeListener();
		Canvas::initialize(Canvas::GAME, "gameCanvas");
		Canvas::initialize(Canvas::HUD, "hudCanvas");
		Canvas::scaleAttributes.setDevicePixelRatio(getDevicePixelRatio());
		formatCanvas();
	}

	void clearScreen(){
		Canvas::clear(Canvas::GAME);
		Canvas::clear(Canvas::HUD);
	}

	void formatCanvas(){
		Canvas::fitToWindow(Canvas::GAME);
		Canvas::updateAspectRatio(Browser::getWidth(), Browser::getHeight());
		Canvas::updateScale(Browser::getWidth(), Browser::getHeight());
		Canvas::applyScale(Canvas::GAME);
	}

	void addResizeListener(){
		EM_ASM({
			window.onresize = function(){
				Module.resize();
			}
		});
	}

	void resize(){
		if(getWidth() < 0 || getHeight() < 0){
			return;
		}
		formatCanvas();
	}
	EMSCRIPTEN_BINDINGS(resize){
		emscripten::function("resize", &resize);
	}

	int getWidth(){
		return EM_ASM_INT({
			return window.innerWidth;
		});
	}

	int getHeight(){
		return EM_ASM_INT({
			return window.innerHeight;
		});
	}

	double getDevicePixelRatio(){
		return EM_ASM_DOUBLE({
			return window.devicePixelRatio;
		});
	}
}