#ifndef MAP_H
#define MAP_H

class Map{
public:
	Map();
	void update();
	void draw();
private:
	const int MAX_WIDTH = 10000, MAX_HEIGHT = 10000;

	void drawBackground();
	void drawGridLines();
};

#endif