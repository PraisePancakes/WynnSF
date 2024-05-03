#include <iostream>
#include "Game/Game.hpp"

int main(int arc, char* argv[]) {
	
	Game g;
	g.Run();
	
	std::cout << "Process Finished" << std::endl;
	return EXIT_SUCCESS;
}