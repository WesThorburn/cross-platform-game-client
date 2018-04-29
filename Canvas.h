#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include <vector>
#include <math.h>

namespace Canvas{
	enum Layer{ GAME, HUD };

	void initialize(Layer layer, std::string name);
	void clear(Layer layer);
	void fitToWindow(Layer layer);
	void scale(Layer layer, double scaleX, double scaleY);
	void setTransform(Layer layer, double hScale, double hSkew, double vSkew, double vScale, double hMove, double vMove);
	void drawLine(Layer layer, int x1, int y1, int x2, int y2);
	void beginPath(Layer layer);
	void arc(Layer layer, int x, int y, int radius, double startAngleRadians = 0, double endAngleRadians = 2 * M_PI);
	void moveTo(Layer layer, double x, double y);
	void lineTo(Layer layer, double x, double y);
	void fill(Layer layer);
	void stroke(Layer layer);
	void setLineWidth(Layer layer, int lineWidth);
	void strokeRect(Layer layer, int x, int y, int width, int height);
	void fillRect(Layer layer, int x, int y, int width, int height);
	void setStrokeStyle(Layer layer, int r, int g, int b);
	void setFillStyle(Layer layer, int r, int g, int b);
	void setGlobalAlpha(Layer layer, double globalAlpha);

};

#endif