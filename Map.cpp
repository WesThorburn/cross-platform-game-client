#include <iostream>
#include "Map.h"
#include "Canvas.h"

const int Map::MAX_WIDTH = 2000;
const int Map::MAX_HEIGHT = 2000;

Map::Map(){}

void Map::update(){

}

void Map::draw(Camera& camera){
	drawBackground(camera);
	drawGridLines(camera);
}

void Map::drawBackground(Camera& camera){
	Canvas::setFillStyle(Canvas::GAME, 206, 206, 206);
	Location mapOrigin = getRelativeMapOrigin(camera);
	Canvas::fillRect(Canvas::GAME, mapOrigin.x, mapOrigin.y, MAX_WIDTH, MAX_HEIGHT);
}

void Map::drawGridLines(Camera& camera){
	Canvas::setLineWidth(Canvas::GAME, 1);
	Canvas::setStrokeStyle(Canvas::GAME, 199, 199, 198);

	Location mapOrigin = getRelativeMapOrigin(camera);

	//Vertical Lines
	for(int i = mapOrigin.x; i < mapOrigin.x + MAX_WIDTH; i += 20){
		Canvas::drawLine(Canvas::GAME, i, mapOrigin.y, i, mapOrigin.y + MAX_HEIGHT);
	}
	//Horizontal Lines
	for(int j = mapOrigin.y; j < mapOrigin.y + MAX_HEIGHT; j += 20){
		Canvas::drawLine(Canvas::GAME, mapOrigin.x, j, mapOrigin.x + MAX_WIDTH, j);
	}
}

Location Map::getRelativeMapOrigin(Camera& camera){
	return camera.getRelativeLocation({0, 0});
}