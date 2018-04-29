#include <emscripten.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"

Game game;

void gameLoop(){
	game.clear();
	game.update();
	game.draw();
}

void setGlobals(){
	EM_ASM(
		contexts = {};
		renderArea = {};
	);
}

int main(){
	srand(time(NULL)); //Seed randomizer
	setGlobals();

	game = Game();
	game.initialize();

	emscripten_set_main_loop(gameLoop, 0, 1);
}