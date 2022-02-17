#include "Game.h"
#include <ctime>
using namespace sf;
int main()
{
	bool restart = true;
	srand(static_cast<unsigned int>(time(0)));
	Game* game;
	

	while (restart)
	{
		game = new Game;
		restart = game->run();
		delete game;
	}

	return 0;
}