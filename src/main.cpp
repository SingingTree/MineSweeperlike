#include <iostream>
#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	int r = game.init();
	if(r == 0)
	{
		return game.main_loop();
	}
	else
	{
		return r;
	}
}