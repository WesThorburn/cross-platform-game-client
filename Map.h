#ifndef MAP_H
#define MAP_H

class Map{
public:
	Map();
	void update();
	void draw();
private:
	static const int MAX_WIDTH, MAX_HEIGHT;

	void drawBackground();
	void drawGridLines();
};

#endif