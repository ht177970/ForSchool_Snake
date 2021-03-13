#ifndef SNAKE_RG_GAME_H_
#define SNAKE_RG_GAME_H_

#include "Snake.hpp"
#include "Food.hpp"
#include <SFML/Graphics.hpp>

namespace rg {
	class Game {
	private:
		sf::RenderWindow window;
		Snake* m_game_snake;
		Food* m_game_food;
		int m_outgame_size, m_ingame_width, m_ingame_height, m_snake_size;
		int score;
		float m_game_speed;
		bool pause = false;
		void GameOver();
		void GameLoop();
		void drawWall();
		bool isInFood();
		void AteFood();
		void genFood();
	public:
		explicit Game(int outgame_size, int ingame_width, int ingame_height, int snake_size, float game_speed);
		~Game() = default;
		void StartGame();
		int getScore();
	};
}

#endif