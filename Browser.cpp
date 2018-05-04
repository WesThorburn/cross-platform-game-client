#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream>
#include "Browser.h"
#include "Canvas.h"

namespace Browser{
	Attributes attributes;

	void initialize(){
		setAttributes();
		Canvas::initialize(Canvas::GAME, "gameCanvas");
		Canvas::initialize(Canvas::HUD, "hudCanvas");
		Canvas::scaleAttributes.setDevicePixelRatio(getDevicePixelRatio());
		formatCanvas();
		addResizeListener();
		addOrientationChangeListener();
	}

	void setAttributes(){
		attributes.width = getWidth();
		attributes.height = getHeight();
		attributes.devicePixelRatio = getDevicePixelRatio();
		attributes.isMobile = isMobile();
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

	bool isMobile(){
		return EM_ASM_INT({
			return isMobile.any;	
		});
	}

	void formatCanvas(){
		Canvas::fitToWindow(Canvas::GAME);
		Canvas::updateAspectRatio(attributes.width, attributes.height);
		Canvas::updateScale(attributes.width, attributes.height);
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

	void addOrientationChangeListener(){
		EM_ASM({
			window.addEventListener('orientationchange', Module.resize());
		});
	}

	void clearScreen(){
		Canvas::clear(Canvas::GAME);
		Canvas::clear(Canvas::HUD);
	}
}