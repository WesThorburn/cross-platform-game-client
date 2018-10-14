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

	void update(){
		updateResizeTimer();
	}

	void updateSize(){
		attributes.width = getWidth();
		attributes.height = getHeight();
	}

	void startResizeTimer(){
		attributes.followUpResizeCountdownTicks = attributes.FOLLOW_UP_RESIZE_DELAY_TICKS;
	}

	void updateResizeTimer(){
		if(attributes.followUpResizeCountdownTicks == 0){
			return;
		}

		--attributes.followUpResizeCountdownTicks;

		if(attributes.followUpResizeCountdownTicks == 0){
			resize();
		}
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

	void hideElement(std::string elementId){
		EM_ASM({
			document.getElementById(UTF8ToString($0)).style.display = 'none';
		}, elementId.c_str());
	}

	void showElement(std::string elementId){
		EM_ASM({
			document.getElementById(UTF8ToString($0)).style.display = 'initial';
		}, elementId.c_str());
	}

	void showGame(){
		hideElement("connecting");
		showElement("gameCanvas");
		showElement("hudCanvas");
	}

	void showConnecting(){
		hideElement("gameCanvas");
		hideElement("hudCanvas");
		showElement("connecting");
	}

	extern "C"{
		void orientationchange(){
			startResizeTimer();
			resize();
		}

		void onresize(){
			startResizeTimer();
			resize();
		}
	}
}