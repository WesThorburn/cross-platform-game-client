#ifndef BROWSER_H
#define BROWSER_H

namespace Browser{
	void initialize();
	void clearScreen();
	int getWidth();
	int getHeight();
	double getDevicePixelRatio();
	void addResizeListener();
	void resize();
};

#endif