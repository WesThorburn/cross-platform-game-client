#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include <vector>
#include <math.h>

namespace Canvas{
	struct ScaleAttributes{
		const int NATIVE_WIDTH = 1366;
		const int NATIVE_HEIGHT = 768;
		double nativeAspectRatio = 0.0;
		double currentAspectRatio = 0.0;
		double scaleX = 0.0;
		double scaleY = 0.0;
		int scaledWidth = 0;
		int scaledHeight = 0;
	};
	extern ScaleAttributes scaleAttributes;
	enum Layer{ GAME, HUD };

	void initialize(Layer layer, std::string name);
	void clear(Layer layer);
	void fitToWindow(Layer layer);
	void updateAspectRatio(int browserWidth, int browserHeight);
	void updateScale(int browserWidth, int browserHeight);
	void applyScale(Layer layer);
	void scale(Layer layer, double scaleX, double scaleY);
	void setTransform(Layer layer, double hScale, double hSkew, double vSkew, double vScale, double hMove, double vMove);
	void drawLine(Layer layer, int x1, int y1, int x2, int y2);
	void beginPath(Layer layer);
	void arc(Layer layer, int x, int y, int radius, double startAngleRadians = 0, double endAngleRadians = 2 * M_PI);
	void arcTo(Layer layer, int x1, int y1, int x2, int y2, int radius);
	void moveTo(Layer layer, double x, double y);
	void lineTo(Layer layer, double x, double y);
	void fill(Layer layer);
	void stroke(Layer layer);
	void setLineWidth(Layer layer, int lineWidth);
	void strokeRect(Layer layer, int x, int y, int width, int height);
	void fillRect(Layer layer, int x, int y, int width, int height);
	void drawCurvedRectangle(Layer layer, int x, int y, int width, int height, int cornerRadius);
	void drawFilledCurvedRectangle(Layer layer, int x, int y, int width, int height, int cornerRadius);
	void setStrokeStyle(Layer layer, int r, int g, int b);
	void setFillStyle(Layer layer, int r, int g, int b);
	void setGlobalAlpha(Layer layer, double globalAlpha);
	void setTextAlign(Layer layer, std::string alignment);
	void setTextBaseline(Layer layer, std::string alignment);
	void setFont(Layer layer, int size, std::string variant = "");
	void fillText(Layer layer, std::string text, int x, int y);
	void strokeText(Layer layer, std::string text, int x, int y);
	void setCursorDefault();
	void setCursorText();
	void setCursorPointer();
};

#endif