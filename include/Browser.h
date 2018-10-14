#ifndef BROWSER_H
#define BROWSER_H

namespace Browser{
	struct Attributes{
		const int FOLLOW_UP_RESIZE_DELAY_TICKS = 120;

		int width = 0;
		int height = 0;
		double devicePixelRatio = 0.0;
		bool isMobile = 0;
		int followUpResizeCountdownTicks = 0;
	};
	extern Attributes attributes;

	void initialize();
	void setAttributes();
	void update();
	void updateSize();
	void startResizeTimer();
	void updateResizeTimer();
	int getWidth();
	int getHeight();
	double getDevicePixelRatio();
	bool isMobile();
	void formatCanvas();
	void clearScreen();
	void addOrientationChangeListener();
	void resize();
	void hideElement(std::string elementId);
	void showElement(std::string elementId);
	void showGame();
	void showConnecting();

	extern "C"{
		void orientationchange();
		void onresize();
	}
};

#endif