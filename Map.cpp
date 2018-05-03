#include <iostream>
#include "Map.h"
#include "Canvas.h"

const int Map::MAX_WIDTH = 2000;
const int Map::MAX_HEIGHT = 2000;
const int Map::OUTER_X_BUFFER = 2000;
const int Map::OUTER_Y_BUFFER = 1000;

Map::Map(){}

void Map::update(){

}

void Map::draw(Camera& camera){
	drawGridLines(camera);
	drawBackground(camera);
}

void Map::drawBackground(Camera& camera){
	Location mapOrigin = getRelativeMapOrigin(camera);

	Canvas::setGlobalAlpha(Canvas::GAME, 0.7);
	Canvas::setFillStyle(Canvas::GAME, 187, 187, 187);
	Canvas::fillRect(Canvas::GAME, mapOrigin.x - OUTER_X_BUFFER, mapOrigin.y - OUTER_Y_BUFFER, MAX_WIDTH + OUTER_X_BUFFER * 2, MAX_HEIGHT + OUTER_Y_BUFFER * 2);

	Canvas::setGlobalAlpha(Canvas::GAME, 0.4);
	Canvas::setFillStyle(Canvas::GAME, 245, 245, 245);
	Canvas::fillRect(Canvas::GAME, mapOrigin.x, mapOrigin.y, MAX_WIDTH, MAX_HEIGHT);

	Canvas::setGlobalAlpha(Canvas::GAME, 1);
}

void Map::drawGridLines(Camera& camera){
	Canvas::setLineWidth(Canvas::GAME, 1);
	Canvas::setStrokeStyle(Canvas::GAME, 199, 199, 198);

	Location mapOrigin = getRelativeMapOrigin(camera);

	//Vertical Lines
	for(int i = mapOrigin.x - OUTER_X_BUFFER; i < mapOrigin.x + MAX_WIDTH + OUTER_X_BUFFER; i += 20){
		Canvas::drawLine(Canvas::GAME, i, mapOrigin.y - OUTER_Y_BUFFER, i, mapOrigin.y + MAX_HEIGHT + OUTER_Y_BUFFER);
	}
	//Horizontal Lines
	for(int j = mapOrigin.y - OUTER_Y_BUFFER; j < mapOrigin.y + MAX_HEIGHT + OUTER_Y_BUFFER; j += 20){
		Canvas::drawLine(Canvas::GAME, mapOrigin.x - OUTER_X_BUFFER, j, mapOrigin.x + MAX_WIDTH + OUTER_X_BUFFER, j);
	}
}

Location Map::getRelativeMapOrigin(Camera& camera){
	return camera.getLocationOnScreen({0, 0});
}