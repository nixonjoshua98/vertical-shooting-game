#include <iostream>
#include <memory>

#include "JN_Game.h"
#include "JN_SDLRenderer.h"

int main(int argc, char* argv[])
{
	std::shared_ptr<JN_SDLRenderer> renderer = std::make_shared<JN_SDLRenderer>();

	std::unique_ptr<JN_Game> game = std::make_unique<JN_Game>(renderer);

	game->Run();

	return 0;
}
