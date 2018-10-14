#include <emscripten.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "RenderTimer.h"

Game game;
RenderTimer timer;

void gameLoop(){
	timer.start();

	game.clear();
	game.update();
	game.draw();
	game.reset();

	timer.stop();
	timer.print();
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