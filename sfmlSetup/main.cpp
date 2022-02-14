#include "Game.h"
#include <ctime>
using namespace sf;

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	Game game;
	game.run();
	return 0;
}