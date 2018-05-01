#ifndef MAP_H
#define MAP_H

#include "Camera.h"
#include "Location.h"

class Map{
public:
	Map();
	void update();
	void draw(Camera& camera);
private:
	static const int MAX_WIDTH, MAX_HEIGHT, OUTER_X_BUFFER, OUTER_Y_BUFFER;

	void drawBackground(Camera& camera);
	void drawGridLines(Camera& camera);
	Location getRelativeMapOrigin(Camera& camera);
};

#endif