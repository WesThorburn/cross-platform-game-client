#include "Map.h"
#include "Canvas.h"

Map::Map(){}

void Map::update(){

}

void Map::draw(){
	drawBackground();
	drawGridLines();
}

void Map::drawBackground(){
	Canvas::setFillStyle(Canvas::GAME, 206, 206, 206);
	Canvas::fillRect(Canvas::GAME, 0, 0, MAX_WIDTH, MAX_HEIGHT);
}

void Map::drawGridLines(){
	Canvas::setLineWidth(Canvas::GAME, 1);
	Canvas::setStrokeStyle(Canvas::GAME, 199, 199, 198);

	//Vertical Lines
	for(int i = 0; i < MAX_WIDTH; i += 25){
		Canvas::drawLine(Canvas::GAME, i, 0, i, MAX_HEIGHT);
	}
	//Horizontal Lines
	for(int j = 0; j < MAX_HEIGHT; j += 25){
		Canvas::drawLine(Canvas::GAME, 0, j, MAX_WIDTH, j);
	}
}