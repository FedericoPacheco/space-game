#include "Game.h"
using namespace std;

// https://stackoverflow.com/questions/827127/how-do-i-show-how-many-lines-of-code-my-project-contains-in-visual-studio

int main()
{
	Game game;

	game.initialScreen();
	while (game.gameLoop());

	return 0;
} 
