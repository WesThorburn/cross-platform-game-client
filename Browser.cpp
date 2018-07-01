#include <emscripten.h>
#include <iostream>
#include "Browser.h"
#include "Canvas.h"

namespace Browser{
	Attributes attributes;

	void initialize(){
		setAttributes();
		Canvas::initialize(Canvas::GAME, "gameCanvas");
		Canvas::initialize(Canvas::HUD, "hudCanvas");
		formatCanvas();
	}

	void setAttributes(){
		updateSize();
		attributes.devicePixelRatio = getDevicePixelRatio();
		attributes.isMobile = isMobile();
	}

	void updateSize(){
		attributes.width = getWidth();
		attributes.height = getHeight();
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
		double devicePixelRatio = EM_ASM_DOUBLE({
			return window.devicePixelRatio;
		});
		if(devicePixelRatio < 1){
			devicePixelRatio = 1.0;
		}
		return devicePixelRatio;
	}

	bool isMobile(){
		return EM_ASM_INT({
			return isMobile.any;	
		});
	}

	void formatCanvas(){
		updateSize();
		Canvas::fitToWindow(Canvas::GAME);
		Canvas::fitToWindow(Canvas::HUD);
		Canvas::updateAspectRatio(attributes.width, attributes.height);
		Canvas::updateScale(attributes.width, attributes.height);
		Canvas::applyScale(Canvas::GAME);
		Canvas::applyScale(Canvas::HUD);
	}

	void clearScreen(){
		Canvas::clear(Canvas::GAME);
		Canvas::clear(Canvas::HUD);
	}

	void resize(){
		if(getWidth() < 0 || getHeight() < 0){
			return;
		}
		formatCanvas();
	}

	extern "C"{
		void orientationchange(){
			resize();
		}

		void onresize(){
			resize();
		}
	}
}