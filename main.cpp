#include <iostream>
#include "Game.hpp"

int main() {
	rg::Game g(100, 800, 600, 20, 0.01);
	g.StartGame();
	std::cout << g.getScore() << " scores you got.\n";
	system("pause");
	return 0;
}