#ifndef BROWSER_H
#define BROWSER_H

namespace Browser{
	struct Attributes{
		bool isMobile = 0;
		int width = 0;
		int height = 0;
		double devicePixelRatio = 0.0;
	};
	extern Attributes attributes;

	void initialize();
	void setAttributes();
	void clearScreen();
	void formatCanvas();
	int getWidth();
	int getHeight();
	double getDevicePixelRatio();
	bool isMobile();
	void addResizeListener();
	void resize();
};

#endif