#ifndef SNAKE_RG_FOOD_H_
#define SNAKE_RG_FOOD_H_

#include "Base.h"
#include <SFML/Graphics.hpp>

namespace rg {
	class Food : BaseDrawable {
	private:
		int x, y;
		sf::RectangleShape grap;
		Food(int X, int Y, int size);
	public:
		static Food* generateFood(int outgame_size, int game_width, int game_height, int size);
		int getX();
		int getY();
		//sf::RectangleShape getDrawable();
		void draw(sf::RenderWindow& window) override;
	};
}

#endif 
