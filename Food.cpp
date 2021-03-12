#include "Food.hpp"
#include <random>

namespace rg {
	Food* Food::generateFood(int outgame_size, int game_width, int game_height, int size) {
		std::random_device random;
		std::mt19937 generator(random());
		int x = generator() % (game_width/size);//+1-1¬Û©è
		int y = generator() % (game_height/size);//¦P¤W
		return new Food(outgame_size + x * size, outgame_size + y * size, size);
	}

	Food::Food(int X, int Y, int size) {
		x = X;
		y = Y;
		grap.setPosition(x, y);
		grap.setSize(sf::Vector2f(size, size));
		grap.setFillColor(sf::Color::Yellow);
	}

	int Food::getX() {
		return x;
	}

	int Food::getY() {
		return y;
	}

	void Food::draw(sf::RenderWindow& window) {
		window.draw(grap);
	}

	/*sf::RectangleShape Food::getDrawable() {
		return grap;
	}*/
}