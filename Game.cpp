#include "Game.hpp"
#include <iostream>
#include <cstring>

namespace rg {
	Game::Game(int outgame_size, int ingame_width, int ingame_height, int snake_size, float game_speed) {
		this->m_outgame_size = outgame_size;
		this->m_ingame_width = ingame_width;
		this->m_ingame_height = ingame_height;
		this->m_snake_size = snake_size;
		this->m_game_speed = game_speed;
		window.create(sf::VideoMode(2 * m_outgame_size + m_ingame_width, 2 * m_outgame_size + m_ingame_height), "Snake Game");
		score = 0;
		Snake* game_snake = new Snake(&m_outgame_size, &m_ingame_width, &m_ingame_height, m_snake_size);
		this->m_game_snake = game_snake;
		this->genFood();
	}

	void Game::drawWall() {
		int col = m_ingame_width / m_snake_size;
		int row = m_ingame_height / m_snake_size;
		/*for (int i = 0; i <= row; i++) {
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(m_outgame_size, m_outgame_size + m_snake_size * i)),
				sf::Vertex(sf::Vector2f(m_outgame_size + m_ingame_width, m_outgame_size + m_snake_size * i))
			};
			window.draw(line, 2, sf::Lines);
		}
		for (int i = 0; i <= col; i++) {
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(m_outgame_size + m_snake_size * i, m_outgame_size)),
				sf::Vertex(sf::Vector2f(m_outgame_size + m_snake_size * i, m_outgame_size + m_ingame_height))
			};
			window.draw(line, 2, sf::Lines);
		}*/
		for (int i : {0, col}) {
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(m_outgame_size + m_snake_size * i, m_outgame_size)),
				sf::Vertex(sf::Vector2f(m_outgame_size + m_snake_size * i, m_outgame_size + m_ingame_height))
			};
			window.draw(line, 2, sf::Lines);
		}
		for (int i : {0, row}) {
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(m_outgame_size, m_outgame_size + m_snake_size * i)),
				sf::Vertex(sf::Vector2f(m_outgame_size + m_ingame_width, m_outgame_size + m_snake_size * i))
			};
			window.draw(line, 2, sf::Lines);
		}
	}

	void Game::StartGame() {
		/*sf::Clock gameClock;
		float elapsedGameTime = 0.0f;
		float timeStep = 0.1f;*/
		m_game_food->draw(window);
		this->drawWall();
		if (m_game_snake->wait_start(window))
			GameLoop();
		else
			this->~Game();
	}

	void Game::GameLoop() {
		sf::Clock gameClock;
		float elapsedGameTime = 0.0f;
		float timeStep = 0.1f;
		sf::Event e;
		while (window.isOpen()) {
			while (window.pollEvent(e)) {
				switch (e.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (e.key.code == sf::Keyboard::P) {//edit later
						if (!pause)
							elapsedGameTime += gameClock.restart().asSeconds();
						pause = !pause;
					}
					break;
				default:
					break;
				}
			}
			if (!pause) {
				m_game_snake->detectWayKeys();

				elapsedGameTime += gameClock.restart().asSeconds();
				if (elapsedGameTime > timeStep)
				{
					elapsedGameTime = (static_cast<int>(elapsedGameTime * 100) % static_cast<int>(timeStep * 100)) / 100.0f;
					if (!m_game_snake->move()) {
						this->GameOver();
						return;
					}
					if (this->isInFood()) {
						this->AteFood();
						timeStep -= m_game_speed;
					}
				}
				window.clear();
				this->drawWall();
				m_game_food->draw(window);
				m_game_snake->draw(window);
				window.display();
			}
			else
				gameClock.restart();
		}
	}

	bool Game::isInFood() {
		return (m_game_snake->getHeadX() == m_game_food->getX() && m_game_snake->getHeadY() == m_game_food->getY());
	}

	void Game::AteFood() {
		score++;
		this->genFood();
		m_game_snake->gainFood();
	}

	void Game::genFood() {
		m_game_food = Food::generateFood(m_outgame_size, m_ingame_width, m_ingame_height, m_snake_size);
		while (m_game_snake->posInBody(m_game_food->getX(), m_game_food->getY()))
			m_game_food = Food::generateFood(m_outgame_size, m_ingame_width, m_ingame_height, m_snake_size);
	}
	
	void Game::GameOver() {
		window.clear();
		m_game_food->draw(window);
		m_game_snake->draw(window);
		window.display();
	}

	int Game::getScore() {
		return this->score;
	}
}