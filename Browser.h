#ifndef BROWSER_H
#define BROWSER_H

namespace Browser{
	struct Attributes{
		int width = 0;
		int height = 0;
		double devicePixelRatio = 0.0;
		bool isMobile = 0;
	};
	extern Attributes attributes;

	void initialize();
	void setAttributes();
	int getWidth();
	int getHeight();
	double getDevicePixelRatio();
	bool isMobile();
	void formatCanvas();
	void addResizeListener();
	void resize();
	void addOrientationChangeListener();
	void clearScreen();
};

#endif