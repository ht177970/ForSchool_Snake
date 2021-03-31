#include <iostream>
#include "Game.hpp"

int main() {
	sf::RenderWindow w;
	rg::Game g(w, { 100, 800, 600, 20 }, 0.001f);
	g.StartGame();
	std::cout << g.getScore() << " scores you got.\n";
	system("pause");
	return 0;
}