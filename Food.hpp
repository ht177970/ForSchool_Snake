#ifndef SNAKE_RG_FOOD_H_
#define SNAKE_RG_FOOD_H_

#include "Base.hpp"
#include <SFML/Graphics.hpp>

namespace rg {
	class Food : public BaseDrawable {
	private:
		int x, y;
		int outgame_size, game_width, game_height, size;
		sf::RectangleShape grap;
		//Food(int X, int Y, int size);
	public:
		//static Food* generateFood(int outgame_size, int game_width, int game_height, int size);
		Food(int outgame_size, int game_width, int game_height, int size);
		void generateNewPosition();
		int getX();
		int getY();
		//sf::RectangleShape getDrawable();
		void draw(sf::RenderWindow& window) override;
	};
}

#endif 
